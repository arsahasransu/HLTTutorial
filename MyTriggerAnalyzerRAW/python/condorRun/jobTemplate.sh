#!/bin/bash

voms-proxy-init --voms cms

cd /afs/cern.ch/work/a/asahasra/private/CMSSW_11_1_0/src/
ls
echo "=========================================="

eval `scramv1 runtime -sh`

cd ./HLTTutorial/MyTriggerAnalyzerRAW/python/condorRun/
ls
echo "=========================================="
cp ../MyRunFile_condor.py ./
mv MyRunFile_condor.py MyRunFile_$1.py
sed -i 's/inputFileName/HLT2_HLT_$1.root/g' MyRunFile_$1.py
sed -i 's/rootFileName/ObjectKine_$1.root/g' MyRunFile_$1.py
ls
echo "=========================================="

cmsRun MyRunFile_$1.py
