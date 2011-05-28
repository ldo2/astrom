#ifndef __pthread_ConditionException_HPP__
#define __pthread_ConditionException_HPP__

#include <pthreads/Exception.hpp>

namespace pthreads {

  class ConditionException : public Exception {
    public:
      ConditionException(const char *message) 
       : Exception("ConditionVariable", message) {}
      ConditionException(int error_code) 
       : Exception("ConditionVariable", error_code) {}

      virtual ~ConditionException() throw () {}
  };

}

#endif /* __pthread_ConditionException_HPP__ */
