#include <qaParticleLight.h>

ClassImp(qaParticleLight);

qaParticleLight::qaParticleLight(/* args */) : fPx(0), fPy(0), fPz(0), fE(0), fPdg(0)
{
}

qaParticleLight::~qaParticleLight()
{
}

void qaParticleLight::SetParticle(Float_t _px, Float_t _py, Float_t _pz, Float_t _e, Int_t _pdg, Int_t _charge)
{
    fPx = _px;
    fPy = _py;
    fPz = _pz;
    fE = _e;
    fPdg = _pdg;
    fCharge = _charge;
}

void qaParticleLight::SetParticle(qaParticle *const &_particle)
{
    fPx = _particle->GetPx();
    fPy = _particle->GetPy();
    fPz = _particle->GetPz();
    fE = _particle->GetEnergy();
    fPdg = _particle->GetPdg();
    fCharge = _particle->GetCharge();
}