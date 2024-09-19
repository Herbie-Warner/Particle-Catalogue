//WBoson.h
//Declares the WBoson class which is a polymorphism of the Gauge boson class. Overrides the cloning
//and antiparticle generation functions. No new private data members, but has a new private function
//to validate whether the charge is +- 1.
//Herbie Warner 28/04/2024

#ifndef WBOSON_H
#define WBOSON_H

#include<memory>

#include"bosons/GaugeBoson.h"
#include"utilities/ParticleUtilities.h"

static constexpr double wboson_rest_mass_energy = 80377; //MeV

class WBoson : public GaugeBoson
{
private:
  void init_charge(int charge);
  void initialise_decay_channels() override; //To correctly include the shared w decay channel
public:
  WBoson(int charge, double E, double px, double py, double pz);
  WBoson(int charge);
  ~WBoson() override = default; //Use the GaugeBoson destructor
  WBoson(const WBoson& other) = default;
  WBoson(WBoson&& other) noexcept = default;
  WBoson& operator=(const WBoson& other) = default;
  WBoson& operator=(WBoson&& other) noexcept = default;

  std::unique_ptr<Particle> clone() const override {return std::make_unique<WBoson>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif