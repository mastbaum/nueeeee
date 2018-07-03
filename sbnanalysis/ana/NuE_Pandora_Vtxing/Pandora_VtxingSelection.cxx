#include <cassert>
#include <iostream>
#include <vector>
#include <TH2D.h>
#include <json/json.h>
#include "gallery/ValidHandle.h"
#include "canvas/Utilities/InputTag.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCNeutrino.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "Pandora_VtxingTools.h"
#include "Pandora_VtxingSelection.h"


namespace ana {
  namespace NuE_Pandora_Vtxing {

Pandora_VtxingSelection::Pandora_VtxingSelection() : SelectionBase(), fNuCount(0), fEventCounter(0) {}


void Pandora_VtxingSelection::Initialize(Json::Value* config) {
  // Load configuration parameters
  fTruthTag =   { "generator" };
  fFluxTag =    { "generator" };
  fPandoraTag = { "pandoraNu" };
  fFlashTag =   {"simpleFlashBeam"};

  if (config) {
    fTruthTag = { (*config)["NuE_Pandora_Vtxing"].get("MCTruthTag", fTruthTag.label()).asString() };
    fFluxTag = { (*config)["NuE_Pandora_Vtxing"].get("MCFluxTag", fFluxTag.label()).asString() };
    fPandoraTag = { (*config)["NuE_Pandora_Vtxing"].get("PandoraTag", fPandoraTag.label()).asString() };
  }

  // Add custom branches
  AddBranch("isAV", &fAV);
  AddBranch("nucount", &fNuCount);
  AddBranch("nuCC", &fnuCC);
  AddBranch("nuPdg", &fnuPdg);
  AddBranch("Enu", &fEnu); // GeV
  AddBranch("Elep", &fElep); // GeV
  AddBranch("pMult", &fpMult);
  AddBranch("LpE", &fLpE); // GeV
  AddBranch("piMult", &fpiMult);
  //  AddBranch("nuParPdg", &fnuParPdg);

  AddBranch("pType", &fptype);
  AddBranch("intMode", &fintMode);

  AddBranch("mc_vtx_x", &fmc_vtx_x);
  AddBranch("mc_vtx_y", &fmc_vtx_y);
  AddBranch("mc_vtx_z", &fmc_vtx_z);

  AddBranch("mc_sce_vtx_x", &fmc_sce_vtx_x);
  AddBranch("mc_sce_vtx_y", &fmc_sce_vtx_y);
  AddBranch("mc_sce_vtx_z", &fmc_sce_vtx_z);
 
  AddBranch("min_vtx_z", &fmin_vtx_x);
  AddBranch("min_vtx_z", &fmin_vtx_y);
  AddBranch("min_vtx_z", &fmin_vtx_z);

  AddBranch("min_dist", &fmin_dist);

  AddBranch("beam_flash_T", &fbeam_flash_T);
  AddBranch("beam_flash_absT", &fbeam_flash_absT);
  AddBranch("beam_flash_onbeamT", &fbeam_flash_onbeamT);

}


void Pandora_VtxingSelection::Finalize() {
  fOutputFile->cd();
}


bool Pandora_VtxingSelection::ProcessEvent(gallery::Event& ev) {
  if (fEventCounter % 10 == 0) {
    std::cout << "Pandora_VtxingSelection: Processing event " << fEventCounter << std::endl;
  }
  fEventCounter++;
 
  // Grab a data product from the event
  auto const& mctruths = *ev.getValidHandle<std::vector<simb::MCTruth> >(fTruthTag);
  auto const& mcfluxs = *ev.getValidHandle<std::vector<simb::MCFlux> >(fFluxTag);
  auto const& vtxs = *ev.getValidHandle<std::vector<recob::Vertex> >(fPandoraTag);
  auto const& flashs = *ev.getValidHandle<std::vector<recob::OpFlash> >(fFlashTag);


  // Fill in the custom branches
  fNuCount = mctruths.size();  // Number of neutrinos in this event
 
  if (fNuCount > 1) {
    return false;
  }

  assert(mctruths.size() == mcfluxs.size());

  // Iterate through the neutrinos
  for (size_t i=0; i<mctruths.size(); i++) {
    auto const& mctruth = mctruths.at(i);
    auto const& mcnu    = mctruth.GetNeutrino(); //!< this is the MCNu
    auto const& nu      = mctruth.GetNeutrino().Nu(); //!< this is the MCParitcle
    auto const& lep     = mctruth.GetNeutrino().Lepton(); //!< this is the MCParitcle
    auto const& mcflux  = mcfluxs.at(i);

    fintMode = mctruth.GetNeutrino().Mode();
    fptype = mcflux.fptype;
    
    fAV = isAV(nu.EndX(),nu.EndY(),nu.EndZ());

    // Fill neutrino vertex positions
    fnuCC  = abs( mcnu.CCNC() -1);
    fnuPdg = nu.PdgCode();
    fEnu   = nu.E();
    fElep  = lep.E();
    std::cout << "Enu : " << fEnu << std::endl;  
    fmc_vtx_x = nu.EndX(); //cm
    fmc_vtx_y = nu.EndY(); //cm
    fmc_vtx_z = nu.EndZ(); //cm
  
    std::vector<double> SoSs = SCE.GetPosOffsets(fmc_vtx_x,fmc_vtx_y,fmc_vtx_z);

    fmc_sce_vtx_x = nu.EndX()-SoSs.at(0); //cm
    fmc_sce_vtx_y = nu.EndY()+SoSs.at(1); //cm
    fmc_sce_vtx_z = nu.EndZ()+SoSs.at(2); //cm
    
    //Iterate through all the particles
    fLpE = 0;
    fpMult = 0;
    fpiMult = 0;
    for(int j=0; j<mctruth.NParticles(); j++){
      auto const& part = mctruth.GetParticle(j);
      //protons
      if(part.E() > 0.03 && part.PdgCode() == 2212){
	fpMult++;
	if(part.E() > fLpE) fLpE = part.E(); 
      }
      //pions
      if(abs(part.PdgCode()) == 211){
	fpiMult++;
      }
    }

  }
  
  std::vector<double> vtx_mc = {fmc_sce_vtx_x, fmc_sce_vtx_y, fmc_sce_vtx_z}; //cm
  
  // Iterate through the neutrinos
  //    >> Aim to find the one that's closest for now
  
  fmin_dist = 10000.; //cm

  std::cout << "mc v x : " << fmc_sce_vtx_x << std::endl;

  std::cout << "# verts " << vtxs.size() << std::endl;

  for (size_t i=0; i<vtxs.size(); i++) {
    
    recob::Vertex vtx = vtxs.at(i);
    
    //FIXME: Add dist to mc calc 
    
    double va[3];
    vtx.XYZ(va);
    TVector3 v(va);

    std::cout << "reco v " << i << " x :  "<< v.x() << " y : " << v.y() << " z : " << v.z() << std::endl;

    std::vector<double> vtx_r = {v.x(), v.y(), v.z()};

    double dist = Dist(vtx_mc,vtx_r);

    std::cout << "dist " << dist << std::endl; 

    if(dist < fmin_dist && dist != 0){
      fmin_vtx_x = v.x();
      fmin_vtx_y = v.y();
      fmin_vtx_z = v.z();
      fmin_dist  = dist;    
    }       
  }

  for (size_t i=0; i<flashs.size(); i++){

    recob::OpFlash f = flashs.at(i);

    fbeam_flash_T       = f.Time();
    fbeam_flash_absT    = f.AbsTime();
    fbeam_flash_onbeamT = f.OnBeamTime();

    }

  
  return true;
}

  }  // namespace NuE_Pandora_Vtxing
}  // namespace ana


// This line must be included for all selections!
DECLARE_SBN_PROCESSOR(ana::NuE_Pandora_Vtxing::Pandora_VtxingSelection)

