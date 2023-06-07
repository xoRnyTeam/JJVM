 
#ifndef JJVM_CLASSSPACE_H
#define JJVM_CLASSSPACE_H

#include <algorithm>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ClassFile.hpp"

using namespace std;

class Interpreter;
class JavaClass;
class GC;

//--------------------------------------------------------------------------------
// Class space has responsible to manage all JavaClass objects. A complete
// lifecycle of java class consists of loading class into jvm, linking those
// loaded JavaClass which would initialize its static fields and finally
// initializing them. findJavaClass() used to check if there is a specific
// JavaClass existed in global class table.
//--------------------------------------------------------------------------------
class ClassSpace {
    friend class GC;

public:
    ClassSpace(const string& path);
    ~ClassSpace();

    JavaClass* findJavaClass(const string& jcName);
    bool loadJavaClass(const string& jcName);
    bool removeJavaClass(const string& jcName);
    void linkJavaClass(const string& jcName);
    void initJavaClass(Interpreter& exec, const string& jcName);

public:
    JavaClass* loadClassIfAbsent(const string& jcName);
    void linkClassIfAbsent(const string& jcName);
    void initClassIfAbsent(Interpreter& exec, const string& jcName);

private:
    const string parseNameToPath(const string& name);

private:
    recursive_mutex maMutex;

    unordered_set<string> linkedClasses;
    unordered_set<string> initedClasses;
    unordered_map<string, JavaClass*> classTable;

    vector<string> searchPaths;
};

#endif  // JJVM_CLASSSPACE_H
