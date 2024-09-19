//Lepton.h
//Declares the Lepton class which is a polymorphism of the fermion class. Pure virtual functions installed to insure
//class is abstract and so no random  can be lepton generated. In addition Lepton class includes new private members:
//Lepton flavour, and corresponding lepton numbers, thereby requiring updated copy/move semantics.
//Herbie Warner 28/04/2024

#ifndef LEPTON_H
#define LEPTON_H

#include<memory>
#include"fermions/Fermion.h"
#include"utilities/LeptonUtilities.h"
#include"Utilities/ParticleVisitor.h"

class Lepton : public Fermion
{
private:
  std::unique_ptr<LeptonUtilities::LeptonNumber> lepton_number;
  LeptonUtilities::LeptonType lepton_flavour;
public:
  Lepton(const ParticleUtilities::DecayMode& mode, const LeptonUtilities::LeptonType& lep_flavour,
    double charge, double rest_mass, double E, double px, double py, double pz);
  virtual ~Lepton();
  Lepton(const Lepton& other);
  Lepton(Lepton&& other) noexcept;
  Lepton& operator=(const Lepton& other);
  Lepton& operator=(Lepton&& other) noexcept;

  std::stringstream get_info() const override;

  LeptonUtilities::LeptonType get_lepton_flavour() const {return lepton_flavour;}
  const LeptonUtilities::LeptonNumber get_lepton_number() const {return *lepton_number;}

  //pure virtual functions
  virtual std::unique_ptr<Particle> clone() const = 0;
  virtual std::unique_ptr<Particle> generate_anti_particle() const = 0;

  //Insure visitor gets the additional quantum numbers within a lepton (lepton number)
  void accept(ParticleVisitor* visitor) override {visitor->visit_lepton(this);}

  //For correct identification in ParticleContainer
  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::Lepton;}
};

#endif