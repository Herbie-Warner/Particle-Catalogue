//Boson.h
//Declares the abstract Boson class which is a polymorphism of the Particle class. Includes relevant overridden functions
//for virtuality. This class exists for clear delineation between fermion and boson objects, and, if the user wanted
//mutable spins, this where integer spins can be inforced. E.g if they wanted to create more exotic particles like
//magnons.
//Herbie Warner 28/04/2024

#ifndef BOSON_H
#define BOSON_H

#include"core/particle.h"

class Boson : public Particle
{
public:
  Boson(const ParticleUtilities::DecayMode mode, int spin,
    double charge,double rest_mass, double E, double px, double py, double pz);

  ~Boson() override = default;
  Boson(const Boson& other) = default;
  Boson(Boson&& other) noexcept = default;
  Boson& operator=(const Boson& other) = default;
  Boson& operator=(Boson&& other) noexcept = default;

  std::unique_ptr<Particle> clone() const override = 0;

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::Boson;}
};

#endif