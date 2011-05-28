#ifndef __PhysicalQuantity_HPP__
#define __PhysicalQuantity_HPP__

class PhysicalQuantity {
  public:
    // характерный линейный размер
    double L;
    // характерная плотность 
    double rho;
    // характерное время
    double t;
    // характерная скорость
    double v;
    // характерная температура
    double T;
    // характерная массовая сила
    double F;
    

    class Constants {
      public:
        // гравитационная постоянная
        static const double G = 6.6742867e-11; // м**3 * кг**(-1) * с**(-2)
    };

    double G() {
      return Constants::G;
    }

};

#endif /* __PhysicalQuantity_HPP__ */

