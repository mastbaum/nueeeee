#ifndef __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingSelection__
#define __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingSelection__

/**
 * \file Pandora_VtxingSelection.h
 *
 * This module is intended to mimic the SBN Proposal selection
 *
 * This is intended to perform:
 *  - nue selection
 *      > Based on smeared energy 
 *  - numu selection
 *      > Based on smeared muon energy
 *
 * Author: J. Zennamo <jaz8600@fnal.gov>
 */

// Includes
#include <iostream>
#include "canvas/Utilities/InputTag.h"
#include "core/SelectionBase.hh"
#include "SpaceChargeMicroBooNE.h"

// Forward declarations
class TH2D;
class TTree;

/** All analysis code is defined in namespace "ana" */
namespace ana {

  /** Code specific to the NuE_Pandora_Vtxing. */
  namespace NuE_Pandora_Vtxing {

/**
 * \class Pandora_VtxingSelection
 * \brief An example selection analysis
 *
 * This selection analysis doesn't actually select events, it just
 * demonstrates the framework!
 */
class Pandora_VtxingSelection : public core::SelectionBase {
public:
  /** Constructor. */
  Pandora_VtxingSelection();

  /**
   * Initialization.
   *
   * Here we load configuration parameters, set up histograms for output, and
   * add our own branches to the output tree.
   *
   * \param config A configuration, as a JSON object
   */
  void Initialize(Json::Value* config=NULL);

  /** Finalize and write objects to the output file. */
  void Finalize();

  /**
   * Process one event.
   *
   * \param ev A single event, as a gallery::Event
   * \return True to keep event
   */
  bool ProcessEvent(gallery::Event& ev);

  SpaceChargeMicroBooNE SCE;

protected:
  unsigned fEventCounter;  //!< Count processed events

  /** Configuration parameters */
  art::InputTag fTruthTag;  //!< art tag for MCTruth information
  art::InputTag fPandoraTag;  //!< art tag for MCTruth information

  /** Custom data branches */
  int fNuCount;  //!< Number of neutrino interactions in the event
  int fnuCC;
  int fAV;
  int fnuPdg;
  double fEnu;
  double fElep;
  int fpMult;
  double fLpE;
  int fpiMult;
  double fmc_vtx_x;
  double fmc_vtx_y;
  double fmc_vtx_z;

  double fmc_sce_vtx_x;
  double fmc_sce_vtx_y;
  double fmc_sce_vtx_z;

  double fmin_vtx_x;
  double fmin_vtx_y;
  double fmin_vtx_z;
  double fmin_dist;

  /** Histograms */


};

  }  // namespace NuE_Pandora_Vtxing
}  // namespace ana

#endif  // __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingSelection__

