//ParticleUtilities.h
//Utility namespace of ParticleUtilities for particle class and other functions. Declares enum class for 
//the type of decay, and the ParticleIdentifier to be used in the ParticleCatalogue as the key in the hash map.
//Two functions for getting string equivalents of the enum class member.
//Herbie Warner 28/04/2024

#ifndef PARTICLEUTILITIES_H
#define PARTICLEUTILITIES_H

#include<string>
#include<stdexcept>

namespace ParticleUtilities 
{
  enum class DecayMode 
  {
    Unstable,
    Stable,
    HasDecayed,
  };

  enum class ParticleIdentifier 
  {
    Particle,
    Fermion,
    Boson,
    Lepton,
    Quark,
    HiggsBoson,
    GaugeBoson,
    ZBoson,
    WPlusBoson,
    WMinusBoson,
    Gluon,
    Photon,
    Electron,
    AntiElectron,
    Muon,
    AntiMuon,
    Tau,
    AntiTau,
    Neutrino,
    ElectronNeutrino,
    AntiElectronNeutrino,
    MuonNeutrino,
    AntiMuonNeutrino,
    TauNeutrino,
    AntiTauNeutrino,
    Up,
    AntiUp,
    Down,
    AntiDown,
    Charm,
    AntiCharm,
    Strange,
    AntiStrange,
    Top,
    AntiTop,
    Bottom,
    AntiBottom,
  };

  std::string get_particle_name(ParticleIdentifier id);
  std::string decay_mode_name(const DecayMode& mode);
}

#endif