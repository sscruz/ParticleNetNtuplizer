import FWCore.ParameterSet.Config as cms

ntuplizer = cms.EDAnalyzer('MuonNtuplizer',
                           src = cms.InputTag("pnetMuonVariables"),
)


def customize_ntuplizer(process):
    process.ntuplizer = ntuplizer
    process.nanoSequenceMC.insert(process.nanoSequenceMC.index(process.nanoSequenceOnlyFullSim)+1, process.ntuplizer)
    process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string("tree.root"),
                                       closeFileFast = cms.untracked.bool(True)
                                   )

    return process 
