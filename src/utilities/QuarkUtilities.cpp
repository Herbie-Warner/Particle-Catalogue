//QuarkUtilities.cpp
//Defines the quark utilities namespace. Uses static maps for quick look ups for names, and anti equivalents. Implements
//other functions for assistance in generating decay channels.
//Herbie Warner 09/05/2024

#include<map>
#include<iostream>
#include<stdexcept>

#include"utilities/QuarkUtilities.h"

namespace QuarkUtilities 
{
  //Switch statements can easily be replaced by static maps for faster look up if these functions
  //are called often.
  QuarkFlavour get_anti_quark(const QuarkFlavour& quark_flavour)
  {
    switch(quark_flavour)
    {
      case QuarkFlavour::Up: return QuarkFlavour::Anti_Up;
      case QuarkFlavour::Down: return QuarkFlavour::Anti_Down;
      case QuarkFlavour::Charm: return QuarkFlavour::Anti_Charm;
      case QuarkFlavour::Strange: return QuarkFlavour::Anti_Strange;
      case QuarkFlavour::Top: return QuarkFlavour::Anti_Top;
      case QuarkFlavour::Bottom: return QuarkFlavour::Anti_Bottom;
      case QuarkFlavour::Anti_Up: return QuarkFlavour::Up;
      case QuarkFlavour::Anti_Down: return QuarkFlavour::Down;
      case QuarkFlavour::Anti_Charm: return QuarkFlavour::Charm;
      case QuarkFlavour::Anti_Strange: return QuarkFlavour::Strange;
      case QuarkFlavour::Anti_Top: return QuarkFlavour::Top;
      case QuarkFlavour::Anti_Bottom: return QuarkFlavour::Bottom;
      default: throw std::invalid_argument("UNKNOWN QUARKFLAVOUR");
    }
  }
  
  double get_quark_mass(const QuarkFlavour& flavour)
  {
    
    switch(flavour) 
    {
    case QuarkFlavour::Up:
    case QuarkFlavour::Anti_Up: return up_rest_mass_energy;
    case QuarkFlavour::Down:
    case QuarkFlavour::Anti_Down: return down_rest_mass_energy;
    case QuarkFlavour::Charm:
    case QuarkFlavour::Anti_Charm: return charm_rest_mass_energy;
    case QuarkFlavour::Strange:
    case QuarkFlavour::Anti_Strange: return strange_rest_mass_energy;
    case QuarkFlavour::Top:
    case QuarkFlavour::Anti_Top: return top_rest_mass_energy;
    case QuarkFlavour::Bottom:
    case QuarkFlavour::Anti_Bottom: return bottom_rest_mass_energy;
    default:
      throw std::invalid_argument("INVALID OR UNSUPPORTED QUARK FLAVOUR FOR QUARK MASS");
    }
  }

  double get_quark_charge(const QuarkFlavour& flavour)
  {
    switch(flavour) {
    case QuarkFlavour::Up:
    case QuarkFlavour::Anti_Up:
    case QuarkFlavour::Charm:
    case QuarkFlavour::Anti_Charm:
    case QuarkFlavour::Top:
    case QuarkFlavour::Anti_Top:
      return (is_anti_quark(flavour) ? -2.0 : 2.0) / 3.0;
    case QuarkFlavour::Down:
    case QuarkFlavour::Anti_Down:
    case QuarkFlavour::Strange:
    case QuarkFlavour::Anti_Strange:
    case QuarkFlavour::Bottom:
    case QuarkFlavour::Anti_Bottom:
      return (is_anti_quark(flavour) ? 1.0 : -1.0) / 3.0;
    default:
      throw std::invalid_argument("INVALID OR UNSUPPORTED QUARK FLAVOUR FOR QUARK CHARGE");
    }
  }

  ColourCharge get_anti_colour(const ColourCharge& colour_charge)
  {
    static const std::map<ColourCharge, ColourCharge> anti_colour_map =
    {
      {ColourCharge::Red, ColourCharge::Anti_Red},
      {ColourCharge::Blue, ColourCharge::Anti_Blue},
      {ColourCharge::Green, ColourCharge::Anti_Green},
      {ColourCharge::Anti_Red, ColourCharge::Red},
      {ColourCharge::Anti_Blue, ColourCharge::Blue},
      {ColourCharge::Anti_Green, ColourCharge::Green},
      {ColourCharge::Neutral, ColourCharge::Neutral}
    };

    auto it = anti_colour_map.find(colour_charge);
    if(it != anti_colour_map.end())
    {
      return it->second;
    }
    else
    {
      throw std::invalid_argument("Unknown ColourCharge");
    }
  }

  std::string get_colour_name(const ColourCharge& colour_charge)
  {
    static const std::map<ColourCharge, std::string> colour_name_map =
    {
      {ColourCharge::Red, "Red"},
      {ColourCharge::Blue, "Blue"},
      {ColourCharge::Green, "Green"},
      {ColourCharge::Anti_Red, "Anti-Red"},
      {ColourCharge::Anti_Blue, "Anti-Blue"},
      {ColourCharge::Anti_Green, "Anti-Green"},
      {ColourCharge::Neutral, "Neutral"}
    };

    auto it = colour_name_map.find(colour_charge);
    if(it != colour_name_map.end())
    {
      return it->second;
    }
    else
    {
      return "UNRECOGNISED COLOUR CHARGE";
    }
  }

  bool is_colour_neutral(const ColourCharge& colour1,const ColourCharge& colour2)
  {
    if((colour1 == ColourCharge::Red && colour2 == ColourCharge::Anti_Red)    ||
      (colour1 == ColourCharge::Anti_Red && colour2 == ColourCharge::Red)     ||
      (colour1 == ColourCharge::Blue && colour2 == ColourCharge::Anti_Blue)   ||
      (colour1 == ColourCharge::Anti_Blue && colour2 == ColourCharge::Blue)   ||
      (colour1 == ColourCharge::Green && colour2 == ColourCharge::Anti_Green) ||
      (colour1 == ColourCharge::Anti_Green && colour2 == ColourCharge::Green) ||
      (colour1 == ColourCharge::Neutral && colour2 == ColourCharge::Neutral))
    {
      return true;
    }
    return false;
  }

  bool is_anti_colour(const ColourCharge& colour)
  {
    if(colour==ColourCharge::Red || colour==ColourCharge::Blue || colour==ColourCharge::Green
      || colour==ColourCharge::Neutral) {return false;}
    return true;
  }

  bool is_anti_quark(const QuarkFlavour& flavour)
  {
  
    switch(flavour)
    {
      case QuarkFlavour::Up:
      case QuarkFlavour::Down:
      case QuarkFlavour::Charm:
      case QuarkFlavour::Strange:
      case QuarkFlavour::Top:
      case QuarkFlavour::Bottom:
        return false;
      case QuarkFlavour::Anti_Up:
      case QuarkFlavour::Anti_Down:
      case QuarkFlavour::Anti_Charm:
      case QuarkFlavour::Anti_Strange:
      case QuarkFlavour::Anti_Top:
      case QuarkFlavour::Anti_Bottom:
        return true;
      default:
        throw std::invalid_argument("UNKNOWN QUARK FLAVOUR");
    }
  }

  ColourCharge get_compatible_colour(const QuarkFlavour& flavour)
  {
    if(is_anti_quark(flavour)) {return ColourCharge::Anti_Red;}
    else {return ColourCharge::Red;}
  }
}