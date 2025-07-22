#ifndef QATOOLS_READERS_HSD_ROOT_H
#define QATOOLS_READERS_HSD_ROOT_H

#include <Rtypes.h>
#include <TChain.h>
#include <TLorentzVector.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

#include <qaReader_manager.h>

#include <phqmd2root/src/libPHQMDEvent.h>

class qaReader_hsd_root : virtual public qaReader_manager
{
private:
  TChain *fChainPHSD, *fChainFrag;

  const char *fChainPHSDName = "PHQMDtree";
  const char *fChainFragName = "FRAGtree";

  bool is_init;
  Long64_t fCurrentEvent;

  Event *fEvent;
  EventClust *fEventFrag;
  Particle *fParticle;
  Baryon *fBaryonMST;
  Fragment *fFragmentMST;
  TLorentzVector fMomentum;

  Bool_t ChainCheck();

public:
  qaReader_hsd_root(/* args */);
  virtual ~qaReader_hsd_root();

  virtual void SetChain(const TString &inputFileName);
  virtual Long64_t GetEntries() { return fChainFrag->GetEntries(); }
  virtual qaEvent *ReadEvent(Long64_t iev);
  virtual qaParticle* ReadParticle(Int_t ipart);

  ClassDef(qaReader_hsd_root, 0);
};

#endif