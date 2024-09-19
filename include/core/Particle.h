//Particle.h
//Declares the base particle class which is abstract. Top of the inheritance chain for particles with derived
//classes fermions and bosons. Uses ParticleUtilities namespace to enable derived classes access to decay modes.
//Includes virtual functions for derived particles to override given unique properties. 
//Herbie Warner 28/04/2024

#ifndef PARTICLE_H
#define PARTICLE_H

#include<string>
#include<memory> 
#include<vector>
#include<sstream>

#include"core/FourVector.h"

#include"utilities/DecayChannels.h"
#include"utilities/ParticleUtilities.h"
#include"utilities/ParticleVisitor.h"

class Particle
{
private:
  std::unique_ptr<FourVector> four_momentum; //Unique ptr of four momentum
  double spin; //No setter as user should not be able to change
  double charge; // In units of the elementrary charge. No setter as user should never be able to change this
  mutable ParticleUtilities::DecayMode mode; //Mutable to be changed in decay functions which are otherwise const
  double rest_mass;
protected:
  //These are protected as particles need to be able to change their decay channels. 
  std::unique_ptr<DecayChannels> decay_channels; //Decay channels for each particle

  //Init should not be done out of the class but needs to be overridden derived classes for correct decay set
  virtual void initialise_decay_channels() {}
public:
  Particle() = delete; //No default constructor
  Particle(const ParticleUtilities::DecayMode& mode, double spin, double c, double rest_mass, double E, double px, double py, double pz);
  virtual ~Particle(); // Destructor

  Particle(const Particle& other); // Copy constructor
  Particle& operator=(const Particle& other); // Copy assignment
  Particle(Particle&& other) noexcept; // Move constructor
  Particle& operator=(Particle&& other) noexcept; // Move assignment operator
  virtual std::unique_ptr<Particle> clone() const = 0; //Pure virtual as particle is abstract

  // Setters
  void set_four_momentum(double E, double px, double py, double pz);
  void set_decay_mode(ParticleUtilities::DecayMode decay) {mode=decay;}

  //Decay methods
  void add_decay_channel(DecayUtilities::DecayChannel channel);
  void add_decay_channel(std::vector<ParticleUtilities::ParticleIdentifier> particles, double branching_ratio);
  void print_all_decays() const;
  void decay_with_print_inbuilt() const;
  void decay_with_print_instance_specific() const;
  virtual DecayProducts decay_inbuilt() const; //Virtual as tau needs to add a tau neutrino
  DecayProducts decay_instante_specific() const;

  // Getters
  double get_charge() const {return charge;}
  double get_E() const {return four_momentum->get_E();}
  double get_px() const {return four_momentum->get_px();}
  double get_py() const {return four_momentum->get_py();}
  double get_pz() const {return four_momentum->get_pz();}
  double get_invariant_mass_squared() const {return four_momentum->dot_product(*four_momentum);}
  double get_spin() const {return spin;}
  double get_rest_mass() const {return rest_mass;}
  FourVector get_four_vector() const {return *four_momentum;}
  ParticleUtilities::DecayMode get_decay_mode() const {return mode;}
  void get_boost_to_lab_frame(double& beta_x, double& beta_y, double& beta_z) const {four_momentum->get_boost_to_lab_frame(beta_x, beta_y, beta_z);}

  //Other functions
  virtual std::unique_ptr<Particle> generate_anti_particle() const = 0;

  void display_properties() const;
  virtual std::stringstream get_info() const; //ss of useful object information. Virtual so derived classes can add further information

  void display_four_vector() const {four_momentum->display_four_vector();}
  double dot_product(const Particle& other) const {return four_momentum->dot_product(*other.four_momentum);}

  virtual void accept(ParticleVisitor* visitor) {visitor->visit_particle(this);} //Virtual so lepton and quark
  //can make sure to accept the correct visitor (that who will take all the necessary quantum numbers). This
  //is vital for decay procedures.

  void boost(double boost_x, double boost_y, double boost_z) {four_momentum->boost(boost_x, boost_y, boost_z);}

  //This is for the ParticleContainer to easily be able to identify by particle type
  virtual ParticleUtilities::ParticleIdentifier get_general_type() const {return ParticleUtilities::ParticleIdentifier::Particle;}
};

#endif