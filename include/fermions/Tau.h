//Tau.h
//Declares the Tau class which is a polymorphism of the Lepton class. Used to make both tau and anti tau by
//charge +- 1. Decay inbuilt overridden here to append the tau neutrino to the decay mode.
//Herbie Warner 25/04/2024

#ifndef TAU_H
#define TAU_H

#include<memory>
#include"fermions/Lepton.h"

class Tau : public Lepton
{
private:
  void initialise_decay_channels() override;
public:
  Tau(int charge, double E, double px, double py, double pz);
  Tau(int charge);
  ~Tau() override = default;
  Tau(const Tau& other) = default; //No new data members
  Tau(Tau&& other) noexcept = default;
  Tau& operator=(const Tau& other) = default;
  Tau& operator=(Tau&& other) noexcept = default;
  
  std::unique_ptr<Particle> clone() const override {return std::make_unique<Tau>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  DecayProducts decay_inbuilt() const override; //Override to add a tau neutrino
  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif