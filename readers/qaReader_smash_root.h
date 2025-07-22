#ifndef QATOOLS_READERS_SMASH_ROOT_H
#define QATOOLS_READERS_SMASH_ROOT_H

#include <Rtypes.h>
#include <TChain.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

#include <qaReader_manager.h>

#define MAX_TRACKS 15000

class qaReader_smash_root : virtual public qaReader_manager
{
private:
  TChain *fChain;

  const char *fChainName = "particles";

  bool is_init;
  Long64_t fCurrentEvent;

  Int_t npart;
  Double_t impact_b;
  Int_t ev;
  Int_t tcounter;
  Int_t pdgcode[MAX_TRACKS]; //[npart]
  Double_t p0[MAX_TRACKS];   //[npart]
  Double_t px[MAX_TRACKS];   //[npart]
  Double_t py[MAX_TRACKS];   //[npart]
  Double_t pz[MAX_TRACKS];   //[npart]
  Double_t t[MAX_TRACKS];    //[npart]
  Double_t x[MAX_TRACKS];    //[npart]
  Double_t y[MAX_TRACKS];    //[npart]
  Double_t z[MAX_TRACKS];    //[npart]

  Bool_t ChainCheck();

public:
  qaReader_smash_root(/* args */);
  virtual ~qaReader_smash_root();

  virtual void SetChain(const TString &inputFileName);
  virtual Long64_t GetEntries() { return fChain->GetEntries(); }
  virtual qaEvent *ReadEvent(Long64_t iev);
  virtual qaParticle* ReadParticle(Int_t ipart);

  ClassDef(qaReader_smash_root, 0);
};

#endif
