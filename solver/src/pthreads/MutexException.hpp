#ifndef __pthread_MutexException_HPP__
#define __pthread_MutexException_HPP__

#include <pthreads/Exception.hpp>

namespace pthreads {

  class MutexException : public Exception {
    public:
      MutexException(const char *message) : Exception("Mutex", message) {}
      MutexException(int error_code) : Exception("Mutex", error_code) {}

      virtual ~MutexException() throw () {}
  };

}

#endif /* __pthread_MutexException_HPP__ */

