//DecayChannels.cpp
//Defines the DecayChannels class. Includes functions for perform decay, and print
//all decays for a given particle. Also includes methods for selecting decays based
//on branching ratios using std::discrete_distribution<>.
//Herbie Warner 09/05/2024

#include<iostream>

#include"core/Particle.h"

#include"utilities/DecayChannels.h"
#include"utilities/FactoryUtilities.h"

using ParticleUtilities::DecayMode;
using DecayUtilities::DecayChannel;

//Require source particle to check if its present in a forbidden decay
DecayChannels::DecayChannels(ParticleUtilities::ParticleIdentifier source,
  const std::shared_ptr<DecayChannelsVector>& shared) : shared_channels(shared), source_particle(source) {}

DecayChannels::DecayChannels(ParticleUtilities::ParticleIdentifier source) : 
  shared_channels(nullptr), source_particle(source) {}

DecayChannels::DecayChannels(const DecayChannels& other)
  : instance_channels(other.instance_channels),
  shared_channels(other.shared_channels), source_particle(other.source_particle) {}

DecayChannels& DecayChannels::operator=(const DecayChannels& other) 
{
  if(this != &other) 
  {
    instance_channels = other.instance_channels;
    shared_channels = other.shared_channels;
    source_particle = other.source_particle;
  }
  return *this;
}

DecayChannels::DecayChannels(DecayChannels&& other) noexcept
  : instance_channels(std::move(other.instance_channels)),
  shared_channels(std::move(other.shared_channels)), source_particle(other.source_particle) {}

DecayChannels& DecayChannels::operator=(DecayChannels&& other) noexcept 
{
  if(this != &other) 
  {
    instance_channels = std::move(other.instance_channels);
    shared_channels = std::move(other.shared_channels);
    source_particle = other.source_particle;
  }
  return *this;
}

DecayProducts DecayChannels::produce_decay(const DecayChannelsVector& vector) const
{
  if(vector.size() == 0) {return std::nullopt;}
  std::vector<double> probabilities;

  for(const auto& decay_mode : vector)
  {
    const auto& forbidden = decay_mode.forbidden_source; //Make sure not to produce a forbidden decay
    if(forbidden && forbidden->find(source_particle) != forbidden->end()) {probabilities.push_back(0);} //So discrete distribution still usable
    else {probabilities.push_back(decay_mode.branching_ratio);}
  }

  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
  int index = dist(gen);

  DecayChannel selected_channel = (vector)[index];
  return selected_channel.factory(); //Invoke the lambda
}

DecayProducts DecayChannels::perform_decay_shared() const
{
  if(!shared_channels) {return std::nullopt;}
  return produce_decay(*shared_channels);
}

DecayProducts DecayChannels::perform_decay_instance() const
{
  return produce_decay(instance_channels);
}

void DecayChannels::add_channel(DecayUtilities::DecayChannel channel) 
{ 
  instance_channels.push_back(std::move(channel)); 
}

void DecayChannels::print_all_decays() const
{
  if(shared_channels)
  {
    std::cout<<"SHARED CHANNELS"<<std::endl;
    for(const auto& decay_mode : *shared_channels)
    {
      const auto& forbidden = decay_mode.forbidden_source;
      double branch = decay_mode.branching_ratio;
      if(forbidden && forbidden->find(source_particle) != forbidden->end()) {continue;}
      std::cout<<"Branching ratio: "<<branch<<std::endl;
      auto decays = decay_mode.factory();
      for(const auto& particle : decays)
      {
        particle->display_properties();
      }
      std::cout<<std::endl;
    }
  }
  if(instance_channels.size() != 0)
  {
    std::cout<<"Instance CHANNELS"<<std::endl;
  }

  for(const auto& decay_mode : instance_channels)
  {
    std::cout<<"Branching ratio: "<<decay_mode.branching_ratio<<std::endl;
    auto decays = decay_mode.factory();
    for(const auto& particle : decays)
    {
      particle->display_properties();
    }
    std::cout<<std::endl;
  }
}

size_t DecayChannels::get_total_decay_channels() const 
{
  return (*shared_channels).size() + instance_channels.size();
}