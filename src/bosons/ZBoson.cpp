//ZBoson.cpp
//Defines the member functions of the ZBoson class which is a polymorphism of the GaugeBoson class.
//initialise_decay_channels overridden to correclty have pointer to shared z decays.
//Herbie Warner 11/05/2024

#include<iostream>

#include"utilities/ParticleUtilities.h"
#include"utilities/SharedDecays.h"

#include"bosons/ZBoson.h"

using ParticleUtilities::DecayMode;

ZBoson::ZBoson(double E, double px, double py, double pz) : 
  GaugeBoson(DecayMode::Unstable, 0, zboson_rest_mass_energy, E, px, py, pz)
{
  initialise_decay_channels();
}

ZBoson::ZBoson() : GaugeBoson(DecayMode::Unstable, 0,zboson_rest_mass_energy, zboson_rest_mass_energy, 0, 0, 0)
{
  initialise_decay_channels();
}

std::unique_ptr<Particle> ZBoson::generate_anti_particle() const
{
  std::cout<<"ZBOSON ARE THEIR OWN ANTIPARTICLES. RETURNING NEW Z INSTANCE"<<std::endl;
  return std::make_unique<ZBoson>(*this);
}

void ZBoson::initialise_decay_channels()
{
  if(!decay_channels) {decay_channels = std::make_unique<DecayChannels>(get_general_type());} //Init ptr to shared z decays
  decay_channels->set_shared_channels(SharedDecays::get_z_channels());
}