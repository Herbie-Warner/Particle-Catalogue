//ParticleCatalogue.cpp
//This file is the main entry point for the Particle Catalogue project, which manages a catalogue
//of standard model particles. It demonstrates functionalities such as particle initialisation,
//decay processes, and momentum distribution among particles. The procedure of main is as follows:
// • Initialise shared decays and inheritance map for the container
// • Create container holding all standard model particles
// • Demonstrate functionality of the codebase
//Herbie Warner 9/05/2024

#include<iostream>
#include<string>
#include<memory>
#include<vector>

//Core
#include"core/FourVector.h"
#include"core/Particle.h"
#include"core/ParticleContainer.h"

//Utilities
#include"utilities/ParticleUtilities.h"
#include"utilities/DecayUtilities.h"
#include"utilities/FactoryUtilities.h"
#include"utilities/LeptonUtilities.h"
#include"utilities/SharedDecays.h"

//fermions
#include"fermions/Electron.h"
#include"fermions/Neutrino.h"
#include"fermions/Muon.h"
#include"fermions/Tau.h"
#include"fermions/Quark.h"

//bosons
#include"bosons/Gluon.h"
#include"bosons/HiggsBoson.h"
#include"bosons/WBoson.h"
#include"bosons/Photon.h"
#include"bosons/ZBoson.h"

//Useful aliases
using QuarkUtilities::QuarkFlavour;
using QuarkUtilities::ColourCharge;
using LeptonUtilities::LeptonType;
using ParticleUtilities::ParticleIdentifier;
using ParticleUtilities::DecayMode;

void print(double number)
{
  std::cout << number << std::endl;
}

void print(std::string string, double number)
{
  std::cout << string << number << std::endl;
}

void print(std::string string)
{
  std::cout << string << std::endl;
}

void print()
{
  std::cout << "-------------" << std::endl;
}

void create_standard_model_particles(ParticleContainer& container)
{
  //Create with some random four momentum and four momentum function will correct for rest mass consistency
  //Demonstrates how four momentum is corrected

  //Quarks
  container.add_particle<Quark>(QuarkFlavour::Up, ColourCharge::Blue, 30, 5, 4, 2);
  container.add_particle<Quark>(QuarkFlavour::Down, ColourCharge::Red, 30, 30, 3, 1);
  container.add_particle<Quark>(QuarkFlavour::Charm, ColourCharge::Green, 5, 3, 4, 2);
  container.add_particle<Quark>(QuarkFlavour::Strange, ColourCharge::Blue, 1, 5, 6, 2);
  container.add_particle<Quark>(QuarkFlavour::Top, ColourCharge::Green, 50, 40, 30, 1);
  container.add_particle<Quark>(QuarkFlavour::Bottom, ColourCharge::Red, 265, 100, 3, 1);

  //Anti Quarks
  container.add_particle<Quark>(QuarkFlavour::Anti_Up, ColourCharge::Anti_Green, 900, 86, 4, 100);
  container.add_particle<Quark>(QuarkFlavour::Anti_Down, ColourCharge::Anti_Blue, 50, 30, 31, 25);
  container.add_particle<Quark>(QuarkFlavour::Anti_Charm, ColourCharge::Anti_Green, 1000, 3, 4, 2);
  container.add_particle<Quark>(QuarkFlavour::Anti_Strange, ColourCharge::Anti_Red, 1, 0, 0, 0);
  container.add_particle<Quark>(QuarkFlavour::Anti_Top);
  container.add_particle<Quark>(QuarkFlavour::Anti_Bottom, ColourCharge::Anti_Blue, 1005, 100, 900, 10);

  //Leptons
  container.add_particle<Electron>(+1, 42, 41, 40, 39);
  container.add_particle<Electron>(-1, 600, 40, 100, 3);

  container.add_particle<Muon>(+1, 30, 1, 5, 29);
  container.add_particle<Muon>(-1, 3, 40, 100, 1000);

  container.add_particle<Tau>(+1, 100, 10000, 10000, 1000);
  container.add_particle<Tau>(-1, 600, 2, 100, 3);

  container.add_particle<Neutrino>(LeptonType::AntiElectronNeutrino, 60, 60, 0, 0);
  container.add_particle<Neutrino>(LeptonType::AntiMuonNeutrino, 4, 3, 2, 1);
  container.add_particle<Neutrino>(LeptonType::AntiTauNeutrino, 0, 40, 0, 0);
  container.add_particle<Neutrino>(LeptonType::ElectronNeutrino, 50, 60, 70, 0);
  container.add_particle<Neutrino>(LeptonType::MuonNeutrino, 0, 60, 0, 1000);
  container.add_particle<Neutrino>(LeptonType::TauNeutrino);

  //Gauge Bosons
  container.add_particle<WBoson>(+1, 0, 0, 0, 4e5);
  container.add_particle<WBoson>(-1, 8e6, 2e7, 0, 0);
  container.add_particle<Gluon>();
  container.add_particle<Photon>(4e6, 9e8, 0, 0);
  container.add_particle<ZBoson>(9e8, 4e10, 0, 0);

  //Scalar Bosons
  container.add_object(std::make_shared<HiggsBoson>()); //Other method for adding a particle
}

void demonstrate_container_functionality(const ParticleContainer& container)
{
  //Get all the leptons
  auto leptons = container[ParticleIdentifier::Lepton];
  print("Number of leptons in standard model container: ", leptons.size());

  //Print number of z bosons in container
  print("Number of z bosons in standard model container: ", container.size(ParticleIdentifier::ZBoson));

  //Print total four momentum of all the leptons
  print("Lepton subcontainer total four momentum");
  leptons.get_total_momentum().display_four_vector();

  //Get vector of shared pointers of all gauge bosons
  std::vector<std::shared_ptr<Particle>> gauge_boson_vector = container.get_particles_of_type(ParticleIdentifier::GaugeBoson);
}

void demonstrate_input_checking()
{
  //Four momentum input checking done above. Some other possible bad inputs.
  Gluon glu{ ColourCharge::Blue, ColourCharge::Green, 10, 5, 1, 1 };
  glu.display_properties();

  //Use try/except to not stop code from running
  try
  {
    Neutrino electron{ LeptonType::Electron };
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr << "Caught exception: " << error.what() << std::endl;
  }

  try
  {
    auto fermion = FactoryUtilities::factory_particle(ParticleIdentifier::Fermion);
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr << "Caught exception: " << error.what() << std::endl;
  }
}

void demonstrate_how_to_add_decays()
{
  Muon muon{ -1 };

  //Add invalid decay 
  auto invalid_muon_decay = { ParticleIdentifier::MuonNeutrino, ParticleIdentifier::Electron, ParticleIdentifier::ElectronNeutrino };
  muon.add_decay_channel(invalid_muon_decay, 0.5);
  print(" ");
  //Add two valid decays via both syntaxes
  auto valid_muon_decay = { ParticleIdentifier::MuonNeutrino, ParticleIdentifier::Electron, ParticleIdentifier::AntiElectronNeutrino };
  muon.add_decay_channel(valid_muon_decay, 0.5);

  //If user wants to set some specific properties and is familiar with lambda syntax
  muon.add_decay_channel(DecayUtilities::DecayChannel([]() -> std::vector<std::unique_ptr<Particle>>
    {
      std::vector<std::unique_ptr<Particle>> particles;
      particles.push_back(std::make_unique<Quark>(QuarkFlavour::Anti_Up, ColourCharge::Anti_Green, 20, 5, 2, 3));
      particles.push_back(std::make_unique<Quark>(QuarkFlavour::Down, ColourCharge::Blue, 90, 4, 100, 10));
      particles.push_back(std::make_unique<Neutrino>(LeptonType::MuonNeutrino, 45, 44, 43, 42));
      return particles;
    },
    1 //Branching
  ));

  //Branching is only relative to eachother and does need to total to unity
  muon.set_decay_mode(DecayMode::Unstable);
  print(" ");
  muon.decay_with_print_instance_specific();
  print(" ");
  muon.decay_with_print_inbuilt();
  print(" ");
  //All muon decays
  print("All muon decays");
  muon.print_all_decays();
}

void demonstrate_some_paritcle_properties()
{
  Gluon gluon;
  gluon.display_properties();
  auto anti_gluon = gluon.generate_anti_particle();
  anti_gluon->display_properties();

  WBoson w_plus{ +1 };
  w_plus.set_four_momentum(3, 2, 1, -5);
  w_plus.display_properties();

  Photon photon{ 5000, 4000, 3000, 2000 };
  std::stringstream photon_info = photon.get_info();
  print(photon_info.str());

  print();
  print("Higgs decays");
  HiggsBoson higgs;
  higgs.print_all_decays();
}

void demonstrate_w_plus_decays()
{
  print("W plus decays");
  WBoson w_minus{ +1 };
  w_minus.add_decay_channel(DecayUtilities::DecayChannel([]() -> std::vector<std::unique_ptr<Particle>>
    {
      std::vector<std::unique_ptr<Particle>> particles;
      particles.push_back(std::make_unique<Quark>(QuarkFlavour::Top));
      particles.push_back(std::make_unique<Quark>(QuarkFlavour::Anti_Bottom));
      particles.push_back(std::make_unique<Photon>(10, 10, 5, 2));
      return particles;
    },
    1.0 //Branching
  ));

  w_minus.print_all_decays();
}

void demonstrate_four_momentum_distribution()
{
  WBoson w_minus{ -1, 3e5, 2e6, 900, 1e5 };
  auto products = w_minus.decay_inbuilt();
  DecayUtilities::distribute_four_momentum(w_minus, products.value());

  w_minus.display_properties();
  for(const auto& particle : products.value())
  {
    particle->display_properties();
  }
  print();
  HiggsBoson higgs{ 5e9, 4e5, -8e10, -6e7 };
  print("SOURCE PARTICLE");
  products = higgs.decay_inbuilt();
  higgs.display_properties();

  print("DECAY PRODUCTS");
  for(const auto& particle : products.value())
  {
    particle->display_properties();
  }
}

void demonstrate_copy_move_semantics()
{
  WBoson original = WBoson(+1, 1e5, 1e6, 1e7, 1e8);
  auto copied = original;
  original.display_properties();
  copied.display_properties();

  original.set_four_momentum(80377, 0, 0, 1);
  auto moved = std::move(original);
  moved.display_properties();

  Gluon glu{ ColourCharge::Anti_Blue, ColourCharge::Green, 100, 8, 6, 0 };
  Gluon glu_copy;
  glu_copy = std::move(glu);
  glu_copy.display_properties();
  glu_copy.generate_anti_particle()->display_properties();

}

int main()
{
  print("START OF MAIN");
  print();
  //Initialisations
  ParticleContainer::initialize_inheritance();
  SharedDecays::initialise_shared_decay_channels();

  ParticleContainer standard_model_particles;
  create_standard_model_particles(standard_model_particles);
  standard_model_particles.print_all();
  print();

  demonstrate_container_functionality(standard_model_particles);
  print();

  demonstrate_input_checking();
  print();

  demonstrate_how_to_add_decays();
  print();

  demonstrate_w_plus_decays();
  print();

  demonstrate_some_paritcle_properties();
  print();

  demonstrate_four_momentum_distribution();
  print();

  demonstrate_copy_move_semantics();
  print();

  print("END OF MAIN");
  return 0;
}