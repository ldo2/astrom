
module SPH

  class ParticleIndex
    @index_id

    attr_reader :index_id

    def initialize(index_id)
      @index_id = index_id
    end

    def type
      :particle_index
    end
  
    def to_s
      @index_id.to_s(?n - ?i).split('').map { |digit| 
        (?i + digit.to_i).chr 
      }.join
    end

  end

end

