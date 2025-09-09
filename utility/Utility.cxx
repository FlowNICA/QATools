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
                         Cut_refmult_Particle_isCharged(1),
                         Cut_v1_Event_bmin(0.),
                         Cut_v1_Event_bmax(16.),
                         sCut_v1_Event_bCent(""),
                         sCut_v1_Event_mCent(""),
                         Cut_v1_Event_bCent({}),
                         Cut_v1_Event_mCent({}),
                         Cut_v1_Particle_ptmin(1.0),
                         Cut_v1_Particle_ptmax(1.5),
                         Cut_v1_Particle_etamin(-100.),
                         Cut_v1_Particle_etamax(100.),
                         Cut_v1_Particle_ymin(-0.25),
                         Cut_v1_Particle_ymax(-0.15),
                         Cut_v1_Particle_ptmin_pi(0.0),
                         Cut_v1_Particle_ptmax_pi(0.5),
                         Cut_v1_Particle_ymin_pi(-0.25),
                         Cut_v1_Particle_ymax_pi(-0.15),
                         Cut_v1_Particle_ptmin_ka(0.2),
                         Cut_v1_Particle_ptmax_ka(0.9),
                         Cut_v1_Particle_ymin_ka(-0.25),
                         Cut_v1_Particle_ymax_ka(-0.15),
                         Cut_v1_Particle_ptmin_pr(1.0),
                         Cut_v1_Particle_ptmax_pr(1.5),
                         Cut_v1_Particle_ymin_pr(-0.25),
                         Cut_v1_Particle_ymax_pr(-0.15),
                         Cut_v1_Particle_ptmin_ne(1.0),
                         Cut_v1_Particle_ptmax_ne(1.5),
                         Cut_v1_Particle_ymin_ne(-0.25),
                         Cut_v1_Particle_ymax_ne(-0.15),
                         Cut_v2_Event_bmin(0.),
                         Cut_v2_Event_bmax(16.),
                         sCut_v2_Event_bCent(""),
                         sCut_v2_Event_mCent(""),
                         Cut_v2_Event_bCent({}),
                         Cut_v2_Event_mCent({}),
                         Cut_v2_Particle_ptmin(1.0),
                         Cut_v2_Particle_ptmax(1.5),
                         Cut_v2_Particle_etamin(-100.),
                         Cut_v2_Particle_etamax(100.),
                         Cut_v2_Particle_ymin(-0.05),
                         Cut_v2_Particle_ymax(0.05),
                         Cut_v2_Particle_ptmin_pi(0.0),
                         Cut_v2_Particle_ptmax_pi(0.5),
                         Cut_v2_Particle_ymin_pi(-0.05),
                         Cut_v2_Particle_ymax_pi(0.05),
                         Cut_v2_Particle_ptmin_ka(0.2),
                         Cut_v2_Particle_ptmax_ka(0.9),
                         Cut_v2_Particle_ymin_ka(-0.05),
                         Cut_v2_Particle_ymax_ka(0.05),
                         Cut_v2_Particle_ptmin_pr(1.0),
                         Cut_v2_Particle_ptmax_pr(1.5),
                         Cut_v2_Particle_ymin_pr(-0.05),
                         Cut_v2_Particle_ymax_pr(0.05),
                         Cut_v2_Particle_ptmin_ne(1.0),
                         Cut_v2_Particle_ptmax_ne(1.5),
                         Cut_v2_Particle_ymin_ne(-0.05),
                         Cut_v2_Particle_ymax_ne(0.05),
                         Cut_v3_Event_bmin(0.),
                         Cut_v3_Event_bmax(16.),
                         sCut_v3_Event_bCent(""),
                         sCut_v3_Event_mCent(""),
                         Cut_v3_Event_bCent({}),
                         Cut_v3_Event_mCent({}),
                         Cut_v3_Particle_ptmin(1.0),
                         Cut_v3_Particle_ptmax(1.5),
                         Cut_v3_Particle_etamin(-100.),
                         Cut_v3_Particle_etamax(100.),
                         Cut_v3_Particle_ymin(-0.05),
                         Cut_v3_Particle_ymax(0.05),
                         Cut_v3_Particle_ptmin_pi(0.0),
                         Cut_v3_Particle_ptmax_pi(0.5),
                         Cut_v3_Particle_ymin_pi(-0.05),
                         Cut_v3_Particle_ymax_pi(0.05),
                         Cut_v3_Particle_ptmin_ka(0.2),
                         Cut_v3_Particle_ptmax_ka(0.9),
                         Cut_v3_Particle_ymin_ka(-0.05),
                         Cut_v3_Particle_ymax_ka(0.05),
                         Cut_v3_Particle_ptmin_pr(1.0),
                         Cut_v3_Particle_ptmax_pr(1.5),
                         Cut_v3_Particle_ymin_pr(-0.05),
                         Cut_v3_Particle_ymax_pr(0.05),
                         Cut_v3_Particle_ptmin_ne(1.0),
                         Cut_v3_Particle_ptmax_ne(1.5),
                         Cut_v3_Particle_ymin_ne(-0.05),
                         Cut_v3_Particle_ymax_ne(0.05),
                         Cut_v4_Event_bmin(0.),
                         Cut_v4_Event_bmax(16.),
                         sCut_v4_Event_bCent(""),
                         sCut_v4_Event_mCent(""),
                         Cut_v4_Event_bCent({}),
                         Cut_v4_Event_mCent({}),
                         Cut_v4_Particle_ptmin(1.0),
                         Cut_v4_Particle_ptmax(1.5),
                         Cut_v4_Particle_etamin(-100.),
                         Cut_v4_Particle_etamax(100.),
                         Cut_v4_Particle_ymin(-0.05),
                         Cut_v4_Particle_ymax(0.05),
                         Cut_v4_Particle_ptmin_pi(0.0),
                         Cut_v4_Particle_ptmax_pi(0.5),
                         Cut_v4_Particle_ymin_pi(-0.05),
                         Cut_v4_Particle_ymax_pi(0.05),
                         Cut_v4_Particle_ptmin_ka(0.2),
                         Cut_v4_Particle_ptmax_ka(0.9),
                         Cut_v4_Particle_ymin_ka(-0.05),
                         Cut_v4_Particle_ymax_ka(0.05),
                         Cut_v4_Particle_ptmin_pr(1.0),
                         Cut_v4_Particle_ptmax_pr(1.5),
                         Cut_v4_Particle_ymin_pr(-0.05),
                         Cut_v4_Particle_ymax_pr(0.05),
                         Cut_v4_Particle_ptmin_ne(1.0),
                         Cut_v4_Particle_ptmax_ne(1.5),
                         Cut_v4_Particle_ymin_ne(-0.05),
                         Cut_v4_Particle_ymax_ne(0.05)
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
  Cut_v1_Event_bmin = env.GetValue("Cut_v1_Event_bmin", 0.);
  Cut_v1_Event_bmax = env.GetValue("Cut_v1_Event_bmax", 0.);
  sCut_v1_Event_bCent = env.GetValue("Cut_v1_Event_bCent", "");
  sCut_v1_Event_mCent = env.GetValue("Cut_v1_Event_mCent", "");

  Cut_v1_Particle_ptmin = env.GetValue("Cut_v1_Particle_ptmin", 0.);
  Cut_v1_Particle_ptmax = env.GetValue("Cut_v1_Particle_ptmax", 0.);
  Cut_v1_Particle_etamin = env.GetValue("Cut_v1_Particle_etamin", 0.);
  Cut_v1_Particle_etamax = env.GetValue("Cut_v1_Particle_etamax", 0.);
  Cut_v1_Particle_ymin = env.GetValue("Cut_v1_Particle_ymin", 0.);
  Cut_v1_Particle_ymax = env.GetValue("Cut_v1_Particle_ymax", 0.);
  Cut_v1_Particle_ptmin_pi = env.GetValue("Cut_v1_Particle_ptmin_pi", 0.);
  Cut_v1_Particle_ptmax_pi = env.GetValue("Cut_v1_Particle_ptmax_pi", 0.);
  Cut_v1_Particle_ymin_pi = env.GetValue("Cut_v1_Particle_ymin_pi", 0.);
  Cut_v1_Particle_ymax_pi = env.GetValue("Cut_v1_Particle_ymax_pi", 0.);
  Cut_v1_Particle_ptmin_ka = env.GetValue("Cut_v1_Particle_ptmin_ka", 0.);
  Cut_v1_Particle_ptmax_ka = env.GetValue("Cut_v1_Particle_ptmax_ka", 0.);
  Cut_v1_Particle_ymin_ka = env.GetValue("Cut_v1_Particle_ymin_ka", 0.);
  Cut_v1_Particle_ymax_ka = env.GetValue("Cut_v1_Particle_ymax_ka", 0.);
  Cut_v1_Particle_ptmin_pr = env.GetValue("Cut_v1_Particle_ptmin_pr", 0.);
  Cut_v1_Particle_ptmax_pr = env.GetValue("Cut_v1_Particle_ptmax_pr", 0.);
  Cut_v1_Particle_ymin_pr = env.GetValue("Cut_v1_Particle_ymin_pr", 0.);
  Cut_v1_Particle_ymax_pr = env.GetValue("Cut_v1_Particle_ymax_pr", 0.);
  Cut_v1_Particle_ptmin_ne = env.GetValue("Cut_v1_Particle_ptmin_ne", 0.);
  Cut_v1_Particle_ptmax_ne = env.GetValue("Cut_v1_Particle_ptmax_ne", 0.);
  Cut_v1_Particle_ymin_ne = env.GetValue("Cut_v1_Particle_ymin_ne", 0.);
  Cut_v1_Particle_ymax_ne = env.GetValue("Cut_v1_Particle_ymax_ne", 0.);

  Is_v2 = env.GetValue("Is_v2", 0);
  Cut_v2_Event_bmin = env.GetValue("Cut_v2_Event_bmin", 0.);
  Cut_v2_Event_bmax = env.GetValue("Cut_v2_Event_bmax", 0.);
  sCut_v2_Event_bCent = env.GetValue("Cut_v2_Event_bCent", "");
  sCut_v2_Event_mCent = env.GetValue("Cut_v2_Event_mCent", "");

  Cut_v2_Particle_ptmin = env.GetValue("Cut_v2_Particle_ptmin", 0.);
  Cut_v2_Particle_ptmax = env.GetValue("Cut_v2_Particle_ptmax", 0.);
  Cut_v2_Particle_etamin = env.GetValue("Cut_v2_Particle_etamin", 0.);
  Cut_v2_Particle_etamax = env.GetValue("Cut_v2_Particle_etamax", 0.);
  Cut_v2_Particle_ymin = env.GetValue("Cut_v2_Particle_ymin", 0.);
  Cut_v2_Particle_ymax = env.GetValue("Cut_v2_Particle_ymax", 0.);
  Cut_v2_Particle_ptmin_pi = env.GetValue("Cut_v2_Particle_ptmin_pi", 0.);
  Cut_v2_Particle_ptmax_pi = env.GetValue("Cut_v2_Particle_ptmax_pi", 0.);
  Cut_v2_Particle_ymin_pi = env.GetValue("Cut_v2_Particle_ymin_pi", 0.);
  Cut_v2_Particle_ymax_pi = env.GetValue("Cut_v2_Particle_ymax_pi", 0.);
  Cut_v2_Particle_ptmin_ka = env.GetValue("Cut_v2_Particle_ptmin_ka", 0.);
  Cut_v2_Particle_ptmax_ka = env.GetValue("Cut_v2_Particle_ptmax_ka", 0.);
  Cut_v2_Particle_ymin_ka = env.GetValue("Cut_v2_Particle_ymin_ka", 0.);
  Cut_v2_Particle_ymax_ka = env.GetValue("Cut_v2_Particle_ymax_ka", 0.);
  Cut_v2_Particle_ptmin_pr = env.GetValue("Cut_v2_Particle_ptmin_pr", 0.);
  Cut_v2_Particle_ptmax_pr = env.GetValue("Cut_v2_Particle_ptmax_pr", 0.);
  Cut_v2_Particle_ymin_pr = env.GetValue("Cut_v2_Particle_ymin_pr", 0.);
  Cut_v2_Particle_ymax_pr = env.GetValue("Cut_v2_Particle_ymax_pr", 0.);
  Cut_v2_Particle_ptmin_ne = env.GetValue("Cut_v2_Particle_ptmin_ne", 0.);
  Cut_v2_Particle_ptmax_ne = env.GetValue("Cut_v2_Particle_ptmax_ne", 0.);
  Cut_v2_Particle_ymin_ne = env.GetValue("Cut_v2_Particle_ymin_ne", 0.);
  Cut_v2_Particle_ymax_ne = env.GetValue("Cut_v2_Particle_ymax_ne", 0.);

  Is_v3 = env.GetValue("Is_v3", 0);
  Cut_v3_Event_bmin = env.GetValue("Cut_v3_Event_bmin", 0.);
  Cut_v3_Event_bmax = env.GetValue("Cut_v3_Event_bmax", 0.);
  sCut_v3_Event_bCent = env.GetValue("Cut_v3_Event_bCent", "");
  sCut_v3_Event_mCent = env.GetValue("Cut_v3_Event_mCent", "");

  Cut_v3_Particle_ptmin = env.GetValue("Cut_v3_Particle_ptmin", 0.);
  Cut_v3_Particle_ptmax = env.GetValue("Cut_v3_Particle_ptmax", 0.);
  Cut_v3_Particle_etamin = env.GetValue("Cut_v3_Particle_etamin", 0.);
  Cut_v3_Particle_etamax = env.GetValue("Cut_v3_Particle_etamax", 0.);
  Cut_v3_Particle_ymin = env.GetValue("Cut_v3_Particle_ymin", 0.);
  Cut_v3_Particle_ymax = env.GetValue("Cut_v3_Particle_ymax", 0.);
  Cut_v3_Particle_ptmin_pi = env.GetValue("Cut_v3_Particle_ptmin_pi", 0.);
  Cut_v3_Particle_ptmax_pi = env.GetValue("Cut_v3_Particle_ptmax_pi", 0.);
  Cut_v3_Particle_ymin_pi = env.GetValue("Cut_v3_Particle_ymin_pi", 0.);
  Cut_v3_Particle_ymax_pi = env.GetValue("Cut_v3_Particle_ymax_pi", 0.);
  Cut_v3_Particle_ptmin_ka = env.GetValue("Cut_v3_Particle_ptmin_ka", 0.);
  Cut_v3_Particle_ptmax_ka = env.GetValue("Cut_v3_Particle_ptmax_ka", 0.);
  Cut_v3_Particle_ymin_ka = env.GetValue("Cut_v3_Particle_ymin_ka", 0.);
  Cut_v3_Particle_ymax_ka = env.GetValue("Cut_v3_Particle_ymax_ka", 0.);
  Cut_v3_Particle_ptmin_pr = env.GetValue("Cut_v3_Particle_ptmin_pr", 0.);
  Cut_v3_Particle_ptmax_pr = env.GetValue("Cut_v3_Particle_ptmax_pr", 0.);
  Cut_v3_Particle_ymin_pr = env.GetValue("Cut_v3_Particle_ymin_pr", 0.);
  Cut_v3_Particle_ymax_pr = env.GetValue("Cut_v3_Particle_ymax_pr", 0.);
  Cut_v3_Particle_ptmin_ne = env.GetValue("Cut_v3_Particle_ptmin_ne", 0.);
  Cut_v3_Particle_ptmax_ne = env.GetValue("Cut_v3_Particle_ptmax_ne", 0.);
  Cut_v3_Particle_ymin_ne = env.GetValue("Cut_v3_Particle_ymin_ne", 0.);
  Cut_v3_Particle_ymax_ne = env.GetValue("Cut_v3_Particle_ymax_ne", 0.);

  Is_v4 = env.GetValue("Is_v4", 0);
  Cut_v4_Event_bmin = env.GetValue("Cut_v4_Event_bmin", 0.);
  Cut_v4_Event_bmax = env.GetValue("Cut_v4_Event_bmax", 0.);
  sCut_v4_Event_bCent = env.GetValue("Cut_v4_Event_bCent", "");
  sCut_v4_Event_mCent = env.GetValue("Cut_v4_Event_mCent", "");

  Cut_v4_Particle_ptmin = env.GetValue("Cut_v4_Particle_ptmin", 0.);
  Cut_v4_Particle_ptmax = env.GetValue("Cut_v4_Particle_ptmax", 0.);
  Cut_v4_Particle_etamin = env.GetValue("Cut_v4_Particle_etamin", 0.);
  Cut_v4_Particle_etamax = env.GetValue("Cut_v4_Particle_etamax", 0.);
  Cut_v4_Particle_ymin = env.GetValue("Cut_v4_Particle_ymin", 0.);
  Cut_v4_Particle_ymax = env.GetValue("Cut_v4_Particle_ymax", 0.);
  Cut_v4_Particle_ptmin_pi = env.GetValue("Cut_v4_Particle_ptmin_pi", 0.);
  Cut_v4_Particle_ptmax_pi = env.GetValue("Cut_v4_Particle_ptmax_pi", 0.);
  Cut_v4_Particle_ymin_pi = env.GetValue("Cut_v4_Particle_ymin_pi", 0.);
  Cut_v4_Particle_ymax_pi = env.GetValue("Cut_v4_Particle_ymax_pi", 0.);
  Cut_v4_Particle_ptmin_ka = env.GetValue("Cut_v4_Particle_ptmin_ka", 0.);
  Cut_v4_Particle_ptmax_ka = env.GetValue("Cut_v4_Particle_ptmax_ka", 0.);
  Cut_v4_Particle_ymin_ka = env.GetValue("Cut_v4_Particle_ymin_ka", 0.);
  Cut_v4_Particle_ymax_ka = env.GetValue("Cut_v4_Particle_ymax_ka", 0.);
  Cut_v4_Particle_ptmin_pr = env.GetValue("Cut_v4_Particle_ptmin_pr", 0.);
  Cut_v4_Particle_ptmax_pr = env.GetValue("Cut_v4_Particle_ptmax_pr", 0.);
  Cut_v4_Particle_ymin_pr = env.GetValue("Cut_v4_Particle_ymin_pr", 0.);
  Cut_v4_Particle_ymax_pr = env.GetValue("Cut_v4_Particle_ymax_pr", 0.);
  Cut_v4_Particle_ptmin_ne = env.GetValue("Cut_v4_Particle_ptmin_ne", 0.);
  Cut_v4_Particle_ptmax_ne = env.GetValue("Cut_v4_Particle_ptmax_ne", 0.);
  Cut_v4_Particle_ymin_ne = env.GetValue("Cut_v4_Particle_ymin_ne", 0.);
  Cut_v4_Particle_ymax_ne = env.GetValue("Cut_v4_Particle_ymax_ne", 0.);

  if (!initCentrality())
    return false;

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

Bool_t qaUtility::initCentrality()
{
  Cut_v1_Event_bCent = ParseVector(sCut_v1_Event_bCent);
  Cut_v2_Event_bCent = ParseVector(sCut_v2_Event_bCent);
  Cut_v3_Event_bCent = ParseVector(sCut_v3_Event_bCent);
  Cut_v4_Event_bCent = ParseVector(sCut_v4_Event_bCent);

  Cut_v1_Event_mCent = ParseVector(sCut_v1_Event_mCent);
  Cut_v2_Event_mCent = ParseVector(sCut_v2_Event_mCent);
  Cut_v3_Event_mCent = ParseVector(sCut_v3_Event_mCent);
  Cut_v4_Event_mCent = ParseVector(sCut_v4_Event_mCent);

  if (Cut_v1_Event_bCent.size() == 0 ||
      Cut_v2_Event_bCent.size() == 0 ||
      Cut_v3_Event_bCent.size() == 0 ||
      Cut_v4_Event_bCent.size() == 0 ||
      Cut_v1_Event_mCent.size() == 0 ||
      Cut_v2_Event_mCent.size() == 0 ||
      Cut_v3_Event_mCent.size() == 0 ||
      Cut_v4_Event_mCent.size() == 0)

  {
    return false;
  }

  return true;
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

Bool_t qaUtility::Cut_Event_v1(qaEvent *const &event)
{
  if (event->GetB() < Cut_v1_Event_bmin)
    return false;
  if (event->GetB() > Cut_v1_Event_bmax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Event_v2(qaEvent *const &event)
{
  if (event->GetB() < Cut_v2_Event_bmin)
    return false;
  if (event->GetB() > Cut_v2_Event_bmax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Event_v3(qaEvent *const &event)
{
  if (event->GetB() < Cut_v3_Event_bmin)
    return false;
  if (event->GetB() > Cut_v3_Event_bmax)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Event_v4(qaEvent *const &event)
{
  if (event->GetB() < Cut_v4_Event_bmin)
    return false;
  if (event->GetB() > Cut_v4_Event_bmax)
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

Bool_t qaUtility::Cut_Particle_v1_acceptance(qaParticle *const &particle)
{
  if (particle->GetEta() < Cut_v1_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_v1_Particle_etamax)
    return false;
  if (particle->GetPt() < Cut_v1_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_v1_Particle_ptmax)
    return false;

  Double_t charge = GetCharge(particle->GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle->GetPdg()) != 2112)
    return false;

  return true;
}

// Bool_t qaUtility::Cut_Particle_v1_PID_pt(qaParticle *const &particle, Int_t _pid)
// {
//   if (particle->GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 4)
//     return false;

//   // PID related kinematics cut
//   Double_t y = 0.5 * TMath::Log( (particle->GetEnergy() + particle->GetPz())/(particle->GetEnergy() - particle->GetPz()) );
//   if (_pid == 1 && y < Cut_v1_Particle_ymin_pi)
//     return false;
//   if (_pid == 1 && y > Cut_v1_Particle_ymax_pi)
//     return false;
//   if (_pid == 2 && y < Cut_v1_Particle_ymin_ka)
//     return false;
//   if (_pid == 2 && y > Cut_v1_Particle_ymax_ka)
//     return false;
//   if (_pid == 3 && y < Cut_v1_Particle_ymin_pr)
//     return false;
//   if (_pid == 3 && y > Cut_v1_Particle_ymax_pr)
//     return false;
//   if (_pid == 5 && y < Cut_v1_Particle_ymin_pi)
//     return false;
//   if (_pid == 5 && y > Cut_v1_Particle_ymax_pi)
//     return false;
//   if (_pid == 6 && y < Cut_v1_Particle_ymin_ka)
//     return false;
//   if (_pid == 6 && y > Cut_v1_Particle_ymax_ka)
//     return false;
//   if (_pid == 7 && y < Cut_v1_Particle_ymin_pr)
//     return false;
//   if (_pid == 7 && y > Cut_v1_Particle_ymax_pr)
//     return false;

//   Double_t charge = GetCharge(particle->GetPdg());
//   if (charge == error_code)
//     return false;
//   if (charge == 0)
//     return false;

//   if (_pid == 0 && charge < 0)
//     return false;
//   if (_pid == 4 && charge > 0)
//     return false;

//   return true;
// }

// Bool_t qaUtility::Cut_Particle_v1_PID_y(qaParticle *const &particle, Int_t _pid)
// {
//   if (particle->GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 4)
//     return false;

//   // PID related kinematics cut
//   if (_pid == 1 && particle->GetPt() < Cut_v1_Particle_ptmin_pi)
//     return false;
//   if (_pid == 1 && particle->GetPt() > Cut_v1_Particle_ptmax_pi)
//     return false;
//   if (_pid == 2 && particle->GetPt() < Cut_v1_Particle_ptmin_ka)
//     return false;
//   if (_pid == 2 && particle->GetPt() > Cut_v1_Particle_ptmax_ka)
//     return false;
//   if (_pid == 3 && particle->GetPt() < Cut_v1_Particle_ptmin_pr)
//     return false;
//   if (_pid == 3 && particle->GetPt() > Cut_v1_Particle_ptmax_pr)
//     return false;
//   if (_pid == 5 && particle->GetPt() < Cut_v1_Particle_ptmin_pi)
//     return false;
//   if (_pid == 5 && particle->GetPt() > Cut_v1_Particle_ptmax_pi)
//     return false;
//   if (_pid == 6 && particle->GetPt() < Cut_v1_Particle_ptmin_ka)
//     return false;
//   if (_pid == 6 && particle->GetPt() > Cut_v1_Particle_ptmax_ka)
//     return false;
//   if (_pid == 7 && particle->GetPt() < Cut_v1_Particle_ptmin_pr)
//     return false;
//   if (_pid == 7 && particle->GetPt() > Cut_v1_Particle_ptmax_pr)
//     return false;

//   Double_t charge = GetCharge(particle->GetPdg());
//   if (charge == error_code)
//     return false;
//   if (charge == 0)
//     return false;

//   if (_pid == 0 && charge < 0)
//     return false;
//   if (_pid == 4 && charge > 0)
//     return false;

//   return true;
// }

Bool_t qaUtility::Cut_Particle_v1_PID_pt(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  Double_t y = particle.GetRapidity(); //0.5 * TMath::Log((particle.GetEnergy() + particle.GetPz()) / (particle.GetEnergy() - particle.GetPz()));
  if (_pid == 1 && y < Cut_v1_Particle_ymin_pi)
    return false;
  if (_pid == 1 && y > Cut_v1_Particle_ymax_pi)
    return false;
  if (_pid == 2 && y < Cut_v1_Particle_ymin_ka)
    return false;
  if (_pid == 2 && y > Cut_v1_Particle_ymax_ka)
    return false;
  if (_pid == 3 && y < Cut_v1_Particle_ymin_pr)
    return false;
  if (_pid == 3 && y > Cut_v1_Particle_ymax_pr)
    return false;
  if (_pid == 4 && y < Cut_v1_Particle_ymin_ne)
    return false;
  if (_pid == 4 && y > Cut_v1_Particle_ymax_ne)
    return false;
  if (_pid == 6 && y < Cut_v1_Particle_ymin_pi)
    return false;
  if (_pid == 6 && y > Cut_v1_Particle_ymax_pi)
    return false;
  if (_pid == 7 && y < Cut_v1_Particle_ymin_ka)
    return false;
  if (_pid == 7 && y > Cut_v1_Particle_ymax_ka)
    return false;
  if (_pid == 8 && y < Cut_v1_Particle_ymin_pr)
    return false;
  if (_pid == 8 && y > Cut_v1_Particle_ymax_pr)
    return false;
  if (_pid == 9 && y < Cut_v1_Particle_ymin_ne)
    return false;
  if (_pid == 9 && y > Cut_v1_Particle_ymax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v1_PID_y(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  if (_pid == 1 && particle.GetPt() < Cut_v1_Particle_ptmin_pi)
    return false;
  if (_pid == 1 && particle.GetPt() > Cut_v1_Particle_ptmax_pi)
    return false;
  if (_pid == 2 && particle.GetPt() < Cut_v1_Particle_ptmin_ka)
    return false;
  if (_pid == 2 && particle.GetPt() > Cut_v1_Particle_ptmax_ka)
    return false;
  if (_pid == 3 && particle.GetPt() < Cut_v1_Particle_ptmin_pr)
    return false;
  if (_pid == 3 && particle.GetPt() > Cut_v1_Particle_ptmax_pr)
    return false;
  if (_pid == 4 && particle.GetPt() < Cut_v1_Particle_ptmin_ne)
    return false;
  if (_pid == 4 && particle.GetPt() > Cut_v1_Particle_ptmax_ne)
    return false;
  if (_pid == 6 && particle.GetPt() < Cut_v1_Particle_ptmin_pi)
    return false;
  if (_pid == 6 && particle.GetPt() > Cut_v1_Particle_ptmax_pi)
    return false;
  if (_pid == 7 && particle.GetPt() < Cut_v1_Particle_ptmin_ka)
    return false;
  if (_pid == 7 && particle.GetPt() > Cut_v1_Particle_ptmax_ka)
    return false;
  if (_pid == 8 && particle.GetPt() < Cut_v1_Particle_ptmin_pr)
    return false;
  if (_pid == 8 && particle.GetPt() > Cut_v1_Particle_ptmax_pr)
    return false;
  if (_pid == 9 && particle.GetPt() < Cut_v1_Particle_ptmin_ne)
    return false;
  if (_pid == 9 && particle.GetPt() > Cut_v1_Particle_ptmax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v2_acceptance(qaParticle *const &particle)
{
  if (particle->GetEta() < Cut_v2_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_v2_Particle_etamax)
    return false;
  if (particle->GetPt() < Cut_v2_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_v2_Particle_ptmax)
    return false;

  Double_t charge = GetCharge(particle->GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle->GetPdg()) != 2112)
    return false;

  return true;
}

// Bool_t qaUtility::Cut_Particle_v2_PID_pt(qaParticle *const &particle, Int_t _pid)
// {
//   if (particle->GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 4)
//     return false;

//   // PID related kinematics cut
//   Double_t y = 0.5 * TMath::Log( (particle->GetEnergy() + particle->GetPz())/(particle->GetEnergy() - particle->GetPz()) );
//   if (_pid == 1 && y < Cut_v2_Particle_ymin_pi)
//     return false;
//   if (_pid == 1 && y > Cut_v2_Particle_ymax_pi)
//     return false;
//   if (_pid == 2 && y < Cut_v2_Particle_ymin_ka)
//     return false;
//   if (_pid == 2 && y > Cut_v2_Particle_ymax_ka)
//     return false;
//   if (_pid == 3 && y < Cut_v2_Particle_ymin_pr)
//     return false;
//   if (_pid == 3 && y > Cut_v2_Particle_ymax_pr)
//     return false;
//   if (_pid == 5 && y < Cut_v2_Particle_ymin_pi)
//     return false;
//   if (_pid == 5 && y > Cut_v2_Particle_ymax_pi)
//     return false;
//   if (_pid == 6 && y < Cut_v2_Particle_ymin_ka)
//     return false;
//   if (_pid == 6 && y > Cut_v2_Particle_ymax_ka)
//     return false;
//   if (_pid == 7 && y < Cut_v2_Particle_ymin_pr)
//     return false;
//   if (_pid == 7 && y > Cut_v2_Particle_ymax_pr)
//     return false;

//   Double_t charge = GetCharge(particle->GetPdg());
//   if (charge == error_code)
//     return false;
//   if (charge == 0)
//     return false;

//   if (_pid == 0 && charge < 0)
//     return false;
//   if (_pid == 4 && charge > 0)
//     return false;

//   return true;
// }

// Bool_t qaUtility::Cut_Particle_v2_PID_y(qaParticle *const &particle, Int_t _pid)
// {
//   if (particle->GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 4)
//     return false;

//   // PID related kinematics cut
//   if (_pid == 1 && particle->GetPt() < Cut_v2_Particle_ptmin_pi)
//     return false;
//   if (_pid == 1 && particle->GetPt() > Cut_v2_Particle_ptmax_pi)
//     return false;
//   if (_pid == 2 && particle->GetPt() < Cut_v2_Particle_ptmin_ka)
//     return false;
//   if (_pid == 2 && particle->GetPt() > Cut_v2_Particle_ptmax_ka)
//     return false;
//   if (_pid == 3 && particle->GetPt() < Cut_v2_Particle_ptmin_pr)
//     return false;
//   if (_pid == 3 && particle->GetPt() > Cut_v2_Particle_ptmax_pr)
//     return false;
//   if (_pid == 5 && particle->GetPt() < Cut_v2_Particle_ptmin_pi)
//     return false;
//   if (_pid == 5 && particle->GetPt() > Cut_v2_Particle_ptmax_pi)
//     return false;
//   if (_pid == 6 && particle->GetPt() < Cut_v2_Particle_ptmin_ka)
//     return false;
//   if (_pid == 6 && particle->GetPt() > Cut_v2_Particle_ptmax_ka)
//     return false;
//   if (_pid == 7 && particle->GetPt() < Cut_v2_Particle_ptmin_pr)
//     return false;
//   if (_pid == 7 && particle->GetPt() > Cut_v2_Particle_ptmax_pr)
//     return false;

//   Double_t charge = GetCharge(particle->GetPdg());
//   if (charge == error_code)
//     return false;
//   if (charge == 0)
//     return false;

//   if (_pid == 0 && charge < 0)
//     return false;
//   if (_pid == 4 && charge > 0)
//     return false;

//   return true;
// }

Bool_t qaUtility::Cut_Particle_v2_PID_pt(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  Double_t y = particle.GetRapidity(); //0.5 * TMath::Log((particle.GetEnergy() + particle.GetPz()) / (particle.GetEnergy() - particle.GetPz()));
  if (_pid == 1 && y < Cut_v2_Particle_ymin_pi)
    return false;
  if (_pid == 1 && y > Cut_v2_Particle_ymax_pi)
    return false;
  if (_pid == 2 && y < Cut_v2_Particle_ymin_ka)
    return false;
  if (_pid == 2 && y > Cut_v2_Particle_ymax_ka)
    return false;
  if (_pid == 3 && y < Cut_v2_Particle_ymin_pr)
    return false;
  if (_pid == 3 && y > Cut_v2_Particle_ymax_pr)
    return false;
  if (_pid == 4 && y < Cut_v2_Particle_ymin_ne)
    return false;
  if (_pid == 4 && y > Cut_v2_Particle_ymax_ne)
    return false;
  if (_pid == 6 && y < Cut_v2_Particle_ymin_pi)
    return false;
  if (_pid == 6 && y > Cut_v2_Particle_ymax_pi)
    return false;
  if (_pid == 7 && y < Cut_v2_Particle_ymin_ka)
    return false;
  if (_pid == 7 && y > Cut_v2_Particle_ymax_ka)
    return false;
  if (_pid == 8 && y < Cut_v2_Particle_ymin_pr)
    return false;
  if (_pid == 8 && y > Cut_v2_Particle_ymax_pr)
    return false;
  if (_pid == 9 && y < Cut_v2_Particle_ymin_ne)
    return false;
  if (_pid == 9 && y > Cut_v2_Particle_ymax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v2_PID_y(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  if (_pid == 1 && particle.GetPt() < Cut_v2_Particle_ptmin_pi)
    return false;
  if (_pid == 1 && particle.GetPt() > Cut_v2_Particle_ptmax_pi)
    return false;
  if (_pid == 2 && particle.GetPt() < Cut_v2_Particle_ptmin_ka)
    return false;
  if (_pid == 2 && particle.GetPt() > Cut_v2_Particle_ptmax_ka)
    return false;
  if (_pid == 3 && particle.GetPt() < Cut_v2_Particle_ptmin_pr)
    return false;
  if (_pid == 3 && particle.GetPt() > Cut_v2_Particle_ptmax_pr)
    return false;
  if (_pid == 4 && particle.GetPt() < Cut_v2_Particle_ptmin_ne)
    return false;
  if (_pid == 4 && particle.GetPt() > Cut_v2_Particle_ptmax_ne)
    return false;
  if (_pid == 6 && particle.GetPt() < Cut_v2_Particle_ptmin_pi)
    return false;
  if (_pid == 6 && particle.GetPt() > Cut_v2_Particle_ptmax_pi)
    return false;
  if (_pid == 7 && particle.GetPt() < Cut_v2_Particle_ptmin_ka)
    return false;
  if (_pid == 7 && particle.GetPt() > Cut_v2_Particle_ptmax_ka)
    return false;
  if (_pid == 8 && particle.GetPt() < Cut_v2_Particle_ptmin_pr)
    return false;
  if (_pid == 8 && particle.GetPt() > Cut_v2_Particle_ptmax_pr)
    return false;
  if (_pid == 9 && particle.GetPt() < Cut_v2_Particle_ptmin_ne)
    return false;
  if (_pid == 9 && particle.GetPt() > Cut_v2_Particle_ptmax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v3_acceptance(qaParticle *const &particle)
{
  if (particle->GetEta() < Cut_v3_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_v3_Particle_etamax)
    return false;
  if (particle->GetPt() < Cut_v3_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_v3_Particle_ptmax)
    return false;

  Double_t charge = GetCharge(particle->GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle->GetPdg()) != 2112)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v3_PID_pt(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  Double_t y = particle.GetRapidity(); //0.5 * TMath::Log((particle.GetEnergy() + particle.GetPz()) / (particle.GetEnergy() - particle.GetPz()));
  if (_pid == 1 && y < Cut_v3_Particle_ymin_pi)
    return false;
  if (_pid == 1 && y > Cut_v3_Particle_ymax_pi)
    return false;
  if (_pid == 2 && y < Cut_v3_Particle_ymin_ka)
    return false;
  if (_pid == 2 && y > Cut_v3_Particle_ymax_ka)
    return false;
  if (_pid == 3 && y < Cut_v3_Particle_ymin_pr)
    return false;
  if (_pid == 3 && y > Cut_v3_Particle_ymax_pr)
    return false;
  if (_pid == 4 && y < Cut_v3_Particle_ymin_ne)
    return false;
  if (_pid == 4 && y > Cut_v3_Particle_ymax_ne)
    return false;
  if (_pid == 6 && y < Cut_v3_Particle_ymin_pi)
    return false;
  if (_pid == 6 && y > Cut_v3_Particle_ymax_pi)
    return false;
  if (_pid == 7 && y < Cut_v3_Particle_ymin_ka)
    return false;
  if (_pid == 7 && y > Cut_v3_Particle_ymax_ka)
    return false;
  if (_pid == 8 && y < Cut_v3_Particle_ymin_pr)
    return false;
  if (_pid == 8 && y > Cut_v3_Particle_ymax_pr)
    return false;
  if (_pid == 9 && y < Cut_v3_Particle_ymin_ne)
    return false;
  if (_pid == 9 && y > Cut_v3_Particle_ymax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v3_PID_y(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  if (_pid == 1 && particle.GetPt() < Cut_v3_Particle_ptmin_pi)
    return false;
  if (_pid == 1 && particle.GetPt() > Cut_v3_Particle_ptmax_pi)
    return false;
  if (_pid == 2 && particle.GetPt() < Cut_v3_Particle_ptmin_ka)
    return false;
  if (_pid == 2 && particle.GetPt() > Cut_v3_Particle_ptmax_ka)
    return false;
  if (_pid == 3 && particle.GetPt() < Cut_v3_Particle_ptmin_pr)
    return false;
  if (_pid == 3 && particle.GetPt() > Cut_v3_Particle_ptmax_pr)
    return false;
  if (_pid == 4 && particle.GetPt() < Cut_v3_Particle_ptmin_ne)
    return false;
  if (_pid == 4 && particle.GetPt() > Cut_v3_Particle_ptmax_ne)
    return false;
  if (_pid == 6 && particle.GetPt() < Cut_v3_Particle_ptmin_pi)
    return false;
  if (_pid == 6 && particle.GetPt() > Cut_v3_Particle_ptmax_pi)
    return false;
  if (_pid == 7 && particle.GetPt() < Cut_v3_Particle_ptmin_ka)
    return false;
  if (_pid == 7 && particle.GetPt() > Cut_v3_Particle_ptmax_ka)
    return false;
  if (_pid == 8 && particle.GetPt() < Cut_v3_Particle_ptmin_pr)
    return false;
  if (_pid == 8 && particle.GetPt() > Cut_v3_Particle_ptmax_pr)
    return false;
  if (_pid == 9 && particle.GetPt() < Cut_v3_Particle_ptmin_ne)
    return false;
  if (_pid == 9 && particle.GetPt() > Cut_v3_Particle_ptmax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v4_acceptance(qaParticle *const &particle)
{
  if (particle->GetEta() < Cut_v4_Particle_etamin)
    return false;
  if (particle->GetEta() > Cut_v4_Particle_etamax)
    return false;
  if (particle->GetPt() < Cut_v4_Particle_ptmin)
    return false;
  if (particle->GetPt() > Cut_v4_Particle_ptmax)
    return false;

  Double_t charge = GetCharge(particle->GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle->GetPdg()) != 2112)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v4_PID_pt(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  Double_t y = 0.5 * TMath::Log((particle.GetEnergy() + particle.GetPz()) / (particle.GetEnergy() - particle.GetPz()));
  if (_pid == 1 && y < Cut_v4_Particle_ymin_pi)
    return false;
  if (_pid == 1 && y > Cut_v4_Particle_ymax_pi)
    return false;
  if (_pid == 2 && y < Cut_v4_Particle_ymin_ka)
    return false;
  if (_pid == 2 && y > Cut_v4_Particle_ymax_ka)
    return false;
  if (_pid == 3 && y < Cut_v4_Particle_ymin_pr)
    return false;
  if (_pid == 3 && y > Cut_v4_Particle_ymax_pr)
    return false;
  if (_pid == 4 && y < Cut_v4_Particle_ymin_ne)
    return false;
  if (_pid == 4 && y > Cut_v4_Particle_ymax_ne)
    return false;
  if (_pid == 6 && y < Cut_v4_Particle_ymin_pi)
    return false;
  if (_pid == 6 && y > Cut_v4_Particle_ymax_pi)
    return false;
  if (_pid == 7 && y < Cut_v4_Particle_ymin_ka)
    return false;
  if (_pid == 7 && y > Cut_v4_Particle_ymax_ka)
    return false;
  if (_pid == 8 && y < Cut_v4_Particle_ymin_pr)
    return false;
  if (_pid == 8 && y > Cut_v4_Particle_ymax_pr)
    return false;
  if (_pid == 9 && y < Cut_v4_Particle_ymin_ne)
    return false;
  if (_pid == 9 && y > Cut_v4_Particle_ymax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

  return true;
}

Bool_t qaUtility::Cut_Particle_v4_PID_y(qaParticleLight const &particle, Int_t _pid)
{
  if (_pid == -1)
    return false;
  if (particle.GetPdg() != vpdg.at(_pid) && _pid != 0 && _pid != 5)
    return false;

  // PID related kinematics cut
  if (_pid == 1 && particle.GetPt() < Cut_v4_Particle_ptmin_pi)
    return false;
  if (_pid == 1 && particle.GetPt() > Cut_v4_Particle_ptmax_pi)
    return false;
  if (_pid == 2 && particle.GetPt() < Cut_v4_Particle_ptmin_ka)
    return false;
  if (_pid == 2 && particle.GetPt() > Cut_v4_Particle_ptmax_ka)
    return false;
  if (_pid == 3 && particle.GetPt() < Cut_v4_Particle_ptmin_pr)
    return false;
  if (_pid == 3 && particle.GetPt() > Cut_v4_Particle_ptmax_pr)
    return false;
  if (_pid == 4 && particle.GetPt() < Cut_v4_Particle_ptmin_ne)
    return false;
  if (_pid == 4 && particle.GetPt() > Cut_v4_Particle_ptmax_ne)
    return false;
  if (_pid == 6 && particle.GetPt() < Cut_v4_Particle_ptmin_pi)
    return false;
  if (_pid == 6 && particle.GetPt() > Cut_v4_Particle_ptmax_pi)
    return false;
  if (_pid == 7 && particle.GetPt() < Cut_v4_Particle_ptmin_ka)
    return false;
  if (_pid == 7 && particle.GetPt() > Cut_v4_Particle_ptmax_ka)
    return false;
  if (_pid == 8 && particle.GetPt() < Cut_v4_Particle_ptmin_pr)
    return false;
  if (_pid == 8 && particle.GetPt() > Cut_v4_Particle_ptmax_pr)
    return false;
  if (_pid == 9 && particle.GetPt() < Cut_v4_Particle_ptmin_ne)
    return false;
  if (_pid == 9 && particle.GetPt() > Cut_v4_Particle_ptmax_ne)
    return false;

  Double_t charge = GetCharge(particle.GetPdg());
  if (charge == error_code)
    return false;
  if (charge == 0 && TMath::Abs(particle.GetPdg()) != 2112)
    return false;

  if (_pid == 0 && charge < 0)
    return false;
  if (_pid == 5 && charge > 0)
    return false;

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
