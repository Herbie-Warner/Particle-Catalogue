//SharedDecays.cpp
//Defines the SharedDecays namespace. Initialises the shared decay ptrs by using templates
//from the DecayTemplates class.
//Branching ratios obtained from following sources:
//Leptonic vs Hadronic for W: https://pdg.lbl.gov/2022/listings/particle_properties.html
//CKM matrix: https://pdg.lbl.gov/2020/reviews/rpp2020-rev-ckm-matrix.pdf
//ZBoson: https://www.hep.phy.cam.ac.uk/~thomson/lectures/partIIIparticles/Handout13_2009.pdf
//Higgs: https://pdg.lbl.gov/2016/reviews/rpp2016-rev-higgs-boson.pdf
//The reason the decays are not simply declared static in their relevant classes is so that
//other particles may access and use them without having to decay through said particle. This permits
//the hard coding of decays, required by the decays mandated, at the cost of prohibiting a nested
//and physically accurate structure. By nested this refers to a tau going into a tau neutrino and a
//W and then the W subsequently decaying and so on.
//Herbie Warner 11/05/2024

#include<utility>
#include<iostream>

//Utilities
#include"utilities/DecayChannels.h"
#include"utilities/DecayTemplates.h"
#include"utilities/DecayUtilities.h"
#include"utilities/SharedDecays.h"
#include"utilities/QuarkUtilities.h"
#include"utilities/FactoryUtilities.h"

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

using LeptonUtilities::LeptonType;
using ParticleUtilities::DecayMode;
using QuarkUtilities::QuarkFlavour;

namespace SharedDecays 
{
  static std::shared_ptr<DecayChannelsVector> w_minus_decays = nullptr;
  static std::shared_ptr<DecayChannelsVector> w_plus_decays = nullptr;
  static std::shared_ptr<DecayChannelsVector> z_decays = nullptr;
  static std::shared_ptr<DecayChannelsVector> higgs_decays = nullptr;

  constexpr double w_branching_hadronic = 0.7; //To multiply in cabibo matrix
  constexpr double w_branching_leptonic_all_flavours = 0.1;

  constexpr double z_branching_ee = 0.035; //Same for ττ and μμ
  constexpr double z_branching_nunu = 0.07; //Same for all neutrino flavours
  constexpr double z_branching_qq = 0.114; //Assume same for all (even Z → ττ)

  constexpr double h_branching_photon_photon = 0.00227;
  constexpr double h_branching_bb = 0.584;
  constexpr double h_branching_ww = 0.214;
  constexpr double h_branching_zz = 0.0262; //Normalisation does not matter here. Will be considered in decay functions

  void initialise_shared_decay_channels() 
  {
    //Called at beginning of main to initialise all the set decays
    if(!w_minus_decays) 
    {
      w_minus_decays = std::make_shared<DecayChannelsVector>();
      generate_w_boson_decays(-1, w_minus_decays);
    }
    if(!w_plus_decays) 
    {
      w_plus_decays = std::make_shared<DecayChannelsVector>();
      generate_w_boson_decays(+1, w_plus_decays);
    }
    if(!z_decays)
    {
      z_decays = std::make_shared<DecayChannelsVector>();
      generate_z_boson_decays(z_decays);
    }
    if(!higgs_decays)
    {
      higgs_decays = std::make_shared<DecayChannelsVector>();
      generate_h_boson_decays(higgs_decays);
    }
  }

  void generate_w_boson_decays(int charge, std::shared_ptr<DecayChannelsVector>& decay)
  {
    //Leptonic decays
    std::vector<LeptonType> leptons;
    std::vector<QuarkFlavour> quarks;
    if(charge == -1) 
    {
      leptons = {LeptonType::Electron, LeptonType::Muon, LeptonType::Tau};
      quarks = {QuarkFlavour::Anti_Up, QuarkFlavour::Anti_Charm, QuarkFlavour::Anti_Top};
    }
    else
    {
      leptons = {LeptonType::AntiElectron, LeptonType::AntiMuon, LeptonType::AntiTau};
      quarks = {QuarkFlavour::Up, QuarkFlavour::Charm, QuarkFlavour::Top};
    }
     
    //Using template from DecayTemplates. This takes a vector of some members of some enum class, a function
    //to generate another member of the same enum class from each variable in the vector, and a factory function
    //to produce them as arguments. Also takes a function to calculate the branching ratio.
    DecayTemplates::add_decay_channels_for_particle_pairs(leptons, LeptonUtilities::get_corresponding_anti_neutrino,
      [](const auto& flavour) -> std::unique_ptr<Particle> {return factory_lepton(flavour);}, 
      [](const auto&, const auto&) -> double {return w_branching_leptonic_all_flavours;}, 
      decay);
    //Branching ratio defined as above so the template is compatible with the cabibo branching which requires
    //quark flavour arguments.

    //Stop taus re decaying into taus. This can also be implemented to stop muons decaying into muons
    //but muons are considered stable in this assignment. Similarly for top and so on. This would also be
    //possible by at each vertex checking the invariant mass after does not exceed that before (for real
    //particles that is).
    auto& forbidden = decay->back().forbidden_source;
    if(!forbidden)
    {
      forbidden = std::make_unique<std::unordered_set<ParticleUtilities::ParticleIdentifier>>();
    }
    if(charge == -1){forbidden->insert(ParticleUtilities::ParticleIdentifier::Tau);}
    else {forbidden->insert(ParticleUtilities::ParticleIdentifier::AntiTau);}
    
    //Hadronic decays
    DecayTemplates::add_decay_channels_for_particle_pairs(quarks,
      get_quark_w_pairs, [](auto flavour) -> std::unique_ptr<Particle> {return std::make_unique<Quark>(flavour);},
      cabibo_branching, decay);  
  }

  void generate_z_boson_decays(std::shared_ptr<DecayChannelsVector>& decay)
  {
    std::vector<LeptonType> leptons = {LeptonType::Electron, LeptonType::Muon, LeptonType::Tau};
    std::vector<LeptonType> neutrinos= {LeptonType::ElectronNeutrino, LeptonType::MuonNeutrino, LeptonType::TauNeutrino};


    //Utilise template
    DecayTemplates::add_decay_channels_for_particle_pairs(leptons, LeptonUtilities::get_anti_lepton,
      [](const auto& flavour) -> std::unique_ptr<Particle> {return factory_lepton(flavour);},
      [](const auto&, const auto&) -> double{return z_branching_ee;},
      decay);
    
    DecayTemplates::add_decay_channels_for_particle_pairs(neutrinos, LeptonUtilities::get_anti_lepton,
      [](const auto& flavour) -> std::unique_ptr<Particle> {return factory_lepton(flavour);},
      [](const auto&, const auto&) -> double {return z_branching_nunu; },
      decay);

    //^Have to call for neutrinos and other leptons seperately as different branching ratio

    std::vector<QuarkUtilities::QuarkFlavour> quarks = {QuarkFlavour::Up, QuarkFlavour::Down,
      QuarkFlavour::Charm, QuarkFlavour::Strange, QuarkFlavour::Bottom, QuarkFlavour::Top};

    DecayTemplates::add_decay_channels_for_particle_pairs(quarks, QuarkUtilities::get_anti_quark,
      [](const auto& flavour) -> std::unique_ptr<Particle> {return std::make_unique<Quark>(flavour); },
      [](const auto&, const auto&) -> double {return z_branching_qq;},
      decay);
  }


  void generate_h_boson_decays(std::shared_ptr<DecayChannelsVector>& decay)
  {
    //Possible to use templates but only limited number of decays mandated and so this is hard coded
    decay->push_back(DecayUtilities::DecayChannel(
      []()
      {
        std::vector<std::unique_ptr<Particle>> particles;
        particles.push_back(std::make_unique<Photon>());
        particles.push_back(std::make_unique<Photon>());
        return particles;
      },
        h_branching_photon_photon
    ));

    decay->push_back(DecayUtilities::DecayChannel(
      []()
      {
        std::vector<std::unique_ptr<Particle>> particles;
        particles.push_back(std::make_unique<Quark>(QuarkFlavour::Bottom));
        particles.push_back(std::make_unique<Quark>(QuarkFlavour::Anti_Bottom));
        return particles;
      },
         h_branching_bb
    ));

    decay->push_back(DecayUtilities::DecayChannel(
      []()
      {
        std::vector<std::unique_ptr<Particle>> particles;
        particles.push_back(std::make_unique<WBoson>(+1));
        particles.push_back(std::make_unique<WBoson>(-1));
        return particles;
      },
        h_branching_ww
    ));

    decay->push_back(DecayUtilities::DecayChannel(
      []()
      {
        std::vector<std::unique_ptr<Particle>> particles;
        particles.push_back(std::make_unique<ZBoson>());
        particles.push_back(std::make_unique<ZBoson>());
        return particles;
      },
        h_branching_zz
    ));
  }


  std::shared_ptr<DecayChannelsVector> get_w_minus_channels()
  {
    return w_minus_decays;
  }
  
  std::shared_ptr<DecayChannelsVector> get_w_plus_channels()
  {
    return w_plus_decays;
  }

  std::shared_ptr<DecayChannelsVector> get_z_channels()
  {
    return z_decays;
  }

  std::shared_ptr<DecayChannelsVector> get_higgs_channels()
  {
    return higgs_decays;
  }

  std::unique_ptr<Lepton> factory_lepton(const LeptonType& flavour)
  {
    //Factory function for creating lepton objects
    if(LeptonUtilities::check_if_neutrino(flavour)) { return std::make_unique<Neutrino>(flavour); }
    switch(flavour)
    {
    case LeptonType::Electron: return std::make_unique<Electron>(-1);
    case LeptonType::AntiElectron: return std::make_unique<Electron>(1);
    case LeptonType::Muon: return std::make_unique<Muon>(-1);
    case LeptonType::AntiMuon: return std::make_unique<Muon>(1);
    case LeptonType::Tau: return std::make_unique<Tau>(-1);
    case LeptonType::AntiTau: return std::make_unique<Tau>(1);
    default:                               break;
    }
    throw("UNSUPPORTED FLAVOUR FOR FACTORY LEPTON");
  }

  double cabibo_branching(QuarkUtilities::QuarkFlavour quark1, QuarkUtilities::QuarkFlavour quark2)
  {
    //It is less hard coded to instead compute row/column in the CKM matrix by checking each flavour
    //in turn and assigning numbers this way, but provided the user does not change the order of flavours
    //in the enum class this method suits and is much neater.
    static double ckm_matrix[3][3] = 
    {
      {0.97401, 0.22650, 0.00361},
      {0.22636, 0.97320, 0.04053},
      {0.00854, 0.03978, 0.999172}
    };

    int type_q1 = static_cast<int>(quark1);
    int type_q2 = static_cast<int>(quark2);

    if(type_q1 > type_q2) 
    {
      int temp = type_q1;
      type_q1 = type_q2;
      type_q2 = temp;
    }

    type_q1 %= 3;
    type_q2 %= 3;

    double branching_ratio = ckm_matrix[type_q1][type_q2];
    // /9 as 9 hadronic decays
    return branching_ratio*branching_ratio/3 * w_branching_hadronic;
  }

  std::vector<QuarkFlavour> get_quark_w_pairs(QuarkFlavour base_quark)
  {
    //For template calls
    if(base_quark == QuarkFlavour::Up || base_quark == QuarkFlavour::Charm || base_quark == QuarkFlavour::Top)
    {
      return {QuarkFlavour::Anti_Down, QuarkFlavour::Anti_Strange, QuarkFlavour::Anti_Bottom};
    }
    else if(base_quark == QuarkFlavour::Anti_Up || base_quark == QuarkFlavour::Anti_Charm || base_quark == QuarkFlavour::Anti_Top)
    {
      return {QuarkFlavour::Down, QuarkFlavour::Strange, QuarkFlavour::Bottom};
    }
    else
    {
      return {};
    }
  }
}