#ifndef QATOOLS_READERS_MCPICO_H
#define QATOOLS_READERS_MCPICO_H

#include <Rtypes.h>
#include <TChain.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

#include <qaReader_manager.h>

#define MAX_TRACKS 15000

class qaReader_mcpico : virtual public qaReader_manager
{
private:
  TChain *fChain;

  const char *fChainName = "mctree";

  bool is_init;
  Long64_t fCurrentEvent;

   Float_t         bimp;
   Float_t         phi2;
   Float_t         phi3;
   Float_t         ecc2;
   Float_t         ecc3;
   Int_t           npart;
   Int_t           nh;
   Float_t         momx[MAX_TRACKS];   //[nh]
   Float_t         momy[MAX_TRACKS];   //[nh]
   Float_t         momz[MAX_TRACKS];   //[nh]
   Float_t         ene[MAX_TRACKS];   //[nh]
   Int_t           hid[MAX_TRACKS];   //[nh]
   Int_t           pdg[MAX_TRACKS];   //[nh]
   Short_t         charge[MAX_TRACKS];   //[nh]

  Bool_t ChainCheck();

public:
  qaReader_mcpico(/* args */);
  virtual ~qaReader_mcpico();

  virtual void SetChain(const TString &inputFileName);
  virtual Long64_t GetEntries() { return fChain->GetEntries(); }
  virtual qaEvent *ReadEvent(Long64_t iev);
  virtual qaParticle* ReadParticle(Int_t ipart);

  ClassDef(qaReader_mcpico, 0);
};

#endif
