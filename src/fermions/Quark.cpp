//Quark.cpp
//Defines the member functions of the Quark class which is a polymorphism of the Fermion class. New private members
//of quark flavour and colour charge are installed mandating updated move and copy operators/ constructos. All masses,
//charges, and baryons numbers are not settable by user but are discerned from the flavour provided.
//Herbie Warner 11/05/2024

#include<iostream>
#include"fermions/Quark.h"

using ParticleUtilities::ParticleIdentifier;
using QuarkUtilities::QuarkFlavour;

Quark::Quark(const QuarkUtilities::QuarkFlavour& flav, const QuarkUtilities::ColourCharge& col,
    double E, double px, double py, double pz) : Fermion(ParticleUtilities::DecayMode::Stable, 0.5
      , QuarkUtilities::get_quark_charge(flav), QuarkUtilities::get_quark_mass(flav), E, px, py, pz),
  flavour(flav), colour(col)
{
  init_baryon_number();
  init_colour();
}

Quark::Quark(const QuarkUtilities::QuarkFlavour& flav) : Fermion(ParticleUtilities::DecayMode::Stable, 0.5,
  QuarkUtilities::get_quark_charge(flav), QuarkUtilities::get_quark_mass(flav), QuarkUtilities::get_quark_mass(flav), 0, 0, 0),
  colour(QuarkUtilities::ColourCharge::Red), flavour(flav)
{
  init_baryon_number();
  init_colour();
}

Quark::Quark(const Quark& other) : Fermion(other), colour(other.colour), flavour(other.flavour) {}

Quark& Quark::operator=(const Quark& other) 
{
  if(this != &other) 
  {
    Fermion::operator=(other);
    flavour = other.flavour;
    colour = other.colour;
  }
  return *this;
}

Quark::Quark(Quark&& other) noexcept : Fermion(std::move(other)), flavour(std::move(other.flavour)), colour(other.colour) {}

Quark& Quark::operator=(Quark&& other) noexcept 
{
  if(this != &other) 
  {
    Fermion::operator=(std::move(other)); 
    colour = std::move(other.colour);
    flavour = other.flavour;
  }
  return *this;
}

std::stringstream Quark::get_info() const
{
  std::stringstream original = Particle::get_info();
  original<<", Colour: "<<QuarkUtilities::get_colour_name(colour);
  return original;
}

void Quark::set_quark_colour(QuarkUtilities::ColourCharge new_colour)
{
  if(QuarkUtilities::is_anti_quark(flavour) == QuarkUtilities::is_anti_colour(new_colour)) 
  {
    colour = new_colour;
  }
  else 
  {
    std::cerr<<"CANNOT SET ANTI-COLOUR TO NON-ANTIQUARK NOR COLOUR TO ANTIQUARK. RETAINING ORIGINAL COLOUR"<<std::endl;
  }
}

void Quark::init_baryon_number()
{

  if(QuarkUtilities::is_anti_quark(flavour)) {baryon_number = -1.0/3.0;}
  else baryon_number = 1.0/3.0;
  
}

void Quark::init_colour()
{
  if(QuarkUtilities::is_anti_quark(flavour) == QuarkUtilities::is_anti_colour(colour)) {}
  else {colour = QuarkUtilities::get_compatible_colour(flavour);}
}


std::unique_ptr<Particle> Quark::generate_anti_particle() const
{
  return std::make_unique<Quark>(QuarkUtilities::get_anti_quark(flavour),
    QuarkUtilities::get_anti_colour(colour), get_E(), get_px(), get_py(), get_pz());
}


ParticleIdentifier Quark::get_correspondance() const 
{
  //To map between particle id and quark flavour
  const QuarkFlavour quark = flavour;
  switch(quark) 
  {
  case QuarkFlavour::Up:
    return ParticleIdentifier::Up;
  case QuarkFlavour::Down:
    return ParticleIdentifier::Down;
  case QuarkFlavour::Charm:
    return ParticleIdentifier::Charm;
  case QuarkFlavour::Strange:
    return ParticleIdentifier::Strange;
  case QuarkFlavour::Top:
    return ParticleIdentifier::Top;
  case QuarkFlavour::Bottom:
    return ParticleIdentifier::Bottom;
  case QuarkFlavour::Anti_Up:
    return ParticleIdentifier::AntiUp;
  case QuarkFlavour::Anti_Down:
    return ParticleIdentifier::AntiDown;
  case QuarkFlavour::Anti_Charm:
    return ParticleIdentifier::AntiCharm;
  case QuarkFlavour::Anti_Strange:
    return ParticleIdentifier::AntiStrange;
  case QuarkFlavour::Anti_Top:
    return ParticleIdentifier::AntiTop;
  case QuarkFlavour::Anti_Bottom:
    return ParticleIdentifier::AntiBottom;
  default:
    throw std::invalid_argument("Unrecognized QuarkFlavour."); //Should never occur
  }
}

ParticleUtilities::ParticleIdentifier Quark::get_general_type() const
{
  return get_correspondance();
}