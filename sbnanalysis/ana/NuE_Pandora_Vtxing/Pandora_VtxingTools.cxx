#include <iostream>
#include <vector>
#include <cmath>

namespace ana {
  namespace NuE_Pandora_Vtxing {

    // Active Volume Check
    bool isAV(double x, double y, double z){

      const double x_boundary1 = 0;
      const double x_boundary2 = 256.35;
      const double y_boundary1 = -116.5;
      const double y_boundary2 = 116.5;
      const double z_boundary1 = 0;
      const double z_boundary2 = 1036.8;
      
      if(x > x_boundary1 &&
	 x < x_boundary2 &&
	 y > y_boundary1 &&
	 y < y_boundary2 &&
	 z > z_boundary1 &&
	 z < z_boundary2)
	{
	  return true;
	}
      return false;
           
    } // Active Volume Check

    // Vtx Distance Calculator 
    double Dist(std::vector< double > mc, std::vector< double > reco){
      double dx = mc.at(0)-reco.at(0);
      double dy = mc.at(1)-reco.at(1);
      double dz = mc.at(2)-reco.at(2);
      
      return sqrt(dx*dx+dy*dy+dz*dz);

    }
  }  // namespace Pandora_Vtxing
}  // namespace ana

