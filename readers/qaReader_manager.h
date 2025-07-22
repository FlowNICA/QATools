#ifndef QATOOLS_READERS_MANAGER_H
#define QATOOLS_READERS_MANAGER_H

#include <Rtypes.h>
#include <TString.h>

#include <qaEvent.h>
#include <qaParticle.h>
#include <Utility.h>

class qaReader_manager
{
private:
  /* data */
public:
  virtual ~qaReader_manager();

  virtual void SetChain(const TString &inputFileName) = 0;
  virtual Long64_t GetEntries() = 0;
  virtual qaEvent *ReadEvent(Long64_t iev) = 0;
  virtual qaParticle* ReadParticle(Int_t ipart) = 0;

  ClassDef(qaReader_manager,0);
};

#endif
