
module SPH

  class Function
    @type
    @name

    @definition

    attr_reader :type, :name, :definition

    def initialize(type, name, definition = nil)
      @type = type
      @name = name
      @definition = definition
    end

    def to_s
      arguments_types, return_type = @type.first
      "#{@name}: (#{arguments_types.join(', ')}) -> #{return_type}"
    end

  end

end

