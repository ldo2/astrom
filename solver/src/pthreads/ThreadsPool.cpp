#include "ThreadsPool.hpp"
#include "MutexLock.hpp"

namespace pthreads {

  /*
   * class ThreadsPool {
   */

      ThreadsPool::ThreadsPool(unsigned int threads_count) {
        MutexLock lock(mutex);
        PoolThread *thread;

        while (threads_count-- > 0) {
          thread = new PoolThread(this);

          threads.push_back(thread);
          free_threads.push_back(thread);

          thread->start();
        }
      }

      ThreadsPool::~ThreadsPool() {
        MutexLock lock(mutex);

        std::list<PoolThread *>::iterator it;
        for (it = threads.begin(); it != threads.end(); ++it) {
          // TODO: cancel thread execution and delete it
          // *it->cancel();
          // delete *it;
        }
      }

      void ThreadsPool::run(IRunnable *runnable) {
        MutexLock lock(mutex);

        if (free_threads.empty()) {
          // invoke later
          tasks.push(runnable);
          return;
        }

        PoolThread *thread = free_threads.front();
        free_threads.pop_front();

        thread->runnable = runnable;
        thread->begin_condition.signal();
      } 


  /*
   * class PoolThread
   */

      PoolThread::PoolThread(ThreadsPool *pool) 
       : pool(pool) {}

      PoolThread::~PoolThread() {}

      void PoolThread::run() {
        while(true) {
          if (runnable == NULL) { begin_condition.wait(); }

          runnable->run();

          {
            MutexLock lock(pool->mutex);

            if (pool->tasks.empty()) {
              pool->free_threads.push_back(this);
              runnable = NULL;
            } else {
              runnable = pool->tasks.front();
              pool->tasks.pop();
            }
          }
        }
      }

}

