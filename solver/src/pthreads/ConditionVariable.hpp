#ifndef __pthreads_ConditionVariable_HPP__
#define __pthreads_ConditionVariable_HPP__

#include <pthread.h>

#include <pthreads/Mutex.hpp>
#include <pthreads/ConditionException.hpp>

namespace pthreads {
  
  class ConditionVariable {
    public:
      ConditionVariable();
      virtual ~ConditionVariable();

      void signal();
      void broadcast();
      void wait();
      void wait(long seconds, long nanoseconds);

    protected:
      Mutex mutex;
      pthread_cond_t condition;
  };

}

#endif /* __pthreads_ConditionVariable_HPP__ */

