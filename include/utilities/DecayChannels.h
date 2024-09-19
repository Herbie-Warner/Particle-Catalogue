//DecayChannels.h
//Declares the DecayChannels class: Class to hold all the decay channels of a given particle using DecayUtilities
//struct DecayChannel. This struct declared outside class so user could easily add more decay channels if they wish,
//and to mitigate circular dependencies. Includes both an instance specific channels, which is empty until the user
//adds decays, and shared decays which will be common to all instances. This is for example taus and w bosons sharing weak
//decays for overhead minimisation and code centralisation.
//Herbie Warner 25/04/2024

#ifndef DECAY_CHANNELS_H
#define DECAY_CHANNELS_H

#include<vector>
#include<memory>
#include<optional>

#include"utilities/DecayUtilities.h"
#include"utilities/ParticleUtilities.h"

typedef std::vector<DecayUtilities::DecayChannel> DecayChannelsVector;
typedef std::optional<std::vector<std::unique_ptr<Particle>>> DecayProducts;

class DecayChannels 
{
private:
  DecayChannelsVector instance_channels;
  std::shared_ptr<const DecayChannelsVector> shared_channels; //Declared const in argument so not modifiable
  ParticleUtilities::ParticleIdentifier source_particle; //Source to check forbidden sources
  DecayProducts produce_decay(const DecayChannelsVector& vector) const;

  //The general decay logic is quasi real interaction logic with some simplifications to allow hard coding
  //for the limitted requested decay types. For example in tau decays, which decay via a w boson, they decay
  //first into a neutrino, and then get a w decay from the shared channels which points to all w decays. In
  //larger applications where one only considers final state particles and wishes to propagate down the entire
  //chain, instead I would have the tau decay into a neutrino and a w, then check the stability of each, and 
  //decay further down the chain. However to allow final state particles like W bosons in Higgs decays a less
  //this method is chosen is required. One pitfall of this is having to tell the tau not to decay into another
  //tau and two neutrinos. This is prevented by a forbidden source member in DecayUtilities::DecayChannel.

public:
  DecayChannels(ParticleUtilities::ParticleIdentifier source); //Set shared to null
  DecayChannels(ParticleUtilities::ParticleIdentifier source, const std::shared_ptr<DecayChannelsVector>& shared);
  ~DecayChannels() = default;
  
  DecayChannels(const DecayChannels& other);
  DecayChannels& operator=(const DecayChannels& other);
  DecayChannels(DecayChannels&& other) noexcept;
  DecayChannels& operator=(DecayChannels&& other) noexcept;

  void set_shared_channels(const std::shared_ptr<DecayChannelsVector>& shared) {shared_channels = shared;}

  void add_channel(DecayUtilities::DecayChannel channel); //Adds to instance specific

  DecayProducts perform_decay_instance() const;
  DecayProducts perform_decay_shared() const;
  
  void print_all_decays() const;
  size_t get_total_decay_channels() const;
};

#endif