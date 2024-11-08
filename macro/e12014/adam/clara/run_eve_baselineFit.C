/*#include "TString.h"
#include "AtEventDrawTask.h"
#include "AtEventManager.h"

#include "FairParRootFileIo.h"
#include "FairRunAna.h"
*/
#include "FairLogger.h"

void run_eve_baselineFit()
{

   auto verbSpec =
      fair::VerbositySpec::Make(fair::VerbositySpec::Info::severity, fair::VerbositySpec::Info::file_line_function);
   fair::Logger::DefineVerbosity("user1", verbSpec);
   // fair::Logger::SetVerbosity("user1");
   // fair::Logger::SetConsoleSeverity("debug");

   TString sharedInfoDir = "~/fission/data/e12014/tpcSharedInfo/";
   TString path = "~/fission/data/e12014/unpacked/";
   TString InputDataFile = path + "/Bi200.root";
   TString OutputDataFile = "./data/output.reco_display.root";

   TString dir = getenv("VMCWORKDIR");
   TString geoFile = "ATTPC_v1.1_geomanager.root";
   TString mapFile = "e12014_pad_map_size.xml";
   TString parFile = "ATTPC.e12014.par";

   TString InputDataPath = InputDataFile;
   TString OutputDataPath = OutputDataFile;
   TString GeoDataPath = dir + "/geometry/" + geoFile;
   TString mapDir = dir + "/scripts/" + mapFile;

   FairRunAna *fRun = new FairRunAna();
   FairRootFileSink *sink = new FairRootFileSink(OutputDataFile);
   FairFileSource *source = new FairFileSource(InputDataFile);
   fRun->SetSource(source);
   fRun->SetSink(sink);
   fRun->SetGeomFile(GeoDataPath);

   // Load all of the parameters
   FairParAsciiFileIo *parIo1 = new FairParAsciiFileIo();
   parIo1->open(dir + "/parameters/" + parFile, "in");
   fRun->GetRuntimeDb()->setFirstInput(parIo1);
   fRun->GetRuntimeDb()->getContainer("AtDigiPar");

   auto fMap = std::make_shared<AtTpcMap>();
   fMap->ParseXMLMap(mapDir.Data());

   // Create viewer manager
   auto eveMan = new AtViewerManager(fMap);

   auto tabMain = std::make_unique<AtTabFission>();

   auto tabPad = std::make_unique<AtTabPad>(2, 2);
   tabPad->DrawRawADC(0, 0);
   tabPad->DrawADC(0, 1);
   tabPad->DrawArrayAug("Qreco", 1, 1);
   tabPad->DrawHits(1, 1);
   tabPad->DrawHits(0, 0);

   // Create PSA task this is the uncorrected data
   auto psa = std::make_unique<AtPSADeconvFitBaseline>();
   psa->SetUseCharge(true);
   AtPSAtask *psaTask = new AtPSAtask(std::move(psa));
   psaTask->SetInputBranch("AtRawEventRaw");
   psaTask->SetOutputBranch("AtEventBaselineFit");
   eveMan->AddTask(psaTask);

   auto method = std::make_unique<SampleConsensus::AtSampleConsensus>(
      SampleConsensus::Estimators::kYRANSAC, AtPatterns::PatternType::kFission, RandomSample::SampleMethod::kY);
   method->SetDistanceThreshold(20);
   method->SetNumIterations(500);
   method->SetMinHitsPattern(150);
   method->SetChargeThreshold(10); //-1 implies no charge-weighted fitting
   method->SetFitPattern(true);
   auto sacTask = new AtSampleConsensusTask(std::move(method));
   sacTask->SetPersistence(false);
   sacTask->SetInputBranch("AtEventBaselineFit");
   sacTask->SetOutputBranch("AtPatternEvent");
   eveMan->AddTask(sacTask);

   AtFissionTask *fissionTask = new AtFissionTask();
   fissionTask->SetUncorrectedEventBranch("AtEventBaselineFit");
   fissionTask->SetPatternBranch("AtPatternEvent");
   fissionTask->SetOutBranch("AtFissionEventBaseline");
   fissionTask->SetPersistance(false);
   eveMan->AddTask(fissionTask);

   auto &fissionBranch = tabMain->GetFissionBranch();
   auto tabFF = std::make_unique<AtTabFF>(fissionBranch, false);

   eveMan->AddTab(std::move(tabMain));
   eveMan->AddTab(std::move(tabPad));
   eveMan->AddTab(std::move(tabFF));

   eveMan->Init();

   std::cout << "Finished init" << std::endl;
}
