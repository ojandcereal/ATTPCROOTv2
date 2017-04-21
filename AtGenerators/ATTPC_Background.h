// -------------------------------------------------------------------------
// -----                   ATTPC_Background header file              -----
// -----                    Inherit from FairIonGenerator       ----
// -----                 Created 17/04/17  by J. C. Zamora -----
// -------------------------------------------------------------------------


#ifndef ATTPC_Background_H
#define ATTPC_Background_H


#include "FairGenerator.h"
#include "FairIon.h"
#include "FairParticle.h"

#include <iostream>
#include <map>

class FairPrimaryGenerator;
class ATTPC_Background;

class ATTPC_Background : public FairGenerator
{

 public:

  /** Default constructor **/
  ATTPC_Background();


  ATTPC_Background(const char* name,std::vector<Int_t> *z,std::vector<Int_t> *a,std::vector<Int_t> *q, Int_t mult, std::vector<Double_t> *px, 
          std::vector<Double_t>* py,std::vector<Double_t> *pz, std::vector<Double_t> *mass , std::vector<Double_t> *Ex);


  ATTPC_Background(const ATTPC_Background&);


  ATTPC_Background& operator=(const ATTPC_Background&) { return *this; }

  virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);
  
  virtual Double_t omega(Double_t x, Double_t y, Double_t z);
 
  virtual Double_t* TwoB(Double_t  m1b, Double_t m2b, Double_t m3b, Double_t m4b,  Double_t Kb, Double_t thetacm);

  /** Destructor **/
  virtual ~ATTPC_Background();

private:

                static Int_t fgNIon;                      //! Number of the instance of this class
                Int_t    fMult;                           // Multiplicity per event
                Bool_t fIsDecay;
                Double_t fVx, fVy, fVz;                   // Vertex coordinates [cm]
                std::vector<FairIon*>  fIon;              // Pointer to the FairIon to be generated
                std::vector<TString> fPType;           
                std::vector<FairParticle*>  fParticle; 
                std::vector<Double_t> fPx, fPy, fPz;      // Momentum components [MeV] per nucleon
		std::vector<Double_t> Masses;             // Masses of the N products
                std::vector<Double_t> fExEnergy;           // Excitation energies of the products
                std::vector<Double_t> fWm;                                 // Total mass
               	Int_t fN;
                

                Double_t K1;
                Double_t m1, m2 , m3, m4, m7,  m8;
                Double_t Ex_ejectile,  Ex_2he;
                Double_t test_var;



                Double_t ran1, ran2, ranX;
		Int_t ran_theta;

                Double_t Prec;
                

                
  
  
  		std::vector<Int_t>   fQ;		    // Electric charge [e]
  
  		Double_t fBeamEnergy;			    // Residual beam energy for phase calculation
  		Double_t fPxBeam;
  		Double_t fPyBeam;
  		Double_t fPzBeam;
 
                Double_t random_z;
                Double_t random_r;
                Double_t random_phi;

 
 
 


  ClassDef(ATTPC_Background,2)

}; 


#endif

