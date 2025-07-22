#ifndef QATOOLS_FORMAT_EVENT_H
#define QATOOLS_FORMAT_EVENT_H

#include <iostream>
#include <vector>

#include <Rtypes.h>

class qaEvent
{
private:
  Float_t fB;
  Float_t fPhiRP;
  Int_t fNparticles;

public:
  qaEvent(/* args */);
  virtual ~qaEvent();

  // Setters
  virtual void SetB(Float_t _a) { fB = _a; }
  virtual void SetPhiRP(Float_t _a) { fPhiRP = _a; }
  virtual void SetNparticles(Float_t _a) { fNparticles = _a; }

  // Getters
  virtual Float_t GetB() const { return fB; }
  virtual Float_t GetPhiRP() const { return fPhiRP; }
  virtual Int_t GetNparticles() const { return fNparticles; }

  ClassDef(qaEvent, 0);
};

#endif