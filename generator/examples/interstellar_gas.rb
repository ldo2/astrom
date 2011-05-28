require 'sph'

#
# Пример записи системы уравнений
#

InterstellarGas = SPH::continua do
  field :time,   :time,            :as => :t

  field :vector, :position,        :as => :r
  field :vector, :velocity,        :as => :v

  field :scalar, :density,         :as => :rho
  field :scalar, :pressure,        :as => :p
  field :scalar, :internal_energy, :as => :e
  
  constant :scalar, :gravitational_constant, :as => :g,     :value => 6.67428e-11
  constant :scalar, :adiabatic_index,        :as => :gamma, :value => (5.0/3.0)

  # пример записи некоторой заданной функции
  function :state_function, [:scalar, :scalar] => :scalar do |a, b|
    (gamma - 1) * a * b
  end

  # пример сложной функции
  #artificial_viscosity = case_expression(
  #  div(v) <  0  =>  rho * div(v)**2, 
  #  div(v) >= 0  =>  0
  #)

  equation derivative(rho, t) == - rho * div(v) 
  equation derivative(r, t)   == v
  equation derivative(v, t)   == - grad(p)/rho  + 
    integral { |xi| g * rho * (xi - r) / length(xi - r)**3 }
  equation p == (gamma - 1) * rho * e
end

#
# Пример записи аппроксимации по частицам системы уравнений
#(должен автоматически генерироваться по системе уравнений 
# приведенной выше)
#

InterstellarGasSph = SPH::continua do
  field :time,   :time,            :as => :t

  field :scalar, :mass,            :as => :m

  field :vector, :position,        :as => :r
  field :vector, :velocity,        :as => :v

  field :scalar, :density,         :as => :rho
  field :scalar, :pressure,        :as => :p
  field :scalar, :internal_energy, :as => :e
  
  constant :scalar, :gravitational_constant, :as => :g,     :value => 6.67428e-11
  constant :scalar, :adiabatic_index,        :as => :gamma, :value => (5.0/3.0)

  constant :scalar, :smooth_length,          :as => :h

  particle do |i|
    equation derivative(rho[i], t) == particle_sum { |j| 
      - rho[i] * m[j]/rho[j] * dot(v[j], grad(kernel(r[i] - r[j], h))) 
    }

    equation derivative(r[i], t) == v[i]

    equation derivative(v[i], t) == particle_sum { |j| 
      - m[j] * (p[i] + p[j])/(rho[i] * rho[j]) * grad(kernel(r[i] - r[j], h))
    } + particle_sum { |j| 
      g * rho[j] * (r[j] - r[i]) / length(r[j] - r[i])**3 
    }

    equation p[i] == (gamma - 1 )* rho[i] * e[i]
  end
end

