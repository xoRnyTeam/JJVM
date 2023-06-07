 
#ifndef JJVM_JJVM_H
#define JJVM_JJVM_H

#ifndef PEREYEB_OFF
// #include "../gc/Concurrent.hpp"
#endif

#include "Interpreter.hpp"
#include "RuntimeEnv.hpp"

extern RuntimeEnv runtime;

struct JJVM {
    explicit JJVM();

    static void callMain(const std::string& name);
    static void initialize(const std::string& libPath);

#ifdef PEREYEB_OFF
    class ExecutorThreadPool : public ThreadPool {
    public:
        ExecutorThreadPool() : ThreadPool() {}
        void createThread() {
            threads.emplace_back(&ThreadPool::runPendingWork, this);
        }
        size_t getThreadNum() const { return threads.size(); }
        void storeTaskFuture(shared_future<void> taskFuture) {
            taskFutures.push_back(taskFuture);
        }
        vector<shared_future<void>> getTaskFutures() const {
            return taskFutures;
        }

    private:
        vector<shared_future<void>> taskFutures;
    };
    static ExecutorThreadPool executor;
#endif
};

#endif  // JJVM_JJVM_H
