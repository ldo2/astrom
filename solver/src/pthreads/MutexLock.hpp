#ifndef __pthreads_MutexLock_HPP__
#define __pthreads_MutexLock_HPP__

#include <pthreads/Mutex.hpp>

namespace pthreads {

  class MutexLock {
    public:
      MutexLock(Mutex &mutex) : mutex(mutex) {
        mutex.lock();
      }

      virtual ~MutexLock() {
        mutex.unlock();
      }

    protected:
      Mutex &mutex;
  };

}

#endif /* __pthreads_MutexLock_HPP__ */

