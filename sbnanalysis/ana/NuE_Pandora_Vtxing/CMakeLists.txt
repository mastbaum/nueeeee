# Define the subproject name
project(NuE_Pandora_Vtxing)

# Directories where includes are found (in addition to those defined in the
# parent CMakeLists.txt, one directory up).
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Declare libraries to build
# Note that the library names (the first argument) should follow the convention
# "sbnanalysis_ThisAnalysis_LibraryName)". Libraries can be built from multiple
# source files.
add_library(sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingTools SHARED Pandora_VtxingTools.cxx)
add_library(sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingSelection SHARED Pandora_VtxingSelection.cxx)
add_library(sbnanalysis_NuE_Pandora_Vtxing_SpaceChargeMicroBooNE SHARED SpaceChargeMicroBooNE.C)
# Define library linking
target_link_libraries(sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingSelection sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingTools)
target_link_libraries(sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingSelection sbnanalysis_NuE_Pandora_Vtxing_SpaceChargeMicroBooNE)

# Install all libraries to the main "lib" directory
install(TARGETS sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingTools DESTINATION lib)
install(TARGETS sbnanalysis_NuE_Pandora_Vtxing_Pandora_VtxingSelection DESTINATION lib)
install(TARGETS sbnanalysis_NuE_Pandora_Vtxing_SpaceChargeMicroBooNE DESTINATION lib)

