//Muon.h
//Declares the Muon class which is a polymorphism of the Lepton class. New private boolean member for isolation variable.
//Is used to generate both muons and antimuons via charge argument.
//Herbie Warner 24/04/2024

#ifndef MUON_H
#define MUON_H

#include<memory>
#include<sstream>
#include"fermions/Lepton.h"
#include"utilities/LeptonUtilities.h"

class AntiMuon;

class Muon : public Lepton
{
private:
  bool is_isolated; //New private member
public:
  Muon(int charge, double E, double px, double py, double pz);
  Muon(int charge);
  ~Muon() override = default;
  Muon(const Muon& other); //Redefine for new is_isolated variable
  Muon(Muon&& other) noexcept;
  Muon& operator=(const Muon& other);
  Muon& operator=(Muon&& other) noexcept;
  
  bool get_is_isolated() const {return is_isolated;}
  void set_is_isolated(bool new_isolation) {is_isolated = new_isolation;}

  std::stringstream get_info() const override;

  std::unique_ptr<Particle> clone() const override {return std::make_unique<Muon>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif