//ParticleContainer.tpp
//Defines the templaes for the recursion method to get both specific and general particle types,
//and the variadic template for adding particles of different arguments.
//Herbie Warner 05/05/2024

template<typename ParticleType, typename... Args>
void ParticleContainer::add_particle(Args&&... args)
{
  //To be able add a particle with some unique properties
  auto particle = std::make_shared<ParticleType>(std::forward<Args>(args)...);
  particle_map[particle->get_general_type()].push_back(particle);
}

template<typename Func>
void ParticleContainer::process_particles_of_type(ParticleUtilities::ParticleIdentifier identity, Func func) const 
{
  //Various optimisations here allow for 0(n) complexity where n is the number of unique particle identifiers. This function is templated
  //as it is the same procedure to iterate through the map for several functionalities. E.g the func might correspond to getting the size
  //of a particular type like fermion, or it mighgt be to get a subcontainer of all the gauge bosons.

  //Use unordered_set to track which particle types have been processed already to avoid infinite recursion
  std::unordered_set<ParticleUtilities::ParticleIdentifier> processed_types;

  //Define as std::function to allow recursion
  std::function<void(const ParticleUtilities::ParticleIdentifier&)> collect_objects = [&](const ParticleUtilities::ParticleIdentifier& type_index) 
  {
    //Check if this type has already been processed
    if(processed_types.find(type_index) != processed_types.end()) 
    {
      return; //End of this tree
    }
    processed_types.insert(type_index);

    if(auto it = particle_map.find(type_index); it != particle_map.end()) 
    {
      //Perform the func with this identifier and this element of the map
      func(type_index, it->second);
    }

    //Check if the current particle type has any derived types
    if(auto it = inheritance_map.find(type_index); it != inheritance_map.end()) 
    {
      for(const auto& derived_type : it->second) 
      {
        collect_objects(derived_type);
      }
    }
  };

  collect_objects(identity); //Begin the recursion
}