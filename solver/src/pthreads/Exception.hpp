#ifndef __pthreads_Exception_HPP__
#define __pthreads_Exception_HPP__

#include <string>
#include <exception>

#include <cstring>

#include <typeinfo>

namespace pthreads {

  class Exception : public std::exception {
    public:
      Exception();
      Exception(const char *message);
      Exception(const char *message, Exception *cause);
      Exception(int error_code);

      Exception(const char *source_class, const char *message);
      Exception(const char *source_class, const char *message, 
                 Exception *cause);
      Exception(const char *source_class, int error_code);

      virtual ~Exception() throw();

      virtual const char *what() const throw();
      virtual Exception &getCause() const throw();
      virtual const std::string &getMessage() const throw();
    protected: 
      std::string message;
      Exception *cause;

      virtual Exception *clone() const;
  };

}

#endif /* __pthreads_Exception_HPP__ */

