//GaugeBoson.h
//Declares the GaugeBoson class which is a polymorphism of the Boson class. Pure virtual functions installed to insure
//class is abstract and so no random gauge boson can be generated. Could demote from abstract to create new gauge bosons
//such as graviton for example. Enforces spin-1 on all derived gauge bosons.
//Herbie Warner 28/04/2024

#ifndef GAUGEBOSON_H
#define GAUGEBOSON_H

#include"Boson.h"
#include"utilities/ParticleUtilities.h"

class GaugeBoson : public Boson
{
public:
  GaugeBoson(const ParticleUtilities::DecayMode& mode, int charge, 
    double rest_mass, double E, double px, double py, double pz);
  ~GaugeBoson() override = default;
  GaugeBoson(const GaugeBoson& other) = default;
  GaugeBoson(GaugeBoson&& other) noexcept = default;
  GaugeBoson& operator=(const GaugeBoson& other) = default;
  GaugeBoson& operator=(GaugeBoson&& other) noexcept = default;

  //pure virtual functions for abstraction
  virtual std::unique_ptr<Particle> clone() const = 0;

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::GaugeBoson;}
};

#endif