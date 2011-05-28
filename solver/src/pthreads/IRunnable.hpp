#ifndef __pthreads_IRunnable_HPP__
#define __pthreads_IRunnable_HPP__

namespace pthreads {

  class IRunnable {
    public:
      IRunnable() {}
      virtual ~IRunnable() {}

      virtual void run() = 0;
  };

}

#endif /* __pthreads_IRunnable_HPP__ */

