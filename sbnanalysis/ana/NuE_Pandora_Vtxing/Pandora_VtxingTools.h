#ifndef __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingTools__
#define __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingTools__

/**
 * \file Pandora_VtxingTools.h
 *
 * Pandora_Vtxing library code.
 * 
 * 
 * 
 * 
 * 
 * Authors: J. Zennamo <jaz8600@fnal.gov>, (you!)
 */

namespace ana {
  namespace NuE_Pandora_Vtxing {

    bool isAV(double x, double y, double z);
    double Dist(std::vector< double > mc, std::vector< double > reco);

  }  // namespace NuE_Pandora_Vtxing
}  // namespace ana

#endif  // __sbnanalysis_ana_NuE_Pandora_Vtxing_Pandora_VtxingTools__

