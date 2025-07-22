#ifndef QATOOLS_READERS_EPOS4_ROOT_H
#define QATOOLS_READERS_EPOS4_ROOT_H

#include <Rtypes.h>
#include <TChain.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

#include <qaReader_manager.h>

#define MAX_TRACKS 15000

class qaReader_epos4_root : virtual public qaReader_manager
{
private:
  TChain *fChain;

  const char *fChainName = "teposevent";

  bool is_init;
  Long64_t fCurrentEvent;

  Int_t np;
  Float_t bim;
  Float_t phi;
  Int_t nev;
  Int_t id[MAX_TRACKS]; //[np]
  Float_t e[MAX_TRACKS];   //[np]
  Float_t px[MAX_TRACKS];   //[np]
  Float_t py[MAX_TRACKS];   //[np]
  Float_t pz[MAX_TRACKS];   //[np]
  Float_t t[MAX_TRACKS];    //[np]
  Float_t x[MAX_TRACKS];    //[np]
  Float_t y[MAX_TRACKS];    //[np]
  Float_t z[MAX_TRACKS];    //[np]

  std::map<int,int> fId2pdg;

  void SetPidMap();

  Bool_t ChainCheck();

public:
  qaReader_epos4_root(/* args */);
  virtual ~qaReader_epos4_root();

  virtual void SetChain(const TString &inputFileName);
  virtual Long64_t GetEntries() { return fChain->GetEntries(); }
  virtual qaEvent *ReadEvent(Long64_t iev);
  virtual qaParticle* ReadParticle(Int_t ipart);

  ClassDef(qaReader_epos4_root, 0);
};

#endif
