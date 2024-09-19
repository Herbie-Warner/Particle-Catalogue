//Photon.h
//Declares the Photon class which is a polymorphism of the Gauge boson class. Overrides the cloning
//and antiparticle generation functions. Has no new private data members so using default copy/move
//semantics and destructor (the GaugeBoson defined ones).
//Herbie Warner 28/04/2024

#ifndef PHOTON_H
#define PHOTON_H

#include<memory>
#include"bosons/GaugeBoson.h"

class Photon : public GaugeBoson
{
public:
  Photon(double E, double px, double py, double pz);
  Photon();
  ~Photon() override = default;
  Photon(const Photon& other) = default;
  Photon(Photon&& other) noexcept = default;
  Photon& operator=(const Photon& other) = default;
  Photon& operator=(Photon&& other) = default;

  std::unique_ptr<Particle> clone() const override {return std::make_unique<Photon>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::Photon;}
};

#endif