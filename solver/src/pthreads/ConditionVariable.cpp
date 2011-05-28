#include "ConditionVariable.hpp"

#include "MutexLock.hpp"

#include <ctime>
#include <sys/time.h>

namespace pthreads {
  
  /*
   * class ConditionVariable 
   */

    ConditionVariable::ConditionVariable() {
      int return_value;

      return_value = pthread_cond_init(&condition, NULL);
      if (return_value != 0) throw ConditionException(return_value);
    }

    ConditionVariable::~ConditionVariable() {
      int return_value;

      return_value = pthread_cond_destroy(&condition);
      if (return_value != 0) throw ConditionException(return_value);
    }

    void ConditionVariable::signal() {
      MutexLock lock(mutex);

      pthread_cond_signal(&condition);
    }

    void ConditionVariable::broadcast() {
      MutexLock lock(mutex);

      pthread_cond_broadcast(&condition);
    }

    void ConditionVariable::wait() {
      MutexLock lock(mutex);

      pthread_cond_wait(&condition, mutex.getMutex());
    }

    void ConditionVariable::wait(long seconds, long nanoseconds) {
      struct timespec timeout;
      struct timeval now;

      gettimeofday(&now, NULL);

      timeout.tv_sec  = now.tv_sec + seconds;
      timeout.tv_nsec = now.tv_usec*1000 + nanoseconds;
      
      MutexLock lock(mutex);

      pthread_cond_timedwait(&condition, mutex.getMutex(), &timeout);
    }



}

