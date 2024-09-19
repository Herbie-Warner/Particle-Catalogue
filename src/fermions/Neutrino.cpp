//Neutrino.cpp
//Defines the member functions of the Neutrino class which is a polymorphism of the Lepton class. Only one class
//for all neutrinos. Rest mass assumed 0.
//Herbie Warner 11/05/2024

#include<iostream>
#include"fermions/Neutrino.h"

using LeptonUtilities::LeptonType;
using ParticleUtilities::ParticleIdentifier;

Neutrino::Neutrino(LeptonType type, double E, double px, double py, double pz) : 
  Lepton(ParticleUtilities::DecayMode::Stable,
  type, 0, 0, E, px, py, pz), interacts_with_detector(false)
{
  LeptonUtilities::is_neutrino(type); //Throws error if not
}

Neutrino::Neutrino(LeptonType type) : Lepton(ParticleUtilities::DecayMode::Stable, type, 0, 0, 0, 0, 0, 0),
interacts_with_detector(false)
{
  LeptonUtilities::is_neutrino(type); //Throws error if not
}

Neutrino::Neutrino(const Neutrino& other) : Lepton(other), interacts_with_detector(other.interacts_with_detector) {}

Neutrino::Neutrino(Neutrino&& other) noexcept : Lepton(std::move(other)), interacts_with_detector(other.interacts_with_detector) {}

Neutrino& Neutrino::operator=(const Neutrino& other) 
{
  if(this != &other)
  {
    Lepton::operator=(other);
    interacts_with_detector = other.interacts_with_detector;
  }
  return *this;
}

Neutrino& Neutrino::operator=(Neutrino&& other) noexcept 
{
  if(this != &other) 
  {
    Lepton::operator=(std::move(other));
    interacts_with_detector = other.interacts_with_detector;
  }
  return *this;
}

std::unique_ptr<Particle> Neutrino::generate_anti_particle() const
{
  return std::make_unique<Neutrino>(LeptonUtilities::get_anti_lepton(get_lepton_flavour()), get_E(), get_px(), get_py(), get_pz());
}

ParticleUtilities::ParticleIdentifier Neutrino::get_correspondance() const //get correspondnace between lepon type and particle identifier
{
  const LeptonType lepton = this->get_lepton_flavour();
  switch(lepton) 
  {
  case LeptonType::ElectronNeutrino:
    return ParticleIdentifier::ElectronNeutrino;
  case LeptonType::MuonNeutrino:
    return ParticleIdentifier::MuonNeutrino;
  case LeptonType::TauNeutrino:
    return ParticleIdentifier::TauNeutrino;
  case LeptonType::AntiElectronNeutrino:
    return ParticleIdentifier::AntiElectronNeutrino;
  case LeptonType::AntiMuonNeutrino:
    return ParticleIdentifier::AntiMuonNeutrino;
  case LeptonType::AntiTauNeutrino:
    return ParticleIdentifier::AntiTauNeutrino;
  default:
    throw std::invalid_argument("INVALID NEUTRINO TYPE"); //should never happen
  }
}

ParticleUtilities::ParticleIdentifier Neutrino::get_general_type() const
{
  return get_correspondance();
}

std::stringstream Neutrino::get_info() const
{
  std::stringstream original = Lepton::get_info();
  original<<", Interacts: "<<std::boolalpha<<interacts_with_detector;
  return original;
}