#ifdef __CINT__

#pragma link off all global;
#pragma link off all classes;
#pragma link off all functions;
//#pragma link off all extern;

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class qaParticle+;
#pragma link C++ class qaParticleLight+;
#pragma link C++ class qaEvent+;
#pragma link C++ class qaReader_smash_root+;
#pragma link C++ class qaReader_epos4_root+;
#pragma link C++ class qaReader_mcpico+;
#ifdef _MCINI_
#pragma link C++ class qaReader_mcini+;
#endif
#ifdef _PHQMD_
#pragma link C++ class qaReader_phqmd+;
#endif
#ifdef _HSD_ROOT_
#pragma link C++ class qaReader_hsd_root+;
#endif
#pragma link C++ class qaReader_manager+;
#pragma link C++ class qaUtility+;

#endif
