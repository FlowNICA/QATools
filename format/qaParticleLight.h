#ifndef QATOOLS_FORMAT_PARTICLE_LIGHT_H
#define QATOOLS_FORMAT_PARTICLE_LIGHT_H

#include <iostream>
#include <Rtypes.h>
#include <TMath.h>

#include <qaParticle.h>

class qaParticleLight
{
private:
    Float_t fPx;
    Float_t fPy;
    Float_t fPz;
    Float_t fE;
    Int_t fPdg;
    Int_t fCharge;

public:
    qaParticleLight(/* args */);
    virtual ~qaParticleLight();

    virtual void SetParticle(Float_t _px, Float_t _py, Float_t _pz, Float_t _e, Int_t _pdg, Int_t _charge);
    virtual void SetParticle(qaParticle *const &_particle);

    virtual Float_t GetPx() const { return fPx; }
    virtual Float_t GetPy() const { return fPy; }
    virtual Float_t GetPz() const { return fPz; }
    virtual Float_t GetEnergy() const { return fE; }
    virtual Int_t GetPdg() const { return fPdg; }
    virtual Int_t GetCharge() const { return fCharge; }

    virtual Float_t GetPt() const { return TMath::Sqrt(TMath::Power(fPx, 2) + TMath::Power(fPy, 2)); }
    virtual Float_t GetP() const { return TMath::Sqrt(TMath::Power(fPx, 2) + TMath::Power(fPy, 2) + TMath::Power(fPz, 2)); }
    virtual Float_t GetEta() const { return 0.5 * TMath::Log((TMath::Sqrt(TMath::Power(fPx, 2) + TMath::Power(fPy, 2) + TMath::Power(fPz, 2)) + fPz) / (TMath::Sqrt(TMath::Power(fPx, 2) + TMath::Power(fPy, 2) + TMath::Power(fPz, 2)) - fPz)); }
    virtual Float_t GetRapidity() const { return 0.5 * TMath::Log((fE + fPz) / (fE - fPz)); }
    virtual Float_t GetPhi() const { return TMath::ATan2(fPy, fPx); }

    ClassDef(qaParticleLight, 0);
};

#endif