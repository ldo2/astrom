require 'sph/Field'
require 'sph/Constant'
require 'sph/IntegrationVariable'
require 'sph/Expression'
require 'sph/Function'
require 'sph/CaseExpression'
require 'sph/ParticleIndex'
require 'sph/ExpressionWrapper'

module SPH

  class Continua
    class << self
      include ExpressionWrapper
    end

    # дифференциальные операторы
    register_operator :grad,    [:scalar] => :vector
    register_operator :div,     [:vector] => :scalar
    register_operator :rot,     [:vector] => :vector
    register_operator :laplace, [:scalar] => :scalar

    register_operator :derivative, [:scalar, :time] => :scalar
    register_operator :derivative, [:vector, :time] => :vector

    # скалярная арифметика
    register_operator :+, [:scalar, :scalar] => :scalar
    register_operator :-, [:scalar, :scalar] => :scalar
    register_operator :*, [:scalar, :scalar] => :scalar
    register_operator :/, [:scalar, :scalar] => :scalar
    register_operator :**, [:scalar, :scalar] => :scalar
    register_operator :-@, [:scalar] => :scalar

    # векторная арифметика
    register_operator :+, [:vector, :vector] => :vector
    register_operator :-, [:vector, :vector] => :vector

    register_operator :-@, [:vector] => :vector

    register_operator :*, [:scalar, :vector] => :vector
    register_operator :*, [:vector, :scalar] => :vector
    register_operator :/, [:vector, :scalar] => :vector

    register_operator :dot,    [:vector, :vector] => :scalar
    register_operator :cross,  [:vector, :vector] => :vector
    register_operator :length, [:vector] => :scalar

    # равенство (создание уравнения)
    register_template_operator :== do |type|
      { [type, type] => :equation }
    end

    # операторы сравнения
    register_operator :<, [:scalar, :scalar] => :bool
    register_operator :>, [:scalar, :scalar] => :bool
    register_operator :<=, [:scalar, :scalar] => :bool
    register_operator :>=, [:scalar, :scalar] => :bool

    # операторы аппроксимации по частицам
    register_operator :[], [:scalar, :particle_index] => :scalar
    register_operator :[], [:vector, :particle_index] => :vector

    # оператор сглаживающего ядра
    register_operator :kernel, [:vector, :scalar] => :scalar
    
    # 
    # Continua implementation
    # 

    @fields
    @constants
    @functions

    @equations

    @index_depth

    def initialize
      @fields    = []
      @constants = []
      @functions = []
      @equations = []
      @index_depth = 0
    end

    def field(type, name, parameters = {})
      self.class.validate_type(type)

      field = Field.new(type, name)
      @fields << field

      eigenclass.class_eval do
        # puts "generate accessors for <#{name}>"
        define_method(name) do
          # puts "access field #{name}"
          field
        end
        define_method(parameters[:as]) do
          # puts "access field #{name} as #{parameters[:as]}"
          field
        end if parameters[:as]
      end

      field
    end

    def constant(type, name, parameters = {})
      self.class.validate_type(type)

      constant = Constant.new(type, name)
      @constants << constant

      constant.value = parameters[:value] if parameters[:value]

      eigenclass.class_eval do
        # puts "generate accessors for <#{name}>"
        define_method(name) do
          # puts "access field #{name}"
          constant
        end
        define_method(parameters[:as]) do
          # puts "access field #{name} as #{parameters[:as]}"
          constant
        end if parameters[:as]
      end

      constant
    end

    def function(name, type, &definition)
      self.class.register_operator(name, type)

      func = Function.new(type, name, definition)
      @functions << func

      func
    end 

    def equation(definition)
      @equations << definition
      puts definition
    end

    def integral(&func)
      integration_variable = IntegrationVariable.new(:vector)
      integrand = func.call(integration_variable)
      Expression.new(integrand.type, :integral, 
                      [integrand, integration_variable])
    end

    def case_expression(hash)
      CaseExpression.new(hash)
    end

    def particle_sum(&expression)
      invoke_with_index &expression
    end

    def particle(&block)
      invoke_with_index &block
    end

    protected

    def eigenclass
      class << self
        self
      end
    end

    def invoke_with_index(&block)
      index = ParticleIndex.new(@index_depth)

      @index_depth += 1

      result = block.call(index)

      @index_depth -= 1
      
      result
    end

  end

end

