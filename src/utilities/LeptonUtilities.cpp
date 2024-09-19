//LeptonUtilities.cpp
//Defines the lepton utilities namespace. Uses static maps for quick look ups for names, corresponding neutrinos,
//and antiparticles. Includes function implementations for useful utility functions.
//Herbie Warner 28/04/2024

#include<map>
#include<iostream>

#include"utilities/LeptonUtilities.h"

namespace LeptonUtilities 
{
  LeptonType get_anti_lepton(const LeptonType& lep_type) 
  {
    static const std::map<LeptonType, LeptonType> anti_particle_map = 
    {
      {LeptonType::Electron, LeptonType::AntiElectron},
      {LeptonType::Muon, LeptonType::AntiMuon},
      {LeptonType::Tau, LeptonType::AntiTau},
      {LeptonType::AntiElectron, LeptonType::Electron},
      {LeptonType::AntiMuon, LeptonType::Muon},
      {LeptonType::AntiTau, LeptonType::Tau},
      {LeptonType::ElectronNeutrino, LeptonType::AntiElectronNeutrino},
      {LeptonType::MuonNeutrino, LeptonType::AntiMuonNeutrino},
      {LeptonType::TauNeutrino, LeptonType::AntiTauNeutrino},
      {LeptonType::AntiElectronNeutrino, LeptonType::ElectronNeutrino},
      {LeptonType::AntiMuonNeutrino, LeptonType::MuonNeutrino},
      {LeptonType::AntiTauNeutrino, LeptonType::TauNeutrino},
    };

    auto it = anti_particle_map.find(lep_type);
    if(it != anti_particle_map.end()) 
    {
      return it->second;
    }
    else 
    {
      throw std::invalid_argument("Unknown LeptonType");
    }
  }

  LeptonType get_corresponding_neutrino(const LeptonType& lep_type)
  {
    static const std::map<LeptonType, LeptonType> neutrino_map = 
    {
       {LeptonType::Electron, LeptonType::ElectronNeutrino},
       {LeptonType::Muon, LeptonType::MuonNeutrino},
       {LeptonType::Tau, LeptonType::TauNeutrino},
       {LeptonType::AntiElectron, LeptonType::AntiElectronNeutrino},
       {LeptonType::AntiMuon, LeptonType::AntiMuonNeutrino},
       {LeptonType::AntiTau, LeptonType::AntiTauNeutrino},
    };

    auto it = neutrino_map.find(lep_type);
    if(it != neutrino_map.end()) 
    {
      return it->second;
    }
    else
    {
      std::string error_string = "UNKNOWN LEPTON TYPE FOR DECAY";
      throw std::invalid_argument(error_string);
    }
  }

  LeptonType get_corresponding_neutrino(const LeptonType& lep_type, int charge)
  {
    //This function is for use when using factory functions
    if(std::abs(charge) != 1)
    {
      throw std::invalid_argument("UNSUPPORTED CHARGE FOR GET CORRESPONDING NEUTRINO");
    }

    if(lep_type == LeptonType::Electron)
    {
      if(charge == 1) {return LeptonType::AntiElectronNeutrino;}
      else {return LeptonType::ElectronNeutrino;}
    }
    else if(lep_type == LeptonType::Muon)
    {
      if(charge == 1) {return LeptonType::AntiMuonNeutrino;}
      else {return LeptonType::MuonNeutrino;}
    }
    else if(lep_type == LeptonType::Tau)
    {
      if(charge == 1) {return LeptonType::AntiTauNeutrino;}
      else {return LeptonType::TauNeutrino;}
    }
    else
    {
      throw std::invalid_argument("UNSUPPORTED LEPTON TYPE FOR GET CORRESPONDING NEUTRINO");
    }  
  }

  LeptonNumber get_lepton_number(const LeptonType& type) {
    switch(type) 
    {
    case LeptonType::Electron:
    case LeptonType::ElectronNeutrino:
      return LeptonNumber(1, 0, 0);
    case LeptonType::Muon:
    case LeptonType::MuonNeutrino:
      return LeptonNumber(0, 1, 0);
    case LeptonType::Tau:
    case LeptonType::TauNeutrino:
      return LeptonNumber(0, 0, 1);
    case LeptonType::AntiElectron:
    case LeptonType::AntiElectronNeutrino:
      return LeptonNumber(-1, 0, 0);
    case LeptonType::AntiMuon:
    case LeptonType::AntiMuonNeutrino:
      return LeptonNumber(0, -1, 0);
    case LeptonType::AntiTau:
    case LeptonType::AntiTauNeutrino:
      return LeptonNumber(0, 0, -1);
    default:
      throw std::invalid_argument("INVALID OR UNSUPPORTED LEPTON TYPE FOR LEPTON NUMBER");
    }
  }

  void is_neutrino(const LeptonType& lep_type)
  {
    switch(lep_type) 
    {
    case LeptonType::ElectronNeutrino:
    case LeptonType::MuonNeutrino:
    case LeptonType::TauNeutrino:
    case LeptonType::AntiElectronNeutrino:
    case LeptonType::AntiMuonNeutrino:
    case LeptonType::AntiTauNeutrino:
      break;
    default:
      throw std::invalid_argument("CANNOT GENERATE NON-NEUTRINO NEUTRINO OBJECT");
    }
  }

  LeptonType real_or_anti_flavour(const LeptonType& type, int charge)
  {
    //For factory functions
    if(type == LeptonType::Electron)
    {
      if(charge == -1) {return LeptonType::Electron;}
      else if(charge == 1) {return LeptonType::AntiElectron;}
      else 
      {
        throw std::invalid_argument("CANNOT CREATE ELECTRON OBJECT WITH NOT -1 OR 1 CHARGE");
      }
    }
    else if(type == LeptonType::Muon)
    {
      if(charge == -1) {return LeptonType::Muon;}
      else if(charge == 1) {return LeptonType::AntiMuon;}
      else
      {
        throw std::invalid_argument("CANNOT CREATE MUON OBJECT WITH NOT -1 OR 1 CHARGE");
      }
    }
    else if(type == LeptonType::Tau)
    {
      if(charge == -1) {return LeptonType::Tau;}
      else if(charge == 1) {return LeptonType::AntiTau;}
      else
      {
        throw std::invalid_argument("CANNOT CREATE TAU OBJECT WITH NOT -1 OR 1 CHARGE");
      }
    }
    else
    {
      throw std::invalid_argument("UNSUPPORTED TYPE FOR REAL OR ANTI FLAVOUR FUNCTION CALL");
    }
  }

  bool check_if_neutrino(const LeptonType& type)
  {
    switch(type)
    {
    case LeptonType::AntiElectronNeutrino: return true;
    case LeptonType::AntiMuonNeutrino:     return true;
    case LeptonType::AntiTauNeutrino:      return true;
    case LeptonType::ElectronNeutrino:     return true;
    case LeptonType::MuonNeutrino:         return true;
    case LeptonType::TauNeutrino:          return true;
    default:                               return false;
    }
    return false;
  }

  LeptonType get_corresponding_anti_neutrino(const LeptonType& type)
  {
    auto corresponding_neutrino = get_corresponding_neutrino(type);
    return get_anti_lepton(corresponding_neutrino);
  }

  //LeptonNumber class functions

  void LeptonNumber::display_lepton_numbers() const
  {
    std::cout<<"Electron number: "<<electron_number<<", Muon number: "<<muon_number<<", Tau number: "<<tau_number;
  }

  bool LeptonNumber::operator!=(const LeptonNumber& other) const 
  { 
    return electron_number != other.electron_number || muon_number != other.muon_number
      || tau_number != other.tau_number; 
  }

  bool LeptonNumber::operator==(const LeptonNumber& other) const
  {
    return electron_number == other.electron_number && muon_number == other.muon_number
      && tau_number == other.tau_number;
  }

  //For aggregating quantum numbers
  LeptonNumber LeptonNumber::operator+=(const LeptonNumber& other)
  {
    electron_number += other.electron_number;
    muon_number += other.muon_number;
    tau_number += other.tau_number;
    return *this;
  }
}