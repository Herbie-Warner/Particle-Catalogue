//QuantumNumberVisitor.h
//Polymorphism of ParticleVisitor class. Visits particles and aggregates the following quantum
//numbers of interest: spin, charge, lepton number, baryon number. Allows removal of downcasting
//for every check, and removal of circular dependence in decay functions that are both called, and
//rely on given particle types. Instance of the visitor pattern. Can easily upgrade to also consider
//CP.
//Herbie Warner 28/04/2024

#ifndef QUANTUM_NUMBER_VISITOR_H
#define QUANTUM_NUMBER_VISITOR_H

#include"utilities/ParticleVisitor.h"
#include"utilities/LeptonUtilities.h"

class QuantumNumberVisitor : public ParticleVisitor 
{
private:
  double total_charge = 0.0;
  double total_spin = 0.0;
  LeptonUtilities::LeptonNumber lepton_number; //Defaults to (0,0,0)
  double total_baryon_number = 0.0;
public:
  //No required user defined constructor as setting all values for every instance of this class.
  void visit_particle(Particle* particle) override;
  void visit_lepton(Lepton* lepton) override;
  void visit_quark(Quark* quark) override;

  double get_total_charge() const {return total_charge;}
  double get_total_spin() const {return total_spin;}
  LeptonUtilities::LeptonNumber get_total_lepton_numbers() const {return lepton_number;}
  double get_total_baryon_number() const {return total_baryon_number;}

  void display_quantum_numbers() const;

  bool spin_validation(double new_spin) const; //As only total fermion number needs to be preserved
  bool operator==(const QuantumNumberVisitor& other) const; //Check if another state is equivalent to this
};

#endif