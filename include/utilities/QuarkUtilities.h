//QuarkUtilities.h
//Declares the utility namespace of QuarkUtilities for quark class and other functions. Declares enum class for the quark
//flavour (e.g up, down), as well as ColourcCharge. Functions aid in constructors and input checking on data
//such as colour.
//Herbie Warner 28/04/2024

#ifndef QUARKUTILITIES_H
#define QUARKUTILITIES_H

#include<string>

namespace QuarkUtilities 
{
  //It is possible to not have QuarkFlavour and use those in ParticleUtilities::ParticleIdentifier, but that
  //requires constant correspondance checking. It is simpler to thus have a separate enum class for the quark
  //flavours, allowing easier function definitions.
  enum class QuarkFlavour //Order matters for cabibo mixing in decays
  {
    Up,
    Charm,
    Top,
    Anti_Up,
    Anti_Charm,
    Anti_Top,
    Down,
    Strange,
    Bottom,
    Anti_Down,
    Anti_Strange,
    Anti_Bottom
  };

  enum class ColourCharge 
  {
    Red,
    Blue,
    Green,
    Anti_Red,
    Anti_Blue,
    Anti_Green,
    Neutral     
  };

  inline const double up_rest_mass_energy = 2.3;    // MeV
  inline const double down_rest_mass_energy = 4.8;  // MeV
  inline const double charm_rest_mass_energy = 1275; // MeV
  inline const double strange_rest_mass_energy = 95; // MeV
  inline const double top_rest_mass_energy = 173000; // MeV
  inline const double bottom_rest_mass_energy = 4180; // MeV

  QuarkFlavour get_anti_quark(const QuarkFlavour& flavour);

  std::string get_colour_name(const ColourCharge& colour);
  ColourCharge get_anti_colour(const ColourCharge& colour);

  bool is_colour_neutral(const ColourCharge& colour1, const ColourCharge& colour2);
  bool is_anti_colour(const ColourCharge& colour);
  bool is_anti_quark(const QuarkFlavour& flavour);

  
  double get_quark_mass(const QuarkFlavour& flavour);
  double get_quark_charge(const QuarkFlavour& flavour);

  ColourCharge get_compatible_colour(const QuarkFlavour& flavour);
}

#endif