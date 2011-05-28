#ifndef __pthreads_Mutex_HPP__
#define __pthreads_Mutex_HPP__

#include <pthread.h>
#include <pthreads/MutexException.hpp>

namespace pthreads {
  
  enum MutexType {
    NORMAL     = PTHREAD_MUTEX_TIMED_NP,
    FAST       = PTHREAD_MUTEX_FAST_NP,
    RECURSIVE  = PTHREAD_MUTEX_RECURSIVE_NP,
    ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
    ADAPTIVE   = PTHREAD_MUTEX_ADAPTIVE_NP
  };

  class Mutex {
    public:
      Mutex(MutexType mutex_type = (MutexType) PTHREAD_MUTEX_DEFAULT);
      virtual ~Mutex();

      void lock() throw(MutexException);
      void trylock() throw(MutexException);
      void unlock() throw(MutexException);

      pthread_mutex_t *getMutex() throw();
    protected:
      pthread_mutex_t mutex;
      pthread_mutexattr_t attributes;
  };

}

#endif /* __pthreads_Mutex_HPP__ */

