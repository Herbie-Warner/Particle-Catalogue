//FactoryUtilities.h
//Declares the factory function for all particles.
//Herbie Warner 27/04/2024

#ifndef FACTORYUTILITIES_H
#define FACTORYUTILITIES_H

#include<memory>
#include"core/Particle.h"
#include"utilities/ParticleUtilities.h"

namespace FactoryUtilities
{
  std::unique_ptr<Particle> factory_particle(ParticleUtilities::ParticleIdentifier type);
}

#endif