//Electron.cpp
//Defines the member functions of the Electron class which is a polymorphism of the Lepton class. 
//New copy/move semantics for new data member Calorimeter. The calorimeter energies are intially
//all set at zero and only when set_calorimeter_deposit is called are they given non-zero values.
//The code checks whether the sum of the inputted values is equal to its energy, augmenting the
//values provided if not.
//Herbie Warner 11/05/2024

#include<iostream>
#include"fermions/Electron.h"

using LeptonUtilities::electron_rest_mass_energy;
using ParticleUtilities::DecayMode;
using LeptonUtilities::LeptonType;

Electron::Electron(int charge, double E, double px, double py, double pz) : Lepton(ParticleUtilities::DecayMode::Stable,
  LeptonUtilities::real_or_anti_flavour(LeptonType::Electron, charge), charge, electron_rest_mass_energy, E, px, py, pz),
  calorimeter_deposit(4, 0.0) {}

Electron::Electron(int charge) : Lepton(ParticleUtilities::DecayMode::Stable,
  LeptonUtilities::real_or_anti_flavour(LeptonType::Electron, charge), charge, electron_rest_mass_energy,
  electron_rest_mass_energy, 0,0,0), calorimeter_deposit(4, 0.0) {}

//New copy/move semantics
Electron::Electron(const Electron& other) : Lepton(other), calorimeter_deposit(other.calorimeter_deposit) {}

Electron::Electron(Electron&& other) noexcept : Lepton(std::move(other)), calorimeter_deposit(other.calorimeter_deposit) {}

Electron& Electron::operator=(const Electron& other)
{
  if(this != &other)
  {
    Lepton::operator=(other);
    calorimeter_deposit = other.calorimeter_deposit;
  }
  return *this;
}

Electron& Electron::operator=(Electron&& other) noexcept
{
  if(this != &other)
  {
    Lepton::operator=(std::move(other));
    calorimeter_deposit = other.calorimeter_deposit;
  }
  return *this;
}

void Electron::change_calorimeter(double layer_1, double layer_2, double layer_3, double layer_4)
{
  calorimeter_deposit[0] = layer_1;
  calorimeter_deposit[1] = layer_2;
  calorimeter_deposit[2] = layer_3;
  calorimeter_deposit[3] = layer_4;
}

void Electron::set_calorimeter_deposit(double EM_1, double EM_2, double HAD_1, double HAD_2)
{
  double energy = get_E();
  double sum = EM_1 + EM_2 + HAD_1 + HAD_2;
  if(EM_1 < 0 || EM_2 < 0 || HAD_1 < 0 || HAD_2 < 0)
  {
    std::cout<<"CANNOT HAVE NEGATIVE ENERGIES: SETTING ALL EQUAL TO ELECTRON ENERGY/4"<<std::endl;
    double energy_in_each_layer = energy / 4;
    change_calorimeter(energy_in_each_layer, energy_in_each_layer, energy_in_each_layer, energy_in_each_layer);
  }
  else if(sum == energy)
  {
    change_calorimeter(EM_1, EM_2, HAD_1, HAD_2);
  }
  else if(sum < energy)
  {
    std::cout<<"AUGMENTING LAYER_1 ENERGY TO ACCOMADATE EXCESS ENERGY IN ELECTRON FOUR VECTOR"<<std::endl;
    double difference = energy - sum;
    EM_1 += difference;
    change_calorimeter(EM_1, EM_2, HAD_1, HAD_2);
  }
  else
  {
    std::cout<<"ENERGY SET EXCEEDS ELECTRON ENERGY: SETTING ALL EQUAL TO ELECTRON ENERGY/4"<<std::endl;
    double energy_in_each_layer = energy / 4;
    change_calorimeter(energy_in_each_layer, energy_in_each_layer, energy_in_each_layer, energy_in_each_layer);
  }
}

std::vector<double> Electron::get_calorimeter_deposit() const
{
  return calorimeter_deposit;
}

std::unique_ptr<Particle> Electron::generate_anti_particle() const
{
  return std::make_unique<Electron>(-get_charge(), get_E(), get_px(), get_py(), get_pz());
}

ParticleUtilities::ParticleIdentifier Electron::get_general_type() const //For container
{ 
  if(get_charge() == -1) {return ParticleUtilities::ParticleIdentifier::Electron;}
  else {return ParticleUtilities::ParticleIdentifier::AntiElectron;}
}

std::stringstream Electron::get_info() const
{
  std::stringstream original = Lepton::get_info();
  original<<", Calorimeter deposit (MeV): EM1 "<<get_EM_1()<<
    ", EM 2 "<<get_EM_2()<<", HAD_1 "<<get_HAD_1()<<", HAD_2 "<<get_HAD_2();
  return original;
}