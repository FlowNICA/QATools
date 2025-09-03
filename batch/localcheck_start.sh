#!/bin/bash

#
#$ -wd /scratch2/$USER/TMP
#$ -cwd
#$ -N run_QAtools
#$ -q all.q
#$ -l h_rt=0:45:00
#$ -l s_rt=0:45:00
#$ -t 1-849
#
#$ -o /scratch2/$USER/TMP
#$ -e /scratch2/$USER/TMP
#

source /cvmfs/nica.jinr.ru/sw/os/login.sh
module add CMake/ ROOT/

export JOB_ID=local
export SGE_TASK_ID=1

export model=HSD
export sys=AuAu
export ecm=2.4
#export format=mcpico
export format=phqmd
export eos=cascade
export programm=HADES_2gev
#export programm=STAR_3gev
#export programm=enscan2

export START_POSITION=$PWD
export MAIN_DIR=/scratch2/parfenov/Soft/QATools
#export CONFIG_FILE=$MAIN_DIR/batch/qa_STAR_3gev_20M.cfg
#export CONFIG_FILE=$MAIN_DIR/batch/qa_HADES_2gev.cfg
export CONFIG_FILE=$MAIN_DIR/batch/qa_${programm}.cfg
export INPUT_FILELISTS=$MAIN_DIR/batch/model_filelists.list
export INPUT_FILELIST=`sed "${SGE_TASK_ID}q;d" $INPUT_FILELISTS`
export COMMIT=${model}_${sys}_${programm}_${ecm}gev_${eos}
export JOBID=${JOB_ID}

export OUT=$MAIN_DIR/OUT/$COMMIT/$JOBID
export OUT_LOG=$OUT/log
export OUT_FILES=$OUT/files
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log
export OUTPUT=${OUT_FILES}/qa_${JOB_ID}_${SGE_TASK_ID}.root
export TMPALL=$MAIN_DIR/TMP
export TMPDIR=$TMPALL/TMP_${JOB_ID}_${SGE_TASK_ID}

# mkdir -p $TMPDIR
mkdir -p $OUT
mkdir -p $OUT_LOG
mkdir -p $OUT_FILES

#source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh &>>$LOG
source /scratch2/parfenov/Soft/mcini-new/macro/config.sh &>> $LOG
export PHQMD_PATH=/scratch2/parfenov/Soft/hic-stuff

export BIN_QA=$MAIN_DIR/build/qaProcess

echo "Binary file: $BIN_QA" &>> $LOG
echo "qaProcess options:" &>> $LOG
echo "    -i      $INPUT_FILELIST" &>> $LOG
echo "    -format $format" &>> $LOG
echo "    -config $CONFIG_FILE" &>> $LOG
echo "    -0      $OUTPUT" &>> $LOG

$BIN_QA -i $INPUT_FILELIST -format $format -config $CONFIG_FILE -o $OUTPUT &>> $LOG

cd $START_POSITION
echo "Job is done!" &>> $LOG
