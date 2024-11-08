#include "FairLogger.h"

// Macro to fit data using BaselineDeconv code on the HPC
// Loads in a data file containing Bi200 fission events.
// It coppies the data into a new file, and then re-fits the traces in the
// data using the BaselineDeconv code.
void runFitting()
{

   auto verbSpec =
      fair::VerbositySpec::Make(fair::VerbositySpec::Info::severity, fair::VerbositySpec::Info::file_line_function);
   fair::Logger::DefineVerbosity("user1", verbSpec);
   // fair::Logger::SetVerbosity("user1");
   // fair::Logger::SetConsoleSeverity("debug");
   TString sharedInfoDir = "~/fission/data/e12014/tpcSharedInfo/";
   TString path = "~/fission/data/e12014/unpacked/";
   TString InputDataFile = path + "/Bi200.root";
   TString OutputDataFile = path + "/baselineFit/Bi200.root";

   TString dir = getenv("VMCWORKDIR");
   TString geoFile = "ATTPC_v1.1_geomanager.root";
   TString mapFile = "e12014_pad_map_size.xml";
   TString parFile = "ATTPC.e12014.par";

   TString InputDataPath = InputDataFile;
   TString OutputDataPath = OutputDataFile;
   TString GeoDataPath = dir + "/geometry/" + geoFile;
   TString mapDir = dir + "/scripts/" + mapFile;

   // Create the input and output for the data and create the run to manage the tasks
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

   E12014::CreateMap();
   auto fMap = E12014::fMap;

   AtCopyTreeTask *copyTask = new AtCopyTreeTask();

   AtRawEvent *respAvgEvent;
   TFile *f2 = new TFile(sharedInfoDir + "respAvg.root");
   f2->GetObject("avgResp", respAvgEvent);
   f2->Close();

   // Create PSA task this is the uncorrected data
   auto psa = std::make_unique<AtPSADeconvFitBaseline>();
   psa->SetResponse(*respAvgEvent);
   psa->SetThreshold(15); // Threshold in charge units
   psa->SetFilterOrder(6);
   psa->SetCutoffFreq(75);
   AtPSAtask *psaTask = new AtPSAtask(std::move(psa));
   psaTask->SetInputBranch("AtRawEventRaw");

   fRun->AddTask(reduceTask);
   fRun->AddTask(copyTask);
   fRun->AddTask(fitTask);

   auto initStart = std::chrono::high_resolution_clock::now();
   fRun->Init();
   auto runStart = std::chrono::high_resolution_clock::now();
   // fRun->Run(0, 4);
   // fRun->Run(0, 100);
   // fRun->Run(0, 2000);
   fRun->Run();
   auto runStop = std::chrono::high_resolution_clock::now();

   LOG(info) << "Run processed in "
             << std::chrono::duration_cast<std::chrono::milliseconds>(runStop - initStart).count() / (double)1000
             << " seconds.";
}
