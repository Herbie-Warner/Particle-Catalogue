//DecayUtilities.h
//Utility namespace of DecayUtilities for propagating and validating decay chains given an initial state. 
//Declaes the DecayChannel struct that contains all the decay information.
//Herbie Warner 25/04/2024

#ifndef DECAYUTILITIES_H
#define DECAYUTILITIES_H

#include<vector>
#include<memory>
#include<random>
#include<functional>
#include<unordered_set>

#include"utilities/ParticleUtilities.h"

class Particle; //Foward declaration to break circular dependence

namespace DecayUtilities 
{
  using ParticleFactory = std::function<std::vector<std::unique_ptr<Particle>>()>;
  struct DecayChannel 
  {
    ParticleFactory factory; //Function that when called executes and produces the particles
    double branching_ratio;

    //Some decays are valid for some but not others. E.g generally a W boson can decay into a τ ν_τ but not
    //in the case of when the W boson was produces by a τ. Similarly for μ. So to have shared decay, i.e have
    //decay channels for the W boson that the tau uses, it is necessary to indicate the tau may not decay
    //via this mode. This is a ptr to an unordered set as generally, in this project, there are no forbidden
    //sources and so it useful to have this automatically be a nullptr than to hold an empty set.
    std::unique_ptr<std::unordered_set<ParticleUtilities::ParticleIdentifier>> forbidden_source;

    DecayChannel(ParticleFactory factor, double branch);
    ~DecayChannel();

    DecayChannel(const DecayChannel& other);
    DecayChannel(DecayChannel&&) noexcept;
    DecayChannel& operator=(const DecayChannel& other);
    DecayChannel& operator=(DecayChannel&&) noexcept;

    std::unique_ptr<DecayChannel> clone() const;
  };

  bool validate_decay(const std::vector<std::unique_ptr<Particle>>& initial_state,
    const std::vector<std::unique_ptr<Particle>>& final_state); //For validating for several particles either side
  bool validate_decay(Particle* initial_state, const std::vector<std::unique_ptr<Particle>>& final_state); //For single particle decay
  
  //Distribute the initial four momentum amongst decay products
  void distribute_four_momentum(const Particle& source, std::vector<std::unique_ptr<Particle>>& products);
}

#endif