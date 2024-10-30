#include "AtPSADeconvFitBaseline.h"

#include "AtPSATestFixture.h"

#include <FairParAsciiFileIo.h>
#include <FairRuntimeDb.h>

#include <gtest/gtest.h>

class AtPSADeconvFitBaselineTestFixture : public AtPSATestFixture {

protected:
   std::unique_ptr<AtPSADeconvFitBaseline> fit;

   virtual void SetUp() override
   {
      AtPSATestFixture::SetUp();

      // Set any AtDigiPar parameters here if needed
      fPar->fDriftVelocity = 0.815; // As an example. This is the default value for e12014.

      // Create the object to test and setup any parameters
      fit = std::make_unique<AtPSADeconvFitBaseline>();
      fit->Init(fPar.get());
   }
};

TEST_F(AtPSADeconvFitBaselineTestFixture, Init)
{
   // Add assertions to check if the object is initialized properly
   EXPECT_TRUE(true);
}
