//ParticleVisitor.h
//Pure virtual base class defining interface for visiting a particle. Will allow checking of particle properties
//for all types of particles with having to downcast everytime e.g 
//const Lepton* lepton_ptr = dynamic_cast<const Lepton*>(particle.get());
//if(lepton_ptr != nullptr)...
//and similarly for all other types. This is the visitor pattern.
//The forward declarations remove the circular dependence and are permitted completely as this is a purely
//virtual class.
//Herbie Warner 28/04/2024

#ifndef PARTICLE_VISITOR_H
#define PARTICLE_VISITOR_H

//Forward declaration to remove circular dependence
class Particle;
class Lepton;
class Quark;

class ParticleVisitor 
{
public:
  virtual ~ParticleVisitor() {}
  //All unique quantum numbers of interest are expressed in these three base classes.
  virtual void visit_particle(Particle* particle) = 0;
  virtual void visit_lepton(Lepton* lepton) = 0;
  virtual void visit_quark(Quark* quark) = 0;
};
#endif