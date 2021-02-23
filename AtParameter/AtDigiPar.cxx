#include "AtDigiPar.h"

ClassImp(AtDigiPar)

   AtDigiPar::AtDigiPar(const Char_t *name, const Char_t *title, const Char_t *context)
   : FairParGenericSet("AtDigiPar", "AtTPC Parameter Container", ""), fGas(NULL)
{
   fInitialized = kFALSE;

   fLogger = FairLogger::GetLogger();
}

AtDigiPar::~AtDigiPar() {}

// Getters
Int_t AtDigiPar::GetPadPlaneX()
{
   return fPadPlaneX;
}
Int_t AtDigiPar::GetPadPlaneZ()
{
   return fPadPlaneZ;
}
Int_t AtDigiPar::GetPadSizeX()
{
   return fPadSizeX;
}
Int_t AtDigiPar::GetPadSizeZ()
{
   return fPadSizeZ;
}
Int_t AtDigiPar::GetPadRows()
{
   return fPadRows;
}
Int_t AtDigiPar::GetPadLayers()
{
   return fPadLayers;
}
Double_t AtDigiPar::GetAnodeWirePlaneY()
{
   return fAnodeWirePlaneY;
}
Double_t AtDigiPar::GetGroundWirePlaneY()
{
   return fGroundWirePlaneY;
}
Double_t AtDigiPar::GetGatingWirePlaneY()
{
   return fGatingWirePlaneY;
}
Int_t AtDigiPar::GetNumTbs()
{
   return fNumTbs;
}
Double_t AtDigiPar::GetDriftVelocity()
{
   return fDriftVelocity;
}
Double_t AtDigiPar::GetDriftLength()
{
   return fDriftLength;
}
Int_t AtDigiPar::GetYDivider()
{
   return fYDivider;
}
Double_t AtDigiPar::GetBField()
{
   return fBField;
}
Double_t AtDigiPar::GetEField()
{
   return fEField;
}
Double_t AtDigiPar::GetTiltAngle()
{
   return fTiltAng;
}
Int_t AtDigiPar::GetTB0()
{
   return fTB0;
}
Double_t AtDigiPar::GetThetaLorentz()
{
   return fThetaLorentz;
}
Int_t AtDigiPar::GetTBEntrance()
{
   return fTBEntrance;
}
Double_t AtDigiPar::GetZPadPlane()
{
   return fZPadPlane;
}
Double_t AtDigiPar::GetDensity()
{
   return fDensity;
}
Double_t AtDigiPar::GetThetaPad()
{
   return fThetaPad;
}
Double_t AtDigiPar::GetThetaRot()
{
   return fThetaRot;
}
Double_t AtDigiPar::GetGasPressure()
{
   return fGasPressure;
}
Double_t AtDigiPar::GetEIonize()
{
   return fEIonize;
}
Double_t AtDigiPar::GetFano()
{
   return fFano;
}
Double_t AtDigiPar::GetCoefDiffusionLong()
{
   return fCoefL;
}
Double_t AtDigiPar::GetCoefDiffusionTrans()
{
   return fCoefT;
}
Double_t AtDigiPar::GetGain()
{
   return fGain;
}
Double_t AtDigiPar::GetGETGain()
{
   return fGETGain;
}
Int_t AtDigiPar::GetPeakingTime()
{
   return fPeakingTime;
}
Double_t AtDigiPar::GetMaxRange()
{
   return fMaxRange;
}

AtGas *AtDigiPar::GetGas()
{
   if (fGas == NULL) {
      std::cerr << "Initializing gas file with " << fGasFileName.Data() << std::endl;
      fGas = new AtGas(fGasFileName.Data());
   }
   return fGas;
   // return new STGas(*fGas);
}

Int_t AtDigiPar::GetTBTime()
{

   switch (fSamplingRate) {
   case 3: return 320;
   case 6: return 160;
   case 12: return 80;
   case 25: return 40;
   case 50: return 20;
   case 100: return 10;
   default: return -1;
   }
}

Bool_t AtDigiPar::getParams(FairParamList *paramList) // TODO Change all these parameters
{
   if (!paramList) {
      fLogger->Fatal(MESSAGE_ORIGIN, "Parameter list doesn't exist!");
      return kFALSE;
   }

   if (!fInitialized) {
      if (!(paramList->fill("PadPlaneX", &fPadPlaneX))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadPlaneX parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadPlaneZ", &fPadPlaneZ))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadPlaneZ parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadSizeX", &fPadSizeX))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadSizeX parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadSizeZ", &fPadSizeZ))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadSizeZ parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadRows", &fPadRows))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadRows parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadLayers", &fPadLayers))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadRows parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("AnodeWirePlaneY", &fAnodeWirePlaneY))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find AnodeWirePlaneY parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("GroundWirePlaneY", &fGroundWirePlaneY))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find GroundWirePlaneY parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("GatingWirePlaneY", &fGatingWirePlaneY))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find GatingWirePlaneY parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("EField", &fEField))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find EField parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("NumTbs", &fNumTbs))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find NumTbs parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("SamplingRate", &fSamplingRate))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find SamplingRate parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("DriftVelocity", &fDriftVelocity))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find DriftVelocity parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("DriftLength", &fDriftLength))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find DriftLength parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("YDivider", &fYDivider))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find YDivider parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("GasFile", &fGasFile))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find GasFile parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadPlaneFile", &fPadPlaneFile))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadPlaneFile parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("PadShapeFile", &fPadShapeFile))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PadShapeFile parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("BField", &fBField))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find BField parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("TiltAng", &fTiltAng))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find TiltAng parameter!");
         return kFALSE;
      }
      if (!(paramList->fill("TB0", &fTB0))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find TB0 parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("LorentzAngle", &fThetaLorentz))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find LorentzAngle parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("TBEntrance", &fTBEntrance))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find TBEntrance parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("ZPadPlane", &fZPadPlane))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find ZPadPlane parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("Density", &fDensity))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find Density parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("ThetaPad", &fThetaPad))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find ThetaPad parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("ThetaRot", &fThetaRot))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find ThetaRot parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("GasPressure", &fGasPressure))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find GasPressure parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("EIonize", &fEIonize))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find EIonize parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("Fano", &fFano))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find Fano parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("CoefL", &fCoefL))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find CoefL parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("CoefT", &fCoefT))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find CoefT parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("Gain", &fGain))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find Gain parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("GETGain", &fGETGain))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find GETGain parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("PeakingTime", &fPeakingTime))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find PeakingTime parameter!");
         return kFALSE;
      }

      if (!(paramList->fill("MaxRange", &fMaxRange))) {
         fLogger->Fatal(MESSAGE_ORIGIN, "Cannot find Gain parameter!");
         return kFALSE;
      }

      fGasFileName = GetFile(fGasFile);
   }

   return kTRUE;
}

void AtDigiPar::putParams(FairParamList *paramList)
{
   if (!paramList) {
      fLogger->Fatal(MESSAGE_ORIGIN, "Parameter list doesn't exist!");
      return;
   }

   paramList->add("PadPlaneX", fPadPlaneX);
   paramList->add("PadPlaneZ", fPadPlaneZ);
   paramList->add("PadSizeX", fPadSizeX);
   paramList->add("PadSizeZ", fPadSizeZ);
   paramList->add("PadRows", fPadRows);
   paramList->add("PadLayers", fPadLayers);
   paramList->add("AnodeWirePlaneY", fAnodeWirePlaneY);
   paramList->add("GroundWirePlaneY", fGroundWirePlaneY);
   paramList->add("GatingWirePlaneY", fGatingWirePlaneY);
   paramList->add("EField", fEField);
   paramList->add("NumTbs", fNumTbs);
   paramList->add("SamplingRate", fSamplingRate);
   paramList->add("DriftVelocity", fDriftVelocity);
   paramList->add("DriftLength", fDriftLength);
   paramList->add("YDivider", fYDivider);
   paramList->add("GasFile", fGasFile);
   paramList->add("PadPlaneFile", fPadPlaneFile);
   paramList->add("PadShapeFile", fPadShapeFile);
   paramList->add("BField", fBField);
   paramList->add("TiltAng", fTiltAng);
   paramList->add("TB0", fTB0);
   paramList->add("LorentzAngle", fThetaLorentz);
   paramList->add("TBEntrance", fTBEntrance);
   paramList->add("ZPadPlane", fZPadPlane);
   paramList->add("Density", fDensity);
   paramList->add("ThetaPad", fThetaPad);
   paramList->add("ThetaRot", fThetaRot);
   paramList->add("GasPressure", fGasPressure);
   paramList->add("EIonize", fEIonize);
   paramList->add("Fano", fFano);
   paramList->add("CoefL", fCoefL);
   paramList->add("CoefT", fCoefT);
   paramList->add("Gain", fGain);
   paramList->add("GETGain", fGETGain);
   paramList->add("PeakingTime", fPeakingTime);
   paramList->add("MaxRange", fMaxRange);
}

TString AtDigiPar::GetFile(Int_t fileNum)
{
   std::ifstream fileList;
   TString sysFile = gSystem->Getenv("VMCWORKDIR");
   TString parFile = sysFile + "/parameters/At.files.par";
   fileList.open(parFile.Data());

   if (!fileList) {
      fLogger->Fatal(MESSAGE_ORIGIN, Form("File %s not found!", parFile.Data()));

      throw;
   }

   Char_t buffer[256];
   for (Int_t iFileNum = 0; iFileNum < fileNum + 1; ++iFileNum) {
      if (fileList.eof()) {
         fLogger->Fatal(MESSAGE_ORIGIN, Form("Did not find string #%d in file %s.", fileNum, parFile.Data()));

         throw;
      }

      fileList.getline(buffer, 256);
   }

   fileList.close();

   return TString(sysFile + "/" + buffer);
}
