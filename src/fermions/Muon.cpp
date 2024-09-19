//Muon.cpp
//Defines the member functions of the Muon class which is a polymorphism of the Lepton class. One class
//for both muon and anti muon with the lepton type discerned by the charge.
//Herbie Warner 11/05/2024

#include<iostream>
#include"fermions/Muon.h"

using LeptonUtilities::muon_rest_mass_energy;
using ParticleUtilities::DecayMode;
using LeptonUtilities::LeptonType;


Muon::Muon(int charge, double E, double px, double py, double pz) : Lepton(DecayMode::Stable,
  LeptonUtilities::real_or_anti_flavour(LeptonType::Muon, charge), charge,
  muon_rest_mass_energy, E, px, py, pz), is_isolated(false) {}

Muon::Muon(int charge) : Lepton(DecayMode::Stable, LeptonUtilities::real_or_anti_flavour(LeptonType::Muon,
  charge), charge, muon_rest_mass_energy, muon_rest_mass_energy, 0, 0, 0), is_isolated(false) {}

//Semantics for new is isolated variable
Muon::Muon(const Muon& other) : Lepton(other), is_isolated(other.is_isolated) {}

Muon::Muon(Muon&& other) noexcept : Lepton(std::move(other)), is_isolated(other.is_isolated) {}

Muon& Muon::operator=(const Muon& other) 
{
  if(this != &other)
  {
    Lepton::operator=(other);
    is_isolated = other.is_isolated;
  }
  return *this;
}

Muon& Muon::operator=(Muon&& other) noexcept 
{
  if(this != &other) 
  {
    Lepton::operator=(std::move(other));
    is_isolated = other.is_isolated;
  }
  return *this;
}


std::unique_ptr<Particle> Muon::generate_anti_particle() const
{
  return std::make_unique<Muon>(-get_charge(), get_E(), get_px(), get_py(), get_pz());
}

ParticleUtilities::ParticleIdentifier Muon::get_general_type() const
{
  if(get_charge() == -1) {return ParticleUtilities::ParticleIdentifier::Muon;}
  else { return ParticleUtilities::ParticleIdentifier::AntiMuon; }
}

std::stringstream Muon::get_info() const
{
  std::stringstream original = Lepton::get_info();
  original<<", Is isolated: "<<std::boolalpha<<is_isolated;
  return original;
}
