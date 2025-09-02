#!/bin/bash

#
#SBATCH -D /lustre/stor2/mephi/parfenov/TMP/
#SBATCH -J QAToolsRun
#SBATCH --mem-per-cpu=2G
#SBATCH -p cascade
#SBATCH --time=10:30:00
#SBATCH -a 1-1
#
#SBATCH -o /lustre/stor2/mephi/parfenov/TMP/slurm_qatools_%A_%a.out
#SBATCH -e /lustre/stor2/mephi/parfenov/TMP/slurm_qatools_%A_%a.out
#

ls /cvmfs/nica.jinr.ru/
sleep 5

source /cvmfs/nica.jinr.ru/sw/os/login.sh latest
module add mpddev/v24.12.24-1
#export MPDROOT=/lustre/home/user/p/parfenov/Soft/mpdroot/install
#source /lustre/home/user/p/parfenov/Soft/mpdroot/install/config/env.sh

export JOB_ID=${SLURM_ARRAY_JOB_ID}
export TASK_ID=${SLURM_ARRAY_TASK_ID}

# Directories
export QAFILE=/lustre/home/user/p/parfenov/Soft/QATools/qa_enscan2.cfg
export FILELIST=/lustre/home/user/p/parfenov/Soft/QATools/batch/lists/urqmd_xexe_2.87gev_mcpico.list
#export FILELIST=/lustre/home/user/p/parfenov/Soft/QATools/batch/lists/urqmd_xew_2.87gev_mcpico.list
export MAIN_DIR=/lustre/home/user/p/parfenov/Soft/QATools
export MAIN_OUT=/lustre/stor2/mephi/parfenov/QAToolsResults
export TMP=/lustre/stor2/mephi/parfenov/TMP

export FORMAT=mcpico

export SHORTNAME1=`basename $FILELIST`
export SHORTNAME11=${SHORTNAME1%.list*}
export LABEL=${SHORTNAME11}

export INFILE=`sed "${TASK_ID}q;d" ${FILELIST}`
echo "input: $INFILE"

if [[ -f "$INFILE" ]]; then
export DATE=${JOB_ID} # or `date '+%Y%m%d_%H%M%S'`

export OUT_DIR=${MAIN_OUT}/${LABEL}/${DATE}

export OUT_FILE_DIR=${OUT_DIR}/files
export OUT_LOG_DIR=${OUT_DIR}/log
export OUT_FILE=${OUT_FILE_DIR}/qatools_${LABEL}_${JOB_ID}_${TASK_ID}.root
export OUT_LOG=${OUT_LOG_DIR}/qatools_${LABEL}_${JOB_ID}_${TASK_ID}.log

export TMP_DIR=${TMP}/TMP_${JOB_ID}_${TASK_ID}

mkdir -p $OUT_FILE_DIR
mkdir -p $OUT_LOG_DIR
#mkdir -p $TMP_DIR
touch $OUT_LOG

echo "Input list : ${INFILE}" &>> $OUT_LOG
echo "QA config  : ${QAFILE}" &>> $OUT_LOG
echo "Format     : ${FORMAT}" &>> $OUT_LOG
echo "Output file: ${OUT_FILE}" &>> $OUT_LOG

cd ${TMP_DIR}
${MAIN_DIR}/build/qaProcess -i $INFILE -o $OUT_FILE -format $FORMAT -config $QAFILE &>> $OUT_LOG

#rm -rfv ${TMP_DIR} &>> $OUT_LOG

echo "Job is finished!" &>> $OUT_LOG

fi
