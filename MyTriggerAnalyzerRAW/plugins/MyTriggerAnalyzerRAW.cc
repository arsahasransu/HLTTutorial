// -*- C++ -*-
//
// Package:    HLTAnalysis/MyTriggerAnalyzerRAW
// Class:      MyTriggerAnalyzerRAW
// 
/**\class MyTriggerAnalyzerRAW MyTriggerAnalyzerRAW.cc HLTAnalysis/MyTriggerAnalyzerRAW/plugins/MyTriggerAnalyzerRAW.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Laurent Thomas
//         Created:  Fri, 24 Mar 2017 04:09:55 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/Common/interface/AssociationMap.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"

#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeed.h"
#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeedCollection.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TLorentzVector.h"
#include "TTree.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

using namespace edm;
using namespace reco;
using namespace std;
using namespace trigger;

class MyTriggerAnalyzerRAW : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit MyTriggerAnalyzerRAW(const edm::ParameterSet&);
  ~MyTriggerAnalyzerRAW();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  int muondxy(const edm::Event&, const edm::EventSetup&, std::vector<double> &, std::vector<double> &);
  
  edm::EDGetTokenT<edm::TriggerResults> trgresultsORIGToken_;
  //edm::EDGetTokenT<edm::TriggerResults> trgresultsHLT2Token_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsMyRAWToken_;

  edm::EDGetTokenT<reco::BeamSpot> beamspotToken_;
  // token identifying product contains muons
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> candToken_; 
  // token identifying product contains muons passing the previous level
  //edm::InputTag muonL3Tag_;
  //edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> muonL3Token_;         

  edm::Service<TFileService> fs;
  TTree* hltObjects;
  std::vector<double> mu_id;
  std::vector<double> mu_pt;
  std::vector<double> mu_eta;
  std::vector<double> mu_phi;
  std::vector<double> mu_m;
  int mu_n;
  std::vector<double> muOrig_id;
  std::vector<double> muOrig_pt;
  std::vector<double> muOrig_eta;
  std::vector<double> muOrig_phi;
  std::vector<double> muOrig_m;
  int muOrig_n;
  std::vector<double> muCheck_pt;
  std::vector<double> muCheck_dxy;
  int muCheck_n;
  std::vector<double> ht_id;
  std::vector<double> ht_pt;
  std::vector<double> ht_eta;
  std::vector<double> ht_phi;
  std::vector<double> ht_m;
  int ht_n;
  bool DoubleMu33NoFiltersNoVtxTrigBit;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyTriggerAnalyzerRAW::MyTriggerAnalyzerRAW(const edm::ParameterSet& iConfig):
  //muonL3Tag_(iConfig.getParameter<InputTag>("MuonL3CandTag")),
  //muonL3Token_(consumes<trigger::TriggerFilterObjectWithRefs>(muonL3Tag_)),
  mu_id(),mu_pt(),mu_eta(),mu_phi(),mu_m(),mu_n(0),
  muOrig_id(),muOrig_pt(),muOrig_eta(),muOrig_phi(),muOrig_m(),muOrig_n(0),
  ht_id(),ht_pt(),ht_eta(),ht_phi(),ht_m(),ht_n(0){

  trgresultsORIGToken_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT") );
  //trgresultsHLT2Token_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT2") );
  trigobjectsRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT"));
  trigobjectsMyRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT2"));
  beamspotToken_=consumes<reco::BeamSpot>(edm::InputTag("hltOnlineBeamSpot"));
  candToken_=consumes<reco::RecoChargedCandidateCollection>(edm::InputTag("hltL3NoFiltersNoVtxMuonCandidates"));
  //muonL3Token_=consumes<trigger::TriggerFilterObjectWithRefs>(edm::InputTag("hltL3fDimuonL1f0L2NVf16L3NoFiltersNoVtxFiltered16Displaced"));

  hltObjects = fs->make<TTree>("TrigObjects","TrigObjects");
  hltObjects->Branch("mu_id", &mu_id);
  hltObjects->Branch("mu_pt", &mu_pt);
  hltObjects->Branch("mu_eta", &mu_eta);
  hltObjects->Branch("mu_phi", &mu_phi);
  hltObjects->Branch("mu_m", &mu_m);
  hltObjects->Branch("mu_n", &mu_n);
  hltObjects->Branch("ht_id", &ht_id);
  hltObjects->Branch("ht_pt", &ht_pt);
  hltObjects->Branch("ht_eta", &ht_eta);
  hltObjects->Branch("ht_phi", &ht_phi);
  hltObjects->Branch("ht_m", &ht_m);
  hltObjects->Branch("ht_n", &ht_n);
  hltObjects->Branch("DoubleMu33NoFiltersNoVtxTrigBit", &DoubleMu33NoFiltersNoVtxTrigBit);
  hltObjects->Branch("muOrig_id", &muOrig_id);
  hltObjects->Branch("muOrig_pt", &muOrig_pt);
  hltObjects->Branch("muOrig_eta", &muOrig_eta);
  hltObjects->Branch("muOrig_phi", &muOrig_phi);
  hltObjects->Branch("muOrig_m", &muOrig_m);
  hltObjects->Branch("muOrig_n", &muOrig_n);
  hltObjects->Branch("muCheck_pt", &muCheck_pt);
  hltObjects->Branch("muCheck_dxy", &muCheck_dxy);
  hltObjects->Branch("muCheck_n", &muCheck_n);
}


MyTriggerAnalyzerRAW::~MyTriggerAnalyzerRAW() {
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyTriggerAnalyzerRAW::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;
   using namespace reco;
   using namespace std;

   mu_n = 0;
   mu_id.erase(mu_id.begin(), mu_id.end());
   mu_pt.erase(mu_pt.begin(), mu_pt.end());
   mu_eta.erase(mu_eta.begin(), mu_eta.end());
   mu_phi.erase(mu_phi.begin(), mu_phi.end());
   mu_m.erase(mu_m.begin(), mu_m.end());
   muOrig_n = 0;
   muOrig_id.erase(muOrig_id.begin(), muOrig_id.end());
   muOrig_pt.erase(muOrig_pt.begin(), muOrig_pt.end());
   muOrig_eta.erase(muOrig_eta.begin(), muOrig_eta.end());
   muOrig_phi.erase(muOrig_phi.begin(), muOrig_phi.end());
   muOrig_m.erase(muOrig_m.begin(), muOrig_m.end());
   muCheck_n = 0;
   muCheck_pt.erase(muCheck_pt.begin(), muCheck_pt.end());
   muCheck_pt.erase(muCheck_pt.begin(), muCheck_pt.end());
   ht_n = 0;
   ht_id.erase(ht_id.begin(), ht_id.end());
   ht_pt.erase(ht_pt.begin(), ht_pt.end());
   ht_eta.erase(ht_eta.begin(), ht_eta.end());
   ht_phi.erase(ht_phi.begin(), ht_phi.end());
   ht_m.erase(ht_m.begin(), ht_m.end());

   edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
   iEvent.getByToken(trigobjectsRAWToken_ ,triggerObjectsSummary);

   edm::Handle<trigger::TriggerEvent> myTriggerObjectsSummary;
   iEvent.getByToken(trigobjectsMyRAWToken_ ,myTriggerObjectsSummary);
   
   bool passHLT_DoubleMu33NoFiltersNoVtxDisplaced(false);

   //Accessing trigger bits:
   //This works in both RAW, AOD or MINIAOD 
   //Here we access the decision provided by the HLT (i.e. original trigger step). 
   edm::Handle<edm::TriggerResults> trigResults;
   iEvent.getByToken(trgresultsORIGToken_, trigResults);   if( !trigResults.failedToGet() ) {
     int N_Triggers = trigResults->size();
     const edm::TriggerNames & trigName = iEvent.triggerNames(*trigResults);

     for( int i_Trig = 0; i_Trig < N_Triggers; ++i_Trig ) {
       if (trigResults.product()->accept(i_Trig)) {
	 TString TrigPath =trigName.triggerName(i_Trig);
	 if(TrigPath.Index("HLT_DoubleMu33NoFiltersNoVtxDisplaced_v") >=0) passHLT_DoubleMu33NoFiltersNoVtxDisplaced=true; 
	 if(passHLT_DoubleMu33NoFiltersNoVtxDisplaced){
	  cout << "Passed path: HLT_DoubleMu33NoFiltersNoVtxDisplaced"<<endl;
	 }
       }
     }
   }

   DoubleMu33NoFiltersNoVtxTrigBit = passHLT_DoubleMu33NoFiltersNoVtxDisplaced;
   /*
   std::cout<<"My Trigger Summary"<<std::endl;
   for(trigger::size_type ctr=0; ctr<(*myTriggerObjectsSummary).sizeFilters(); ctr++) {
     std::cout<<(*myTriggerObjectsSummary).filterLabel(ctr)<<std::endl;
   }

   std::cout<<"Original Trigger Summary"<<std::endl;
   for(trigger::size_type ctr=0; ctr<(*triggerObjectsSummary).sizeFilters(); ctr++) {
     std::cout<<(*triggerObjectsSummary).filterLabel(ctr)<<std::endl;
   }
   */
   /*
   std::vector< std::string > colTag = (*myTriggerObjectsSummary).collectionTags();
   for(unsigned int i=0; i<colTag.size(); i++) {
     std::cout<<colTag[i]<<std::endl;
   }
   */
   unsigned int nMuOrig = 0;
   if (myTriggerObjectsSummary.isValid()) {
     size_t filterIndex = (*myTriggerObjectsSummary).filterIndex( edm::InputTag("hltL3fDimuonL1f0L2NVf16L3NoFiltersNoVtxFiltered16Displaced","","HLT2") );
     //std::cout<<filterIndex<<std::endl;
     trigger::TriggerObjectCollection allTriggerObjects = myTriggerObjectsSummary->getObjects();
     if (filterIndex < (*myTriggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*myTriggerObjectsSummary).filterKeys(filterIndex);
       nMuOrig = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nMuOrig; j++) {
	 std::cout<<"MuOrig \t"<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 muOrig_id.push_back(foundObject.id());
	 muOrig_pt.push_back(foundObject.pt());
	 muOrig_eta.push_back(foundObject.eta());
	 muOrig_phi.push_back(foundObject.phi());
	 muOrig_m.push_back(foundObject.mass());
       }
     }
   }

   unsigned int nMu = 0;
   if (myTriggerObjectsSummary.isValid()) {
     size_t filterIndex = (*myTriggerObjectsSummary).filterIndex( edm::InputTag("hltL3fDimuonL1f0L2NVf16L3NoFiltersNoVtxFiltered16Displaced","","HLT2") );
     //std::cout<<filterIndex<<std::endl;
     trigger::TriggerObjectCollection allTriggerObjects = myTriggerObjectsSummary->getObjects();
     if (filterIndex < (*myTriggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*myTriggerObjectsSummary).filterKeys(filterIndex);
       nMu = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nMu; j++) {
	 std::cout<<"Mu \t"<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 mu_id.push_back(foundObject.id());
	 mu_pt.push_back(foundObject.pt());
	 mu_eta.push_back(foundObject.eta());
	 mu_phi.push_back(foundObject.phi());
	 mu_m.push_back(foundObject.mass());
       }
     }
   }
   
   unsigned int nHt = 0;
   if (myTriggerObjectsSummary.isValid()) {
     size_t filterIndex = (*myTriggerObjectsSummary).filterIndex( edm::InputTag("hltPFHT30Jet30","","HLT2") );
     //std::cout<<filterIndex<<std::endl;
     trigger::TriggerObjectCollection allTriggerObjects = myTriggerObjectsSummary->getObjects();
     if (filterIndex < (*myTriggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*myTriggerObjectsSummary).filterKeys(filterIndex);
       nHt = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nHt; j++) {
	 std::cout<<"HT \t"<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 ht_id.push_back(foundObject.id());
	 ht_pt.push_back(foundObject.pt());
	 ht_eta.push_back(foundObject.eta());
	 ht_phi.push_back(foundObject.phi());
	 ht_m.push_back(foundObject.mass());
       }
     }
   }

   muOrig_n = nMuOrig;
   mu_n = nMu;
   ht_n = nHt;

   muCheck_n = muondxy(iEvent, iSetup, muCheck_pt, muCheck_dxy);

   hltObjects->Fill();
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
MyTriggerAnalyzerRAW::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyTriggerAnalyzerRAW::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyTriggerAnalyzerRAW::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("MuonL3CandTag", edm::InputTag(""));
  descriptions.addDefault(desc);
}

// ------------ method to compute and store muon dxy ----------------
int 
MyTriggerAnalyzerRAW::muondxy(const edm::Event& iEvent, const edm::EventSetup& iSetup, std::vector<double> &pt, std::vector<double> &dxy) {

  using namespace edm;
  using namespace reco;
  using namespace std;
  using namespace trigger;
  
  // Read RecoChargedCandidates from L3MuonCandidateProducer:
  Handle<RecoChargedCandidateCollection> mucands;
  iEvent.getByToken(candToken_, mucands);
  /*  
  // Read L3 triggered objects:
  Handle<trigger::TriggerFilterObjectWithRefs> muonL3Cands;
  iEvent.getByToken(muonL3Token_, muonL3Cands);
  vector<RecoChargedCandidateRef> vl3cands;
  muonL3Cands->getObjects(trigger::TriggerMuon, vl3cands);
  */
  // Read BeamSpot information:
  Handle<BeamSpot> recoBeamSpotHandle;
  iEvent.getByToken(beamspotToken_, recoBeamSpotHandle);
  const BeamSpot& beamSpot = *recoBeamSpotHandle;
  
  // Number of objects in the L3 Trigger:
  int n = 0;

  unsigned int maxI = mucands->size();
  for (unsigned int i = 0; i != maxI; ++i) {
    const TrackRef& tk = (*mucands)[i].track();
    double absDxy = std::abs(tk->dxy(beamSpot.position()));
    dxy.push_back(absDxy);
    pt.push_back((*mucands)[i].pt());
    n++;
  }

  /*
  for (auto& vcand : vl3cands) {
    
    if (mucands->empty()) continue;
    auto const& tk = (*mucands)[0].track();
    bool useL3MTS = false;

    if (tk->seedRef().isNonnull()) {
      auto a = dynamic_cast<const L3MuonTrajectorySeed*>(tk->seedRef().get());
      useL3MTS = a != nullptr;
    }

    if(useL3MTS) {
      unsigned int maxI = mucands->size();
      for (unsigned int i = 0; i != maxI; ++i) {
	const TrackRef& tk = (*mucands)[i].track();
	edm::Ref<L3MuonTrajectorySeedCollection> l3seedRef =
	  tk->seedRef().castTo<edm::Ref<L3MuonTrajectorySeedCollection> >();
	TrackRef staTrack = l3seedRef->l2Track();
	if (vcand->get<TrackRef>() == staTrack) {
	  double absDxy = std::abs(tk->dxy(beamSpot.position()));
	  dxy.push_back(absDxy);
	  pt.push_back((*mucands)[i].pt());
	  n++;
	  break;
	}
      } // end loop on mucands
    } //end of useL3MTS
  } // end loop on vl3cands 
  */
  return n;
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyTriggerAnalyzerRAW);
