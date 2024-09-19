//ZBoson.h
//Declares the ZBoson class which is a polymorphism of the Gauge boson class. Overrides the cloning
//and antiparticle generation functions. No new private data members so uses default copy/move semantics.
//Herbie Warner 28/04/2024

#ifndef ZBOSON_H
#define ZBOSON_H

#include<memory>
#include"bosons/GaugeBoson.h"

static constexpr double zboson_rest_mass_energy = 91200; //(MeV)

class ZBoson : public GaugeBoson
{
private:
  void initialise_decay_channels() override;
public:
  ZBoson(double E, double px, double py, double pz);
  ZBoson();
  ~ZBoson() override = default;
  ZBoson(const ZBoson& other) = default;
  ZBoson(ZBoson&& other) noexcept = default;
  ZBoson& operator=(const ZBoson& other) = default;
  ZBoson& operator=(ZBoson&& other) noexcept = default;

  std::unique_ptr<Particle> clone() const override {return std::make_unique<ZBoson>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::ZBoson; }
};

#endif