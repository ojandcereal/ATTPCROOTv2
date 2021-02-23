/*****************************************************************/
/*    AtClusterizeTask: Simulates the ionized electrons which are    */
/*    drifted and amplified by avalanche when reaching the mesh. */
/*    Log: Created in 24-10-2016     				 */
/*    Author: Nathan Watwood (NSCL) 				 */
/*    ayyadlim@nscl.msu.edu                                      */
/*****************************************************************/
#ifndef AtClusterizeTask_H
#define AtClusterizeTask_H

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "FairTask.h"
#include "FairMCPoint.h"

#include "TClonesArray.h"
#include "AtDigiPar.h"
#include "AtGas.h"
#include "AtTpcPoint.h"

class AtClusterizeTask : public FairTask {
public:
   AtClusterizeTask();
   ~AtClusterizeTask();

   void SetPersistence(Bool_t val) { fIsPersistent = val; }
   // void SetTestMode()              { fTestMode = kTRUE; };

   virtual InitStatus Init();        //!< Initiliazation of task at the beginning of a run.
   virtual void Exec(Option_t *opt); //!< Executed for each event.
   virtual void SetParContainers();  //!< Load the parameter container from the runtime database.

private:
   Int_t fEventID;     //!< EventID
   Double_t fEIonize;  //!< Effective ionization energy of gas. [eV]
   Double_t fFano;     //!< Fano factor of the gas
   Double_t fVelDrift; //!< Drift velocity of electron in gas. [mm/ns]
   Double_t fCoefT;    //!< Transversal diffusion coefficient. [mm^(-1/2)]
   Double_t fCoefL;    //!< Longitudinal diffusion coefficient. [mm^(-1/2)]

   AtGas *fGas;     //!< Gas parameter container.
   AtDigiPar *fPar; //!< Base parameter container.

   TClonesArray *fMCPointArray;
   AtTpcPoint *fMCPoint;
   TClonesArray *fElectronNumberArray; //!< Primary cluster array
   Bool_t fIsPersistent;               //!< If true, save container

   ClassDef(AtClusterizeTask, 1);
};

#endif
