
#include "AtPSADeconvFitBaseline.h"

#include "AtContainerManip.h"
#include "AtDigiPar.h"
#include "AtPSADeconvFit.h"

#include <FairLogger.h> // for Logger, LOG
#include <FairParSet.h> // for FairParSet
#include <FairRun.h>
#include <FairRuntimeDb.h>

#include <Math/WrappedMultiTF1.h>
#include <TF1.h>
#include <TH1.h>     // for TH1D
#include <TMath.h>   // for Pi
#include <TString.h> // for TString

#include <HFitInterface.h>

#include <Fit/BinData.h>
#include <Fit/DataOptions.h> // for DataOptions
#include <Fit/DataRange.h>   // for DataRange
#include <Fit/FitConfig.h>   // for FitConfig
#include <Fit/Fitter.h>
#include <algorithm>  // for max_element
#include <cmath>      // for sqrt
#include <functional> // for hash
#include <iterator>   // for begin, distance, end
#include <memory>     // for allocator, unique_ptr
#include <thread>

AtPSADeconvFitBaseline::AtPSADeconvFitBaseline() = default;
AtPSADeconvFitBaseline::~AtPSADeconvFitBaseline() = default;

AtPSADeconv::HitData AtPSADeconvFitBaseline::getZandQ(const AtPad::trace &charge)
{
   // Get initial guess for hit. Z loc is max and std dev is estimated from diffusion
   auto maxTB = std::max_element(begin(charge), end(charge));
   auto zTB = static_cast<double>(std::distance(begin(charge), maxTB));

   auto sigTB = getSigTB(zTB); // [us] drift velocity is cm/us

   // Create a historgram to fit and fit to range mean +- 4 sigma.
   auto id = std::hash<std::thread::id>{}(std::this_thread::get_id());
   if (fHist)
      ContainerManip::SetHistFromData(*fHist, charge);
   else
      fHist = ContainerManip::CreateHistFromData<TH1F>(TString::Format("%lu", id).Data(), charge);

   // Add an addition +-2 for when we are close to the pad plane and diffusion is small
   auto fitRange = 3 * sigTB + 2;
   if (fitRange < 3)
      fitRange = 3;

   TF1 gauss(TString::Format("fitGauss%lu", id), "gaus(0)", zTB - fitRange, zTB + fitRange, TF1::EAddToList::kNo);
   gauss.SetParameter(0, *maxTB); // Set initial height of gaussian
   gauss.SetParameter(1, zTB);    // Set initial position of gaussian
   gauss.SetParameter(2, sigTB);  // Set initial sigma of gaussian

   // Fit without graphics and saving everything in the result ptr
   // auto resultPtr = hist->Fit(&gauss, "SQNR");
   auto result = FitHistorgramParallel(*fHist, gauss);
   if (!result.IsValid()) {
      LOG(info) << "Fit did not converge using initial conditions:"
                << " mean: " << zTB << " sig:" << sigTB << " max:" << *maxTB;
      return {};
   }

   auto amp = result.GetParams()[0];
   auto z = result.GetParams()[1];
   auto sig = result.GetParams()[2];

   // auto Q = amp * sig * std::sqrt(2 * TMath::Pi());
   auto begin = zTB - z * 3;
   auto end = zTB + z * 3;
   TF1 Baseline(TString::Format("Baseline%lu", id), "[0]*exp(-0.5*((x-[1])/[2])^2) + [3] + [4]*x", begin, end,
                TF1::EAddToList::kNo);
   Baseline.SetParameter(0, *maxTB); // Set initial height of gaussian
   Baseline.SetParameter(1, zTB);    // Set initial position of gaussian
   Baseline.SetParameter(2, sig);    // Set initial sigma of gaussian
   Baseline.SetParameter(3, 0);      // Set initial intercept of the line
   Baseline.SetParameter(4, 0);

   auto result2 = FitHistorgramParallel(*fHist, Baseline);

   if (!result2.IsValid()) {
      LOG(info) << "Fit did not converge using initial conditions:"
                << " mean: " << zTB << " sig:" << sigTB << " max:" << *maxTB;
      return {};
   }
   auto amp2 = result2.GetParams()[0];
   auto z2 = result2.GetParams()[1];
   auto sig2 = result2.GetParams()[2];
   auto Q = amp2 * sig2 * std::sqrt(2 * TMath::Pi());

   LOG(debug) << "Initial: " << *maxTB << " " << zTB << " " << sigTB;
   LOG(debug) << "Fit: " << amp << " " << z << " " << sig;

   return {{z2, sig2 * sig2, Q, 0}};
}