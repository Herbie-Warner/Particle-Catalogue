//Neutrino.h
//Declares the Neutrino class which is a polymorphism of the Lepton class. Overrides the cloning antiparticle generation,
//function. New private boolean member for isolation variable. Assumes the neutrinos to be massless.
//Herbie Warner 28/04/2024

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<memory>

#include"fermions/Lepton.h"
#include"utilities/LeptonUtilities.h"

class Neutrino : public Lepton
{
private:
  bool interacts_with_detector;
  ParticleUtilities::ParticleIdentifier get_correspondance() const; //To map between particle id and leptonType
public:
  Neutrino(LeptonUtilities::LeptonType flavour, double E, double px, double py, double pz);
  Neutrino(LeptonUtilities::LeptonType flavour);

  ~Neutrino() override = default;
  Neutrino(const Neutrino& other); //Redefine for interacts_with_detector variable
  Neutrino(Neutrino&& other) noexcept;
  Neutrino& operator=(const Neutrino& other);
  Neutrino& operator=(Neutrino&& other) noexcept;

  std::stringstream get_info() const override; //For interaction variable

  void set_interacts_with_detector(bool new_interact) {interacts_with_detector = new_interact;}
  bool get_interacts_with_detector() const {return interacts_with_detector;}

  std::unique_ptr<Particle> clone() const override {return std::make_unique<Neutrino>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;
  
  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif