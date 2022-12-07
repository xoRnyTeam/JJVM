#include <jjvm.hpp>

#include <fstream>
#include <iostream>

namespace vm
{

jjvm::jjvm(const std::string &class_name, const std::vector< std::string > &class_path) {
    std::ifstream fIn;
    std::string finded_name;
    for(const auto& path: class_path) {
        finded_name = path + '/' + class_name;
        fIn.open(finded_name);
        if(fIn.is_open()) {
            break;
        }
    }
    
    if(!fIn.is_open()) {
        throw std::runtime_error("Cant find class '" + class_name + "'");
    }
    fIn.close();
    m_class = ClassFile::create(finded_name);

    if(!m_class.isTopClass()) {
        throw std::runtime_error("Top class isn't implemented!");
    }
    
    intiHandlers();
}

void jjvm::execute() {
    // init class file
    //=---------------
    auto&& init_method = m_class.getMethod("<clinit>", "()V");
    if(init_method.second) {
        methodCall("<clinit>", "()V", ACC_STATIC | ACC_NONE);
    }
    // TODO: call 'init' for super class

    // call main
    //=---------
    // TODO: place argv to frame
    methodCall("main", "([Ljava/lang/String;)V", ACC_PUBLIC | ACC_STATIC);
}

void jjvm::methodCall(const std::string &name, const std::string &descriptor, int16_t flags) {
    std::pair<Method, bool> hasMethod = m_class.getMethod(name, descriptor);
    if(!hasMethod.second) {
        std::runtime_error("Unknown method '" + name + "'");
    }

    Method method = hasMethod.first;
    
    // check access flags
    //=------------------
    if ((flags != ACC_NONE) && !(method.access_flags & flags))
		throw std::runtime_error("Bad flags!");

    auto&& codeAttr = std::static_pointer_cast<Code_attribute>(getAttr(method.attributes, AttributeTag::Code));
    if(codeAttr == nullptr) {
		throw std::runtime_error("Could not find code for method '" + name + "'");
    }

    Frame methodFrame(codeAttr->max_locals, codeAttr->max_stack);

    // load args
    //=---------
    if(!m_frames.empty()) {
        // pars descriptor
        //=---------------
        uint16_t localCounter = 0;
        for(size_t i = 0; i < descriptor.size() && descriptor[i] != ')'; ++i) {
            Value v = m_frames.top().stackTop();
            m_frames.top().stackPop();

            methodFrame.lockalStore(localCounter++, v);
            i += 1;
            switch(static_cast<Field::FieldType>(descriptor[i])) {
                case Field::FieldType::REFERENCE:
                    i = descriptor.find(';', i);
                    if (i != std::string::npos) {
                        i ++;
                    }
                    break;
                case Field::FieldType::ARRAY:
                    i = descriptor.find_first_not_of(static_cast<char>(Field::FieldType::ARRAY), i);
                    if (i != std::string::npos && descriptor[i] == 'L') {
                        i = descriptor.find(';', i);
                        if(i != std::string::npos) {
                            i += 1;
                        }
                    } 
                    else {
                        i += 1;
                    }
                    break;
                case Field::FieldType::DOUBLE:
                case Field::FieldType::LONG:
                    methodFrame.lockalStore(localCounter++, v);
                default:
                    i++;
                    break;
            }
        } // pars descriptor
    } // load args

    // push new frame
    //=--------------
    m_frames.push(methodFrame);

    // loop over instractions
    //=----------------------
    auto&& code = codeAttr->code;
    size_t len = code.size();
    while(m_frames.top().pc < len) {
        // go to instraction handler
        m_handlers[code[m_frames.top().pc++]]();
    }

    m_frames.pop();
}



std::shared_ptr<AttributeBase> jjvm::getAttr(std::vector<std::shared_ptr<AttributeBase>> & attrs, AttributeTag tag) const {
    std::shared_ptr<AttributeBase> res = nullptr;
    for(auto&& attr: attrs) {
        if(attr->getTag() == tag) {
            res = attr;
            break;
        }
    }
    return res;
}

Value jjvm::resolveConstant(uint16_t id) {
    Value v;
	v.i = 0;
	switch (m_class.cp[id]->getTag()) {
	case ConstantTag::CONSTANT_Integer:
		v.i = m_class.getInteger(id);
		break;
	case ConstantTag::CONSTANT_Float:
		v.f = m_class.getFloat(id);
		break;
	case ConstantTag::CONSTANT_Long:
		v.l = m_class.getLong(id);
		break;
	case ConstantTag::CONSTANT_Double:
		v.d = m_class.getDouble(id);
		break;
	case ConstantTag::CONSTANT_String: {
        // TODO immediately upload to heap when parsing
        throw std::runtime_error("Don't implemented!");
    }
    }
	return v;
}

} // namespace vm