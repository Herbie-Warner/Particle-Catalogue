//Tau.cpp
//Defines the member functions of the Tau class which is a polymorphism of the Lepton class.
//User generates both tau and anti tau by simply specifying the charge when instantiating a tau.
//Herbie Warner 11/05/2024

#include<iostream>

#include"utilities/DecayUtilities.h"
#include"utilities/LeptonUtilities.h"
#include"utilities/SharedDecays.h"

#include"fermions/Tau.h"
#include"fermions/Neutrino.h"

using LeptonUtilities::tau_rest_mass_energy;
using ParticleUtilities::DecayMode;
using LeptonUtilities::LeptonType;

Tau::Tau(int charge, double E, double px, double py, double pz) : Lepton(DecayMode::Unstable,
  LeptonUtilities::real_or_anti_flavour(LeptonType::Tau, charge), charge,tau_rest_mass_energy, E, px, py, pz)
{
  initialise_decay_channels();
}

Tau::Tau(int charge) : Lepton(DecayMode::Unstable, 
  LeptonUtilities::real_or_anti_flavour(LeptonType::Tau, charge), charge, tau_rest_mass_energy, tau_rest_mass_energy,
  0, 0, 0)
{
  initialise_decay_channels();
}

void Tau::initialise_decay_channels() 
{
  if(!decay_channels) {decay_channels = std::make_unique<DecayChannels>(get_general_type());} 
  const int charge = get_charge();
  if(charge == 1) {decay_channels->set_shared_channels(SharedDecays::get_w_plus_channels());} //Set the shared ptr to w
  else if(charge == -1) {decay_channels->set_shared_channels(SharedDecays::get_w_minus_channels());}
}

std::unique_ptr<Particle> Tau::generate_anti_particle() const
{
  return std::make_unique<Tau>(-get_charge(), get_E(), get_px(), get_py(), get_pz());
}

ParticleUtilities::ParticleIdentifier Tau::get_general_type() const
{
  if(get_charge() == -1) {return ParticleUtilities::ParticleIdentifier::Tau;}
  else { return ParticleUtilities::ParticleIdentifier::AntiTau; }
}

DecayProducts Tau::decay_inbuilt() const
{
  //Necessary as tau shared points to w decay so needs to append a tau
  //Note tau does not print the neutrino in print all decays function
  auto results = Particle::decay_inbuilt();
  if(results)
  {
    //Append the neutrino for the W decay
    results->push_back(std::make_unique<Neutrino>(LeptonUtilities::get_corresponding_neutrino(get_lepton_flavour())));
  }
  return results; //Results maybe nullopt
}