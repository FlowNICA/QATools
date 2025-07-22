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
  TString iFileName, oFileName, configFileName = "";

  if (argc < 7)
  {
    std::cerr << "./qaProcess -i input.list -o qa_output.root -format [FORMAT] [OPTIONAL: -config qa.cfg]" << std::endl;
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
        std::string(argv[i]) != "-format" &&
        std::string(argv[i]) != "-config")
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
      if (std::string(argv[i]) == "-config" && i != argc - 1)
      {
        configFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-config" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  TStopwatch timer;
  timer.Start();

  Bool_t IsRead = true;

  if (configFileName.Length() > 0)
  {
    IsRead = qaUtility::GetInstance()->ReadConfig(configFileName);
  }

  if (!IsRead)
  {
    std::cerr << "Error while reading config file. Exiting..." << std::endl;
    return 2;
  }

  if (qaUtility::GetInstance()->debug)
  {
    std::cout << "Format = " << qaUtility::GetInstance()->format << std::endl;
    std::cout << "Configuration:" << std::endl;
    std::cout << "debug = " << qaUtility::GetInstance()->debug << std::endl;
    std::cout << "Nevents = " << qaUtility::GetInstance()->Nevents << std::endl;
    if (qaUtility::GetInstance()->Is_minbias)
    {
      std::cout << "Is_minbias = " << qaUtility::GetInstance()->Is_minbias << std::endl;
      std::cout << "Cut_minbias_Event_bmin = " << qaUtility::GetInstance()->Cut_minbias_Event_bmin << std::endl;
      std::cout << "Cut_minbias_Event_bmax = " << qaUtility::GetInstance()->Cut_minbias_Event_bmax << std::endl;
      std::cout << "Cut_minbias_Particle_ptmin = " << qaUtility::GetInstance()->Cut_minbias_Particle_ptmin << std::endl;
      std::cout << "Cut_minbias_Particle_ptmax = " << qaUtility::GetInstance()->Cut_minbias_Particle_ptmax << std::endl;
      std::cout << "Cut_minbias_Particle_etamin = " << qaUtility::GetInstance()->Cut_minbias_Particle_etamin << std::endl;
      std::cout << "Cut_minbias_Particle_etamax = " << qaUtility::GetInstance()->Cut_minbias_Particle_etamax << std::endl;
      std::cout << "Cut_minbias_Particle_ymin = " << qaUtility::GetInstance()->Cut_minbias_Particle_ymin << std::endl;
      std::cout << "Cut_minbias_Particle_ymax = " << qaUtility::GetInstance()->Cut_minbias_Particle_ymax << std::endl;
    }
    if (qaUtility::GetInstance()->Is_refmult)
    {
      std::cout << "Is_refmult = " << qaUtility::GetInstance()->Is_refmult << std::endl;
      std::cout << "Cut_refmult_Event_bmin = " << qaUtility::GetInstance()->Cut_refmult_Event_bmin << std::endl;
      std::cout << "Cut_refmult_Event_bmax = " << qaUtility::GetInstance()->Cut_refmult_Event_bmax << std::endl;
      std::cout << "Cut_refmult_Particle_ptmin = " << qaUtility::GetInstance()->Cut_refmult_Particle_ptmin << std::endl;
      std::cout << "Cut_refmult_Particle_ptmax = " << qaUtility::GetInstance()->Cut_refmult_Particle_ptmax << std::endl;
      std::cout << "Cut_refmult_Particle_etamin = " << qaUtility::GetInstance()->Cut_refmult_Particle_etamin << std::endl;
      std::cout << "Cut_refmult_Particle_etamax = " << qaUtility::GetInstance()->Cut_refmult_Particle_etamax << std::endl;
      std::cout << "Cut_refmult_Particle_isCharged = " << qaUtility::GetInstance()->Cut_refmult_Particle_isCharged << std::endl;
    }
    if (qaUtility::GetInstance()->Is_v1)
    {
      std::cout << "Is_v1 = " << qaUtility::GetInstance()->Is_v1 << std::endl;
      std::cout << "Cut_v1_Event_bmin = " << qaUtility::GetInstance()->Cut_v1_Event_bmin << std::endl;
      std::cout << "Cut_v1_Event_bmax = " << qaUtility::GetInstance()->Cut_v1_Event_bmax << std::endl;
      std::cout << "Cut_v1_Event_bCent[" << qaUtility::GetInstance()->Cut_v1_Event_bCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v1_Event_bCent.size(); i++)
      {
        std::cout << qaUtility::GetInstance()->Cut_v1_Event_bCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v1_Event_bCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v1_Event_mCent[" << qaUtility::GetInstance()->Cut_v1_Event_mCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v1_Event_mCent.size(); i++)
      {
        std::cout << (int)qaUtility::GetInstance()->Cut_v1_Event_mCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v1_Event_mCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v1_Particle_ptmin = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmin << std::endl;
      std::cout << "Cut_v1_Particle_ptmax = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmax << std::endl;
      std::cout << "Cut_v1_Particle_etamin = " << qaUtility::GetInstance()->Cut_v1_Particle_etamin << std::endl;
      std::cout << "Cut_v1_Particle_etamax = " << qaUtility::GetInstance()->Cut_v1_Particle_etamax << std::endl;
      std::cout << "Cut_v1_Particle_ymin = " << qaUtility::GetInstance()->Cut_v1_Particle_ymin << std::endl;
      std::cout << "Cut_v1_Particle_ymax = " << qaUtility::GetInstance()->Cut_v1_Particle_ymax << std::endl;
      std::cout << "Cut_v1_Particle_ptmin_pi = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmin_pi << std::endl;
      std::cout << "Cut_v1_Particle_ptmax_pi = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmax_pi << std::endl;
      std::cout << "Cut_v1_Particle_ymin_pi = " << qaUtility::GetInstance()->Cut_v1_Particle_ymin_pi << std::endl;
      std::cout << "Cut_v1_Particle_ymax_pi = " << qaUtility::GetInstance()->Cut_v1_Particle_ymax_pi << std::endl;
      std::cout << "Cut_v1_Particle_ptmin_ka = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmin_ka << std::endl;
      std::cout << "Cut_v1_Particle_ptmax_ka = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmax_ka << std::endl;
      std::cout << "Cut_v1_Particle_ymin_ka = " << qaUtility::GetInstance()->Cut_v1_Particle_ymin_ka << std::endl;
      std::cout << "Cut_v1_Particle_ymax_ka = " << qaUtility::GetInstance()->Cut_v1_Particle_ymax_ka << std::endl;
      std::cout << "Cut_v1_Particle_ptmin_pr = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmin_pr << std::endl;
      std::cout << "Cut_v1_Particle_ptmax_pr = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmax_pr << std::endl;
      std::cout << "Cut_v1_Particle_ymin_pr = " << qaUtility::GetInstance()->Cut_v1_Particle_ymin_pr << std::endl;
      std::cout << "Cut_v1_Particle_ymax_pr = " << qaUtility::GetInstance()->Cut_v1_Particle_ymax_pr << std::endl;
      std::cout << "Cut_v1_Particle_ptmin_ne = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmin_ne << std::endl;
      std::cout << "Cut_v1_Particle_ptmax_ne = " << qaUtility::GetInstance()->Cut_v1_Particle_ptmax_ne << std::endl;
      std::cout << "Cut_v1_Particle_ymin_ne = " << qaUtility::GetInstance()->Cut_v1_Particle_ymin_ne << std::endl;
      std::cout << "Cut_v1_Particle_ymax_ne = " << qaUtility::GetInstance()->Cut_v1_Particle_ymax_ne << std::endl;
    }
    if (qaUtility::GetInstance()->Is_v2)
    {
      std::cout << "Is_v2 = " << qaUtility::GetInstance()->Is_v2 << std::endl;
      std::cout << "Cut_v2_Event_bmin = " << qaUtility::GetInstance()->Cut_v2_Event_bmin << std::endl;
      std::cout << "Cut_v2_Event_bmax = " << qaUtility::GetInstance()->Cut_v2_Event_bmax << std::endl;
      std::cout << "Cut_v2_Event_bCent[" << qaUtility::GetInstance()->Cut_v2_Event_bCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v2_Event_bCent.size(); i++)
      {
        std::cout << qaUtility::GetInstance()->Cut_v2_Event_bCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v2_Event_bCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v2_Event_mCent[" << qaUtility::GetInstance()->Cut_v2_Event_mCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v2_Event_mCent.size(); i++)
      {
        std::cout << (int)qaUtility::GetInstance()->Cut_v2_Event_mCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v2_Event_mCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v2_Particle_ptmin = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmin << std::endl;
      std::cout << "Cut_v2_Particle_ptmax = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmax << std::endl;
      std::cout << "Cut_v2_Particle_etamin = " << qaUtility::GetInstance()->Cut_v2_Particle_etamin << std::endl;
      std::cout << "Cut_v2_Particle_etamax = " << qaUtility::GetInstance()->Cut_v2_Particle_etamax << std::endl;
      std::cout << "Cut_v2_Particle_ymin = " << qaUtility::GetInstance()->Cut_v2_Particle_ymin << std::endl;
      std::cout << "Cut_v2_Particle_ymax = " << qaUtility::GetInstance()->Cut_v2_Particle_ymax << std::endl;
      std::cout << "Cut_v2_Particle_ptmin_pi = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmin_pi << std::endl;
      std::cout << "Cut_v2_Particle_ptmax_pi = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmax_pi << std::endl;
      std::cout << "Cut_v2_Particle_ymin_pi = " << qaUtility::GetInstance()->Cut_v2_Particle_ymin_pi << std::endl;
      std::cout << "Cut_v2_Particle_ymax_pi = " << qaUtility::GetInstance()->Cut_v2_Particle_ymax_pi << std::endl;
      std::cout << "Cut_v2_Particle_ptmin_ka = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmin_ka << std::endl;
      std::cout << "Cut_v2_Particle_ptmax_ka = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmax_ka << std::endl;
      std::cout << "Cut_v2_Particle_ymin_ka = " << qaUtility::GetInstance()->Cut_v2_Particle_ymin_ka << std::endl;
      std::cout << "Cut_v2_Particle_ymax_ka = " << qaUtility::GetInstance()->Cut_v2_Particle_ymax_ka << std::endl;
      std::cout << "Cut_v2_Particle_ptmin_pr = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmin_pr << std::endl;
      std::cout << "Cut_v2_Particle_ptmax_pr = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmax_pr << std::endl;
      std::cout << "Cut_v2_Particle_ymin_pr = " << qaUtility::GetInstance()->Cut_v2_Particle_ymin_pr << std::endl;
      std::cout << "Cut_v2_Particle_ymax_pr = " << qaUtility::GetInstance()->Cut_v2_Particle_ymax_pr << std::endl;
      std::cout << "Cut_v2_Particle_ptmin_ne = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmin_ne << std::endl;
      std::cout << "Cut_v2_Particle_ptmax_ne = " << qaUtility::GetInstance()->Cut_v2_Particle_ptmax_ne << std::endl;
      std::cout << "Cut_v2_Particle_ymin_ne = " << qaUtility::GetInstance()->Cut_v2_Particle_ymin_ne << std::endl;
      std::cout << "Cut_v2_Particle_ymax_ne = " << qaUtility::GetInstance()->Cut_v2_Particle_ymax_ne << std::endl;
    }
    if (qaUtility::GetInstance()->Is_v3)
    {
      std::cout << "Is_v3 = " << qaUtility::GetInstance()->Is_v3 << std::endl;
      std::cout << "Cut_v3_Event_bmin = " << qaUtility::GetInstance()->Cut_v3_Event_bmin << std::endl;
      std::cout << "Cut_v3_Event_bmax = " << qaUtility::GetInstance()->Cut_v3_Event_bmax << std::endl;
      std::cout << "Cut_v3_Event_bCent[" << qaUtility::GetInstance()->Cut_v3_Event_bCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v3_Event_bCent.size(); i++)
      {
        std::cout << qaUtility::GetInstance()->Cut_v3_Event_bCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v3_Event_bCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v3_Event_mCent[" << qaUtility::GetInstance()->Cut_v3_Event_mCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v3_Event_mCent.size(); i++)
      {
        std::cout << (int)qaUtility::GetInstance()->Cut_v3_Event_mCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v3_Event_mCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v3_Particle_ptmin = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmin << std::endl;
      std::cout << "Cut_v3_Particle_ptmax = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmax << std::endl;
      std::cout << "Cut_v3_Particle_etamin = " << qaUtility::GetInstance()->Cut_v3_Particle_etamin << std::endl;
      std::cout << "Cut_v3_Particle_etamax = " << qaUtility::GetInstance()->Cut_v3_Particle_etamax << std::endl;
      std::cout << "Cut_v3_Particle_ymin = " << qaUtility::GetInstance()->Cut_v3_Particle_ymin << std::endl;
      std::cout << "Cut_v3_Particle_ymax = " << qaUtility::GetInstance()->Cut_v3_Particle_ymax << std::endl;
      std::cout << "Cut_v3_Particle_ptmin_pi = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmin_pi << std::endl;
      std::cout << "Cut_v3_Particle_ptmax_pi = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmax_pi << std::endl;
      std::cout << "Cut_v3_Particle_ymin_pi = " << qaUtility::GetInstance()->Cut_v3_Particle_ymin_pi << std::endl;
      std::cout << "Cut_v3_Particle_ymax_pi = " << qaUtility::GetInstance()->Cut_v3_Particle_ymax_pi << std::endl;
      std::cout << "Cut_v3_Particle_ptmin_ka = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmin_ka << std::endl;
      std::cout << "Cut_v3_Particle_ptmax_ka = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmax_ka << std::endl;
      std::cout << "Cut_v3_Particle_ymin_ka = " << qaUtility::GetInstance()->Cut_v3_Particle_ymin_ka << std::endl;
      std::cout << "Cut_v3_Particle_ymax_ka = " << qaUtility::GetInstance()->Cut_v3_Particle_ymax_ka << std::endl;
      std::cout << "Cut_v3_Particle_ptmin_pr = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmin_pr << std::endl;
      std::cout << "Cut_v3_Particle_ptmax_pr = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmax_pr << std::endl;
      std::cout << "Cut_v3_Particle_ymin_pr = " << qaUtility::GetInstance()->Cut_v3_Particle_ymin_pr << std::endl;
      std::cout << "Cut_v3_Particle_ymax_pr = " << qaUtility::GetInstance()->Cut_v3_Particle_ymax_pr << std::endl;
      std::cout << "Cut_v3_Particle_ptmin_ne = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmin_ne << std::endl;
      std::cout << "Cut_v3_Particle_ptmax_ne = " << qaUtility::GetInstance()->Cut_v3_Particle_ptmax_ne << std::endl;
      std::cout << "Cut_v3_Particle_ymin_ne = " << qaUtility::GetInstance()->Cut_v3_Particle_ymin_ne << std::endl;
      std::cout << "Cut_v3_Particle_ymax_ne = " << qaUtility::GetInstance()->Cut_v3_Particle_ymax_ne << std::endl;
    }
    if (qaUtility::GetInstance()->Is_v4)
    {
      std::cout << "Is_v4 = " << qaUtility::GetInstance()->Is_v4 << std::endl;
      std::cout << "Cut_v4_Event_bmin = " << qaUtility::GetInstance()->Cut_v4_Event_bmin << std::endl;
      std::cout << "Cut_v4_Event_bmax = " << qaUtility::GetInstance()->Cut_v4_Event_bmax << std::endl;
      std::cout << "Cut_v4_Event_bCent[" << qaUtility::GetInstance()->Cut_v4_Event_bCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v4_Event_bCent.size(); i++)
      {
        std::cout << qaUtility::GetInstance()->Cut_v4_Event_bCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v4_Event_bCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v4_Event_mCent[" << qaUtility::GetInstance()->Cut_v4_Event_mCent.size() << "] = {";
      for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v4_Event_mCent.size(); i++)
      {
        std::cout << (int)qaUtility::GetInstance()->Cut_v4_Event_mCent.at(i);
        if (i != (int)qaUtility::GetInstance()->Cut_v4_Event_mCent.size() - 1)
          std::cout << ", ";
        else
          std::cout << "};" << std::endl;
      }
      std::cout << "Cut_v4_Particle_ptmin = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmin << std::endl;
      std::cout << "Cut_v4_Particle_ptmax = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmax << std::endl;
      std::cout << "Cut_v4_Particle_etamin = " << qaUtility::GetInstance()->Cut_v4_Particle_etamin << std::endl;
      std::cout << "Cut_v4_Particle_etamax = " << qaUtility::GetInstance()->Cut_v4_Particle_etamax << std::endl;
      std::cout << "Cut_v4_Particle_ymin = " << qaUtility::GetInstance()->Cut_v4_Particle_ymin << std::endl;
      std::cout << "Cut_v4_Particle_ymax = " << qaUtility::GetInstance()->Cut_v4_Particle_ymax << std::endl;
      std::cout << "Cut_v4_Particle_ptmin_pi = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmin_pi << std::endl;
      std::cout << "Cut_v4_Particle_ptmax_pi = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmax_pi << std::endl;
      std::cout << "Cut_v4_Particle_ymin_pi = " << qaUtility::GetInstance()->Cut_v4_Particle_ymin_pi << std::endl;
      std::cout << "Cut_v4_Particle_ymax_pi = " << qaUtility::GetInstance()->Cut_v4_Particle_ymax_pi << std::endl;
      std::cout << "Cut_v4_Particle_ptmin_ka = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmin_ka << std::endl;
      std::cout << "Cut_v4_Particle_ptmax_ka = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmax_ka << std::endl;
      std::cout << "Cut_v4_Particle_ymin_ka = " << qaUtility::GetInstance()->Cut_v4_Particle_ymin_ka << std::endl;
      std::cout << "Cut_v4_Particle_ymax_ka = " << qaUtility::GetInstance()->Cut_v4_Particle_ymax_ka << std::endl;
      std::cout << "Cut_v4_Particle_ptmin_pr = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmin_pr << std::endl;
      std::cout << "Cut_v4_Particle_ptmax_pr = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmax_pr << std::endl;
      std::cout << "Cut_v4_Particle_ymin_pr = " << qaUtility::GetInstance()->Cut_v4_Particle_ymin_pr << std::endl;
      std::cout << "Cut_v4_Particle_ymax_pr = " << qaUtility::GetInstance()->Cut_v4_Particle_ymax_pr << std::endl;
      std::cout << "Cut_v4_Particle_ptmin_ne = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmin_ne << std::endl;
      std::cout << "Cut_v4_Particle_ptmax_ne = " << qaUtility::GetInstance()->Cut_v4_Particle_ptmax_ne << std::endl;
      std::cout << "Cut_v4_Particle_ymin_ne = " << qaUtility::GetInstance()->Cut_v4_Particle_ymin_ne << std::endl;
      std::cout << "Cut_v4_Particle_ymax_ne = " << qaUtility::GetInstance()->Cut_v4_Particle_ymax_ne << std::endl;
    }
    std::cout << std::endl;
  }

  if (qaUtility::GetInstance()->Is_minbias != 1 &&
      qaUtility::GetInstance()->Is_refmult != 1 &&
      qaUtility::GetInstance()->Is_v1 != 1 &&
      qaUtility::GetInstance()->Is_v2 != 1 &&
      qaUtility::GetInstance()->Is_v3 != 1 &&
      qaUtility::GetInstance()->Is_v4 != 1)
  {
    std::cerr << "No options were chosen (minbias, refmult, v1, v2, v3, v4). Exiting..." << std::endl;
    return 100;
  }

  TFile *fo = new TFile(oFileName, "recreate");

  TH1D *h_minbias_Event_b = new TH1D("h_minbias_Event_b", "dN/db minbias;b, fm; dN/db", 200, 0., 20.);
  TH1I *h_minbias_Event_Mult = new TH1I("h_minbias_Event_Mult", "dN/dN_{particles} minbias;N_{particles}; dN/dN_{particles}", 2500, 0, 2500);
  TH2D *h2_minbias_Event_b_Mult = new TH2D("h2_minbias_Event_b_Mult", "b vs N_{particles} minbias;N_{particles};b, fm;", 2500, 0., 2500., 200, 0., 20.);
  TH1D *h_minbias_Particle_pt = new TH1D("h_minbias_Particle_pt", "dN/dp_{T} minbias;p_{T}, GeV/c; dN/dp_{T}", 800, 0., 8.);
  TH1D *h_minbias_Particle_eta = new TH1D("h_minbias_Particle_eta", "dN/d#eta minbias;#eta; dN/d#eta", 2000, -10., 10.);
  TH2D *h2_minbias_Particle_pteta = new TH2D("h2_minbias_Particle_pteta", "dN/dp_{T}d#eta minbias;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH1D *h_minbias_Particle_E = new TH1D("h_minbias_Particle_E", "dN/dE minbias;E, GeV; dN/dE", 800, 0., 8.);
  TH1D *h_minbias_Particle_px = new TH1D("h_minbias_Particle_px", "dN/dp_{x} minbias;p_{x}, GeV/c; dN/dp_{x}", 800, -8., 8.);
  TH1D *h_minbias_Particle_py = new TH1D("h_minbias_Particle_py", "dN/dp_{y} minbias;p_{y}, GeV/c; dN/dp_{y}", 800, -8., 8.);
  TH1D *h_minbias_Particle_pz = new TH1D("h_minbias_Particle_pz", "dN/dp_{z} minbias;p_{z}, GeV/c; dN/dp_{z}", 800, -8., 8.);
  TH1D *h_minbias_Particle_t = new TH1D("h_minbias_Particle_t", "dN/dt minbias;t, fm/c; dN/dt", 800, 0., 800.);
  TH1D *h_minbias_Particle_x = new TH1D("h_minbias_Particle_x", "dN/dx minbias;x, fm; dN/dx", 800, -8., 8.);
  TH1D *h_minbias_Particle_y = new TH1D("h_minbias_Particle_y", "dN/dy minbias;y, fm; dN/dy", 800, -8., 8.);
  TH1D *h_minbias_Particle_z = new TH1D("h_minbias_Particle_z", "dN/dz minbias;z, fm; dN/dz", 800, -8., 8.);
  TH1I *h_minbias_Particle_pdg = new TH1I("h_minbias_Particle_pdg", "PDG minbias;PDG;N_{entries}", 7000, -3500, 3500);
  TH1D *h_minbias_Particle_PID_pt[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_eta[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_Y[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_E[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_px[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_py[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_pz[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_t[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_x[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_y[qaUtility::GetInstance()->npid];
  TH1D *h_minbias_Particle_PID_z[qaUtility::GetInstance()->npid];

  TH1D *h_refmult_Event_b = new TH1D("h_refmult_Event_b", "dN/db refmult;b, fm; dN/db", 200, 0., 20.);
  TH1I *h_refmult_Event_Mult = new TH1I("h_refmult_Event_Mult", "dN/dN_{particles} refmult;N_{particles}; dN/dN_{particles}", 2500, 0, 2500);
  TH2D *h2_refmult_Event_b_Mult = new TH2D("h2_refmult_Event_b_Mult", "b vs N_{particles} refmult;N_{particles};b, fm;", 2500, 0., 2500., 200, 0., 20.);
  TH1D *h_refmult_Particle_pt = new TH1D("h_refmult_Particle_pt", "dN/dp_{T} refmult;p_{T}, GeV/c; dN/dp_{T}", 800, 0., 8.);
  TH1D *h_refmult_Particle_eta = new TH1D("h_refmult_Particle_eta", "dN/d#eta refmult;#eta; dN/d#eta", 2000, -10., 10.);
  TH2D *h2_refmult_Particle_pteta = new TH2D("h2_refmult_Particle_pteta", "dN/dp_{T}d#eta refmult;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH1D *h_refmult_Particle_E = new TH1D("h_refmult_Particle_E", "dN/dE refmult;E, GeV; dN/dE", 800, 0., 8.);
  TH1D *h_refmult_Particle_px = new TH1D("h_refmult_Particle_px", "dN/dp_{x} refmult;p_{x}, GeV/c; dN/dp_{x}", 800, -8., 8.);
  TH1D *h_refmult_Particle_py = new TH1D("h_refmult_Particle_py", "dN/dp_{y} refmult;p_{y}, GeV/c; dN/dp_{y}", 800, -8., 8.);
  TH1D *h_refmult_Particle_pz = new TH1D("h_refmult_Particle_pz", "dN/dp_{z} refmult;p_{z}, GeV/c; dN/dp_{z}", 800, -8., 8.);
  TH1D *h_refmult_Particle_t = new TH1D("h_refmult_Particle_t", "dN/dt refmult;t, fm/c; dN/dt", 800, 0., 800.);
  TH1D *h_refmult_Particle_x = new TH1D("h_refmult_Particle_x", "dN/dx refmult;x, fm; dN/dx", 800, -8., 8.);
  TH1D *h_refmult_Particle_y = new TH1D("h_refmult_Particle_y", "dN/dy refmult;y, fm; dN/dy", 800, -8., 8.);
  TH1D *h_refmult_Particle_z = new TH1D("h_refmult_Particle_z", "dN/dz refmult;z, fm; dN/dz", 800, -8., 8.);
  TH1I *h_refmult_Particle_pdg = new TH1I("h_refmult_Particle_pdg", "PDG refmult;PDG;N_{entries}", 7000, -3500, 3500);
  TH1D *h_refmult_Particle_PID_pt[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_eta[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_Y[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_E[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_px[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_py[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_pz[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_t[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_x[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_y[qaUtility::GetInstance()->npid];
  TH1D *h_refmult_Particle_PID_z[qaUtility::GetInstance()->npid];

  TH2D *h2_v1_Particle_pteta = new TH2D("h2_v1_Particle_pteta", "dN/dp_{T}d#eta v1;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH2D *h2_v1_Event_bCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  TH2D *h2_v1_Event_mCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  // TProfile3D *p3_v1_PID_b_pt_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v1_PID_b_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v1_PID_b_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v1_PID_y_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile2D *p2_v1_PID_M_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v1_PID_M_y[qaUtility::GetInstance()->npid];
  TProfile *p_v1_PID_bCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v1_PID_bCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v1_PID_mCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v1_PID_mCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];

  TH2D *h2_v2_Particle_pteta = new TH2D("h2_v2_Particle_pteta", "dN/dp_{T}d#eta v2;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH2D *h2_v2_Event_bCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  TH2D *h2_v2_Event_mCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  // TProfile3D *p3_v2_PID_b_pt_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v2_PID_b_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v2_PID_b_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v2_PID_y_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile2D *p2_v2_PID_M_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v2_PID_M_y[qaUtility::GetInstance()->npid];
  TProfile *p_v2_PID_bCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v2_PID_bCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v2_PID_mCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v2_PID_mCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];

  TH2D *h2_v3_Particle_pteta = new TH2D("h2_v3_Particle_pteta", "dN/dp_{T}d#eta v3;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH2D *h2_v3_Event_bCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  TH2D *h2_v3_Event_mCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  // TProfile3D *p3_v3_PID_b_pt_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v3_PID_b_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v3_PID_b_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v3_PID_y_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile2D *p2_v3_PID_M_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v3_PID_M_y[qaUtility::GetInstance()->npid];
  TProfile *p_v3_PID_bCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v3_PID_bCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v3_PID_mCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v3_PID_mCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];

  TH2D *h2_v4_Particle_pteta = new TH2D("h2_v4_Particle_pteta", "dN/dp_{T}d#eta v4;#eta;p_{T}, GeV/c;dN/dp_{T}d#eta", 2000, -10., 10., 800, 0., 8.);
  TH2D *h2_v4_Event_bCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  TH2D *h2_v4_Event_mCent_b_Mult[qaUtility::GetInstance()->maxCentBins];
  // TProfile3D *p3_v4_PID_b_pt_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v4_PID_b_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v4_PID_b_y[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v4_PID_y_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile2D *p2_v4_PID_M_pt[qaUtility::GetInstance()->npid];
  TProfile2D *p2_v4_PID_M_y[qaUtility::GetInstance()->npid];
  TProfile *p_v4_PID_bCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v4_PID_bCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v4_PID_mCent_pt[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];
  TProfile *p_v4_PID_mCent_y[qaUtility::GetInstance()->maxCentBins][qaUtility::GetInstance()->npid];

  for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
  {
    h_minbias_Particle_PID_pt[i] = new TH1D(Form("h_minbias_Particle_PID_pt_%i", i), Form("h_minbias_Particle_PID_pt_%i;p_{T}, GeV/c; dN/dp_{T}", i), 800, 0., 8.);
    h_minbias_Particle_PID_eta[i] = new TH1D(Form("h_minbias_Particle_PID_eta_%i", i), Form("h_minbias_Particle_PID_eta_%i;#eta; dN/d#eta", i), 2000, -10., 10.);
    h_minbias_Particle_PID_Y[i] = new TH1D(Form("h_minbias_Particle_PID_Y_%i", i), Form("h_minbias_Particle_PID_Y_%i;y; dN/dy", i), 2000, -10., 10.);
    h_minbias_Particle_PID_E[i] = new TH1D(Form("h_minbias_Particle_PID_E_%i", i), Form("h_minbias_Particle_PID_E_%i;E, GeV; dN/dE", i), 800, 0., 8.);
    h_minbias_Particle_PID_px[i] = new TH1D(Form("h_minbias_Particle_PID_px_%i", i), Form("h_minbias_Particle_PID_px_%i;p_{x}, GeV/c; dN/dp_{x}", i), 800, -8., 8.);
    h_minbias_Particle_PID_py[i] = new TH1D(Form("h_minbias_Particle_PID_py_%i", i), Form("h_minbias_Particle_PID_py_%i;p_{y}, GeV/c; dN/dp_{y}", i), 800, -8., 8.);
    h_minbias_Particle_PID_pz[i] = new TH1D(Form("h_minbias_Particle_PID_pz_%i", i), Form("h_minbias_Particle_PID_pz_%i;p_{z}, GeV/c; dN/dp_{z}", i), 800, -8., 8.);
    h_minbias_Particle_PID_t[i] = new TH1D(Form("h_minbias_Particle_PID_t_%i", i), Form("h_minbias_Particle_PID_t_%i;t, fm/c; dN/dt", i), 800, 0., 8.);
    h_minbias_Particle_PID_x[i] = new TH1D(Form("h_minbias_Particle_PID_x_%i", i), Form("h_minbias_Particle_PID_x_%i;x, fm; dN/dx", i), 800, -8., 8.);
    h_minbias_Particle_PID_y[i] = new TH1D(Form("h_minbias_Particle_PID_y_%i", i), Form("h_minbias_Particle_PID_y_%i;y, fm; dN/dy", i), 800, -8., 8.);
    h_minbias_Particle_PID_z[i] = new TH1D(Form("h_minbias_Particle_PID_z_%i", i), Form("h_minbias_Particle_PID_z_%i;z, fm; dN/dz", i), 800, -8., 8.);

    h_refmult_Particle_PID_pt[i] = new TH1D(Form("h_refmult_Particle_PID_pt_%i", i), Form("h_refmult_Particle_PID_pt_%i;p_{T}, GeV/c; dN/dp_{T}", i), 800, 0., 8.);
    h_refmult_Particle_PID_eta[i] = new TH1D(Form("h_refmult_Particle_PID_eta_%i", i), Form("h_refmult_Particle_PID_eta_%i;#eta; dN/d#eta", i), 2000, -10., 10.);
    h_refmult_Particle_PID_Y[i] = new TH1D(Form("h_refmult_Particle_PID_Y_%i", i), Form("h_refmult_Particle_PID_Y_%i;y; dN/dy", i), 2000, -10., 10.);
    h_refmult_Particle_PID_E[i] = new TH1D(Form("h_refmult_Particle_PID_E_%i", i), Form("h_refmult_Particle_PID_E_%i;E, GeV; dN/dE", i), 800, 0., 8.);
    h_refmult_Particle_PID_px[i] = new TH1D(Form("h_refmult_Particle_PID_px_%i", i), Form("h_refmult_Particle_PID_px_%i;p_{x}, GeV/c; dN/dp_{x}", i), 800, -8., 8.);
    h_refmult_Particle_PID_py[i] = new TH1D(Form("h_refmult_Particle_PID_py_%i", i), Form("h_refmult_Particle_PID_py_%i;p_{y}, GeV/c; dN/dp_{y}", i), 800, -8., 8.);
    h_refmult_Particle_PID_pz[i] = new TH1D(Form("h_refmult_Particle_PID_pz_%i", i), Form("h_refmult_Particle_PID_pz_%i;p_{z}, GeV/c; dN/dp_{z}", i), 800, -8., 8.);
    h_refmult_Particle_PID_t[i] = new TH1D(Form("h_refmult_Particle_PID_t_%i", i), Form("h_refmult_Particle_PID_t_%i;t, fm/c; dN/dt", i), 800, 0., 8.);
    h_refmult_Particle_PID_x[i] = new TH1D(Form("h_refmult_Particle_PID_x_%i", i), Form("h_refmult_Particle_PID_x_%i;x, fm; dN/dx", i), 800, -8., 8.);
    h_refmult_Particle_PID_y[i] = new TH1D(Form("h_refmult_Particle_PID_y_%i", i), Form("h_refmult_Particle_PID_y_%i;y, fm; dN/dy", i), 800, -8., 8.);
    h_refmult_Particle_PID_z[i] = new TH1D(Form("h_refmult_Particle_PID_z_%i", i), Form("h_refmult_Particle_PID_z_%i;z, fm; dN/dz", i), 800, -8., 8.);

    // p3_v1_PID_b_pt_y[i] = new TProfile3D(Form("p3_v1_PID_b_pt_y_%i", i), Form("p3_v1_PID_b_pt_y_%i;p_{T}, GeV/c;y;b, fm;v_{1}", i), 100, 0., 5., 400, -10., 10., 200, 0., 20.);
    p2_v1_PID_b_pt[i] = new TProfile2D(Form("p2_v1_PID_b_pt_%i", i), Form("p2_v1_PID_b_pt_%i;p_{T}, GeV/c;b, fm;v_{1}", i), 100, 0., 5., 200, 0., 20.);
    p2_v1_PID_b_y[i] = new TProfile2D(Form("p2_v1_PID_b_y_%i", i), Form("p2_v1_PID_b_y_%i;y;b, fm;v_{1}", i), 400, -10., 10., 200, 0., 20.);
    p2_v1_PID_M_pt[i] = new TProfile2D(Form("p2_v1_PID_M_pt_%i", i), Form("p2_v1_PID_M_pt_%i;p_{T}, GeV/c;b, fm;v_{1}", i), 100, 0., 5., 2500, 0., 2500.);
    p2_v1_PID_M_y[i] = new TProfile2D(Form("p2_v1_PID_M_y_%i", i), Form("p2_v1_PID_M_y_%i;y;b, fm;v_{1}", i), 400, -10., 10., 2500, 0., 2500.);

    // p3_v2_PID_b_pt_y[i] = new TProfile3D(Form("p3_v2_PID_b_pt_y_%i", i), Form("p3_v2_PID_b_pt_y_%i;p_{T}, GeV/c;y;b, fm;v_{2}", i), 100, 0., 5., 400, -10., 10., 200, 0., 20.);
    p2_v2_PID_b_pt[i] = new TProfile2D(Form("p2_v2_PID_b_pt_%i", i), Form("p2_v2_PID_b_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 200, 0., 20.);
    p2_v2_PID_b_y[i] = new TProfile2D(Form("p2_v2_PID_b_y_%i", i), Form("p2_v2_PID_b_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 200, 0., 20.);
    p2_v2_PID_M_pt[i] = new TProfile2D(Form("p2_v2_PID_M_pt_%i", i), Form("p2_v2_PID_M_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 2500, 0., 2500.);
    p2_v2_PID_M_y[i] = new TProfile2D(Form("p2_v2_PID_M_y_%i", i), Form("p2_v2_PID_M_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 2500, 0., 2500.);

    // p3_v3_PID_b_pt_y[i] = new TProfile3D(Form("p3_v3_PID_b_pt_y_%i", i), Form("p3_v3_PID_b_pt_y_%i;p_{T}, GeV/c;y;b, fm;v_{3}", i), 100, 0., 5., 400, -10., 10., 200, 0., 20.);
    p2_v3_PID_b_pt[i] = new TProfile2D(Form("p2_v3_PID_b_pt_%i", i), Form("p2_v3_PID_b_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 200, 0., 20.);
    p2_v3_PID_b_y[i] = new TProfile2D(Form("p2_v3_PID_b_y_%i", i), Form("p2_v3_PID_b_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 200, 0., 20.);
    p2_v3_PID_M_pt[i] = new TProfile2D(Form("p2_v3_PID_M_pt_%i", i), Form("p2_v3_PID_M_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 2500, 0., 2500.);
    p2_v3_PID_M_y[i] = new TProfile2D(Form("p2_v3_PID_M_y_%i", i), Form("p2_v3_PID_M_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 2500, 0., 2500.);

    // p3_v4_PID_b_pt_y[i] = new TProfile3D(Form("p3_v4_PID_b_pt_y_%i", i), Form("p3_v4_PID_b_pt_y_%i;p_{T}, GeV/c;y;b, fm;v_{4}", i), 100, 0., 5., 400, -10., 10., 200, 0., 20.);
    p2_v4_PID_b_pt[i] = new TProfile2D(Form("p2_v4_PID_b_pt_%i", i), Form("p2_v4_PID_b_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 200, 0., 20.);
    p2_v4_PID_b_y[i] = new TProfile2D(Form("p2_v4_PID_b_y_%i", i), Form("p2_v4_PID_b_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 200, 0., 20.);
    p2_v4_PID_M_pt[i] = new TProfile2D(Form("p2_v4_PID_M_pt_%i", i), Form("p2_v4_PID_M_pt_%i;p_{T}, GeV/c;b, fm;v_{2}", i), 100, 0., 5., 2500, 0., 2500.);
    p2_v4_PID_M_y[i] = new TProfile2D(Form("p2_v4_PID_M_y_%i", i), Form("p2_v4_PID_M_y_%i;y;b, fm;v_{2}", i), 400, -10., 10., 2500, 0., 2500.);
  }
  for (int i = 0; i < qaUtility::GetInstance()->maxCentBins; i++)
  {
    h2_v1_Event_bCent_b_Mult[i] = new TH2D(Form("h2_v1_Event_bCent_b_Mult_%i", i), Form("h2_v1_Event_bCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);
    h2_v1_Event_mCent_b_Mult[i] = new TH2D(Form("h2_v1_Event_mCent_b_Mult_%i", i), Form("h2_v1_Event_mCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);

    h2_v2_Event_bCent_b_Mult[i] = new TH2D(Form("h2_v2_Event_bCent_b_Mult_%i", i), Form("h2_v2_Event_bCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);
    h2_v2_Event_mCent_b_Mult[i] = new TH2D(Form("h2_v2_Event_mCent_b_Mult_%i", i), Form("h2_v2_Event_mCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);

    h2_v3_Event_bCent_b_Mult[i] = new TH2D(Form("h2_v3_Event_bCent_b_Mult_%i", i), Form("h2_v3_Event_bCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);
    h2_v3_Event_mCent_b_Mult[i] = new TH2D(Form("h2_v3_Event_mCent_b_Mult_%i", i), Form("h2_v3_Event_mCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);

    h2_v4_Event_bCent_b_Mult[i] = new TH2D(Form("h2_v4_Event_bCent_b_Mult_%i", i), Form("h2_v4_Event_bCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);
    h2_v4_Event_mCent_b_Mult[i] = new TH2D(Form("h2_v4_Event_mCent_b_Mult_%i", i), Form("h2_v4_Event_mCent_b_Mult_%i;N_{particles};b, fm;", i), 2500, 0, 2500, 200, 0., 20.);

    for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
    {
      p2_v1_PID_y_pt[i][j] = new TProfile2D(Form("p2_v1_PID_y_pt_%i_%i", i, j), Form("p2_v1_PID_y_pt_%i_%i;p_{T}, GeV/c;y;v_{1}", i, j), 100, 0., 5., 800, -10., 10.);
      p_v1_PID_bCent_pt[i][j] = new TProfile(Form("p_v1_PID_bCent_pt_%i_%i", i, j), Form("p_v1_PID_bCent_pt_%i_%i;p_{T}, GeV/c;v_{1}", i, j), 100, 0., 5.);
      p_v1_PID_bCent_y[i][j] = new TProfile(Form("p_v1_PID_bCent_y_%i_%i", i, j), Form("p_v1_PID_bCent_y_%i_%i;y;v_{1}", i, j), 400, -10., 10.);

      p2_v2_PID_y_pt[i][j] = new TProfile2D(Form("p2_v2_PID_y_pt_%i_%i", i, j), Form("p2_v2_PID_y_pt_%i_%i;p_{T}, GeV/c;y;v_{2}", i, j), 100, 0., 5., 800, -10., 10.);
      p_v2_PID_bCent_pt[i][j] = new TProfile(Form("p_v2_PID_bCent_pt_%i_%i", i, j), Form("p_v2_PID_bCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v2_PID_bCent_y[i][j] = new TProfile(Form("p_v2_PID_bCent_y_%i_%i", i, j), Form("p_v2_PID_bCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);

      p2_v3_PID_y_pt[i][j] = new TProfile2D(Form("p2_v3_PID_y_pt_%i_%i", i, j), Form("p2_v3_PID_y_pt_%i_%i;p_{T}, GeV/c;y;v_{3}", i, j), 100, 0., 5., 800, -10., 10.);
      p_v3_PID_bCent_pt[i][j] = new TProfile(Form("p_v3_PID_bCent_pt_%i_%i", i, j), Form("p_v3_PID_bCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v3_PID_bCent_y[i][j] = new TProfile(Form("p_v3_PID_bCent_y_%i_%i", i, j), Form("p_v3_PID_bCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);

      p2_v4_PID_y_pt[i][j] = new TProfile2D(Form("p2_v4_PID_y_pt_%i_%i", i, j), Form("p2_v4_PID_y_pt_%i_%i;p_{T}, GeV/c;y;v_{4}", i, j), 100, 0., 5., 800, -10., 10.);
      p_v4_PID_bCent_pt[i][j] = new TProfile(Form("p_v4_PID_bCent_pt_%i_%i", i, j), Form("p_v4_PID_bCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v4_PID_bCent_y[i][j] = new TProfile(Form("p_v4_PID_bCent_y_%i_%i", i, j), Form("p_v4_PID_bCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);

      p_v1_PID_mCent_pt[i][j] = new TProfile(Form("p_v1_PID_mCent_pt_%i_%i", i, j), Form("p_v1_PID_mCent_pt_%i_%i;p_{T}, GeV/c;v_{1}", i, j), 100, 0., 5.);
      p_v1_PID_mCent_y[i][j] = new TProfile(Form("p_v1_PID_mCent_y_%i_%i", i, j), Form("p_v1_PID_mCent_y_%i_%i;y;v_{1}", i, j), 400, -10., 10.);

      p_v2_PID_mCent_pt[i][j] = new TProfile(Form("p_v2_PID_mCent_pt_%i_%i", i, j), Form("p_v2_PID_mCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v2_PID_mCent_y[i][j] = new TProfile(Form("p_v2_PID_mCent_y_%i_%i", i, j), Form("p_v2_PID_mCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);

      p_v3_PID_mCent_pt[i][j] = new TProfile(Form("p_v3_PID_mCent_pt_%i_%i", i, j), Form("p_v3_PID_mCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v3_PID_mCent_y[i][j] = new TProfile(Form("p_v3_PID_mCent_y_%i_%i", i, j), Form("p_v3_PID_mCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);

      p_v4_PID_mCent_pt[i][j] = new TProfile(Form("p_v4_PID_mCent_pt_%i_%i", i, j), Form("p_v4_PID_mCent_pt_%i_%i;p_{T}, GeV/c;v_{2}", i, j), 100, 0., 5.);
      p_v4_PID_mCent_y[i][j] = new TProfile(Form("p_v4_PID_mCent_y_%i_%i", i, j), Form("p_v4_PID_mCent_y_%i_%i;y;v_{2}", i, j), 400, -10., 10.);
    }
  }

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
  Int_t Nparticles;
  Int_t Ncounter_minbias, Ncounter_refmult;

  qaEvent *event = nullptr;
  qaParticle *particle = nullptr;

  Long64_t Absolute_counter = 0;
  Long64_t Minbias_counter = 0;
  Int_t ipid;
  Double_t v1, v2, v3, v4, y;
  Int_t eta_w, centBinB, centBinM;

  std::vector<qaParticleLight> v_particles_v1;
  std::vector<qaParticleLight> v_particles_v2;
  std::vector<qaParticleLight> v_particles_v3;
  std::vector<qaParticleLight> v_particles_v4;
  qaParticleLight light_particle;

  while (Minbias_counter < Nentries)
  {
    //if (Minbias_counter % 1000 == 0)
      std::cout << "Event [" << Minbias_counter << "/" << Nentries << "]" << std::endl;

    event = (qaEvent *)readerManager->ReadEvent(Absolute_counter);
    Absolute_counter++;

    if (Absolute_counter > Nentries_chain)
      break;

    if (!event)
      continue;

    Ncounter_minbias = 0;
    Ncounter_refmult = 0;

    v_particles_v1.clear();
    v_particles_v2.clear();
    v_particles_v3.clear();
    v_particles_v4.clear();

    Nparticles = event->GetNparticles();
    for (int iparticle = 0; iparticle < Nparticles; iparticle++)
    {
      particle = readerManager->ReadParticle(iparticle);

      if (!particle)
        continue;

      if (qaUtility::GetInstance()->Cut_Event_minbias(event) &&
          qaUtility::GetInstance()->Cut_Particle_minbias(particle) &&
          qaUtility::GetInstance()->Is_minbias == 1)
      {
        Ncounter_minbias++;
        y = 0.5 * TMath::Log((particle->GetEnergy() + particle->GetPz()) / (particle->GetEnergy() - particle->GetPz()));
        h_minbias_Particle_pt->Fill(particle->GetPt());
        h_minbias_Particle_eta->Fill(particle->GetEta());
        h2_minbias_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        h_minbias_Particle_E->Fill(particle->GetEnergy());
        h_minbias_Particle_px->Fill(particle->GetPx());
        h_minbias_Particle_py->Fill(particle->GetPy());
        h_minbias_Particle_pz->Fill(particle->GetPz());
        h_minbias_Particle_t->Fill(particle->GetT());
        h_minbias_Particle_x->Fill(particle->GetX());
        h_minbias_Particle_y->Fill(particle->GetY());
        h_minbias_Particle_z->Fill(particle->GetZ());
        h_minbias_Particle_pdg->Fill(particle->GetPdg());

        if (particle->GetCharge() > 0)
        {
          ipid = 0;
        }
        if (particle->GetCharge() < 0)
        {
          ipid = 4;
        }
        if (ipid == 0 || ipid == 4)
        {
          h_minbias_Particle_PID_pt[ipid]->Fill(particle->GetPt());
          h_minbias_Particle_PID_eta[ipid]->Fill(particle->GetEta());
          h_minbias_Particle_PID_E[ipid]->Fill(particle->GetEnergy());
          h_minbias_Particle_PID_px[ipid]->Fill(particle->GetPx());
          h_minbias_Particle_PID_py[ipid]->Fill(particle->GetPy());
          h_minbias_Particle_PID_pz[ipid]->Fill(particle->GetPz());
          h_minbias_Particle_PID_t[ipid]->Fill(particle->GetT());
          h_minbias_Particle_PID_x[ipid]->Fill(particle->GetX());
          h_minbias_Particle_PID_y[ipid]->Fill(particle->GetY());
          h_minbias_Particle_PID_z[ipid]->Fill(particle->GetZ());
        }

        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1 && ipid != 0 && ipid != 4)
        {
          h_minbias_Particle_PID_pt[ipid]->Fill(particle->GetPt());
          h_minbias_Particle_PID_eta[ipid]->Fill(particle->GetEta());
          h_minbias_Particle_PID_Y[ipid]->Fill(y);
          h_minbias_Particle_PID_E[ipid]->Fill(particle->GetEnergy());
          h_minbias_Particle_PID_px[ipid]->Fill(particle->GetPx());
          h_minbias_Particle_PID_py[ipid]->Fill(particle->GetPy());
          h_minbias_Particle_PID_pz[ipid]->Fill(particle->GetPz());
          h_minbias_Particle_PID_t[ipid]->Fill(particle->GetT());
          h_minbias_Particle_PID_x[ipid]->Fill(particle->GetX());
          h_minbias_Particle_PID_y[ipid]->Fill(particle->GetY());
          h_minbias_Particle_PID_z[ipid]->Fill(particle->GetZ());
        }
      }

      if (qaUtility::GetInstance()->Cut_Event_refmult(event) &&
          qaUtility::GetInstance()->Cut_Particle_refmult(particle) &&
          qaUtility::GetInstance()->Is_refmult == 1)
      {
        Ncounter_refmult++;
        y = 0.5 * TMath::Log((particle->GetEnergy() + particle->GetPz()) / (particle->GetEnergy() - particle->GetPz()));
        h_refmult_Particle_pt->Fill(particle->GetPt());
        h_refmult_Particle_eta->Fill(particle->GetEta());
        h2_refmult_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        h_refmult_Particle_E->Fill(particle->GetEnergy());
        h_refmult_Particle_px->Fill(particle->GetPx());
        h_refmult_Particle_py->Fill(particle->GetPy());
        h_refmult_Particle_pz->Fill(particle->GetPz());
        h_refmult_Particle_t->Fill(particle->GetT());
        h_refmult_Particle_x->Fill(particle->GetX());
        h_refmult_Particle_y->Fill(particle->GetY());
        h_refmult_Particle_z->Fill(particle->GetZ());
        h_refmult_Particle_pdg->Fill(particle->GetPdg());

        if (particle->GetCharge() > 0)
        {
          ipid = 0;
        }
        if (particle->GetCharge() < 0)
        {
          ipid = 4;
        }
        if (ipid == 0 || ipid == 4)
        {
          h_refmult_Particle_PID_pt[ipid]->Fill(particle->GetPt());
          h_refmult_Particle_PID_eta[ipid]->Fill(particle->GetEta());
          h_refmult_Particle_PID_E[ipid]->Fill(particle->GetEnergy());
          h_refmult_Particle_PID_px[ipid]->Fill(particle->GetPx());
          h_refmult_Particle_PID_py[ipid]->Fill(particle->GetPy());
          h_refmult_Particle_PID_pz[ipid]->Fill(particle->GetPz());
          h_refmult_Particle_PID_t[ipid]->Fill(particle->GetT());
          h_refmult_Particle_PID_x[ipid]->Fill(particle->GetX());
          h_refmult_Particle_PID_y[ipid]->Fill(particle->GetY());
          h_refmult_Particle_PID_z[ipid]->Fill(particle->GetZ());
        }

        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1 && ipid != 0 && ipid != 4)
        {
          h_refmult_Particle_PID_pt[ipid]->Fill(particle->GetPt());
          h_refmult_Particle_PID_eta[ipid]->Fill(particle->GetEta());
          h_refmult_Particle_PID_Y[ipid]->Fill(y);
          h_refmult_Particle_PID_E[ipid]->Fill(particle->GetEnergy());
          h_refmult_Particle_PID_px[ipid]->Fill(particle->GetPx());
          h_refmult_Particle_PID_py[ipid]->Fill(particle->GetPy());
          h_refmult_Particle_PID_pz[ipid]->Fill(particle->GetPz());
          h_refmult_Particle_PID_t[ipid]->Fill(particle->GetT());
          h_refmult_Particle_PID_x[ipid]->Fill(particle->GetX());
          h_refmult_Particle_PID_y[ipid]->Fill(particle->GetY());
          h_refmult_Particle_PID_z[ipid]->Fill(particle->GetZ());
        }
      }

      if (qaUtility::GetInstance()->Cut_Event_v1(event) &&
          qaUtility::GetInstance()->Cut_Particle_v1_acceptance(particle) &&
          qaUtility::GetInstance()->Is_v1 == 1)
      {
        h2_v1_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1)
        {
          light_particle.SetParticle(particle);
          v_particles_v1.push_back(light_particle);
        }
      }

      if (qaUtility::GetInstance()->Cut_Event_v2(event) &&
          qaUtility::GetInstance()->Cut_Particle_v2_acceptance(particle) &&
          qaUtility::GetInstance()->Is_v2 == 1)
      {
        h2_v2_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1)
        {
          light_particle.SetParticle(particle);
          v_particles_v2.push_back(light_particle);
        }
      }

      if (qaUtility::GetInstance()->Cut_Event_v3(event) &&
          qaUtility::GetInstance()->Cut_Particle_v3_acceptance(particle) &&
          qaUtility::GetInstance()->Is_v3 == 1)
      {
        h2_v3_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1)
        {
          light_particle.SetParticle(particle);
          v_particles_v3.push_back(light_particle);
        }
      }

      if (qaUtility::GetInstance()->Cut_Event_v4(event) &&
          qaUtility::GetInstance()->Cut_Particle_v4_acceptance(particle) &&
          qaUtility::GetInstance()->Is_v4 == 1)
      {
        h2_v4_Particle_pteta->Fill(particle->GetEta(), particle->GetPt());
        ipid = qaUtility::GetInstance()->GetPdgId(particle->GetPdg());
        if (ipid != -1)
        {
          light_particle.SetParticle(particle);
          v_particles_v4.push_back(light_particle);
        }
      }

      delete particle;
    }

    // Loop over v1-related particles
    centBinB = qaUtility::GetInstance()->GetCentralityBin(event->GetB(), qaUtility::GetInstance()->Cut_v1_Event_bCent);
    centBinM = qaUtility::GetInstance()->GetCentMultBin(Ncounter_refmult, qaUtility::GetInstance()->Cut_v1_Event_mCent);
    if (centBinB != -1) h2_v1_Event_bCent_b_Mult[centBinB]->Fill(Ncounter_refmult, event->GetB());
    if (centBinM != -1) h2_v1_Event_mCent_b_Mult[centBinM]->Fill(Ncounter_refmult, event->GetB());
    if (qaUtility::GetInstance()->Is_v1 == 1)
    {
      for (const auto &lparticle : v_particles_v1)
      {
        v1 = TMath::Cos(1. * (lparticle.GetPhi() - event->GetPhiRP()));
        eta_w = 1; //(particle->GetEta() >= 0.) ? 1 : -1;
        ipid = qaUtility::GetInstance()->GetPdgId(lparticle.GetPdg());
        // if (ipid != -1) p3_v1_PID_b_pt_y[ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), event->GetB(), v1);
        if (ipid != -1 && centBinB != -1) p2_v1_PID_y_pt[centBinB][ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), v1);
        if (qaUtility::GetInstance()->Cut_Particle_v1_PID_pt(lparticle, ipid))
        {
          p2_v1_PID_b_pt[ipid]->Fill(lparticle.GetPt(), event->GetB(), v1 * eta_w);
          p2_v1_PID_M_pt[ipid]->Fill(lparticle.GetPt(), Ncounter_refmult, v1 * eta_w);
          if (centBinB != -1)
            p_v1_PID_bCent_pt[centBinB][ipid]->Fill(lparticle.GetPt(), v1 * eta_w);
          if (centBinM != -1)
            p_v1_PID_mCent_pt[centBinM][ipid]->Fill(lparticle.GetPt(), v1 * eta_w);
        }
        if (qaUtility::GetInstance()->Cut_Particle_v1_PID_y(lparticle, ipid))
        {
          p2_v1_PID_b_y[ipid]->Fill(lparticle.GetRapidity(), event->GetB(), v1);
          p2_v1_PID_M_y[ipid]->Fill(lparticle.GetRapidity(), Ncounter_refmult, v1);
          if (centBinB != -1)
            p_v1_PID_bCent_y[centBinB][ipid]->Fill(lparticle.GetRapidity(), v1);
          if (centBinM != -1)
            p_v1_PID_mCent_y[centBinM][ipid]->Fill(lparticle.GetRapidity(), v1);
        }
      }
    }

    // Loop over v2-related particles
    centBinB = qaUtility::GetInstance()->GetCentralityBin(event->GetB(), qaUtility::GetInstance()->Cut_v2_Event_bCent);
    centBinM = qaUtility::GetInstance()->GetCentMultBin(Ncounter_refmult, qaUtility::GetInstance()->Cut_v2_Event_mCent);
    if (centBinB != -1) h2_v2_Event_bCent_b_Mult[centBinB]->Fill(Ncounter_refmult, event->GetB());
    if (centBinM != -1) h2_v2_Event_mCent_b_Mult[centBinM]->Fill(Ncounter_refmult, event->GetB());
    if (qaUtility::GetInstance()->Is_v2 == 1)
    {
      for (const auto &lparticle : v_particles_v2)
      {
        v2 = TMath::Cos(2. * (lparticle.GetPhi() - event->GetPhiRP()));
        ipid = qaUtility::GetInstance()->GetPdgId(lparticle.GetPdg());
        // if (ipid != -1) p3_v2_PID_b_pt_y[ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), event->GetB(), v2);
        if (ipid != -1 && centBinB != -1) p2_v2_PID_y_pt[centBinB][ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), v2);
        if (qaUtility::GetInstance()->Cut_Particle_v2_PID_pt(lparticle, ipid))
        {
          p2_v2_PID_b_pt[ipid]->Fill(lparticle.GetPt(), event->GetB(), v2);
          p2_v2_PID_M_pt[ipid]->Fill(lparticle.GetPt(), Ncounter_refmult, v2);
          if (centBinB != -1)
            p_v2_PID_bCent_pt[centBinB][ipid]->Fill(lparticle.GetPt(), v2);
          if (centBinM != -1)
            p_v2_PID_mCent_pt[centBinM][ipid]->Fill(lparticle.GetPt(), v2);
        }
        if (qaUtility::GetInstance()->Cut_Particle_v2_PID_y(lparticle, ipid))
        {
          p2_v2_PID_b_y[ipid]->Fill(lparticle.GetRapidity(), event->GetB(), v2);
          p2_v2_PID_M_y[ipid]->Fill(lparticle.GetRapidity(), Ncounter_refmult, v2);
          if (centBinB != -1)
            p_v2_PID_bCent_y[centBinB][ipid]->Fill(lparticle.GetRapidity(), v2);
          if (centBinM != -1)
            p_v2_PID_mCent_y[centBinM][ipid]->Fill(lparticle.GetRapidity(), v2);
        }
      }
    }

    // Loop over v3-related particles
    centBinB = qaUtility::GetInstance()->GetCentralityBin(event->GetB(), qaUtility::GetInstance()->Cut_v3_Event_bCent);
    centBinM = qaUtility::GetInstance()->GetCentMultBin(Ncounter_refmult, qaUtility::GetInstance()->Cut_v3_Event_mCent);
    if (centBinB != -1) h2_v3_Event_bCent_b_Mult[centBinB]->Fill(Ncounter_refmult, event->GetB());
    if (centBinM != -1) h2_v3_Event_mCent_b_Mult[centBinM]->Fill(Ncounter_refmult, event->GetB());
    if (qaUtility::GetInstance()->Is_v3 == 1)
    {
      for (const auto &lparticle : v_particles_v3)
      {
        v3 = TMath::Cos(3. * (lparticle.GetPhi() - event->GetPhiRP()));
        ipid = qaUtility::GetInstance()->GetPdgId(lparticle.GetPdg());
        // if (ipid != -1) p3_v3_PID_b_pt_y[ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), event->GetB(), v3);
        if (ipid != -1 && centBinB != -1) p2_v3_PID_y_pt[centBinB][ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), v3);
        if (qaUtility::GetInstance()->Cut_Particle_v3_PID_pt(lparticle, ipid))
        {
          p2_v3_PID_b_pt[ipid]->Fill(lparticle.GetPt(), event->GetB(), v3);
          p2_v3_PID_M_pt[ipid]->Fill(lparticle.GetPt(), Ncounter_refmult, v3);
          if (centBinB != -1)
            p_v3_PID_bCent_pt[centBinB][ipid]->Fill(lparticle.GetPt(), v3);
          if (centBinM != -1)
            p_v3_PID_mCent_pt[centBinM][ipid]->Fill(lparticle.GetPt(), v3);
        }
        if (qaUtility::GetInstance()->Cut_Particle_v3_PID_y(lparticle, ipid))
        {
          p2_v3_PID_b_y[ipid]->Fill(lparticle.GetRapidity(), event->GetB(), v3);
          p2_v3_PID_M_y[ipid]->Fill(lparticle.GetRapidity(), Ncounter_refmult, v3);
          if (centBinB != -1)
            p_v3_PID_bCent_y[centBinB][ipid]->Fill(lparticle.GetRapidity(), v3);
          if (centBinM != -1)
            p_v3_PID_mCent_y[centBinM][ipid]->Fill(lparticle.GetRapidity(), v3);
        }
      }
    }

    // Loop over v4-related particles
    centBinB = qaUtility::GetInstance()->GetCentralityBin(event->GetB(), qaUtility::GetInstance()->Cut_v4_Event_bCent);
    centBinM = qaUtility::GetInstance()->GetCentMultBin(Ncounter_refmult, qaUtility::GetInstance()->Cut_v4_Event_mCent);
    if (centBinB != -1) h2_v4_Event_bCent_b_Mult[centBinB]->Fill(Ncounter_refmult, event->GetB());
    if (centBinM != -1) h2_v4_Event_mCent_b_Mult[centBinM]->Fill(Ncounter_refmult, event->GetB());
    if (qaUtility::GetInstance()->Is_v4 == 1)
    {
      for (const auto &lparticle : v_particles_v4)
      {
        v4 = TMath::Cos(4. * (lparticle.GetPhi() - event->GetPhiRP()));
        ipid = qaUtility::GetInstance()->GetPdgId(lparticle.GetPdg());
        // if (ipid != -1) p3_v4_PID_b_pt_y[ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), event->GetB(), v4);
        if (ipid != -1 && centBinB != -1) p2_v4_PID_y_pt[centBinB][ipid]->Fill(lparticle.GetPt(), lparticle.GetRapidity(), v4);
        if (qaUtility::GetInstance()->Cut_Particle_v4_PID_pt(lparticle, ipid))
        {
          p2_v4_PID_b_pt[ipid]->Fill(lparticle.GetPt(), event->GetB(), v4);
          p2_v4_PID_M_pt[ipid]->Fill(lparticle.GetPt(), Ncounter_refmult, v4);
          if (centBinB != -1)
            p_v4_PID_bCent_pt[centBinB][ipid]->Fill(lparticle.GetPt(), v4);
          if (centBinM != -1)
            p_v4_PID_mCent_pt[centBinM][ipid]->Fill(lparticle.GetPt(), v4);
        }
        if (qaUtility::GetInstance()->Cut_Particle_v4_PID_y(lparticle, ipid))
        {
          p2_v4_PID_b_y[ipid]->Fill(lparticle.GetRapidity(), event->GetB(), v4);
          p2_v4_PID_M_y[ipid]->Fill(lparticle.GetRapidity(), Ncounter_refmult, v4);
          if (centBinB != -1)
            p_v4_PID_bCent_y[centBinB][ipid]->Fill(lparticle.GetRapidity(), v4);
          if (centBinM != -1)
            p_v4_PID_mCent_y[centBinM][ipid]->Fill(lparticle.GetRapidity(), v4);
        }
      }
    }

    if (qaUtility::GetInstance()->Cut_Event_minbias(event) && qaUtility::GetInstance()->Is_minbias == 1)
    {
      Minbias_counter++;
      h_minbias_Event_b->Fill(event->GetB());
      h_minbias_Event_Mult->Fill(Ncounter_minbias);
      h2_minbias_Event_b_Mult->Fill(Ncounter_minbias, event->GetB());
    }
    else
    {
      vRejectedEvents.push_back(Absolute_counter - 1);
    }

    if (qaUtility::GetInstance()->Cut_Event_refmult(event) && qaUtility::GetInstance()->Is_refmult == 1)
    {
      h_refmult_Event_b->Fill(event->GetB());
      h_refmult_Event_Mult->Fill(Ncounter_refmult);
      h2_refmult_Event_b_Mult->Fill(Ncounter_refmult, event->GetB());
    }

    delete event;
  }

  std::cout << "Loop is closed, " << Minbias_counter << " minbias events were counted (" << Absolute_counter << " events in total)." << std::endl;
  if (qaUtility::GetInstance()->debug)
  {
    if (vRejectedEvents.size() > 0)
    {
      std::cout << vRejectedEvents.size() << " rejected events:" << std::endl;
      for (Long64_t ire = 0; ire < (Long64_t)vRejectedEvents.size(); ire++)
      {
        std::cout << "Event " << vRejectedEvents.at(ire) << std::endl;
      }
    }
    else
    {
      std::cout << "No rejected events." << std::endl;
    }
  }

  if (qaUtility::GetInstance()->Is_minbias)
  {
    fo->mkdir("minbias");
    fo->cd("minbias");

    h_minbias_Event_b->Write();
    h_minbias_Event_Mult->Write();
    h2_minbias_Event_b_Mult->Write();
    h_minbias_Particle_pt->Write();
    h_minbias_Particle_eta->Write();
    h2_minbias_Particle_pteta->Write();
    h_minbias_Particle_E->Write();
    h_minbias_Particle_px->Write();
    h_minbias_Particle_py->Write();
    h_minbias_Particle_pz->Write();
    h_minbias_Particle_t->Write();
    h_minbias_Particle_x->Write();
    h_minbias_Particle_y->Write();
    h_minbias_Particle_z->Write();
    h_minbias_Particle_pdg->Write();

    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      h_minbias_Particle_PID_pt[i]->Write();
      h_minbias_Particle_PID_eta[i]->Write();
      h_minbias_Particle_PID_Y[i]->Write();
      h_minbias_Particle_PID_E[i]->Write();
      h_minbias_Particle_PID_px[i]->Write();
      h_minbias_Particle_PID_py[i]->Write();
      h_minbias_Particle_PID_pz[i]->Write();
      h_minbias_Particle_PID_t[i]->Write();
      h_minbias_Particle_PID_x[i]->Write();
      h_minbias_Particle_PID_y[i]->Write();
      h_minbias_Particle_PID_z[i]->Write();
    }
  }

  if (qaUtility::GetInstance()->Is_refmult)
  {
    fo->mkdir("refmult");
    fo->cd("refmult");

    h_refmult_Event_b->Write();
    h_refmult_Event_Mult->Write();
    h2_refmult_Event_b_Mult->Write();
    h_refmult_Particle_pt->Write();
    h_refmult_Particle_eta->Write();
    h2_refmult_Particle_pteta->Write();
    h_refmult_Particle_E->Write();
    h_refmult_Particle_px->Write();
    h_refmult_Particle_py->Write();
    h_refmult_Particle_pz->Write();
    h_refmult_Particle_t->Write();
    h_refmult_Particle_x->Write();
    h_refmult_Particle_y->Write();
    h_refmult_Particle_z->Write();
    h_refmult_Particle_pdg->Write();

    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      h_refmult_Particle_PID_pt[i]->Write();
      h_refmult_Particle_PID_eta[i]->Write();
      h_refmult_Particle_PID_E[i]->Write();
      h_refmult_Particle_PID_px[i]->Write();
      h_refmult_Particle_PID_py[i]->Write();
      h_refmult_Particle_PID_pz[i]->Write();
      h_refmult_Particle_PID_t[i]->Write();
      h_refmult_Particle_PID_x[i]->Write();
      h_refmult_Particle_PID_y[i]->Write();
      h_refmult_Particle_PID_z[i]->Write();
    }
  }

  if (qaUtility::GetInstance()->Is_v1)
  {
    fo->mkdir("v1");
    fo->cd("v1");

    h2_v1_Particle_pteta->Write();

    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v1_Event_bCent.size() - 1; i++)
    {
      h2_v1_Event_bCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v1_PID_bCent_pt[i][j]->Write();
        p_v1_PID_bCent_y[i][j]->Write();
      }
    }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v1_Event_mCent.size() - 1; i++)
    {
      h2_v1_Event_mCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v1_PID_mCent_pt[i][j]->Write();
        p_v1_PID_mCent_y[i][j]->Write();
      }
    }
    // for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    // {
    //   p3_v1_PID_b_pt_y[i]->Write();
    // }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v1_Event_bCent.size() - 1; i++)
    {
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p2_v1_PID_y_pt[i][j]->Write();
      }
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v1_PID_b_pt[i]->Write();
      p2_v1_PID_b_y[i]->Write();
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v1_PID_M_pt[i]->Write();
      p2_v1_PID_M_y[i]->Write();
    }
  }

  if (qaUtility::GetInstance()->Is_v2)
  {
    fo->mkdir("v2");
    fo->cd("v2");

    h2_v2_Particle_pteta->Write();

    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v2_Event_bCent.size() - 1; i++)
    {
      h2_v2_Event_bCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v2_PID_bCent_pt[i][j]->Write();
        p_v2_PID_bCent_y[i][j]->Write();
      }
    }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v2_Event_mCent.size() - 1; i++)
    {
      h2_v2_Event_mCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v2_PID_mCent_pt[i][j]->Write();
        p_v2_PID_mCent_y[i][j]->Write();
      }
    }
    // for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    // {
    //   p3_v2_PID_b_pt_y[i]->Write();
    // }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v2_Event_bCent.size() - 1; i++)
    {
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p2_v2_PID_y_pt[i][j]->Write();
      }
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v2_PID_b_pt[i]->Write();
      p2_v2_PID_b_y[i]->Write();
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v2_PID_M_pt[i]->Write();
      p2_v2_PID_M_y[i]->Write();
    }
  }

  if (qaUtility::GetInstance()->Is_v3)
  {
    fo->mkdir("v3");
    fo->cd("v3");

    h2_v3_Particle_pteta->Write();

    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v3_Event_bCent.size() - 1; i++)
    {
      h2_v3_Event_bCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v3_PID_bCent_pt[i][j]->Write();
        p_v3_PID_bCent_y[i][j]->Write();
      }
    }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v3_Event_mCent.size() - 1; i++)
    {
      h2_v3_Event_mCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v3_PID_mCent_pt[i][j]->Write();
        p_v3_PID_mCent_y[i][j]->Write();
      }
    }
    // for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    // {
    //   p3_v3_PID_b_pt_y[i]->Write();
    // }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v3_Event_bCent.size() - 1; i++)
    {
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p2_v3_PID_y_pt[i][j]->Write();
      }
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v3_PID_b_pt[i]->Write();
      p2_v3_PID_b_y[i]->Write();
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v3_PID_M_pt[i]->Write();
      p2_v3_PID_M_y[i]->Write();
    }
  }

  if (qaUtility::GetInstance()->Is_v4)
  {
    fo->mkdir("v4");
    fo->cd("v4");

    h2_v4_Particle_pteta->Write();

    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v4_Event_bCent.size() - 1; i++)
    {
      h2_v4_Event_bCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v4_PID_bCent_pt[i][j]->Write();
        p_v4_PID_bCent_y[i][j]->Write();
      }
    }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v4_Event_mCent.size() - 1; i++)
    {
      h2_v4_Event_mCent_b_Mult[i]->Write();
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p_v4_PID_mCent_pt[i][j]->Write();
        p_v4_PID_mCent_y[i][j]->Write();
      }
    }
    // for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    // {
    //   p3_v4_PID_b_pt_y[i]->Write();
    // }
    for (int i = 0; i < (int)qaUtility::GetInstance()->Cut_v4_Event_bCent.size() - 1; i++)
    {
      for (int j = 0; j < qaUtility::GetInstance()->npid; j++)
      {
        p2_v4_PID_y_pt[i][j]->Write();
      }
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v4_PID_b_pt[i]->Write();
      p2_v4_PID_b_y[i]->Write();
    }
    for (int i = 0; i < qaUtility::GetInstance()->npid; i++)
    {
      p2_v4_PID_M_pt[i]->Write();
      p2_v4_PID_M_y[i]->Write();
    }
  }

  fo->Close();

  timer.Stop();
  timer.Print();

  return 0;
}
