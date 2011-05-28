#ifndef __pthreads_ThreadsPool_HPP__
#define __pthreads_ThreadsPool_HPP__

#include <list>
#include <queue>

#include <pthreads/IRunnable.hpp>
#include <pthreads/Thread.hpp>
#include <pthreads/Mutex.hpp>
#include <pthreads/ConditionVariable.hpp>

namespace pthreads {

  class ThreadsPool;
  class PoolThread;

  class ThreadsPool {
    protected:
      std::list<PoolThread *> threads;
      std::list<PoolThread *> free_threads;
      std::queue<IRunnable *> tasks;

      Mutex mutex;

    public:
      ThreadsPool(unsigned int threads_count);
      ~ThreadsPool();

      virtual void run(IRunnable *runnable);

    friend class PoolThread;
  };

  class PoolThread : public Thread {
    protected:
      ThreadsPool *pool;
      ConditionVariable begin_condition;

    public:
      PoolThread(ThreadsPool *pool);
      virtual ~PoolThread();

      virtual void run();

    friend class ThreadsPool;
  };

}

#endif /* __pthreads_ThreadsPool_HPP__ */

