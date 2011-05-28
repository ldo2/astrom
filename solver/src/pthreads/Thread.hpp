#ifndef __pthreads_Thread_HPP__
#define __pthreads_Thread_HPP__

#include <pthread.h>

#include <pthreads/IRunnable.hpp>
#include <pthreads/ThreadException.hpp>

namespace pthreads {

  class Thread {
    protected:
      pthread_t thread;
      pthread_attr_t attributes;

      IRunnable *runnable;

    public:
      Thread(IRunnable *runnable = NULL) throw(ThreadException);
      virtual ~Thread();

      virtual void run();

      void start() throw(ThreadException);
      void join() throw(ThreadException);

      static void exit();
  };

}

#endif /* __pthreads_Thread_HPP__ */

