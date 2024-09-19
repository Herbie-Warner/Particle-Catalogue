//Fourvector.h
//Declares the four vector class. The four vector itself is not a vector but consists of the individual 
//values composing the four vector. No relativity checks, bar energy > 0, are checked. This allows for
//virtual particles. However particle classes will contain consistency checks on the invariant masses. 
//Using natural units in MeV everywhere
//Herbie Warner 28/04/2024

#ifndef FOURVECTOR_H
#define FOURVECTOR_H

class FourVector
{
private:
  double E;
  double px;
  double py;
  double pz;

  double matrix_calculator(double energy, double pimary_b, double secondary_b, double tertiary_b,
    double pimary_p, double secondary_p, double tertiary_p, double gamma, double speed_squared); //Helper function for boosts
public:
  FourVector();
  FourVector(double E, double px, double py, double pz);
  ~FourVector() = default;

  //All trivially copyable members, no dynamic memory allocation, nor pointers/references to external data so can use defaults 
  FourVector(const FourVector&) = default;
  FourVector(FourVector&&) noexcept = default;
  FourVector& operator=(const FourVector&) = default;
  FourVector& operator=(FourVector&&) noexcept = default;

  //Setters
  void set_four_vector(double E, double px, double py, double pz);
  void reset_four_vector(); //Set all to zero
  void set_E(double E);
  void set_px(double p_x) {px = p_x;}
  void set_py(double p_y) {py = p_y;}
  void set_pz(double p_z) {pz = p_z;}

  //Getters
  double get_E() const {return E;}
  double get_px() const {return px;}
  double get_py() const {return py;}
  double get_pz() const {return pz;}
  double get_invariant_mass_squared() const;

  //Operators
  FourVector operator+(const FourVector& other) const;
  FourVector operator-(const FourVector& other) const;
  FourVector& operator+=(const FourVector& other);
  FourVector& operator-=(const FourVector& other);
  double dot_product(const FourVector& other) const;
  void boost(double beta_x, double beta_y, double beta_z); //Boost along some direction
  void get_boost_to_lab_frame(double& beta_x, double& beta_y, double& beta_z) const; //Using & for easier information transmission

  //Other functions
  void display_four_vector() const;
};

#endif