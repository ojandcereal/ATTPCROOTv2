#ifndef ATPSADECONVFITBASELINE_H
#define ATPSADECONVFITBASELINE_H

#include "AtPSADeconvFit.h"

class AtPSADeconvFitBaseline : public AtPSADeconvFit {
public:
   AtPSADeconvFitBaseline();
   virtual ~AtPSADeconvFitBaseline();

   // Override getZandQ method from AtPSADeconv
   virtual HitData getZandQ(const AtPad::trace &charge) override;
};

#endif // ATPSA_DECONV_FIT_BASELINE_H
