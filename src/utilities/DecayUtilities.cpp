//DecayUtilities.cpp
//Defines the decay utilities namespace. Includes functions for distributing four momentum among offspring from original
//state if it is a two body decay. Includes implementation for the DecayChannel struct. Includes function to check if
//a states initial quantum numbers are the same as its final to validate user defined decays.
//Herbie Warner 09/05/2024

#include<iostream>
#include<cmath>

#include"core/Particle.h"
#include"core/FourVector.h"

#include"utilities/DecayUtilities.h"
#include"utilities/QuantumNumberVisitor.h"


namespace DecayUtilities
{
  bool validate_decay(const std::vector<std::unique_ptr<Particle>>& initial_state,
    const std::vector<std::unique_ptr<Particle>>& final_state)
  {
    QuantumNumberVisitor initial_numbers;
    for(const auto& particle : initial_state)
    {
      particle->accept(&initial_numbers);
    }

    QuantumNumberVisitor  final_numbers;
    for(const auto& particle : final_state)
    {
      particle->accept(&final_numbers);
    }
    bool equailty = initial_numbers == final_numbers;

    if(!equailty)
    {
      std::cout<<"INITIAL ";
      initial_numbers.display_quantum_numbers();
      std::cout<<std::endl;
      std::cout<<"FINAL ";
      final_numbers.display_quantum_numbers();
      std::cout<<std::endl;

    }
    return equailty;
  }

  bool validate_decay(Particle* initial_state, const std::vector<std::unique_ptr<Particle>>& final_state)
  {
    QuantumNumberVisitor initial_numbers;
    initial_state->accept(&initial_numbers);
    QuantumNumberVisitor  final_numbers;
    for(const auto& particle : final_state)
    {
      particle->accept(&final_numbers);
    }
    bool equailty = initial_numbers == final_numbers;

    if(!equailty) //Only display if it is not valid to show the quantum number violation
    {
      std::cout<<"INITIAL ";
      initial_numbers.display_quantum_numbers();
      std::cout<<std::endl;
      std::cout<<"FINAL ";
      final_numbers.display_quantum_numbers();
      std::cout<<std::endl;

    }
    return equailty;
  }

  void distribute_four_momentum(const Particle& source, std::vector<std::unique_ptr<Particle>>& products)
  {
    if(products.size() != 2) {return;} //Method only works for 2 products as too many dof in three body decays

    double rest_mass_0 = source.get_rest_mass();
    double rest_mass_1 = products[0]->get_rest_mass();
    double rest_mass_2 = products[1]->get_rest_mass();
    
    if(rest_mass_0 <= rest_mass_1 + rest_mass_2) {return;} //Method only works if particles are non-virtual in source rest frame
    
    double energy_1 = (std::pow(rest_mass_0, 2) + std::pow(rest_mass_1, 2) - std::pow(rest_mass_2, 2))/(2*rest_mass_0);
    double momentum_1 = std::sqrt(std::pow(energy_1,2) - std::pow(rest_mass_1,2));

    double energy_2 = std::pow(momentum_1, 2) + std::pow(rest_mass_2, 2);

    products[0]->set_four_momentum(energy_1, momentum_1, 0, 0);
    products[1]->set_four_momentum(energy_2, -momentum_1, 0, 0);
    
    FourVector initial = source.get_four_vector();
    double beta_x, beta_y, beta_z = 0;
    initial.get_boost_to_lab_frame(beta_x, beta_y, beta_z);

    products[0]->boost(-beta_x, -beta_y, -beta_z);
    products[1]->boost(-beta_x, -beta_y, -beta_z);
  }

  //DecayChannel implementation
  DecayChannel::DecayChannel(ParticleFactory factor, double branch)
    : factory(std::move(factor)), branching_ratio(branch), forbidden_source(nullptr) {}

  DecayChannel::~DecayChannel() = default;

  DecayChannel::DecayChannel(const DecayChannel& other)
    : factory(other.factory), branching_ratio(other.branching_ratio) 
  {
    if(other.forbidden_source) 
    {
      forbidden_source = std::make_unique<std::unordered_set<ParticleUtilities::ParticleIdentifier>>(*other.forbidden_source);
    }
  }

  DecayChannel::DecayChannel(DecayChannel&&) noexcept = default;

  DecayChannel& DecayChannel::operator=(const DecayChannel& other) 
  {
    if(this != &other) 
    {
      factory = other.factory;
      branching_ratio = other.branching_ratio;
      if(other.forbidden_source) 
      {
        forbidden_source = std::make_unique<std::unordered_set<ParticleUtilities::ParticleIdentifier>>(*other.forbidden_source);
      }
      else 
      {
        forbidden_source = nullptr;
      }
    }
    return *this;
  }

  DecayChannel& DecayChannel::operator=(DecayChannel&&) noexcept = default;

  std::unique_ptr<DecayChannel> DecayChannel::clone() const 
  {
    auto cloned_channel = std::make_unique<DecayChannel>(factory, branching_ratio);
    if(forbidden_source) 
    {
      cloned_channel->forbidden_source = std::make_unique<std::unordered_set<ParticleUtilities::ParticleIdentifier>>(*forbidden_source);
    }
    return cloned_channel;
  }
}