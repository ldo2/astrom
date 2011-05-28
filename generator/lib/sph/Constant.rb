
module SPH

  class Constant
    @type
    @name
    @value

    attr_reader :type, :name, :value
    attr_writer :value

    def initialize(type, name, value = nil)
      @type = type
      @name = name
      @value = value

      # puts "create constant <#{name}>"
    end

    def to_s
      @name.to_s
    end
  end

end

