//LeptonUtilities.h
//Utility namespace of LeptonUtilities for lepton class and other functions. Declares enum class for the lepton
//types (e.g electron, tau..), as well as LeptonNumber class. Functions implemented to be used in places such
//as weak decays in SharedDecays namespace.
//Herbie Warner 28/04/2024

#ifndef LEPTONUTILITIES_H
#define LEPTONUTILITIES_H

#include<string>
#include<stdexcept>
#include<memory>

namespace LeptonUtilities 
{
  //It is possible to not have LeptonType and use those in ParticleUtilities::ParticleIdentifier, but that
  //requires constant correspondance checking. It is simpler to thus have a separate enum class for the lepton
  //flavours.
  enum class LeptonType 
  {
    Electron,
    Muon,
    Tau,
    AntiElectron,
    AntiMuon,
    AntiTau,
    ElectronNeutrino,
    MuonNeutrino,
    TauNeutrino,
    AntiElectronNeutrino,
    AntiMuonNeutrino,
    AntiTauNeutrino
  };

  inline constexpr double electron_rest_mass_energy = 0.511; //MeV
  inline constexpr double muon_rest_mass_energy = 106; //MeV
  inline constexpr double tau_rest_mass_energy = 1777; //MeV

  //To conveniently hold and work with lepton quantum number
  class LeptonNumber 
  {
  private:
    int electron_number;
    int muon_number;
    int tau_number;

  public:
    LeptonNumber(int electron, int muon, int tau) : electron_number(electron), muon_number(muon), tau_number(tau) {}
    LeptonNumber() : electron_number(0), muon_number(0), tau_number(0) {}
    ~LeptonNumber() {}

    int get_electron_number() const {return electron_number;}
    int get_muon_number() const {return muon_number;}
    int get_tau_number() const {return tau_number;}

    void display_lepton_numbers() const;
    bool operator!=(const LeptonNumber& other) const;
    bool operator==(const LeptonNumber& other) const;
    LeptonNumber operator+=(const LeptonNumber& other);
  };

  LeptonType get_corresponding_neutrino(const LeptonType& type);
  LeptonType get_corresponding_anti_neutrino(const LeptonType& type);
  LeptonType get_anti_lepton(const LeptonType& type);
  LeptonNumber get_lepton_number(const LeptonType& type);

  void is_neutrino(const LeptonType& type); //For neutrino constructor
  bool check_if_neutrino(const LeptonType& type);

  LeptonType real_or_anti_flavour(const LeptonType& type, int charge);
  LeptonType get_corresponding_neutrino(const LeptonType& type, int charge);
}

#endif