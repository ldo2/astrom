
module SPH

  class UndefinedOperatorException < Exception
    @operator
    @arguments

    def initialize(operator, arguments)
      @operator  = operator
      @arguments = arguments
    end

    def message
      args_str = @arguments.map { |arg| "#{arg.type}::#{arg}" }.join(', ')
      puts "undefined operator <#{@operator}> for arguments (#{args_str})"
    end
  end

end

