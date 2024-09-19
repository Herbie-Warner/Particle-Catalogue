# Particle-Catalogue-in-C-
Made for an introductory module on C++. Excuse lack of commits this was made on another account in a repository I cannot transfer ownership of.

# BUILD INSTRUCTIONS
Building the Project
This project can be compiled using either a single-line g++ command or by utilising the provided Makefile.

Using g++:
To compile the project using a single line g++ command, use the following command:

```bash
g++ -std=gnu++17 -Iinclude -o ParticleCatalogue src/bosons/*.cpp src/core/*.cpp src/fermions/*.cpp src/main/*.cpp src/utilities/*.cpp -mconsole
```

or if your system doesn't support wildcard expansion

```bash
g++ -std=gnu++17 -Iinclude src/bosons/Boson.cpp src/bosons/GaugeBoson.cpp src/bosons/Gluon.cpp src/bosons/HiggsBoson.cpp src/bosons/Photon.cpp src/bosons/WBoson.cpp src/bosons/ZBoson.cpp src/core/FourVector.cpp src/core/Particle.cpp src/core/ParticleContainer.cpp src/fermions/Electron.cpp src/fermions/Fermion.cpp src/fermions/Lepton.cpp src/fermions/Muon.cpp src/fermions/Neutrino.cpp src/fermions/Quark.cpp src/fermions/Tau.cpp src/main/ParticleCatalogue.cpp src/utilities/DecayChannels.cpp src/utilities/DecayUtilities.cpp src/utilities/FactoryUtilities.cpp src/utilities/LeptonUtilities.cpp src/utilities/ParticleUtilities.cpp src/utilities/QuantumNumberVisitor.cpp src/utilities/QuarkUtilities.cpp src/utilities/SharedDecays.cpp -o ParticleCatalogue.exe
```

This will produce the executable ParticleCatalogue.exe in the current directory.

Using Makefile (this Makefile is configured for Windows):
If you prefer using make, you can build the project with the following command:

```bash
make
```

This will produce the executable particle_catalogue.exe in the ./bin directory.

To clean up the build files, you can use:

```bash
make clean
```

# Documentation

To view the project documentation, open the `doxygen/html/index.html` file in a web browser.
