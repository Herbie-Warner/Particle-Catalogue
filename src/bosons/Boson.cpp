//Boson.cpp
//Defines the member functions of the Boson class which is a polymorphism of the Particle class. Exists
//for distinction between particle types. Enforces integer spin even if the user does not enter such. This
//is done using static_cast<int>.
//Herbie Warner 11/05/2024

#include"bosons/Boson.h"

Boson::Boson(const ParticleUtilities::DecayMode mode, int new_spin, double charge, double rest_mass,
  double E, double px, double py, double pz) :
  Particle(mode,static_cast<double>(new_spin),charge, rest_mass, E, px, py, pz) {}