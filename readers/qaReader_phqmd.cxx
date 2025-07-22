#include <qaReader_phqmd.h>

ClassImp(qaReader_phqmd);

qaReader_phqmd::qaReader_phqmd(/* args */) : is_init(false), fCurrentEvent(-1), fEvent(nullptr), fParticle(nullptr)
{
}

qaReader_phqmd::~qaReader_phqmd()
{
}

Bool_t qaReader_phqmd::ChainCheck()
{
  if (!is_init)
  {
    return false;
  }

  if (fCurrentEvent == -1)
  {
    return false;
  }

  if (!fChainPHSD->GetEntry(fCurrentEvent))
  {
    return false;
  }
  if (!fChainFrag->GetEntry(fCurrentEvent))
  {
    return false;
  }

  return true;
}

void qaReader_phqmd::SetChain(const TString &inputFileName)
{
  fChainPHSD = (TChain *)qaUtility::GetInstance()->initChain(inputFileName, fChainPHSDName);

  fChainPHSD->SetBranchAddress("event", &fEvent);

  fChainFrag = (TChain *)qaUtility::GetInstance()->initChain(inputFileName, fChainFragName);

  fChainFrag->SetBranchAddress("eventFrag", &fEventFrag);

  is_init = kTRUE;
}

qaEvent *qaReader_phqmd::ReadEvent(Long64_t iev)
{
  fCurrentEvent = iev;

  if (!ChainCheck())
  {
    return nullptr;
  }

  qaEvent *event = new qaEvent();

  event->SetB(fEvent->GetB());
  // event->SetPhiRP(0.); // in PHQMD axis orientation is rotated by 180 deg. In HSD/PHSD it's ok.
  event->SetPhiRP(TMath::Pi()); // in PHQMD axis orientation is rotated by 180 deg. In HSD/PHSD it's ok.
  event->SetNparticles(fEvent->GetNpart() + fEventFrag->GetNfragMST()); // number of particles from PHSD and number of MST fragments

  return event;
}

qaParticle *qaReader_phqmd::ReadParticle(Int_t ipart)
{
  if (!ChainCheck())
  {
    return nullptr;
  }

  if (ipart >= fEvent->GetNpart() + fEventFrag->GetNfragMST())
  {
    return nullptr;
  }

  if (ipart < 0)
  {
    return nullptr;
  }

  bool is_particle = false;
  bool is_fragment = false;

  if (ipart < fEvent->GetNpart())
  {
    is_particle = true;
  }
  if (ipart >= fEvent->GetNpart())
  {
    is_fragment = true;
  }

  if (!is_particle && !is_fragment)
  {
    return nullptr;
  }

  if (is_particle && is_fragment)
  {
    return nullptr;
  }

  qaParticle *particle = new qaParticle();

  if (is_particle)
  {
    fParticle = fEvent->GetParticle(ipart);
    if (fParticle->IsInMST()) // Check whether the particle from PHSD was used to create MST fragment
    {
      return nullptr;
    }
    particle->SetEnergy(fParticle->E());
    particle->SetPdg(fParticle->GetPdg());
    particle->SetPxPyPz(fParticle->Px(), fParticle->Py(), fParticle->Pz());
    particle->SetTime(0.);
    particle->SetXYZ(0., 0., 0.);
    particle->SetCharge(fParticle->GetCharge());
  }
  if (is_fragment)
  {
    fFragmentMST = fEventFrag->GetFragmentMST(ipart - fEvent->GetNpart());
    particle->SetEnergy(fFragmentMST->E());
    particle->SetPdg(fFragmentMST->GetPdg());
    particle->SetPxPyPz(fFragmentMST->Px(), fFragmentMST->Py(), fFragmentMST->Pz());
    particle->SetTime(0.);
    particle->SetXYZ(0., 0., 0.);
    particle->SetCharge(fFragmentMST->GetZ());
  }

  return particle;
}
