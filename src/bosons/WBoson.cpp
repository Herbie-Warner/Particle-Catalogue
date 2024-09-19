//WBoson.cpp
//Defines the member functions of the WBoson class which is a polymorphism of the GaugeBoson class. User generates
//+- W bosons by specifying charge at spawn. Decays obtained via the SharedDecays namespace.
//Herbie Warner 11/05/2024

#include<iostream>

#include"bosons/WBoson.h"
#include"utilities/ParticleUtilities.h"
#include"utilities/SharedDecays.h"

using ParticleUtilities::DecayMode;

WBoson::WBoson(int charge, double E, double px, double py, double pz) : 
  GaugeBoson(DecayMode::Unstable, static_cast<double>(charge), wboson_rest_mass_energy, E, px, py, pz)
{
  init_charge(charge);
  initialise_decay_channels();
}

WBoson::WBoson(int charge) : GaugeBoson(DecayMode::Unstable, static_cast<double>(charge),wboson_rest_mass_energy, wboson_rest_mass_energy, 0, 0, 0)
{
  init_charge(charge);
  initialise_decay_channels();
}


void WBoson::init_charge(int charge)
{
  if(std::abs(charge) != 1)
  {
    throw std::invalid_argument("W BOSON CHARGE CAN ONLY BE +-1");
  }
}

std::unique_ptr<Particle> WBoson::generate_anti_particle() const
{
  return std::make_unique<WBoson>(-get_charge(),get_E(),get_px(),get_py(),get_pz());
}

void WBoson::initialise_decay_channels()
{
  if(!decay_channels) {decay_channels = std::make_unique<DecayChannels>(get_general_type());}
  const int charge = get_charge();
  if(charge == 1) {decay_channels->set_shared_channels(SharedDecays::get_w_plus_channels());}
  else if(charge == -1) {decay_channels->set_shared_channels(SharedDecays::get_w_minus_channels());}
}

ParticleUtilities::ParticleIdentifier WBoson::get_general_type() const
{
  if(get_charge() == 1) {return ParticleUtilities::ParticleIdentifier::WPlusBoson;}
  else {return ParticleUtilities::ParticleIdentifier::WMinusBoson;}
}
