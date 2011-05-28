#include "Exception.hpp"

namespace pthreads {

  /*
   * class Exception
   */

    Exception::Exception() 
     : message(), cause(NULL) {}

    Exception::Exception(const char *message) 
     : message(message), cause(NULL) {}

    Exception::Exception(const char *message, Exception *cause) 
     : message(message), cause(cause->clone()) {}

    Exception::Exception(int error_code) {
      char error_message[256];
      message = strerror_r(error_code, error_message, 256);
    }

    Exception::Exception(const char *source_class, const char *message) 
     : message(), cause(NULL) {
        this->message = source_class;
        this->message += " : ";
        this->message += message;
    }

    Exception::Exception(const char *source_class, const char *message, 
                          Exception *cause)
     : message(), cause(cause->clone()) {
        this->message = source_class;
        this->message += " : ";
        this->message += message;
    }

    Exception::Exception(const char *source_class, int error_code) 
     : message(), cause(NULL) {
        this->message = source_class;
        this->message += " : ";

        char error_message[256];
        this->message += strerror_r(error_code, error_message, 256);
    }

    Exception::~Exception() throw() {
      if (cause != NULL) delete cause;
    }

    Exception *Exception::clone() const {
      return new Exception(*this);
    }

    const char *Exception::what() const throw() {
      return message.c_str();
    }

    Exception &Exception::getCause() const throw() {
      return *cause;
    }

    const std::string &Exception::getMessage() const throw() {
      return message;
    }

}


