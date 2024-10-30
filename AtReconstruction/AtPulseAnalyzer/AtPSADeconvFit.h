#ifndef ATPSADECONVFIT_H
#define ATPSADECONVFIT_H

#include "AtPSADeconv.h"
#include "AtPad.h" // for AtPad, AtPad::trace

#include <Fit/FitResult.h> // for FitResult
#include <memory>          // for unique_ptr, make_unique
class AtPSA;

class TH1F;
class TF1;

class AtPSADeconvFit : public AtPSADeconv {

protected:
   double fDiffLong; //< Longitudinal diffusion coefficient
   static thread_local std::unique_ptr<TH1F> fHist;

public:
   using AtPSA::Init; // Return base class Init to scope (since the override will shadow it by default)
   virtual void Init(AtDigiPar *fPar) override;
   virtual std::unique_ptr<AtPSA> Clone() override { return std::make_unique<AtPSADeconvFit>(*this); }
   double GetDiffLong() const { return fDiffLong; }

protected:
   HitData getZandQ(const AtPad::trace &charge) override;
   double getSigTB(double zTB) const;

   const ROOT::Fit::FitResult FitHistorgramParallel(TH1F &hist, TF1 &func);
};

#endif // #ifndef ATPSADECONVFIT_H
