#include <cmath>
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

const int PDG_CUT = 2212;

const double B_MIN_CUT = 4.6;
const double B_MAX_CUT = 9.2;

const double Q2_A_MIN_PT_CUT = 0.4;
const double Q2_A_MAX_PT_CUT = 2.0;
const double Q2_A_MIN_ETA_CUT = -5.0;
const double Q2_A_MAX_ETA_CUT = -2.0;
const double Q2_B_MIN_PT_CUT = 0.4;
const double Q2_B_MAX_PT_CUT = 2.0;
const double Q2_B_MIN_ETA_CUT = 2.0;
const double Q2_B_MAX_ETA_CUT = 5.0;
const double PT_C_MIN_Y_CUT = -0.5;
const double PT_C_MAX_Y_CUT = -0.5;

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

  // pt-y, pt-eta plots for A, B, C sub-events
  TH2D *h2_v02_A_ptY = new TH2D("h2_v02_A_ptY", "dN/dp_{T}dy_{CM} for A;y_{CM};p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);
  TH2D *h2_v02_B_ptY = new TH2D("h2_v02_B_ptY", "dN/dp_{T}dy_{CM} for B;y_{CM};p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);
  TH2D *h2_v02_C_ptY = new TH2D("h2_v02_C_ptY", "dN/dp_{T}dy_{CM} for C;y_{CM};p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);

  TH2D *h2_v02_A_pteta = new TH2D("h2_v02_A_pteta", "dN/dp_{T}d#eta for A;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);
  TH2D *h2_v02_B_pteta = new TH2D("h2_v02_B_pteta", "dN/dp_{T}d#eta for B;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);
  TH2D *h2_v02_C_pteta = new TH2D("h2_v02_C_pteta", "dN/dp_{T}d#eta for C;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 500, 0., 5.);

  // Correlations needed for v02
  int nptbins = 50;
  TProfile *p_v02_b_ABC = new TProfile("p_v02_b_ABC", "<ABC> vs. p_{T} in b-cent;p_{T}, GeV/c; <ABC>", nptbins, 0., 5.);
  TProfile *p_v02_b_C = new TProfile("p_v02_b_C", "<C> vs. p_{T} in b-cent;p_{T}, GeV/c; <C>", nptbins, 0., 5.);
  TProfile *p_v02_b_AB = new TProfile("p_v02_b_AB", "<AB> in b-cent bin;b-cent bin; <AB>", 1, 0., 1.);


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
  int Nparticles;

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

    // Basic centrality selection
    if (event->GetB() < B_MIN_CUT) continue;
    if (event->GetB() > B_MAX_CUT) continue;

    Nparticles = event->GetNparticles();
    double Na=0., Qax=0., Qay=0., Nb=0., Qbx=0., Qby=0., Nc=0.;
    double Ncpt[nptbins];
    for (int i=0; i<nptbins; i++) Ncpt[i] = 0.;
    for (int iparticle = 0; iparticle < Nparticles; iparticle++)
    {
      particle = readerManager->ReadParticle(iparticle);

      if (!particle)
        continue;

      // collect A sub-event
      if (particle->GetEta() > Q2_A_MIN_ETA_CUT && particle->GetEta() < Q2_A_MAX_ETA_CUT &&
          particle->GetPt() > Q2_A_MIN_PT_CUT && particle->GetPt() < Q2_A_MAX_PT_CUT) {
            Na++;
            Qax += cos( 2.0 * particle->GetPhi() );
            Qay += sin( 2.0 * particle->GetPhi() );
      }

      // collect B sub-event
      if (particle->GetEta() > Q2_B_MIN_ETA_CUT && particle->GetEta() < Q2_B_MAX_ETA_CUT &&
          particle->GetPt() > Q2_B_MIN_PT_CUT && particle->GetPt() < Q2_B_MAX_PT_CUT) {
            Nb++;
            Qbx += cos( 2.0 * particle->GetPhi() );
            Qby += sin( 2.0 * particle->GetPhi() );
      }

      // collect C sub-event
      double ycm = 0.5 * TMath::Log((particle->GetEnergy() + particle->GetPz()) / (particle->GetEnergy() - particle->GetPz()));
      if (particle->GetEta() > PT_C_MIN_Y_CUT && particle->GetEta() < PT_C_MAX_Y_CUT &&
          ycm > PT_C_MIN_Y_CUT && ycm < PT_C_MAX_Y_CUT) {
            Nc++;
             if (particle->GetPdg() == PDG_CUT) Ncpt[p_v02_b_C->FindBin(particle->GetPt()) - 1]++;
      }

      delete particle;
    }

    // Scale A,B,C properly
    if (Na == 0 || Nb == 0 || Nc == 0) continue;
    Qax /= Na; Qay /= Na;
    Qbx /= Nb; Qby /= Nb;
    for (int i=0; i<nptbins; i++) Ncpt[i] /= Nc;

    p_v02_b_AB->Fill( 1., Qax*Qbx + Qay*Qby );
    for (int i=0; i<nptbins; i++) p_v02_b_C->Fill( p_v02_b_C->GetBinCenter(i+1), Ncpt[i] );
    for (int i=0; i<nptbins; i++) p_v02_b_ABC->Fill( p_v02_b_C->GetBinCenter(i+1), (Qax*Qbx + Qay*Qby) * Ncpt[i] );

    delete event;
  }

  std::cout << "Loop is closed, " << Absolute_counter << " events were counted." << std::endl;

  fo->cd();

  p_v02_b_ABC->Write();
  p_v02_b_AB->Write();
  p_v02_b_C->Write();

  fo->Close();

  timer.Stop();
  timer.Print();

  return 0;
}
