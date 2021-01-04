import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

'''process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_1.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_10.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_11.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_12.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_13.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_14.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_15.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_16.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_17.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_18.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_19.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_2.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_20.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_21.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_22.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_23.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_24.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_25.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_26.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_27.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_28.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_29.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_3.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_30.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_31.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_32.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_33.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_34.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_35.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_36.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_37.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_38.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_39.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_4.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_40.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_41.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_42.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_43.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_44.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_45.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_46.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_47.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_48.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_49.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_5.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_5.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_50.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_51.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_52.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_53.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_54.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_55.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_56.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_57.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_58.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_59.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_6.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_7.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_8.root',
        '/store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_9.root'
    )
)'''

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        'file:/eos/cms/store/data/Run2018D/EphemeralHLTPhysics1/RAW/v1/000/323/775/00000/0244D183-F28D-2741-9DBF-1638BEDC734E.root',
        'root://xrootd-cms.infn.it///store/user/asahasra/EphemeralHLTPhysics1/SoftDisplacedPFHT_HLT_ARSahasransu_CustomRun1/201204_114655/0000/HLT2_HLT_1.root'
    )
)

process.demo = cms.EDAnalyzer('MyTriggerAnalyzerRAW')
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( "ObjectKine.root" )
                                   )
process.demo_step = cms.EndPath(process.demo)

process.p = cms.Path(process.demo)
