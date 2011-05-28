require 'sph/Continua'

module SPH

  def continua(&definition)
    continua_object = Continua.new
    continua_object.instance_eval(&definition)
    return continua_object
  end

  class << self
    include SPH 
  end

end

