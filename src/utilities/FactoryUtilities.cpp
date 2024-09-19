//FactoryUtilities.cpp
//Defines the factory function for all particles. This is necessary to allow the user to add
//decay channels simply rather than forcing them to write lambdas.
//Herbie Warner 11/05/2024

#include<map>
#include<functional>
#include<stdexcept>

//Utilities
#include"utilities/QuarkUtilities.h"

//Fermions
#include"fermions/Electron.h"
#include"fermions/Muon.h"
#include"fermions/Neutrino.h"
#include"fermions/Quark.h"
#include"fermions/Tau.h"

//Bosons
#include"bosons/ZBoson.h"
#include"bosons/WBoson.h"
#include"bosons/Photon.h"
#include"bosons/Gluon.h"
#include"bosons/HiggsBoson.h"

using LeptonUtilities::LeptonType;
using ParticleUtilities::DecayMode;
using ParticleUtilities::ParticleIdentifier;
using QuarkUtilities::QuarkFlavour;

namespace FactoryUtilities
{
  //Use std::function for lazy instantiation
  std::unique_ptr<Particle> factory_particle(ParticleIdentifier id)
  {
    static std::map<ParticleIdentifier, std::function<std::unique_ptr<Particle>()>> factory_map =
    {
      {ParticleIdentifier::Electron, []() -> std::unique_ptr<Particle> {return std::make_unique<Electron>(-1);}},
      {ParticleIdentifier::AntiElectron, []() -> std::unique_ptr<Particle> {return std::make_unique<Electron>(+1);}},
      {ParticleIdentifier::Muon, []() -> std::unique_ptr<Particle> {return std::make_unique<Muon>(-1);}},
      {ParticleIdentifier::AntiMuon, []() -> std::unique_ptr<Particle> {return std::make_unique<Muon>(+1);}},
      {ParticleIdentifier::Tau, []() -> std::unique_ptr<Particle> {return std::make_unique<Tau>(-1); }},
      {ParticleIdentifier::AntiTau, []() -> std::unique_ptr<Particle> {return std::make_unique<Tau>(+1); }},
      {ParticleIdentifier::Up, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Up);}},
      {ParticleIdentifier::AntiUp, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Up);}},
      {ParticleIdentifier::Top, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Top);}},
      {ParticleIdentifier::AntiTop, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Top);}},
      {ParticleIdentifier::Down, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Down);}},
      {ParticleIdentifier::AntiDown, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Down);}},
      {ParticleIdentifier::Charm, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Charm);}},
      {ParticleIdentifier::AntiCharm, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Charm);}},
      {ParticleIdentifier::Strange, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Strange);}},
      {ParticleIdentifier::AntiStrange, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Strange);}},
      {ParticleIdentifier::Bottom, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Bottom);}},
      {ParticleIdentifier::AntiBottom, []() -> std::unique_ptr<Particle> {return std::make_unique<Quark>(QuarkFlavour::Anti_Bottom);}},
      {ParticleIdentifier::ZBoson, []() -> std::unique_ptr<Particle> {return std::make_unique<ZBoson>();}},
      {ParticleIdentifier::WPlusBoson, []() -> std::unique_ptr<Particle> {return std::make_unique<WBoson>(+1);}},
      {ParticleIdentifier::WMinusBoson, []() -> std::unique_ptr<Particle> {return std::make_unique<WBoson>(-1);}},
      {ParticleIdentifier::Gluon, []() -> std::unique_ptr<Particle> {return std::make_unique<Gluon>();}},
      {ParticleIdentifier::Photon, []() -> std::unique_ptr<Particle> {return std::make_unique<Photon>();}},
      {ParticleIdentifier::HiggsBoson, []() -> std::unique_ptr<Particle> {return std::make_unique<HiggsBoson>();}},
      {ParticleIdentifier::ElectronNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::ElectronNeutrino);}},
      {ParticleIdentifier::AntiElectronNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::AntiElectronNeutrino);}},
      {ParticleIdentifier::MuonNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::MuonNeutrino);}},
      {ParticleIdentifier::AntiMuonNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::AntiMuonNeutrino);}},
      {ParticleIdentifier::TauNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::TauNeutrino);}},
      {ParticleIdentifier::AntiTauNeutrino, []() -> std::unique_ptr<Particle> {return std::make_unique<Neutrino>(LeptonType::AntiTauNeutrino);}},
    };

    auto it = factory_map.find(id);
    if(it != factory_map.end()) 
    {
      return it->second();
    }
    std::stringstream error_ss;
    error_ss<<"CANNOT GENERATE PARTICLE OF TYPE: "<<ParticleUtilities::get_particle_name(id);
    throw std::invalid_argument(error_ss.str());
  }
}