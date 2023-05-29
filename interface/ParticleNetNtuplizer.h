
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "PhysicsTools/PatAlgos/interface/LeptonTagInfoCollectionProducer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"

template <typename T>
class MvaNtuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources> {

 public:
  explicit MvaNtuplizer(const edm::ParameterSet&);
  ~MvaNtuplizer();

 private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  edm::EDGetTokenT<pat::LeptonTagInfoCollection<T>> src_;
  TTree* outtree;
  edm::Service<TFileService> fs;  
  std::map<std::string, std::vector<float>> output_vars;

};
