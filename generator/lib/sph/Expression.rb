
module SPH

  class Expression
    @type

    @operator
    @arguments

    attr_reader :type, :operator, :arguments

    def initialize(type, operator, arguments)
      @type = type
      @operator  = operator
      @arguments = arguments
    end

    def to_s
      "#{@operator}(#{@arguments.join(", ")})"
    end
  end

end

