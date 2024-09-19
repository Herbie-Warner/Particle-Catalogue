//Particle.cpp
//Defines the member functions of the Particle class, which is the base of all particles (electron, gluon and so on).
//Base functions for copy/move semantics defined, along with printing functions, decay function, and add decay
//channel function.
//Herbie Warner 09/05/2024

#include<iostream>
#include<vector>
#include<cmath>

#include"core/Particle.h"
#include"utilities/FactoryUtilities.h"

using ParticleUtilities::DecayMode;

Particle::Particle(const DecayMode& d_mode, double spin, double c, double rest_mass, double E, double px, double py, double pz)
  :  charge(c), rest_mass(rest_mass), four_momentum(std::make_unique<FourVector>()), mode(d_mode), spin(spin),
  decay_channels(nullptr)  
{
  set_four_momentum(E, px, py, pz);
}

Particle::~Particle() {}

// Copy constructor
Particle::Particle(const Particle& other): charge(other.charge),mode(other.mode),
four_momentum(std::make_unique<FourVector>(*other.four_momentum)), spin(other.spin), rest_mass(other.rest_mass),
decay_channels(other.decay_channels ? std::make_unique<DecayChannels>(*other.decay_channels) : nullptr) {}

// Copy assignment operator
Particle& Particle::operator=(const Particle& other) 
{
  if(this != &other) 
  {
    spin = other.spin;
    charge = other.charge;
    rest_mass = other.rest_mass;
    four_momentum = std::make_unique<FourVector>(*other.four_momentum);
    mode = other.mode;
    decay_channels = other.decay_channels ? std::make_unique<DecayChannels>(*other.decay_channels) : nullptr; //Make sure it exists
  }
  return *this;
}

// Move constructor
Particle::Particle(Particle&& other) noexcept 
  :  four_momentum(std::move(other.four_momentum)),
  mode(other.mode), decay_channels(std::move(other.decay_channels)), charge(other.charge),
  spin(other.spin), rest_mass(other.rest_mass) {}

// Move assignment operator
Particle& Particle::operator=(Particle&& other) noexcept 
{
  if(this != &other) 
  {
    spin = other.spin;
    charge = other.charge;
    rest_mass = other.rest_mass;
    four_momentum = std::move(other.four_momentum);
    mode = other.mode;
    decay_channels = std::move(other.decay_channels);
  }
  return *this;
}

//Overloaded in case the user wants to add with DecayUtilities::DecayChannel directly or vector of
//ParticleIdentifier.
void Particle::add_decay_channel(DecayUtilities::DecayChannel channel)
{
  auto products = channel.factory();
  bool is_valid_decay = DecayUtilities::validate_decay(this, products);
  if(!is_valid_decay)
  {
    std::cerr<<"NOT VALID DECAY: NOT ADDING TO POSSIBLE DECAY CHAINS"<<std::endl;
  }
  else
  {
    if(!decay_channels) {decay_channels = std::make_unique<DecayChannels>(get_general_type());}
    decay_channels->add_channel(channel);
  }
}

void Particle::add_decay_channel(std::vector<ParticleUtilities::ParticleIdentifier> particles, double branching_ratio)
{
  DecayUtilities::DecayChannel decay(
    [particles]()
    {
      std::vector<std::unique_ptr<Particle>> products;
      for(const auto& particle : particles)
      {
        products.push_back(FactoryUtilities::factory_particle(particle));
      }
      return products;
    },
    branching_ratio
  );
  add_decay_channel(decay);
}

void Particle::print_all_decays() const
{
  if(decay_channels != nullptr) {decay_channels->print_all_decays();}
  else {std::cerr<<"DECAY CHANNELS IS NULLPTR"<<std::endl;}
}

void Particle::decay_with_print_inbuilt() const
{
  auto products = decay_inbuilt();
  if(products)
  {
    for(const auto& particle : *products)
    {
      particle->display_properties();
    }
  }
  else
  {
    std::cout<<"NO SHARED DECAYS FOR PARTICLE: "<<ParticleUtilities::get_particle_name(get_general_type())<<std::endl;
  }
}

void Particle::decay_with_print_instance_specific() const 
{
  auto products = decay_instante_specific();
  if(products)
  {
    for(const auto& particle : *products)
    {
      particle->display_properties();
    }
  }
  else
  {
    std::cout<<"NO INSTANCE SPECIFIC DECAYS FOR PARTICLE: "<<ParticleUtilities::get_particle_name(get_general_type())<<std::endl;
  }
}

DecayProducts Particle::decay_inbuilt() const
{

  if(mode != DecayMode::Unstable)
  {
    std::cout<<ParticleUtilities::get_particle_name(get_general_type())<<" is "
     <<ParticleUtilities::decay_mode_name(mode)<<std::endl;
    return std::nullopt;
  }
  if(decay_channels)
  {
    auto products = decay_channels->perform_decay_shared();
    if(products){DecayUtilities::distribute_four_momentum(*this, products.value());}
    mode = DecayMode::HasDecayed;
    return products;
  }
  return std::nullopt;
}

DecayProducts Particle::decay_instante_specific() const
{
  if(mode != DecayMode::Unstable)
  {
    std::cout<<ParticleUtilities::get_particle_name(get_general_type())<<" is "
     <<ParticleUtilities::decay_mode_name(mode)<<std::endl;
    return std::nullopt;
  }
  if(decay_channels)
  {
    auto products = decay_channels->perform_decay_instance();
    if(products){DecayUtilities::distribute_four_momentum(*this, products.value());}
    mode = DecayMode::HasDecayed;
    return products;
  }
  return std::nullopt;
}

void Particle::display_properties() const
{
  std::cout<<get_info().str()<<std::endl;
}

std::stringstream Particle::get_info() const
{
  std::stringstream ss;
  //Base particle information. New details appended for derived classes such as colour, lepton number etc.
  ss<<ParticleUtilities::get_particle_name(get_general_type())<<", Charge: "
   <<charge<<", Spin: "<<spin<<", Rest Mass: "<<rest_mass<<" MeV, Decay mode: "<<
    ParticleUtilities::decay_mode_name(mode)<<", Four Momentum: "<<get_E()<<", "<<get_px()
   <<", "<<get_py()<<", "<<get_pz()<<" MeV";
  return ss;
}

void Particle::set_four_momentum(double E, double px, double py, double pz)
{
  //Augments energies to adhere to known rest mass.
  FourVector new_momentum(E, px, py, pz);
  double four_momentum_sqr = new_momentum.dot_product(new_momentum);
  double invariant_mass_squared = rest_mass * rest_mass;
  double difference = std::abs(invariant_mass_squared - four_momentum_sqr);
  static const double tolerance = 0.01;

  if(difference / invariant_mass_squared > tolerance)
  {
    double E_squared = E*E;
    double delta = four_momentum_sqr - invariant_mass_squared;
    if(delta < E_squared)
    {;
      E = std::sqrt(E_squared - delta);
    }
    else
    {
      E = rest_mass;
      px = 0; 
      py = 0;
      pz = 0;
    }
  }
  four_momentum->set_four_vector(E, px, py, pz);
}