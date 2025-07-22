#include <qaReader_mcpico.h>

ClassImp(qaReader_mcpico);

qaReader_mcpico::qaReader_mcpico(/* args */) : is_init(false), fCurrentEvent(-1)
{
}

qaReader_mcpico::~qaReader_mcpico()
{
}

Bool_t qaReader_mcpico::ChainCheck()
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

void qaReader_mcpico::SetChain(const TString &inputFileName)
{
  fChain = (TChain *)qaUtility::GetInstance()->initChain(inputFileName, fChainName);

  fChain->SetBranchAddress("bimp", &bimp);
  fChain->SetBranchAddress("phi2", &phi2);
  fChain->SetBranchAddress("phi3", &phi3);
  fChain->SetBranchAddress("ecc2", &ecc2);
  fChain->SetBranchAddress("ecc3", &ecc3);
  fChain->SetBranchAddress("npart", &npart);
  fChain->SetBranchAddress("nh", &nh);
  fChain->SetBranchAddress("momx", momx);
  fChain->SetBranchAddress("momy", momy);
  fChain->SetBranchAddress("momz", momz);
  fChain->SetBranchAddress("ene", ene);
  fChain->SetBranchAddress("hid", hid);
  fChain->SetBranchAddress("pdg", pdg);
  fChain->SetBranchAddress("charge", charge);

  is_init = kTRUE;
}

qaEvent *qaReader_mcpico::ReadEvent(Long64_t iev)
{
  fCurrentEvent = iev;

  if (!ChainCheck())
  {
    return nullptr;
  }

  qaEvent *event = new qaEvent();

  event->SetB(bimp);
  event->SetPhiRP(phi2);
  event->SetNparticles(nh);

  return event;
}

qaParticle *qaReader_mcpico::ReadParticle(Int_t ipart)
{
  if (!ChainCheck())
  {
    return nullptr;
  }

  if (ipart >= nh)
  {
    return nullptr;
  }

  qaParticle *particle = new qaParticle();

  particle->SetEnergy(ene[ipart]);
  particle->SetPdg(pdg[ipart]);
  particle->SetPxPyPz(momx[ipart], momy[ipart], momz[ipart]);
  particle->SetTime(0.);
  particle->SetXYZ(0., 0., 0.);
  particle->SetCharge(qaUtility::GetInstance()->GetCharge(pdg[ipart]));

  return particle;
}
