import FWCore.ParameterSet.Config as cms
process = cms.Process("MAIN")
import sys

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/Volumes/HDD/DYJetsToLL.root')
  )
process.GlobalTag.globaltag = cms.string('START53_V22::All')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.bestMuons = cms.EDFilter("MuonRefSelector",
  src = cms.InputTag("muons"),
  cut = cms.string("pt > 20 & abs(eta) < 2")
  )

process.mergeMuons = cms.EDProducer("ICMuonMerger",
  merge = cms.VInputTag("bestMuons", "muons")
  )

process.testModule = cms.EDProducer("TestModule")

process.p = cms.Path(
  process.bestMuons+
  process.mergeMuons+
  process.testModule
  )

#print process.dumpPython()