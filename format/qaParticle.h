#ifndef QATOOLS_FORMAT_PARTICLE_H
#define QATOOLS_FORMAT_PARTICLE_H

#include <iostream>

#include <Rtypes.h>
#include <TVector3.h>

class qaParticle
{
private:
  TVector3 fMom;
  TVector3 fR;
  Float_t fEn;
  Float_t fT;
  Int_t fPdg;
  Int_t fCharge;

public:
  qaParticle(/* args */);
  virtual ~qaParticle();

  // Setters
  virtual void SetPxPyPz(Float_t _px, Float_t _py, Float_t _pz) { fMom.SetXYZ(_px, _py, _pz); }
  virtual void SetXYZ(Float_t _x, Float_t _y, Float_t _z) { fR.SetXYZ(_x, _y, _z); }
  virtual void SetPx(Float_t _a) { fMom.SetX(_a); }
  virtual void SetPy(Float_t _a) { fMom.SetY(_a); }
  virtual void SetPz(Float_t _a) { fMom.SetZ(_a); }
  virtual void SetX(Float_t _a) { fR.SetX(_a); }
  virtual void SetY(Float_t _a) { fR.SetY(_a); }
  virtual void SetZ(Float_t _a) { fR.SetZ(_a); }
  virtual void SetPdg(Int_t _a) { fPdg = _a; }
  virtual void SetEnergy(Float_t _a) { fEn = _a; }
  virtual void SetTime(Float_t _a) { fT = _a; }
  virtual void SetCharge(Int_t _a) { fCharge = _a; }

  // Getters
  virtual TVector3 GetMom() { return fMom; }
  virtual TVector3 GetR() { return fR; }
  virtual Float_t GetPx() { return fMom.X(); }
  virtual Float_t GetPy() { return fMom.Y(); }
  virtual Float_t GetPz() { return fMom.Z(); }
  virtual Float_t GetPt() { return fMom.Perp(); }
  virtual Float_t GetP() { return fMom.Mag(); }
  virtual Float_t GetEta() { return fMom.Eta(); }
  virtual Float_t GetPhi() { return fMom.Phi(); }
  virtual Float_t GetT() { return fT; }
  virtual Float_t GetX() { return fR.X(); }
  virtual Float_t GetY() { return fR.Y(); }
  virtual Float_t GetZ() { return fR.Z(); }
  virtual Int_t GetPdg() const { return fPdg; }
  virtual Float_t GetEnergy() const { return fEn; }
  virtual Int_t GetCharge() const { return fCharge; }

  ClassDef(qaParticle, 0);
};

#endif