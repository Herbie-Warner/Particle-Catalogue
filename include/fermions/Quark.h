//Quark.h
//Declares the Quark class which is a polymorphism of the fermion class. Quark class includes new private members:
//Quark flavour, and colour. As no quarks in this assignment have unique properties every quark can be created by
//calling this quark class with a particular flavour. QuarkUtilities will then discern the mass, and charge, and
//colour/Anti-Colour from the users choice, enabling a simpler interface and correct property inforcement.
//Herbie Warner 28/04/2024

#ifndef QUARK_H
#define QUARK_H

#include<memory>
#include<sstream>

#include"fermions/Fermion.h"

#include"utilities/QuarkUtilities.h"

class Quark : public Fermion
{
private:
  QuarkUtilities::QuarkFlavour flavour;
  QuarkUtilities::ColourCharge colour;
  double baryon_number;
  void init_baryon_number();
  void init_colour();

  ParticleUtilities::ParticleIdentifier get_correspondance() const; //For correspondance between quark flavour and particle identifier
public:
  Quark(const QuarkUtilities::QuarkFlavour& flav, const QuarkUtilities::ColourCharge& col, double E, double px, double py, double pz);
  Quark(const QuarkUtilities::QuarkFlavour& flav);
  ~Quark() override = default;

  Quark(const Quark& other); //Needs to be defined as new fields colour and flavour
  Quark(Quark&& other) noexcept;
  Quark& operator=(const Quark& other);
  Quark& operator=(Quark&& other) noexcept;

  QuarkUtilities::QuarkFlavour get_quark_flavour() const {return flavour;}
  QuarkUtilities::ColourCharge get_quark_colour() const {return colour;}
  double get_baryon_number() const {return baryon_number;}

  void set_quark_colour(QuarkUtilities::ColourCharge new_colour);
 
  std::unique_ptr<Particle> clone() const override {return std::make_unique<Quark>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  std::stringstream get_info() const override; //To include new data about colour

  //Insure visitor gets the additional quantum numbers within a quark (baryon number-ignoring colour)
  void accept(ParticleVisitor* visitor) override {visitor->visit_quark(this);}

  //For correct identification in ParticleContainer
  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif