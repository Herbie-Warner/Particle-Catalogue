//ParticleContainer.h
//Declares the particle container class. Uses an unorder map of shared pointers to particle objects using
//ParticleIdentifier from ParticleUtilities as the key. Uses a secondary map, inheritance map, to hold
//information of where each class derives, so that a user may be able to search for all fermoins, as well
//as unique types such as an Up quark. This is done using recursion in a template implemented outside
//of this .h for cleanliness in: 'include/core/ParticleContainer.tpp'.
//Herbie Warner 05/05/2024

#ifndef PARTICLECONTAINER_H
#define PARTICLECONTAINER_H

#include<unordered_map>
#include<vector>
#include<memory>
#include<unordered_set>

#include"utilities/ParticleUtilities.h"
#include"core/FourVector.h"
#include"core/Particle.h"

class ParticleContainer
{
private:
  static std::unordered_map<ParticleUtilities::ParticleIdentifier, std::unordered_set<ParticleUtilities::ParticleIdentifier>> inheritance_map; //Static as to be shared by all instances
  std::unordered_map<ParticleUtilities::ParticleIdentifier, std::vector<std::shared_ptr<Particle>>> particle_map;

  //These functions are private as user should not be able to interact with them as they are utility
  static void register_inheritance(ParticleUtilities::ParticleIdentifier base, ParticleUtilities::ParticleIdentifier derived);

  //Implemented in 'include/core/ParticleContainer.tpp': utility function for recursion across particle types
  template<typename Func>
  void process_particles_of_type(ParticleUtilities::ParticleIdentifier identity, Func func) const;

public:
  ParticleContainer() = default;
  ~ParticleContainer() = default;

  ParticleContainer(const ParticleContainer& other);
  ParticleContainer& operator=(const ParticleContainer& other);
  ParticleContainer(ParticleContainer&& other) noexcept;
  ParticleContainer& operator=(ParticleContainer&& other) noexcept;

  FourVector get_total_momentum() const;
  size_t size() const;
  size_t size(ParticleUtilities::ParticleIdentifier identity) const;
  void print_all() const;
  void print_all(ParticleUtilities::ParticleIdentifier identity) const;

  void add_object(std::shared_ptr<Particle> obj); //Add using a shared ptr directly

  std::vector<std::shared_ptr<Particle>> get_particles_of_type(ParticleUtilities::ParticleIdentifier identity) const;
  ParticleContainer get_subcontainer_of_type(ParticleUtilities::ParticleIdentifier identity) const;

  //Vadiadic template. Example usage shown in 'src/main/ParticleCatalogue.cpp'. Implemented in 'include/core/ParticleContainer.tpp'
  template<typename ParticleType, typename... Args>
  void add_particle(Args&&... args);

  static void initialize_inheritance(); // Initialize the inheritance structure

  ParticleContainer operator[](ParticleUtilities::ParticleIdentifier particle) const;
};

#include<functional>
#include"core/ParticleContainer.tpp"

#endif