
module SPH

  class CaseExpression
    @type
    @branches

    def initialize(branches)
      validate_branches(branches)

      @branches = branches
      @type = ExpressionWrapper::type_of(branches.first.last)
    end

    def to_s
      "{#{
        @branches.to_a.map{ |branch_pair| 
            branch_pair.reverse.join(' if ') 
        }.join('; ')
      }}"
    end

    private
    
    def validate_branches(branches)
      type = nil
      branches.each do |condition, expression|
        if ExpressionWrapper::type_of(condition) != :bool
          raise "invalid case expression: condition #{condition} "\
                "has type #{condition.type} but expected type is bool"
        end
        if (!type.nil? && ExpressionWrapper::type_of(expression) != type)
          raise "invalid case expression: branches has different type"
        end
        type = ExpressionWrapper::type_of(expression)
      end
    end
  end

end

