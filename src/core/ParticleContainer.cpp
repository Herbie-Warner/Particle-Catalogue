//ParticleContainer.cpp
//Defines the particle container class member functions. Defines the static inheritance map so all
//containers use this same inheritance map to reduce the overhead. Searches for derived classes
//as well as specific classes by using recursion across the inheritance map. Includes useful container
//functions like size().
//Herbie Warner 28/04/2024

#include<memory>
#include<unordered_map>
#include<unordered_set>
#include<iostream>

#include"core/ParticleContainer.h"
#include"utilities/ParticleUtilities.h"

using ParticleUtilities::ParticleIdentifier; 

std::unordered_map<ParticleIdentifier, std::unordered_set<ParticleIdentifier>> ParticleContainer::inheritance_map; //Define the staitc inheritance map

void ParticleContainer::initialize_inheritance()
{
  //Register entire chain of derived classes. In an even large application it may be
  //suitable to within each particle keep track of both its type, and its parents type
  //so this procedure is automated.
  register_inheritance(ParticleIdentifier::Particle, ParticleIdentifier::Fermion);
  register_inheritance(ParticleIdentifier::Particle, ParticleIdentifier::Boson);

  register_inheritance(ParticleIdentifier::Fermion, ParticleIdentifier::Lepton);
  register_inheritance(ParticleIdentifier::Fermion, ParticleIdentifier::Quark);

  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::Electron);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::AntiElectron);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::Muon);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::AntiMuon);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::Tau);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::AntiTau);
  register_inheritance(ParticleIdentifier::Lepton, ParticleIdentifier::Neutrino);

  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::ElectronNeutrino);
  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::MuonNeutrino);
  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::TauNeutrino);
  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::AntiElectronNeutrino);
  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::AntiMuonNeutrino);
  register_inheritance(ParticleIdentifier::Neutrino, ParticleIdentifier::AntiTauNeutrino);

  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Up);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiBottom);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Bottom);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiUp);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Down);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiDown);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Charm);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiCharm);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Strange);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiStrange);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::Top);
  register_inheritance(ParticleIdentifier::Quark, ParticleIdentifier::AntiTop);

  register_inheritance(ParticleIdentifier::Boson, ParticleIdentifier::HiggsBoson);
  register_inheritance(ParticleIdentifier::Boson, ParticleIdentifier::GaugeBoson);

  register_inheritance(ParticleIdentifier::GaugeBoson, ParticleIdentifier::Photon);
  register_inheritance(ParticleIdentifier::GaugeBoson, ParticleIdentifier::Gluon);
  register_inheritance(ParticleIdentifier::GaugeBoson, ParticleIdentifier::ZBoson);
  register_inheritance(ParticleIdentifier::GaugeBoson, ParticleIdentifier::WPlusBoson);
  register_inheritance(ParticleIdentifier::GaugeBoson, ParticleIdentifier::WMinusBoson);
}

void ParticleContainer::register_inheritance(ParticleIdentifier base, ParticleIdentifier derived)
{
  inheritance_map[base].insert(derived);
  for(auto& [ancestor, descendants] : inheritance_map)
  {
    if(descendants.find(base) != descendants.end())
    {
      descendants.insert(derived);
    }
  }
}

//Inheritance map is static so no need to copy/move across
ParticleContainer::ParticleContainer(const ParticleContainer& other) : particle_map(other.particle_map) {}
ParticleContainer& ParticleContainer::operator=(const ParticleContainer& other)
{
  if(this != &other)
  {
    particle_map = other.particle_map;
  }
  return *this;
}
ParticleContainer::ParticleContainer(ParticleContainer&& other) noexcept : particle_map(std::move(other.particle_map)) {}
ParticleContainer& ParticleContainer::operator=(ParticleContainer&& other) noexcept
{
  if(this != &other)
  {
    particle_map = std::move(other.particle_map);
  }
  return *this;
}

void ParticleContainer::add_object(std::shared_ptr<Particle> obj)
{
  ParticleIdentifier index = obj->get_general_type();
  particle_map[index].push_back(obj);
}

ParticleContainer ParticleContainer::get_subcontainer_of_type(ParticleIdentifier identity) const
{
  ParticleContainer new_container;
  process_particles_of_type(identity, [&](const ParticleIdentifier& id, const auto& particles) 
  {
    //Have class based access as access control based on class and not instances themselves (i.e can access
    //private data members of another instance of the same class)
    new_container.particle_map[id] = particles;
  });
  return new_container;
}

size_t ParticleContainer::size() const
{
  size_t size = 0;
  for(const auto& pair : particle_map)
  {
    size += pair.second.size();
  }
  return size;
}

size_t ParticleContainer::size(ParticleIdentifier identity) const
{
  size_t total_size = 0;
  process_particles_of_type(identity, [&](const ParticleIdentifier& id, const auto& particles) 
  {
    total_size += particles.size();
  });
  return total_size;
}

void ParticleContainer::print_all() const
{
  for(const auto& [_, objects] : particle_map)
  {
    for(const auto& obj : objects)
    {
      obj->display_properties();
      std::cout<<std::endl;
    }
  }
}

void ParticleContainer::print_all(ParticleUtilities::ParticleIdentifier identity) const
{
  process_particles_of_type(identity, [&](const ParticleIdentifier& id, const auto& particles)
  {
    for(const auto& particle : particles)
    {
      particle->display_properties();
    }
  });
}

FourVector ParticleContainer::get_total_momentum() const
{
  FourVector total;
  for(const auto& [_, objects] : particle_map)
  {
    for(const auto& obj : objects)
    {
      total += obj->get_four_vector();
    }
  }
  return total;
}

ParticleContainer ParticleContainer::operator[](ParticleUtilities::ParticleIdentifier particle) const
{
  return get_subcontainer_of_type(particle); 
  //Operator [] definition as this is common syntax albeit [] usually refers to a particular element
  //of the container and not a new container. However it is nice to work with.
}

std::vector<std::shared_ptr<Particle>> ParticleContainer::get_particles_of_type(ParticleUtilities::ParticleIdentifier identity) const
{
  std::vector<std::shared_ptr<Particle>> particle_vector;
  process_particles_of_type(identity, [&](const ParticleIdentifier& id, const auto& particles) 
  {
    particle_vector.insert(particle_vector.end(), particles.begin(), particles.end());
  });
  return particle_vector; 
}