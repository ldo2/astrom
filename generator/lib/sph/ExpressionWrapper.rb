require 'sph/Field'
require 'sph/Constant'
require 'sph/Expression'
require 'sph/CaseExpression'
require 'sph/IntegrationVariable'

require 'sph/UndefinedOperatorException'

module SPH

  module ExpressionWrapper
    @@known_operators = {}
    @@types = [:scalar, :vector, :time, :equation, :bool, :particle_index]

    RUBY_OPERATORS = [:+, :-, :*, :/, :-@, :**, :==, :<, :>, :<=, :>=, :[]]

    AUXILIARY_CLASSES = [ Field, Constant, IntegrationVariable, 
                          Expression, CaseExpression ]

    def register_operator(operator, type)
      arguments_types, return_type = type.first

       puts "register operator #{operator}(#{arguments_types.join(', ')}) in #{self}"
      @@known_operators[operator] ||= {}
      @@known_operators[operator][arguments_types] = return_type

      operator_handler = Proc.new do |*args|
        # puts "call operator #{operator} for #{args.inspect}"
        args_types  = args.map {|arg| ExpressionWrapper::type_of(arg) }
        result_type = @@known_operators[operator][args_types]

        raise UndefinedOperatorException.new(operator, args) if result_type.nil?

        Expression.new(result_type, operator, args)
      end

      if RUBY_OPERATORS.include?(operator)
        AUXILIARY_CLASSES.each do |aux_class|
          aux_class.class_eval do
            define_method(operator) do |*args|
              operator_handler.call(*args.unshift(self))
            end
          end
        end
      else
        self.class_eval do
          define_method(operator, operator_handler)
        end 
      end

      true
    end

    def register_template_operator(operator, arity = nil, &template)
      arity ||= template.arity

      if arity <= 0
        register_operator(operator, template.call)
      else
        @@types.each do |type|
          register_template_operator(operator, arity - 1) do |*instance_types|
            template.call(*([type] + instance_types))
          end
        end
      end

      true
    end

    def validate_type(type)
      unless @@types.include?(type)
        raise "unknown type <#{type}>"
      end
    end

    def self.type_of(object)
      if object.is_a?(Numeric) 
        return :scalar
      elsif object.is_a?(TrueClass) || object.is_a?(FalseClass)
        :bool
      else 
        object.type
      end
    end

  end

end

