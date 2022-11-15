#include "dpm.h"

// function definitions go here

// Main constructor
sp::sp(int n, int seed) {
  // local variables
  int d, i;

  // print to console
  cout << "** Instantiating sp object, NCELLS = " << n << ", seed = " << seed << " ..." << endl;

  // main variables
  NCELLS = n;
  NDIM = 2;

  // set scalars to default values
  dt = 0.0;

  k = 0.0;

  // default boundary variables
  L.resize(NDIM);
  pbc.resize(NDIM);
  for (d = 0; d < NDIM; d++) {
    L[d] = 1.0;
    pbc[d] = 1;
  }

  // seed random number generator
  srand48(seed);
}

// destructor
dpm::~dpm() {
  // clear all private vectors
  L.clear();
  pbc.clear();
  k.clear();
  r.clear();
  x.clear();
  v.clear();
  F.clear();
  // add more as you go, but not important unless you're constantly constructing and destructing

  if (posout.is_open())
    posout.close();
}

// get vertex kinetic energy
double sp::kineticEnergy() {
  double K = 0;

  for (int i = 0; i < NCELLS; i++)
    K += v[i] * v[i];
  K *= 0.5;

  return K;
}

void sp::repulsiveForceUpdate() {
  resetForcesAndEnergy();
  repulsiveForces();
}

void sp::printConfiguration() {
// check if pos object is open
	if (!posout.is_open()) {
		cerr << "** ERROR: in printConfiguration2D, posout is not open, but function call will try to use. Ending here." << endl;
		exit(1);
	}
	else
		cout << "** In printConfiguration2D, printing particle positions to file..." << endl;

  // save box sizes
	Lx = L.at(0);
	Ly = L.at(1);

	// print information starting information
	posout << setw(w) << left << "NEWFR"
		   << " " << endl;

}
