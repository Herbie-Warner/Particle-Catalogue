//Gluon.h
//Declares the Gluon class which is a polymorphism of the Gauge boson class. Overrides the cloning
//and antiparticle generation functions. Has new private members for colour anti-colour pair, along
//with new functions to set these. Non-neutrality are set using functions from quark utilities
//namespace.
//Herbie Warner 28/04/2024

#ifndef GLUON_H
#define GLUON_H

#include<memory>

#include"bosons/GaugeBoson.h"
#include"utilities/QuarkUtilities.h"

class Gluon : public GaugeBoson
{
private:
  //Anti_colour is not explicitly an anti-colour: only the pair of colour and anti_colour members together,
  //are a non-neutral colour state, and are not necessarily this way around.
  QuarkUtilities::ColourCharge colour;
  QuarkUtilities::ColourCharge anti_colour;
public:
  Gluon(const QuarkUtilities::ColourCharge& col, const QuarkUtilities::ColourCharge& anti_col,
    double E, double px, double py, double pz);
  Gluon(double E, double px, double py, double pz); //To default set colour set
  Gluon();
  ~Gluon() override = default;

  //Updated copy/move semantics to reflect new data members
  Gluon(const Gluon& other);
  Gluon(Gluon&& other) noexcept;
  Gluon& operator=(const Gluon& other);
  Gluon& operator=(Gluon&& other) noexcept;

  std::stringstream get_info() const override; //To include the colours

  QuarkUtilities::ColourCharge get_colour() const {return colour;}
  QuarkUtilities::ColourCharge get_anti_colour() const {return anti_colour;}

  std::unique_ptr<Particle> clone() const override {return std::make_unique<Gluon>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  void set_gluon_colour_state(const QuarkUtilities::ColourCharge& colour,const QuarkUtilities::ColourCharge& anti_colour);
  void set_gluon_colour_state(); //Reset to default

  ParticleUtilities::ParticleIdentifier get_general_type() const override {return ParticleUtilities::ParticleIdentifier::Gluon;}
};

#endif