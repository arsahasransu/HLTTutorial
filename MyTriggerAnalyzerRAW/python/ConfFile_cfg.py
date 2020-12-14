import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_1.root'
    )
)

process.demo = cms.EDAnalyzer('MyTriggerAnalyzerRAW'
)


process.p = cms.Path(process.demo)
