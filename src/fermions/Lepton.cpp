//Lepton.cpp
//Defines the member functions of the Lepton class which is a polymorphism of the Fermion class. New private members
//of lepton flavour and number are installed mandating updated move and copy operators/ constructos. Class is abstract.
//Herbie Warner 11/05/2024

#include<iostream>
#include"fermions/Lepton.h"

Lepton::Lepton(const ParticleUtilities::DecayMode& mode, const LeptonUtilities::LeptonType& lep_flavour,
  double charge, const double rest_mass, double E, double px, double py, double pz) :
  Fermion(mode, 1.0/2.0, charge, rest_mass, E, px, py, pz),
lepton_number(std::make_unique<LeptonUtilities::LeptonNumber>(LeptonUtilities::get_lepton_number(lep_flavour))),
lepton_flavour(lep_flavour) {}

Lepton::~Lepton() {}

Lepton::Lepton(const Lepton& other) : Fermion(other), lepton_flavour(other.lepton_flavour)
{
  if(other.lepton_number) //As lepton number is unique_ptr
  {
    lepton_number = std::make_unique<LeptonUtilities::LeptonNumber>(*other.lepton_number);
  }
  else
  {
    lepton_number.reset();
  }
}

Lepton& Lepton::operator=(const Lepton& other) 
{
  if(this != &other) 
  {
    Fermion::operator=(other);
    lepton_flavour = other.lepton_flavour;
    if(other.lepton_number) 
    {
      lepton_number = std::make_unique<LeptonUtilities::LeptonNumber>(*other.lepton_number);
    }
    else 
    {
      lepton_number.reset(); //Need to test this
    }
  }
  return *this;
}

Lepton::Lepton(Lepton&& other) noexcept : 
  Fermion(std::move(other)), lepton_number(std::move(other.lepton_number)), lepton_flavour(other.lepton_flavour) {}

Lepton& Lepton::operator=(Lepton&& other) noexcept 
{
  if(this != &other) 
  {
    Fermion::operator=(std::move(other)); 
    lepton_number = std::move(other.lepton_number);
    lepton_flavour = other.lepton_flavour;
  }
  return *this;
}

std::stringstream Lepton::get_info() const
{
  std::stringstream original = Particle::get_info();
  int e_number = lepton_number->get_electron_number();
  int m_number = lepton_number->get_muon_number();
  int t_number = lepton_number->get_tau_number();
  original<<", Lepton Number (e, mu, tau): "<<e_number<<", "<<m_number<<", "<<t_number;
  return original;
}