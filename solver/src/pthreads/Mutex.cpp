#include "Mutex.hpp"

namespace pthreads {

  /*
   * class Mutex {
   */ 
    Mutex::Mutex(MutexType mutex_type) {
      int return_value;

      return_value = pthread_mutexattr_init(&attributes);
      if (return_value != 0) goto mutexattr_init_error;

      return_value = pthread_mutexattr_settype(&attributes, mutex_type);
      if (return_value != 0) goto mutexattr_settype_error;

      return_value = pthread_mutex_init(&mutex, &attributes);
      if (return_value != 0) goto mutex_init_error;

      return;
      /* error handling */
      mutex_init_error:
      mutexattr_settype_error:
        pthread_mutexattr_destroy(&attributes);
      mutexattr_init_error:
        throw MutexException(return_value);
    }

    Mutex::~Mutex() {
      int return_value;

      return_value = pthread_mutexattr_destroy(&attributes);
      // if (return_value != 0) throw MutexException(return_value);

      return_value = pthread_mutex_destroy(&mutex);
      if (return_value != 0) throw MutexException(return_value);
    }

    void Mutex::lock() throw(MutexException) {
      int return_value;

      return_value = pthread_mutex_lock(&mutex);
      if (return_value != 0) throw MutexException(return_value);
    }

    void Mutex::trylock() throw(MutexException) {
      int return_value;

      return_value = pthread_mutex_trylock(&mutex);
      if (return_value != 0) throw MutexException(return_value);
    }

    void Mutex::unlock() throw(MutexException) {
      int return_value;

      return_value = pthread_mutex_unlock(&mutex);
      if (return_value != 0) throw MutexException(return_value);
    }

    pthread_mutex_t *Mutex::getMutex() throw() {
      return &mutex;
    }

}

