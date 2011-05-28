#include "Thread.hpp"

#include <iostream>

namespace pthreads {

  static void *_dispatch_thread(void *arg);

  /*
   * class Thread {
   */ 
      pthread_t thread;
      pthread_attr_t attributes;

      IRunnable *runnable;

    Thread::Thread(IRunnable *runnable) throw(ThreadException) 
     : runnable(runnable) {
      int return_value;

      return_value = pthread_attr_init(&attributes);
      if (return_value != 0) throw ThreadException(return_value);
    }

    Thread::~Thread() {
/*
      int return_value;

      return_value = pthread_attr_destroy(&attributes);
      if (return_value != 0) throw ThreadException(return_value);
 */
    }

    void Thread::run() {
      if (runnable) {
        runnable->run();
      }
    }

    void Thread::start() throw(ThreadException) {
      int return_value;

      return_value = pthread_create(&thread, &attributes, &_dispatch_thread, this);
      if (return_value != 0) throw ThreadException(return_value);
    }

    void Thread::join()throw(ThreadException) {
      int return_value;
      void *thread_return;

      return_value = pthread_join(thread, &thread_return);
      if (return_value != 0) throw ThreadException(return_value);
    }

    void Thread::exit() {
      pthread_exit(NULL);
    }

    static void *_dispatch_thread(void *arg) {
      Thread *thread = reinterpret_cast<Thread *>(arg);

      thread->run();

      return NULL;
    }

}


