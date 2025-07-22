#ifndef QATOOLS_READERS_MCINI_H
#define QATOOLS_READERS_MCINI_H

#include <Rtypes.h>
#include <TChain.h>
#include <TLorentzVector.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

#include <qaReader_manager.h>

#include <URun.h>
#include <UEvent.h>
#include <UParticle.h>
#include <EventInitialState.h>

class qaReader_mcini : virtual public qaReader_manager
{
private:
  TChain *fChain;

  const char *fChainName = "events";

  bool is_init;
  Long64_t fCurrentEvent;

  UEvent *fEvent;
  UParticle *fParticle;
  TLorentzVector fMomentum;

  Bool_t ChainCheck();

public:
  qaReader_mcini(/* args */);
  virtual ~qaReader_mcini();

  virtual void SetChain(const TString &inputFileName);
  virtual Long64_t GetEntries() { return fChain->GetEntries(); }
  virtual qaEvent *ReadEvent(Long64_t iev);
  virtual qaParticle* ReadParticle(Int_t ipart);

  ClassDef(qaReader_mcini, 0);
};

#endif
