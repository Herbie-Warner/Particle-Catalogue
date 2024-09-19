//GuageBoson.cpp
//Defines the member functions of the GaugeBoson class which is a polymorphism of the Boson class.
//Cloning as well as antiparticle creation are pure virtual so that GaugeBoson is an abstract class.
//Enforces spin 1
//Herbie Warner 11/05/2024

#include"bosons/GaugeBoson.h"

GaugeBoson::GaugeBoson(const ParticleUtilities::DecayMode& mode, int charge,double rest_mass, double E, double px, double py, double pz) : 
  Boson(mode,1,static_cast<double>(charge), rest_mass, E, px, py, pz) {}