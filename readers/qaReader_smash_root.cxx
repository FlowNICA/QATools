#include <qaReader_smash_root.h>

ClassImp(qaReader_smash_root);

qaReader_smash_root::qaReader_smash_root(/* args */) : is_init(false), fCurrentEvent(-1)
{
}

qaReader_smash_root::~qaReader_smash_root()
{
}

Bool_t qaReader_smash_root::ChainCheck()
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

void qaReader_smash_root::SetChain(const TString &inputFileName)
{
  fChain = (TChain *)qaUtility::GetInstance()->initChain(inputFileName, fChainName);

  fChain->SetBranchAddress("npart", &npart);
  fChain->SetBranchAddress("impact_b", &impact_b);
  fChain->SetBranchAddress("pdgcode", pdgcode);
  fChain->SetBranchAddress("p0", p0);
  fChain->SetBranchAddress("px", px);
  fChain->SetBranchAddress("py", py);
  fChain->SetBranchAddress("pz", pz);
  fChain->SetBranchAddress("t", t);
  fChain->SetBranchAddress("x", x);
  fChain->SetBranchAddress("y", y);
  fChain->SetBranchAddress("z", z);

  is_init = kTRUE;
}

qaEvent *qaReader_smash_root::ReadEvent(Long64_t iev)
{
  fCurrentEvent = iev;

  if (!ChainCheck())
  {
    return nullptr;
  }

  qaEvent *event = new qaEvent();

  event->SetB(impact_b);
  event->SetPhiRP(0.);
  event->SetNparticles(npart);

  return event;
}

qaParticle *qaReader_smash_root::ReadParticle(Int_t ipart)
{
  if (!ChainCheck())
  {
    return nullptr;
  }

  if (ipart >= npart)
  {
    return nullptr;
  }

  qaParticle *particle = new qaParticle();

  particle->SetEnergy(p0[ipart]);
  particle->SetPdg(pdgcode[ipart]);
  particle->SetPxPyPz(px[ipart], py[ipart], pz[ipart]);
  particle->SetTime(t[ipart]);
  particle->SetXYZ(x[ipart], y[ipart], z[ipart]);
  particle->SetCharge(qaUtility::GetInstance()->GetCharge(pdgcode[ipart]));

  return particle;
}
