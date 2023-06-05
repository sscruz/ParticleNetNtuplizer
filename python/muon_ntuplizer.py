import FWCore.ParameterSet.Config as cms

ntuplizer = cms.EDAnalyzer('MuonNtuplizer',
                           src = cms.InputTag("pnetMuonVariables"),
                           srcLeptons = cms.InputTag("linkedObjects","muons"),
                           srcMcTable = cms.InputTag("muonMCTable"),
                           leptonSelection = cms.string("pt > 5 && passed('CutBasedIdLoose') && (userFloat('miniIsoAll')/pt < 0.4) && (abs(dB('PV3D')/edB('PV3D')) < 8) && (dB('PV2D') < 0.05) && (dB('PVDZ') < 0.1)"),
)


def customize_ntuplizer(process):
    process.ntuplizer = ntuplizer
    process.nanoSequenceMC.insert(process.nanoSequenceMC.index(process.nanoSequenceOnlyFullSim)+1, process.ntuplizer)
    process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string("tree.root"),
                                       closeFileFast = cms.untracked.bool(True)
                                   )

    return process 
