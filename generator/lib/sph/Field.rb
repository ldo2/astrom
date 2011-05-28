module SPH

  class Field
    @type
    @name

    attr_reader :type, :name

    def initialize(type, name)
      @type = type
      @name = name

      # puts "create field <#{name}>"
    end

    def ==(field)
      puts "biuld equation for #{self} and #{field}"
    end

    def to_s
      @name.to_s
    end
  end

end

