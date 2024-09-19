//FourVector.cpp
//Defines the functions in FourVector class. Does not employ relativity checks allowing for
//some virtuality, but does stop negative energies.
//Using natural units in MeV
//Herbie Warner 28/04/2024

#include<iostream>
#include<stdexcept>
#include<cmath>

#include"core/FourVector.h"

FourVector::FourVector() {reset_four_vector();}
FourVector::FourVector(double E, double px, double py, double pz) {set_four_vector(E, px, py, pz);}

//Setters
void FourVector::set_four_vector(double energy, double p_x, double p_y, double p_z)
{
  if(energy < 0)
  {
    throw std::invalid_argument("Energy cannot be negative");
  }
  E = energy;
  px = p_x;
  py = p_y;
  pz = p_z;
}

void FourVector::reset_four_vector()
{
  E = 0;
  px = 0;
  py = 0;
  pz = 0;
}

void FourVector::set_E(double energy)
{
  if(energy < 0)
  {
    throw std::invalid_argument("Energy cannot be negative");
  }
  E = energy;
}

//Operators
FourVector FourVector::operator+(const FourVector& other) const
{
  return FourVector(E + other.get_E(),
    px + other.get_px(), py + other.get_py(),
    pz + other.get_pz());
}

FourVector FourVector::operator-(const FourVector& other) const
{
  return FourVector(E - other.get_E(),
    px - other.get_px(), py - other.get_py(),
    pz - other.get_pz());
}

FourVector& FourVector::operator+=(const FourVector& other)
{
  E += other.E;
  px += other.px;
  py += other.py;
  pz += other.pz;
  return *this; 
}

FourVector& FourVector::operator-=(const FourVector& other)
{
  E -= other.E;
  px -= other.px;
  py -= other.py;
  pz -= other.pz;
  return *this;
}

double FourVector::dot_product(const FourVector& other) const
{
  //Using Minkowski metric +---
  double dot = E * other.get_E() - px * other.get_px() - py * other.get_py() - pz * other.get_pz();
  return dot; 
}

//Other Functions
void FourVector::display_four_vector() const
{
  std::cout<<"Four momentum (MeV): "<<E<<", "<<px<<", "<<py<<", "<<pz<<std::endl;
}

double FourVector::matrix_calculator(double energy, double primary_b, double secondary_b, double tertiary_b,
  double primary_p, double secondary_p, double tertiary_p, double gamma, double speed_squared)
{
  //Non-zero row calculations for boost matrix in boost function
  return (- gamma*primary_b)*energy + (1 + (gamma-1)*std::pow(primary_b,2)/speed_squared)*primary_p +
    ((gamma-1)*primary_b*secondary_b/speed_squared)*secondary_p +
    ((gamma - 1) * primary_b * tertiary_b / speed_squared) * tertiary_p;
}

void FourVector::boost(double beta_x, double beta_y, double beta_z) 
{
  /*
   * Lorentz boost matrix using this signature
   *
   * | γ              -γβx            -γβy            -γβz            |
   * | -γβx      1 + (γ - 1)βx²/β²  (γ - 1)βxβy/β²  (γ - 1)βxβz/β²    |
   * | -γβy      (γ - 1)βxβy/β²    1 + (γ - 1)βy²/β²  (γ - 1)βyβz/β²  |
   * | -γβz      (γ - 1)βxβz/β²    (γ - 1)βyβz/β²    1 + (γ - 1)βz²/β²|
  */
  double speed_squared = std::pow(beta_x,2) + std::pow(beta_y, 2) + std::pow(beta_z, 2);

  if(speed_squared==0 || speed_squared >= 1){return;} //To leave the function

  double gamma = std::pow(std::pow(1-speed_squared,0.5),-1);
  double new_E = (E * gamma) - (gamma * beta_x * px) - (gamma * beta_y * py) - (gamma * beta_z * pz);
  double new_px = matrix_calculator(E, beta_x, beta_y, beta_z, px, py, pz, gamma, speed_squared);
  double new_py = matrix_calculator(E, beta_y, beta_z, beta_x, py, pz, px, gamma, speed_squared);
  double new_pz = matrix_calculator(E, beta_z, beta_x, beta_y, pz, px, py, gamma,speed_squared);

  E = new_E;
  px = new_px;
  py = new_py;
  pz = new_pz;
}

void FourVector::get_boost_to_lab_frame(double& beta_x, double& beta_y, double& beta_z) const
{
  //Use & for easier data transmission
  beta_x = px/E;
  beta_y = py/E;
  beta_z = pz/E;
}

double FourVector::get_invariant_mass_squared() const
{
  return dot_product(*this);
}