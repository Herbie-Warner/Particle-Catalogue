//Fermion.cpp
//Defines the member functions of the Fermion class which is a polymorphism of the Particle class. Only
//exists for distinction of particle types.
//Herbie Warner 11/05/2024

#include"fermions/Fermion.h"

Fermion::Fermion(const ParticleUtilities::DecayMode mode, double spin, double charge,
  double rest_mass, double E, double px, double py, double pz) :
  Particle(mode, spin, charge, rest_mass, E, px, py, pz) {} 