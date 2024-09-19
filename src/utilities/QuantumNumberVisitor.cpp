//QuantumNumberVisitor.cpp
//Defines the QuantumNumberVisitor class functions including necessary getters, and the visit methods themselves.
//Visitor pattern.
//Herbie Warner 09/05/2024

#include<iostream>

#include"core/Particle.h"

#include"fermions/Lepton.h" //Can include without any dependency issues due to this being derived class of ParticleVisitor
#include"fermions/Quark.h"

#include"utilities/QuantumNumberVisitor.h"

void QuantumNumberVisitor::visit_particle(Particle* particle) 
{
  //Can easily upgrade to consider CP as well
  if(particle) 
  {
    total_charge += particle->get_charge();
    total_spin += particle->get_spin();
  }
}

void QuantumNumberVisitor::visit_lepton(Lepton* lepton) 
{
  if(lepton) 
  {
    lepton_number += (lepton->get_lepton_number());
    visit_particle(lepton); //Accumulate the spin and charge also
  }
}

void QuantumNumberVisitor::visit_quark(Quark* quark) 
{
  if(quark) 
  {
    total_baryon_number += quark->get_baryon_number();
    visit_particle(quark);
  }
}

void QuantumNumberVisitor::display_quantum_numbers() const
{
  std::cout<<"SYSTEM: Total charge: "<<total_charge<<", Total spin: "<<total_spin<<", Total baryon number: "
   <<total_baryon_number<<", ";
  lepton_number.display_lepton_numbers();
}

bool QuantumNumberVisitor::spin_validation(double new_spin) const
{
  //As the exact equality of spin of particles does not count for equality, checks if system goes from spin 1/2 -> spin 1 
  double current_spin = total_spin;
  current_spin *= 2;
  int int_current_spin = static_cast<int>(current_spin);
  new_spin *= 2;
  int int_new_spin = static_cast<int>(new_spin);

  return (int_new_spin % 2) == (int_current_spin % 2);
}

bool QuantumNumberVisitor::operator==(const QuantumNumberVisitor& other) const {
  return total_charge == other.total_charge &&
    spin_validation(other.get_total_spin()) &&
    lepton_number == other.lepton_number && //lepton_number == defined with lepton class
    total_baryon_number == other.total_baryon_number;
}