#include <Utility.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>

ClassImp(qaUtility);

qaUtility *qaUtility::fUtility = nullptr;
;

qaUtility::qaUtility() : Nevents(-1),
                         debug(0),
                         format("mctree"),
                         Is_minbias(1),
                         Is_refmult(1),
                         Is_v1(1),
                         Is_v2(1),
                         Is_v3(1),
                         Is_v4(1),
                         Cut_minbias_Event_bmin(0.),
                         Cut_minbias_Event_bmax(16.),
                         Cut_minbias_Particle_ptmin(0.),
                         Cut_minbias_Particle_ptmax(100.),
                         Cut_minbias_Particle_etamin(-100.),
                         Cut_minbias_Particle_etamax(100.),
                         Cut_minbias_Particle_ymin(-100.),
                         Cut_minbias_Particle_ymax(100.),
                         Cut_refmult_Event_bmin(0.),
                         Cut_refmult_Event_bmax(16.),
                         Cut_refmult_Particle_ptmin(0.15),
                         Cut_refmult_Particle_ptmax(3.),
                         Cut_refmult_Particle_etamin(-0.5),
                         Cut_refmult_Particle_etamax(0.5),
                         Cut_refmult_Particle_isCharged(1)
{
}

qaUtility::~qaUtility()
{
}

qaUtility *qaUtility::GetInstance()
{
  if (fUtility == nullptr)
  {
    fUtility = new qaUtility();
  }
  return fUtility;
}

Bool_t qaUtility::ReadConfig(const TString &configFileName)
{
  if (configFileName.Length() == 0)
  {
    return false;
  }

  TEnv env(configFileName);

  Nevents = env.GetValue("Nevents", 0);
  debug = env.GetValue("debug", 0);

  Is_minbias = env.GetValue("Is_minbias", 0);
  Cut_minbias_Event_bmin = env.GetValue("Cut_minbias_Event_bmin", 0.);
  Cut_minbias_Event_bmax = env.GetValue("Cut_minbias_Event_bmax", 0.);

  Cut_minbias_Particle_ptmin = env.GetValue("Cut_minbias_Particle_ptmin", 0.);
  Cut_minbias_Particle_ptmax = env.GetValue("Cut_minbias_Particle_ptmax", 0.);
  Cut_minbias_Particle_etamin = env.GetValue("Cut_minbias_Particle_etamin", 0.);
  Cut_minbias_Particle_etamax = env.GetValue("Cut_minbias_Particle_etamax", 0.);
  Cut_minbias_Particle_ymin = env.GetValue("Cut_minbias_Particle_ymin", 0.);
  Cut_minbias_Particle_ymax = env.GetValue("Cut_minbias_Particle_ymax", 0.);

  Is_refmult = env.GetValue("Is_refmult", 0);
  Cut_refmult_Event_bmin = env.GetValue("Cut_refmult_Event_bmin", 0.);
  Cut_refmult_Event_bmax = env.GetValue("Cut_refmult_Event_bmax", 0.);

  Cut_refmult_Particle_ptmin = env.GetValue("Cut_refmult_Particle_ptmin", 0.);
  Cut_refmult_Particle_ptmax = env.GetValue("Cut_refmult_Particle_ptmax", 0.);
  Cut_refmult_Particle_etamin = env.GetValue("Cut_refmult_Particle_etamin", 0.);
  Cut_refmult_Particle_etamax = env.GetValue("Cut_refmult_Particle_etamax", 0.);
  Cut_refmult_Particle_isCharged = env.GetValue("Cut_refmult_Particle_isCharged", 0);

  Is_v1 = env.GetValue("Is_v1", 0);
  Is_v2 = env.GetValue("Is_v2", 0);
  Is_v3 = env.GetValue("Is_v3", 0);
  Is_v4 = env.GetValue("Is_v4", 0);

  return true;
}

TChain *qaUtility::initChain(const TString &inputFileName, const char *chainName)
{
  TChain *chain = new TChain(chainName);
  std::ifstream file(inputFileName.Data());
  std::string line;
  while (std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  return chain;
}

std::vector<Float_t> qaUtility::ParseVector(std::string _input)
{
  std::vector<Float_t> vB;

  std::istringstream iss(_input);

  std::copy(std::istream_iterator<Float_t>(iss),
            std::istream_iterator<Float_t>(),
            std::back_inserter(vB));

  return vB;
}

Bool_t qaUtility::Cut_Event_minbias(qaEvent *const &event)
{
  if (event->GetB() < Cut_minbias_Event_bmin)
    return false;
  if (event->GetB() > Cut_minbias_Event_bmax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Event_refmult(qaEvent *const &event)
{
  if (event->GetB() < Cut_refmult_Event_bmin)
    return false;
  if (event->GetB() > Cut_refmult_Event_bmax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_minbias(qaParticle *const &particle)
{
  if (particle->GetPt() < Cut_minbias_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_minbias_Particle_ptmax)
    return false;
  if (particle->GetEta() < Cut_minbias_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_minbias_Particle_etamax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_refmult(qaParticle *const &particle)
{
  if (particle->GetPt() < Cut_refmult_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_refmult_Particle_ptmax)
    return false;
  if (particle->GetEta() < Cut_refmult_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_refmult_Particle_etamax)
    return false;

  Double_t charge = GetCharge(particle->GetPdg());
  if (Cut_refmult_Particle_isCharged)
  {
    if (charge == error_code)
      return false;
    if (charge == 0)
      return false;
  }

  return true;
}

Double_t qaUtility::GetCharge(Int_t pdg)
{
  auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg);
  if (!particle)
    return error_code;
  return particle->Charge() / 3.;
}

Int_t qaUtility::GetPdgId(Int_t pdg)
{
  if (pdg == vpdg.at(1))
    return 1;
  if (pdg == vpdg.at(2))
    return 2;
  if (pdg == vpdg.at(3))
    return 3;
  if (pdg == vpdg.at(4))
    return 4;
  if (pdg == vpdg.at(6))
    return 6;
  if (pdg == vpdg.at(7))
    return 7;
  if (pdg == vpdg.at(8))
    return 8;
  if (pdg == vpdg.at(9))
    return 9;
  return -1;
}

Int_t qaUtility::GetCentralityBin(Float_t b, std::vector<Float_t> vcent)
{
  if (vcent.size() == 0)
    return -1;

  for (int i = 0; i < (int)vcent.size() - 1; i++)
  {
    if (b >= vcent.at(i) && b < vcent.at(i + 1))
      return i;
  }

  return -1;
}

Int_t qaUtility::GetCentMultBin(Int_t mult, std::vector<Float_t> vcent)
{
  if (vcent.size() == 0)
    return -1;

  for (int i = 0; i < (int)vcent.size() - 1; i++)
  {
    if (mult >= vcent.at(i) && mult < vcent.at(i + 1))
      return i;
  }

  return -1;
}
