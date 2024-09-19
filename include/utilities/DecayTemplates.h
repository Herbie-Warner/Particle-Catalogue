//DecayTemplates.h
//Declares the decay templates namespace. Declared seperately from the decay utilities namespace to
//avoid circular dependencies with DecayChannels class. Includes two templates: one for generating particle
//pairs (auxiliary to second template), second to add decays given some functions and requirements.
//Herbie Warner 28/04/2024

#ifndef DECAYTEMPLATES_H
#define DECAYTEMPLATES_H

#include<vector>
#include<memory>

#include"utilities/DecayChannels.h"
#include"utilities/DecayUtilities.h"

namespace DecayTemplates
{
  //get_conjugate_particle_func generates the compliment particle to another particle and is changed
  //upon need. E.g in w+- decay one will want to given an electron and this function to generate
  //an anti electron neutrino. But in z decay this function can be used to generate an up and
  //an antiup by using an anti particle function.
  template<typename particle_type, typename get_conjugate_particle_func>
  std::vector<std::pair<particle_type, particle_type>> generate_particle_pairs(
      const std::vector<particle_type>& particles,
      get_conjugate_particle_func get_conjugate_particle);

  //The particle type is commonly an enum type: either LeptonType, or QuarkFlavour. The factory func tells
  //the lambda decay within the DecayChannelsVector how to create the objects and the branching func how to
  //compute the branching ratio for this particular mode. This sometimes is independent of the particle type,
  //but is necessary for cabibo mixing. decay_channels is that which will have the decay appended to.
  template<typename particle_type, typename get_conjugate_particle_func, typename factory_func, typename branching_func>
  void add_decay_channels_for_particle_pairs(const std::vector<particle_type>& particle_types,
                                             get_conjugate_particle_func get_conjugate_particle,
                                             factory_func factory_function,
                                             branching_func branching_function,
                                             std::shared_ptr<DecayChannelsVector>& decay_channels);
}

#include"utilities/DecayTemplates.tpp" //Include template implementation

#endif