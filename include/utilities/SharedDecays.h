//SharedDecays.h
//As decays are mediated by bosons, and are common to multiple instances this namespace includes the
//constructions and holding of common decays. The idea is to adhere to the vertex structure of decay 
//chains by naturally embedding this nature though intermediate decays. For example a tau upon decay
//will have a shared ptr to a w decay and will then have decay products that spawn from this w decay
//along with the original tau neutrino. This namespace merely holds this shared decays and interactions
//with this ptrs are mediated through the DecayChannels class.
//Herbie Warner 28/04/2024

#ifndef SHAREDDECAYS_H
#define SHAREDDECAYS_H

#include<memory>

#include"fermions/Lepton.h"
#include"utilities/QuarkUtilities.h"

namespace SharedDecays 
{
  std::unique_ptr<Lepton> factory_lepton(const LeptonUtilities::LeptonType& flavour);
  void generate_w_boson_decays(int charge, std::shared_ptr<DecayChannelsVector>& decay);
  void generate_z_boson_decays(std::shared_ptr<DecayChannelsVector>& decay);
  void generate_h_boson_decays(std::shared_ptr<DecayChannelsVector>& decay);

  void initialise_shared_decay_channels();

  std::shared_ptr<DecayChannelsVector> get_w_minus_channels();
  std::shared_ptr<DecayChannelsVector> get_w_plus_channels();
  std::shared_ptr<DecayChannelsVector> get_z_channels();
  std::shared_ptr<DecayChannelsVector> get_higgs_channels();

  double cabibo_branching(QuarkUtilities::QuarkFlavour quark1, QuarkUtilities::QuarkFlavour quark2);
  std::vector<QuarkUtilities::QuarkFlavour> get_quark_w_pairs(QuarkUtilities::QuarkFlavour base_quark);
}

#endif