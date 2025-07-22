#include <qaReader_mcini.h>

ClassImp(qaReader_mcini);

qaReader_mcini::qaReader_mcini(/* args */) : is_init(false), fCurrentEvent(-1), fEvent(nullptr), fParticle(nullptr)
{
}

qaReader_mcini::~qaReader_mcini()
{
}

Bool_t qaReader_mcini::ChainCheck()
{
  if (!is_init)
  {
    return false;
  }

  if (fCurrentEvent == -1)
  {
    return false;
  }

  if (!fChain->GetEntry(fCurrentEvent))
  {
    return false;
  }

  return true;
}

void qaReader_mcini::SetChain(const TString &inputFileName)
{
  fChain = (TChain *)qaUtility::GetInstance()->initChain(inputFileName, fChainName);

  fChain->SetBranchAddress("event", &fEvent);

  is_init = kTRUE;
}

qaEvent *qaReader_mcini::ReadEvent(Long64_t iev)
{
  fCurrentEvent = iev;

  if (!ChainCheck())
  {
    return nullptr;
  }

  qaEvent *event = new qaEvent();

  event->SetB(fEvent->GetB());
  event->SetPhiRP(fEvent->GetPhi());
  event->SetNparticles(fEvent->GetNpa());

  return event;
}

qaParticle *qaReader_mcini::ReadParticle(Int_t ipart)
{
  if (!ChainCheck())
  {
    return nullptr;
  }

  if (ipart >= fEvent->GetNpa())
  {
    return nullptr;
  }

  fParticle = fEvent->GetParticle(ipart);
  fMomentum = fParticle->GetMomentum();

  qaParticle *particle = new qaParticle();

  particle->SetEnergy(fMomentum.E());
  particle->SetPdg(fParticle->GetPdg());
  particle->SetPxPyPz(fMomentum.Px(), fMomentum.Py(), fMomentum.Pz());
  particle->SetTime(0.);
  particle->SetXYZ(0., 0., 0.);
  particle->SetCharge(qaUtility::GetInstance()->GetCharge(fParticle->GetPdg()));

  return particle;
}