#ifndef __RandomGenerator_HPP__
#define __RandomGenerator_HPP__

class RandomGenerator {
  protected:
    unsigned long a, c;
    unsigned long state;

  public:
    RandomGenerator();
    ~RandomGenerator();

    double rand();
    double rand(double range_max);
    double rand(double range_min, double range_max);
    
    double normal(double m = 0.0, double sigma = 1.0);
};

#endif /* __RandomGenerator_HPP__ */

