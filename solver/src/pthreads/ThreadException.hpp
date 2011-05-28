#ifndef __pthreads_ThreadException_HPP__
#define __pthreads_ThreadException_HPP__

#include <pthreads/Exception.hpp>

namespace pthreads {

  class ThreadException : public Exception {
    public:
      ThreadException(int error_code) : Exception(error_code) {}
      virtual ~ThreadException() throw () {}
  };

}

#endif /* __pthreads_ThreadException_HPP__ */

