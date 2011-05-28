
module SPH

  class IntegrationVariable
    @type

    attr_reader :type

    def initialize(type)
      @type = type
    end

    def to_s
      "#{@type}::_"
    end
  end

end

