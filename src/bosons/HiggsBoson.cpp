//HiggsBoson.cpp
//Defines the member functions of the HiggsBoson class which is a polymorphism of the Boson class.
//Cloning and antiparticle generator overrided to return correct outputs.
//Herbie Warner 11/05/2024

#include<iostream>

#include"utilities/ParticleUtilities.h"
#include"utilities/SharedDecays.h"

#include"bosons/HiggsBoson.h"

HiggsBoson::HiggsBoson(double E, double px, double py, double pz) : Boson(ParticleUtilities::DecayMode::Unstable, 0, 0, higgs_rest_mass_ennergy, E, px, py, pz)
{
  initialise_decay_channels();
}

HiggsBoson::HiggsBoson() : Boson(ParticleUtilities::DecayMode::Unstable, 0, 0, higgs_rest_mass_ennergy, higgs_rest_mass_ennergy, 0, 0, 0)
{
  initialise_decay_channels();
}

void HiggsBoson::initialise_decay_channels()
{
  if(!decay_channels) {decay_channels = std::make_unique<DecayChannels>(get_general_type());}
  decay_channels->set_shared_channels(SharedDecays::get_higgs_channels());
}

std::unique_ptr<Particle> HiggsBoson::generate_anti_particle() const
{
  return std::make_unique<HiggsBoson>(*this);
}