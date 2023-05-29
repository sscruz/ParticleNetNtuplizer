#include"ParticleNetNtuplizer/ParticleNetNtuplizer/interface/ParticleNetNtuplizer.h"

template <typename T>
MvaNtuplizer<T>::MvaNtuplizer(const edm::ParameterSet& iConfig) : 
  src_(consumes<pat::LeptonTagInfoCollection<T>>(iConfig.getParameter<edm::InputTag>("src")))
{
  std::cout << "Making tree" << std::endl;
  outtree = fs->make<TTree>( "Events"  , "Events");

}

template <typename T>
MvaNtuplizer<T>::~MvaNtuplizer() {}

template <typename T>
void MvaNtuplizer<T>::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<pat::LeptonTagInfoCollection<T>> src;
  iEvent.getByToken(src_, src); 


  // First time initialize branches if theres a lepton to read them from
  if (src->size() > 0 && output_vars.empty()){
    const pat::LeptonTagInfo<T> taginfo = (*src)[0];
    for (auto& var : taginfo.features().get_all()){
      output_vars[var.first]=std::vector<float>();
      outtree->Branch(var.first.c_str(), &output_vars[var.first]);
    }
  }
  
  // now lets actually fill things
  for (size_t ilep=0; ilep < src->size(); ilep++){
    const pat::LeptonTagInfo<T> taginfo = (*src)[ilep];
    for (auto& var : taginfo.features().get_all()){
      output_vars[var.first]=var.second;
    }
    outtree->Fill();
  }

   
}

template <typename T>
void MvaNtuplizer<T>::beginJob(){}

template <typename T>
void MvaNtuplizer<T>::endJob(){}

typedef MvaNtuplizer<pat::Muon> MuonNtuplizer;
typedef MvaNtuplizer<pat::Electron> ElectronNtuplizer;

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(MuonNtuplizer);
DEFINE_FWK_MODULE(ElectronNtuplizer);
		  
