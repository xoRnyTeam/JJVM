#pragma once

#include <string>
#include <vector>
#include <stack>
#include <functional>
#include <array>

#include "ClassFile.hpp"
#include "Heap.hpp"
#include "memory.hpp"

namespace vm
{
    
/// @brief 
enum AccessFlags : int16_t {
	ACC_NONE         = 0x0000,
	ACC_PUBLIC       = 0x0001,
	ACC_PRIVATE      = 0x0002,
	ACC_PROTECTED    = 0x0004,
	ACC_STATIC       = 0x0008,
	ACC_FINAL        = 0x0010,
	ACC_SUPER        = 0x0020,
	ACC_SYNCHRONIZED = 0x0020,
	ACC_VOLATILE     = 0x0040,
	ACC_BRIDGE       = 0x0040,
	ACC_TRANSIENT    = 0x0080,
	ACC_VARARGS      = 0x0080,
	ACC_NATIVE       = 0x0100,
	ACC_INTERFACE    = 0x0200,
	ACC_ABSTRACT     = 0x0400,
	ACC_STRICT       = 0x0800,
	ACC_SYNTHETIC    = 0x1000,
	ACC_ANNOTATION   = 0x2000,
	ACC_ENUM         = 0x4000
};

class jjvm final {
    ClassFile         m_class;
    Heap              m_heap;
    std::stack<Frame> m_frames;

    std::array<std::function<void()>, 0xFF> m_handlers;

public:
    /// @brief 
    /// @param class_name 
    /// @param class_path 
    jjvm(const std::string &class_name, const std::vector<std::string> &class_path);

public:
    /// @brief init class
    void execute();

private:
    void methodCall(const std::string &name, const std::string &descriptor, int16_t flags);

    std::shared_ptr<AttributeBase> jjvm::getAttr(std::vector<std::shared_ptr<AttributeBase>> & attrs, AttributeTag tag) const;

    Value resolveConstant(uint16_t id);

    // handlers
    //=--------
    void intiHandlers();

    void opnop();
    void opaconst_null();
    void opiconst_m1();
    void opiconst_0();
    void opiconst_1();
    void opiconst_2();
    void opiconst_3();
    void opiconst_4();
    void opiconst_5();
    void oplconst_0();
    void oplconst_1();
    void opfconst_0();
    void opfconst_1();
    void opfconst_2();
    void opdconst_0();
    void opdconst_1();
    void opbipush();
    void opldc();
    void opiload();
    void oplload();
    void opiload_0();
    void opiload_1();
    void opiload_2();
    void opiload_3();
    void oplload_0();
    void oplload_1();
    void oplload_2();
    void oplload_3();
    void opladd();
    void opldc2_w();
    void opldc_w();
    void opiaload();
    void oplaload();
    void opfaload();
    void opdaload();
    void opistore();
    void oplstore();
    void opistore_0();
    void opistore_1();
    void opistore_2();
    void opistore_3();
    void oplstore_0();
    void oplstore_1();
    void oplstore_2();
    void oplstore_3();
    void opiastore();
    void oplastore();
    void opfastore();
    void opdastore();
    void oppop();
    void oppop2();
    void opdup();
    void opdup2();
    void opdup_x1();
    void opdup_x2();
    void opdup2_x1();
    void opdup2_x2();
    void opswap();
    void opiadd();
    void opfadd();
    void opdadd();
    void opisub();
    void oplsub();
    void opfsub();
    void opdsub();
    void opimul();
    void oplmul();
    void opfmul();
    void opdmul();
    void opidiv();
    void opldiv();
    void opfdiv();
    void opddiv();
    void opirem();
    void oplrem();
    void opfrem();
    void opdrem();
    void opineg();
    void oplneg();
    void opfneg();
    void opdneg();
    void opishl();
    void oplshl();
    void opishr();
    void oplshr();
    void opiushr();
    void oplushr();
    void opiand();
    void opland();
    void opior();
    void oplor();
    void opixor();
    void oplxor();
    void opiinc();
    void opi2l();
    void opi2f();
    void opi2d();
    void opl2i();
    void opl2f();
    void opl2d();
    void opf2i();
    void opf2l();
    void opf2d();
    void opd2i();
    void opd2l();
    void opd2f();
    void oplcmp();
    void opfcmpl();
    void opfcmpg();
    void opdcmpl();
    void opdcmpg();
    void opifne();
    void opifle();
    void opif_icmpne();
    void opif_icmpge();
    void opgoto();
    void opreturn();
    void opireturn();
    void oparraylength();
    void opnewarray();
    void opinvokestatic();
    
    void opgetstatic(); // IGNORED

    // standart functions
    void opinvokevirtual();
    //
    void println(const std::string &descriptor);


}; // class jjvm

} // namespace vm