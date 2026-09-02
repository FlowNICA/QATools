#include <iostream>
#include <vector>

#include <TString.h>
#include <TH1D.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TProfile2D.h>
// #include <TProfile3D.h>
#include <TFile.h>
#include <TStopwatch.h>

#include <qaParticle.h>
#include <qaParticleLight.h>
#include <qaEvent.h>
#include <qaReader_manager.h>
#include <qaReader_smash_root.h>
#include <qaReader_epos4_root.h>
#include <qaReader_mcpico.h>
#include <Utility.h>

#ifdef _MCINI_
#include <qaReader_mcini.h>
#endif
#ifdef _PHQMD_
#include <qaReader_phqmd.h>
#endif
#ifdef _HSD_ROOT_
#include <qaReader_hsd_root.h>
#endif

int main(int argc, char **argv)
{
  TString iFileName, oFileName = "";

  if (argc < 7)
  {
    std::cerr << "./calcv02 -i input.list -o qa_output.root -format [FORMAT]" << std::endl;
    std::cerr << "Available formats:" << std::endl;
    std::cerr << "\tmcpico - simple custom ROOT format to store model data" << std::endl;
    std::cerr << "\tparticle - ROOT format that is used by the SMASH model" << std::endl;
    std::cerr << "\tepos4root - ROOT format that is used by the EPOS4 model" << std::endl;
  #ifdef _MCINI_
    std::cerr << "\tmcini - custom ROOT format to store both initial state and final state (UniGen data format) model data" << std::endl;
  #endif
  #ifdef _PHQMD_
    std::cerr << "\tphqmd - custom ROOT format to store PHQMD (with MST) model data" << std::endl;
  #endif
  #ifdef _HSD_ROOT_
    std::cerr << "\thsd - custom ROOT format to store HSD model data" << std::endl;
  #endif
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "-format")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-format" && i != argc - 1)
      {
        qaUtility::GetInstance()->format = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-format" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  TStopwatch timer;
  timer.Start();

  TFile *fo = new TFile(oFileName, "recreate");

  // pt-y plots for A, B, C sub-events
  TH2D *h2_v02_ParticleA_PID_ptY[qaUtility::GetInstance()->npid];
  TH2D *h2_v02_ParticleB_PID_ptY[qaUtility::GetInstance()->npid];
  TH2D *h2_v02_ParticleC_PID_ptY[qaUtility::GetInstance()->npid];



  qaReader_manager *readerManager;
  if (qaUtility::GetInstance()->format == "mcpico")
  {
    readerManager = new qaReader_mcpico();
  }
#ifdef _MCINI_
  if (qaUtility::GetInstance()->format == "mcini")
  {
    readerManager = new qaReader_mcini();
  }
#endif
#ifdef _PHQMD_
  if (qaUtility::GetInstance()->format == "phqmd")
  {
    readerManager = new qaReader_phqmd();
  }
#endif
#ifdef _HSD_ROOT_
  if (qaUtility::GetInstance()->format == "hsd")
  {
    readerManager = new qaReader_hsd_root();
  }
#endif
  if (qaUtility::GetInstance()->format == "particles")
  {
    readerManager = new qaReader_smash_root();
  }
  if (qaUtility::GetInstance()->format == "epos4root")
  {
    readerManager = new qaReader_epos4_root();
  }

  if (!readerManager)
  {
    std::cerr << "This input format is not found!" << std::endl;
    return 20;
  }

  readerManager->SetChain(iFileName.Data());

  std::vector<Long64_t> vRejectedEvents;

  Long64_t Nentries_chain = readerManager->GetEntries();
  Long64_t Nentries = (qaUtility::GetInstance()->Nevents > Nentries_chain) ? Nentries_chain : qaUtility::GetInstance()->Nevents;
  if (qaUtility::GetInstance()->Nevents == -1)
    Nentries = Nentries_chain;

  qaEvent *event = nullptr;
  qaParticle *particle = nullptr;

  Long64_t Absolute_counter = 0;
  Int_t ipid;

  while (Absolute_counter < Nentries)
  {
    //if (Minbias_counter % 1000 == 0)
      std::cout << "Event [" << Absolute_counter << "/" << Nentries << "]" << std::endl;

    event = (qaEvent *)readerManager->ReadEvent(Absolute_counter);
    Absolute_counter++;

    if (Absolute_counter > Nentries_chain)
      break;

    if (!event)
      continue;

    Nparticles = event->GetNparticles();
    for (int iparticle = 0; iparticle < Nparticles; iparticle++)
    {
      particle = readerManager->ReadParticle(iparticle);

      if (!particle)
        continue;


      delete particle;
    }

    delete event;
  }

  std::cout << "Loop is closed, " << Absolute_counter << " events were counted." << std::endl;

  fo->cd();

  fo->Close();

  timer.Stop();
  timer.Print();

  return 0;
}
