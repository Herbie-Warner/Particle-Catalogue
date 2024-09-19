//DecayTemplates.tpp
//Defines the templaes for generating anti particles, and adding decay channels to a vector.
//Herbie Warner 09/05/2024

namespace DecayTemplates
{
  template<typename particle_type, typename get_conjugate_particle_func>
  auto generate_particle_pairs(const std::vector<particle_type>& particles,
  get_conjugate_particle_func get_conjugate_particle) -> std::vector<std::pair<particle_type, particle_type>>
  {
    //Check the return type to inforce compatibility. This is as in certain cases, e.g Z decays, for
    //every lepton there is only one conjugate particle e.g e- and e+. However, for hadronic w decays
    //due to Cabibo mixing, each particle has three conjugate particles. For instance Anti-Up in W- pairs
    //to d s and b, and so the template needs to correctly handle this as well. This method allows the
    //get_conjugate_particle_func to return one a single particle_type or a vector of particle_type.

    using return_type = std::invoke_result_t<get_conjugate_particle_func, particle_type>;
    using is_same = std::is_same<return_type, std::vector<particle_type>>;
    
    std::vector<std::pair<particle_type, particle_type>> particle_pairs;

    if constexpr(is_same::value) 
    {
      //If get_conjugate_particle returns a std::vector<particle_type>
      for (const auto& particle : particles) 
      {
        auto anti_particles = get_conjugate_particle(particle);
        for (const auto& anti_particle : anti_particles) 
        {
          particle_pairs.emplace_back(particle, anti_particle);
        }
      }
    } 
    else 
    {
      //If get_conjugate_particle returns a single particle_type
      for (const auto& particle : particles) 
        {
          particle_type anti_particle = get_conjugate_particle(particle);
          particle_pairs.emplace_back(particle, anti_particle);
        }
    }

    return particle_pairs;
  }

  template<typename particle_type, typename get_conjugate_particle_func, typename factory_func, typename branching_func>
  void add_decay_channels_for_particle_pairs(const std::vector<particle_type>& particle_types,
                                             get_conjugate_particle_func get_conjugate_particle,
                                             factory_func factory_function,
                                             branching_func branching_function,
                                             std::shared_ptr<DecayChannelsVector>& decay_channels)
  {
    //Get vector of all the pairs (std::vector<std::pair<particle_type, particly_type>)
    auto particle_pairs = generate_particle_pairs(particle_types, get_conjugate_particle);
    for (const auto& pair : particle_pairs)
    {
      decay_channels->push_back(DecayUtilities::DecayChannel(       
        [pair, factory_function]() -> std::vector<std::unique_ptr<Particle>>
        {
            std::vector<std::unique_ptr<Particle>> particles;
            particles.push_back(factory_function(pair.first));
            particles.push_back(factory_function(pair.second));
            return particles;
        },
        branching_function(pair.first, pair.second)
       ));
     }
  }

}