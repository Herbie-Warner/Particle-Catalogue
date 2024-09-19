//Electron.h
//Declares the Electron class which is a polymorphism of the Lepton class. Is used to generate both electrons
//and antielectrons via charge argument in constructor. New copy/move semantics for new data member calorimeter.
//Herbie Warner 25/04/2024

#ifndef ELECTRON_H
#define ELECTRON_H

#include<memory>

#include"fermions/Lepton.h"
#include"utilities/LeptonUtilities.h"

class Electron : public Lepton
{
private:
  std::vector<double> calorimeter_deposit;
  void change_calorimeter(double layer_1, double layer_2, double layer_3, double layer_4);
public:
  Electron(int charge, double E, double px, double py, double pz);
  Electron(int charge);
  ~Electron() override = default;

  //Upade for calorimeter deposit data member
  Electron(const Electron& other);
  Electron(Electron&& other) noexcept;
  Electron& operator=(const Electron& other);
  Electron& operator=(Electron&& other) noexcept;

  void set_calorimeter_deposit(double EM_1, double EM_2, double HAD_1, double HAD_2);
  std::vector<double> get_calorimeter_deposit() const;
  double get_EM_1() const {return calorimeter_deposit[0];}
  double get_EM_2() const {return calorimeter_deposit[1];}
  double get_HAD_1() const {return calorimeter_deposit[2];}
  double get_HAD_2() const {return calorimeter_deposit[3];}

  std::stringstream get_info() const override;

  std::unique_ptr<Particle> clone() const override {return std::make_unique<Electron>(*this);}
  std::unique_ptr<Particle> generate_anti_particle() const override;

  ParticleUtilities::ParticleIdentifier get_general_type() const override;
};

#endif