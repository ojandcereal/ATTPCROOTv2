#ifndef ATPSACOMPOSITE_H
#define ATPSACOMPOSITE_H

#include "AtPSA.h"

#include <memory> // for unique_ptr, make_unique
class AtPad;

/**
 * @brief Uses different PSA methods in/out of beam region.
 *
 */
class AtPSAComposite : public AtPSA {
private:
   std::unique_ptr<AtPSA> fBeamPSA;
   std::unique_ptr<AtPSA> fPSA;

   double fBeamRadius; //< Beam radius in mm

public:
   AtPSAComposite(std::unique_ptr<AtPSA> beamPSA, std::unique_ptr<AtPSA> PSA, double beamRadius = 40);
   AtPSAComposite(const AtPSAComposite &);

   using AtPSA::Init; // Return base class Init to scope (since the override will shadow it by default)
   void Init(AtDigiPar *fPar) override;
   virtual HitVector AnalyzePad(AtPad *) override;
   std::unique_ptr<AtPSA> Clone() override { return std::make_unique<AtPSAComposite>(*this); }
};

#endif // #ifndef ATPSAFISSION_H