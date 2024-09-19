//Gluon.cpp
//Defines the member functions of the Gluon class which is a polymorphism of the GaugeBoson class.
//Cloning and antiparticle generator overrided to return correct outputs, along with rule of
//five operators to correctly copy/move gluons with their new colour data members. Antiparticle
//generator conjugates colour charge.
//Herbie Warner 11/05/2024

#include<iostream>

#include"bosons/Gluon.h"

#include"utilities/ParticleUtilities.h"

using QuarkUtilities::ColourCharge;

Gluon::Gluon(const ColourCharge& colour_a,const ColourCharge& colour_b,double E, double px, double py, double pz) : 
  GaugeBoson(ParticleUtilities::DecayMode::Stable,0, 0,E,px,py,pz)
{
  set_gluon_colour_state(colour_a,colour_b);
}

Gluon::Gluon(double E, double px, double py, double pz) :
  GaugeBoson(ParticleUtilities::DecayMode::Stable, 0, 0, E, px, py, pz)
{
  set_gluon_colour_state();
}

Gluon::Gluon() : GaugeBoson(ParticleUtilities::DecayMode::Stable, 0, 0, 0, 0, 0, 0) 
{
  set_gluon_colour_state();
}

//Updated copy/move semantics for new data members colour, anti_colour
Gluon::Gluon(const Gluon& other) : GaugeBoson(other), colour(other.colour), anti_colour(other.anti_colour) {}

Gluon& Gluon::operator=(const Gluon& other)
{
  if(this != &other)
  {
    GaugeBoson::operator=(other);
    colour = other.colour;
    anti_colour = other.anti_colour;
  }
  return *this;
}

Gluon::Gluon(Gluon&& other) noexcept : GaugeBoson(std::move(other)), colour(other.colour), anti_colour(other.anti_colour) {}

Gluon& Gluon::operator=(Gluon&& other) noexcept
{
  if(this != &other)
  {
    GaugeBoson::operator=(std::move(other));
    colour = other.colour;
    anti_colour = other.anti_colour;
  }
  return *this;
}

std::unique_ptr<Particle> Gluon::generate_anti_particle() const
{
  auto new_colour = QuarkUtilities::get_anti_colour(get_colour());
  auto new_anti = QuarkUtilities::get_anti_colour(get_anti_colour());
  return std::make_unique<Gluon>(new_colour, new_anti, get_E(), get_px(), get_py(), get_pz());
}

void Gluon::set_gluon_colour_state(const ColourCharge& colour_a,const ColourCharge& colour_b)
{
  if((QuarkUtilities::is_anti_colour(colour_a) != QuarkUtilities::is_anti_colour(colour_b))
    && !QuarkUtilities::is_colour_neutral(colour_a,colour_b))
  {
    colour = colour_a;
    anti_colour = colour_b;
  }
  else
  {
    std::cout<<"GLUON INCOMPATIBLE COLOUR CHARGE OF "<<QuarkUtilities::get_colour_name(colour_a)<<" AND "<<
      QuarkUtilities::get_colour_name(colour_b)<<", USING RED ANTI-BLUE"<<std::endl;
    set_gluon_colour_state();
  }
}

void Gluon::set_gluon_colour_state()
{
  //Default for ease of reset
  colour = ColourCharge::Red;
  anti_colour = ColourCharge::Anti_Blue;
}

std::stringstream Gluon::get_info() const
{
  std::stringstream original = Particle::get_info();
  original<<", Colour: "<<QuarkUtilities::get_colour_name(colour)<<", "<<QuarkUtilities::get_colour_name(anti_colour);
  return original;
}