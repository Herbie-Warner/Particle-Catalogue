//ParticleUtilities.cpp
//Defines the particle utilities namespace. Uses a static map for getting the name of a particular decay mode,
//and name of a particle type. Used maps here as opposed to switch statements as these are called often.
//Herbie Warner 28/04/2024

#include<map>
#include"utilities/ParticleUtilities.h"

namespace ParticleUtilities 
{
  std::string decay_mode_name(const DecayMode& mode) 
  {
    static const std::map<DecayMode, std::string> decay_mode_map = 
    {
      {DecayMode::Unstable, "Unstable"},
      {DecayMode::Stable, "Stable"},
      {DecayMode::HasDecayed, "Decayed"},
    };

    auto it = decay_mode_map.find(mode);
    if(it != decay_mode_map.end()) {return it->second;}
    return "UNRECOGNISED DECAY MODE";
  }

  std::string get_particle_name(ParticleIdentifier id) 
  {
    static const std::map<ParticleIdentifier, std::string> particle_names = 
    {
      {ParticleIdentifier::Particle, "Particle"},
      {ParticleIdentifier::Fermion, "Fermion"},
      {ParticleIdentifier::Boson, "Boson"},
      {ParticleIdentifier::Lepton, "Lepton"},
      {ParticleIdentifier::Quark, "Quark"},
      {ParticleIdentifier::HiggsBoson, "HiggsBoson"},
      {ParticleIdentifier::GaugeBoson, "GaugeBoson"},
      {ParticleIdentifier::ZBoson, "ZBoson"},
      {ParticleIdentifier::WPlusBoson, "WPlusBoson"},
      {ParticleIdentifier::WMinusBoson, "WMinusBoson"},
      {ParticleIdentifier::Gluon, "Gluon"},
      {ParticleIdentifier::Photon, "Photon"},
      {ParticleIdentifier::Electron, "Electron"},
      {ParticleIdentifier::AntiElectron, "AntiElectron"},
      {ParticleIdentifier::Muon, "Muon"},
      {ParticleIdentifier::AntiMuon, "AntiMuon"},
      {ParticleIdentifier::Tau, "Tau"},
      {ParticleIdentifier::AntiTau, "AntiTau"},
      {ParticleIdentifier::Neutrino, "Neutrino"},
      {ParticleIdentifier::ElectronNeutrino, "ElectronNeutrino"},
      {ParticleIdentifier::AntiElectronNeutrino, "AntiElectronNeutrino"},
      {ParticleIdentifier::MuonNeutrino, "MuonNeutrino"},
      {ParticleIdentifier::AntiMuonNeutrino, "AntiMuonNeutrino"},
      {ParticleIdentifier::TauNeutrino, "TauNeutrino"},
      {ParticleIdentifier::AntiTauNeutrino, "AntiTauNeutrino"},
      {ParticleIdentifier::Up, "Up"},
      {ParticleIdentifier::AntiUp, "AntiUp"},
      {ParticleIdentifier::Down, "Down"},
      {ParticleIdentifier::AntiDown, "AntiDown"},
      {ParticleIdentifier::Charm, "Charm"},
      {ParticleIdentifier::AntiCharm, "AntiCharm"},
      {ParticleIdentifier::Strange, "Strange"},
      {ParticleIdentifier::AntiStrange, "AntiStrange"},
      {ParticleIdentifier::Top, "Top"},
      {ParticleIdentifier::AntiTop, "AntiTop"},
      {ParticleIdentifier::Bottom, "Bottom"},
      {ParticleIdentifier::AntiBottom, "AntiBottom"},
    };

    auto it = particle_names.find(id);
    if(it != particle_names.end()) 
    {
      return it->second;
    }
    else 
    {
      return "Unknown Particle";
    }
  }
}