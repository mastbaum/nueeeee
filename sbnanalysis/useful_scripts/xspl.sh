#!/bin/bash

###########################################################
# Submit jobs to calculate cross section splines only
#
# Note: Please adjust the GXML and OUTDIR paths!
#
# Usage:
#
#     $ ./xspl.sh TARGET_PDG CONFIG
#
# Example:
#
#     $ ./xspl.sh 1000180400 LocalFGNievesQEAndMEC
#
# A. Mastbaum <mastbaum@uchicago.edu>, 2017/12/14
###########################################################

# GENIE settings
TGT="${1}"
CONFIG="${2}"
NUPDG="14"
GENERATORS="CCinclMEC"

# File I/O Settings
GXML="/pnfs/uboone/persistent/users/mastbaum/genie_xsec/v2_12_6/NULL/${CONFIG}/data"
OUTDIR="/pnfs/uboone/scratch/users/${USER}/ccpi0Final"

# CC only for EffSFTEM (no MEC)
if [[ "$CONFIG" == *"EffSFTEM"* ]]; then
  GENERATORS="CC"
fi

echo "TARGET: ${TGT}"
echo "CONFIG: ${CONFIG}"
echo "GENERATORS: ${GENERATORS}"

gspl2root \
    -f ${GXMLPATH}/gxspl-FNALsmall.xml -p ${NUPDG} -t ${TGT} \
    --event-generator-list ${GENERATORS} \
    -o gxsectot_${NUPDG}_${TGT}.root

OUT="${OUTDIR}/${CONFIG}_${GENERATORS}_${TGT}"
mkdir -p ${OUT}
mv gxsectot_${NUPDG}_${TGT}.root ${OUT}

