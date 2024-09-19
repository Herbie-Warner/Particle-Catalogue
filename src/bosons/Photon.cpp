//Photon.cpp
//Defines the member functions of the Photon class which is a polymorphism of the GaugeBoson class. 
//Cloning and antiparticle generator overrided to return correct outputs.
//Herbie Warner 11/05/2024

#include<iostream>

#include"bosons/Photon.h"

#include"utilities/ParticleUtilities.h"

using ParticleUtilities::DecayMode;

Photon::Photon(double E, double px, double py, double pz) : 
  GaugeBoson(DecayMode::Stable, 0,0, E, px, py, pz) {}

Photon::Photon() : GaugeBoson(DecayMode::Stable, 0, 0, 0, 0, 0, 0) {}

std::unique_ptr<Particle> Photon::generate_anti_particle() const
{
  return std::make_unique<Photon>(*this);
}