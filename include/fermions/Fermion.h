//Fermion.h
//Declares the abstract Fermion class which is a polymorphism of the particle class. Exists
//for clearer distinction between particle types. User cannot generate custom particles so
//no spin validation is required, but upon extension this is where one would implement
//spin 1/2 validation.
//Herbie Warner 28/04/2024

#ifndef FERMION_H
#define FERMION_H

#include"core/Particle.h"

class Fermion : public Particle
{
public:
  Fermion(const ParticleUtilities::DecayMode mode, double spin,
    double charge,const double rest_mass, double E, double px, double py, double pz);
  ~Fermion() override = default;

  //No new data members so use default from base Particle class
  Fermion(const Fermion& other) = default;
  Fermion(Fermion&& other) noexcept = default;
  Fermion& operator=(const Fermion& other) = default;
  Fermion& operator=(Fermion&& other) noexcept = default;

  std::unique_ptr<Particle> clone() const override = 0;
  std::unique_ptr<Particle> generate_anti_particle() const override = 0;

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::Fermion;}
};

#endif