#include "AtDigiPar.h"

#include <gtest/gtest.h>
/**
 * @brief Test fixture for AtPSA that creates a default AtDigiPar object to use.
 * @ingroup Testing
 */
class AtPSATestFixture : public ::testing::Test {

protected:
   std::unique_ptr<AtDigiPar> fPar;

   void SetUp() override
   {
      fPar = std::make_unique<AtDigiPar>("", "", "");
      fPar->fEField = 70000;
      fPar->fBField = 0.0;
      fPar->fTBEntrance = 457;
      fPar->fZPadPlane = 1000.0;
      fPar->fEIonize = 42.70;
      fPar->fFano = 0.24;
      fPar->fCoefL = 0.0055;
      fPar->fCoefT = 0.0038;
      fPar->fGasPressure = 800;
      fPar->fDensity = 0.175;
      fPar->fDriftVelocity = 0.815;
      fPar->fGain = 1000;
      fPar->fSamplingRate = 3;
      fPar->fGETGain = 1000;
      fPar->fPeakingTime = 720;
   }

   void TearDown() override {}
};