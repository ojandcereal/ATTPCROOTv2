#include "AtPSADeconvFitBaseline.h"
#include "AtRunAna.h"
#include <FairParAsciiFileIo.h>
#include <FairRuntimeDb.h>

#include <gtest/gtest.h>

TEST(AtPSADeconvFitBaselineTest, Init)
{
   AtRunAna *fRun = new AtRunAna();
   TString parFile = "ATTPC.e12014.par";

   TString dir = getenv("VMCWORKDIR");
   FairParAsciiFileIo *parIo1 = new FairParAsciiFileIo();
   parIo1->open(dir + "/parameters/" + parFile, "in");
   fRun->GetRuntimeDb()->setFirstInput(parIo1);
   fRun->GetRuntimeDb()->getContainer("AtDigiPar");

   AtPSADeconvFitBaseline fit;
   fit.Init();
   //  Add assertions to check if the object is initialized properly
   EXPECT_EQ(fit.GetDiffLong(), 0);
}