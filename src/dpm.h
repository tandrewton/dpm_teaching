#ifndef DPM_H
#define DPM_H
/*

        HEADER FILE FOR DPM CLASS

                -- Stores vertex information for NCELLS with NV vertices each
                -- Stores shape parameters + spring constants
                -- Integrates equations of motion (NVE)
                -- Prints data to files

*/

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// global constants
const double PI = 4.0 * atan(1.0);

// function declarations and classes go here
class sp {  // soft particle sp
 protected:
  // int scalars
  int NCELLS;

  // number of dimensions
  int NDIM;

  // time step size
  double dt;

  // potential energy
  double U;

  // particle spring constants
  double k;

  // particle parameters
  std::vector<double> r;


  // boundary parameters
  std::vector<double> L;
  std::vector<bool> pbc;

  // dynamical variables
  std::vector<double> x;
  std::vector<double> v;
  std::vector<double> F;

  // output objects
  std::ofstream posout;

 public:
  // Constructors and Destructors
  sp(int n, int seed);
  sp(int n, int seed)
      : sp(n, seed) {}
  ~sp();

  // -- G E T T E R S

  // main ints
  int getNCELLS() { return NCELLS; };
  int getNDIM() { return NDIM; };

  // force parameters
  double getdt() { return dt; };
  double getk() { return k; };

  // boundary variables
  double getL(int d) { return L.at(d); };
  bool getpbc(int d) { return pbc.at(d); };

  // calculate system properties
  double packingFraction();
  double kineticEnergy();

  // Initialize particles (two dimensions)
  void monodisperse();
  void bidisperse(double smallfrac, double sizefrac);

  void initializePositions(double phi0, double Ftol);

  // editing & updating
  void scaleParticleSizes(double scaleFactor);
  void drawVelocities(double T);

  // force definitions
  void resetForcesAndEnergy();
  void repulsiveForces();

  // force updates
  void repulsiveForceUpdate();

  // simple integrators
  void vertexFIRE2D(dpmMemFn forceCall, double Ftol, double dt0);
  void vertexNVE2D(std::ofstream& enout, dpmMemFn forceCall, double T, double dt0, int NT, int NPRINTSKIP);

  // protocols
  void vertexCompress2Target(dpmMemFn forceCall, double Ftol, double dt0, double phi0Target, double dphi0);
  void vertexJamming(dpmMemFn forceCall, double Ftol, double Ptol, double dt0, double dphi0, bool plotCompression);

  // print vertex information to file
  void printConfiguration();
};

#endif
