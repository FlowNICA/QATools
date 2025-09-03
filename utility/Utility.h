#ifndef QATOOLS_UTILITY_H
#define QATOOLS_UTILITY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>
#include <string>

#include <Rtypes.h>
#include <TString.h>
#include <TChain.h>
#include <TEnv.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <qaParticleLight.h>

class qaUtility
{
protected:
  qaUtility();
  virtual ~qaUtility();
  static qaUtility *fUtility;

public:
  qaUtility(qaUtility &other) = delete;
  void operator=(const qaUtility &) = delete;

  static qaUtility *GetInstance();

  const Double_t error_code = -999.;
  const Int_t npid = 10;
  const std::vector<Int_t> vpdg = {0, 211, 321, 2212, 2112, 0, -211, -321, -2212, -2112};
  const std::vector<Double_t> mpdg = {error_code, 0.13957, 0.493677, 0.938272, 0.88277299, error_code, 0.13957, 0.493677, 0.938272, 0.88277299};
  const Int_t maxCentBins = 20;

  Int_t Nevents;
  Int_t debug;
  std::string format;

  Int_t Is_minbias;
  Int_t Is_refmult;
  Int_t Is_v1;
  Int_t Is_v2;
  Int_t Is_v3;
  Int_t Is_v4;

  Double_t Cut_minbias_Event_bmin;
  Double_t Cut_minbias_Event_bmax;
  Double_t Cut_minbias_Particle_ptmin;
  Double_t Cut_minbias_Particle_ptmax;
  Double_t Cut_minbias_Particle_etamin;
  Double_t Cut_minbias_Particle_etamax;
  Double_t Cut_minbias_Particle_ymin;
  Double_t Cut_minbias_Particle_ymax;

  Double_t Cut_refmult_Event_bmin;
  Double_t Cut_refmult_Event_bmax;
  Double_t Cut_refmult_Particle_ptmin;
  Double_t Cut_refmult_Particle_ptmax;
  Double_t Cut_refmult_Particle_etamin;
  Double_t Cut_refmult_Particle_etamax;
  Int_t    Cut_refmult_Particle_isCharged;

  Bool_t ReadConfig(const TString &configFileName);
  TChain *initChain(const TString &inputFileName, const char *chainName);

  std::vector<Float_t> ParseVector(std::string _input);
  Bool_t initCentrality();

  Bool_t Cut_Event_minbias(qaEvent *const &event);
  Bool_t Cut_Event_refmult(qaEvent *const &event);
  Bool_t Cut_Particle_minbias(qaParticle *const &particle);
  Bool_t Cut_Particle_refmult(qaParticle *const &particle);

  Double_t GetCharge(Int_t pdg);
  Int_t GetPdgId(Int_t pdg);

  Int_t GetCentralityBin(Float_t b, std::vector<Float_t> vcent);
  Int_t GetCentMultBin(Int_t mult, std::vector<Float_t> vcent);

  ClassDef(qaUtility, 0);
}; // class qaUtility

#endif
