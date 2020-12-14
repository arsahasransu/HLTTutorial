import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/inputFileName'
    )
)

process.demo = cms.EDAnalyzer('MyTriggerAnalyzerRAW')
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( "rootFileName" )
                                   )
process.demo_step = cms.EndPath(process.demo)

process.p = cms.Path(process.demo)
