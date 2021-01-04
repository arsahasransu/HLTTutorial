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

class MyTriggerAnalyzerRAW : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MyTriggerAnalyzerRAW(const edm::ParameterSet&);
      ~MyTriggerAnalyzerRAW();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  edm::EDGetTokenT<edm::TriggerResults> trgresultsORIGToken_;
  //edm::EDGetTokenT<edm::TriggerResults> trgresultsHLT2Token_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsMyRAWToken_;

  edm::Service<TFileService> fs;
  TTree* hltObjects;
  std::vector<double> mu_id;
  std::vector<double> mu_pt;
  std::vector<double> mu_eta;
  std::vector<double> mu_phi;
  std::vector<double> mu_m;
  int mu_n;
  std::vector<double> eg_id;
  std::vector<double> eg_pt;
  std::vector<double> eg_eta;
  std::vector<double> eg_phi;
  std::vector<double> eg_m;
  int eg_n;
  std::vector<double> ht_id;
  std::vector<double> ht_pt;
  std::vector<double> ht_eta;
  std::vector<double> ht_phi;
  std::vector<double> ht_m;
  int ht_n;
  std::vector<double> met_id;
  std::vector<double> met_pt;
  std::vector<double> met_eta;
  std::vector<double> met_phi;
  std::vector<double> met_m;
  int met_n;
  std::vector<double> jetak4_id;
  std::vector<double> jetak4_pt;
  std::vector<double> jetak4_eta;
  std::vector<double> jetak4_phi;
  std::vector<double> jetak4_m;
  int jetak4_n;
  std::vector<double> jetak8_id;
  std::vector<double> jetak8_pt;
  std::vector<double> jetak8_eta;
  std::vector<double> jetak8_phi;
  std::vector<double> jetak8_m;
  int jetak8_n;
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
  mu_id(),mu_pt(),mu_eta(),mu_phi(),mu_m(),mu_n(0),
  eg_id(),eg_pt(),eg_eta(),eg_phi(),eg_m(),eg_n(0),
  ht_id(),ht_pt(),ht_eta(),ht_phi(),ht_m(),ht_n(0),
  met_id(),met_pt(),met_eta(),met_phi(),met_m(),met_n(0),
  jetak4_id(),jetak4_pt(),jetak4_eta(),jetak4_phi(),jetak4_m(),jetak4_n(0),
  jetak8_id(),jetak8_pt(),jetak8_eta(),jetak8_phi(),jetak8_m(),jetak8_n(0) {

  trgresultsORIGToken_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT") );
  //trgresultsHLT2Token_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT2") );
  trigobjectsRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT"));
  trigobjectsMyRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::MyHLT"));

  hltObjects = fs->make<TTree>("TrigObjects","TrigObjects");
  hltObjects->Branch("mu_id", &mu_id);
  hltObjects->Branch("mu_pt", &mu_pt);
  hltObjects->Branch("mu_eta", &mu_eta);
  hltObjects->Branch("mu_phi", &mu_phi);
  hltObjects->Branch("mu_m", &mu_m);
  hltObjects->Branch("mu_n", &mu_n);
  hltObjects->Branch("eg_id", &eg_id);
  hltObjects->Branch("eg_pt", &eg_pt);
  hltObjects->Branch("eg_eta", &eg_eta);
  hltObjects->Branch("eg_phi", &eg_phi);
  hltObjects->Branch("eg_m", &eg_m);
  hltObjects->Branch("eg_n", &eg_n);
  hltObjects->Branch("ht_id", &ht_id);
  hltObjects->Branch("ht_pt", &ht_pt);
  hltObjects->Branch("ht_eta", &ht_eta);
  hltObjects->Branch("ht_phi", &ht_phi);
  hltObjects->Branch("ht_m", &ht_m);
  hltObjects->Branch("ht_n", &ht_n);
  hltObjects->Branch("met_id", &met_id);
  hltObjects->Branch("met_pt", &met_pt);
  hltObjects->Branch("met_eta", &met_eta);
  hltObjects->Branch("met_phi", &met_phi);
  hltObjects->Branch("met_m", &met_m);
  hltObjects->Branch("met_n", &met_n);
  hltObjects->Branch("jetak4_id", &jetak4_id);
  hltObjects->Branch("jetak4_pt", &jetak4_pt);
  hltObjects->Branch("jetak4_eta", &jetak4_eta);
  hltObjects->Branch("jetak4_phi", &jetak4_phi);
  hltObjects->Branch("jetak4_m", &jetak4_m);
  hltObjects->Branch("jetak4_n", &jetak4_n);
  hltObjects->Branch("jetak8_id", &jetak8_id);
  hltObjects->Branch("jetak8_pt", &jetak8_pt);
  hltObjects->Branch("jetak8_eta", &jetak8_eta);
  hltObjects->Branch("jetak8_phi", &jetak8_phi);
  hltObjects->Branch("jetak8_m", &jetak8_m);
  hltObjects->Branch("jetak8_n", &jetak8_n);
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
   eg_n = 0;
   eg_id.erase(eg_id.begin(), eg_id.end());
   eg_pt.erase(eg_pt.begin(), eg_pt.end());
   eg_eta.erase(eg_eta.begin(), eg_eta.end());
   eg_phi.erase(eg_phi.begin(), eg_phi.end());
   eg_m.erase(eg_m.begin(), eg_m.end());
   ht_n = 0;
   ht_id.erase(ht_id.begin(), ht_id.end());
   ht_pt.erase(ht_pt.begin(), ht_pt.end());
   ht_eta.erase(ht_eta.begin(), ht_eta.end());
   ht_phi.erase(ht_phi.begin(), ht_phi.end());
   ht_m.erase(ht_m.begin(), ht_m.end());
   met_n = 0;
   met_id.erase(met_id.begin(), met_id.end());
   met_pt.erase(met_pt.begin(), met_pt.end());
   met_eta.erase(met_eta.begin(), met_eta.end());
   met_phi.erase(met_phi.begin(), met_phi.end());
   met_m.erase(met_m.begin(), met_m.end());
   jetak4_n = 0;
   jetak4_id.erase(jetak4_id.begin(), jetak4_id.end());
   jetak4_pt.erase(jetak4_pt.begin(), jetak4_pt.end());
   jetak4_eta.erase(jetak4_eta.begin(), jetak4_eta.end());
   jetak4_phi.erase(jetak4_phi.begin(), jetak4_phi.end());
   jetak4_m.erase(jetak4_m.begin(), jetak4_m.end());
   jetak8_n = 0;
   jetak8_id.erase(jetak8_id.begin(), jetak8_id.end());
   jetak8_pt.erase(jetak8_pt.begin(), jetak8_pt.end());
   jetak8_eta.erase(jetak8_eta.begin(), jetak8_eta.end());
   jetak8_phi.erase(jetak8_phi.begin(), jetak8_phi.end());
   jetak8_m.erase(jetak8_m.begin(), jetak8_m.end());

   edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
   iEvent.getByToken(trigobjectsRAWToken_ ,triggerObjectsSummary);

   edm::Handle<trigger::TriggerEvent> myTriggerObjectsSummary;
   iEvent.getByToken(trigobjectsMyRAWToken_ ,myTriggerObjectsSummary);

   unsigned int nMu = 0;
   if (myTriggerObjectsSummary.isValid()) {
     size_t filterIndex = (*myTriggerObjectsSummary).filterIndex( edm::InputTag("hltL3fDimuonL1f0L2NVf16L3NoFiltersNoVtxFiltered16Displaced","","MyHLT") );
     trigger::TriggerObjectCollection allTriggerObjects = myTriggerObjectsSummary->getObjects();
     if (filterIndex < (*myTriggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*myTriggerObjectsSummary).filterKeys(filterIndex);
       nMu = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nMu; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 mu_id.push_back(foundObject.id());
	 mu_pt.push_back(foundObject.pt());
	 mu_eta.push_back(foundObject.eta());
	 mu_phi.push_back(foundObject.phi());
	 mu_m.push_back(foundObject.mass());
       }
     }
   }
   
   unsigned int nEG = 0;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("HLTEle15WPLooseGsfSequence","","HLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nEG = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nEG; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 eg_id.push_back(foundObject.id());
	 eg_pt.push_back(foundObject.pt());
	 eg_eta.push_back(foundObject.eta());
	 eg_phi.push_back(foundObject.phi());
	 eg_m.push_back(foundObject.mass());
       }
     }
   }

   unsigned int nHt = 0;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltPFHT30Jet30","","MyHLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nHt = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nHt; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 ht_id.push_back(foundObject.id());
	 ht_pt.push_back(foundObject.pt());
	 ht_eta.push_back(foundObject.eta());
	 ht_phi.push_back(foundObject.phi());
	 ht_m.push_back(foundObject.mass());
       }
     }
   }

   unsigned int nMet = 0;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltPFMET50","","HLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nMet = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nMet; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 met_id.push_back(foundObject.id());
	 met_pt.push_back(foundObject.pt());
	 met_eta.push_back(foundObject.eta());
	 met_phi.push_back(foundObject.phi());
	 met_m.push_back(foundObject.mass());
       }
     }
   }

   unsigned int nJetAK4 = 0;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltSinglePFJet40","","HLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nJetAK4 = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nJetAK4; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 jetak4_id.push_back(foundObject.id());
	 jetak4_pt.push_back(foundObject.pt());
	 jetak4_eta.push_back(foundObject.eta());
	 jetak4_phi.push_back(foundObject.phi());
	 jetak4_m.push_back(foundObject.mass());
       }
     }
   }

   unsigned int nJetAK8 = 0;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltSinglePFJet40AK8","","HLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nJetAK8 = keys.size();
       trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
       for (size_t j = 0; j < nJetAK8; j++) {
	 //std::cout<<j<<"\t"<<std::endl;
	 foundObject = (allTriggerObjects)[keys[j]];
	 jetak8_id.push_back(foundObject.id());
	 jetak8_pt.push_back(foundObject.pt());
	 jetak8_eta.push_back(foundObject.eta());
	 jetak8_phi.push_back(foundObject.phi());
	 jetak8_m.push_back(foundObject.mass());
       }
     }
   }

   mu_n = nMu;
   eg_n = nEG;
   ht_n = nHt;
   met_n = nMet;
   jetak4_n = nJetAK4;
   jetak8_n = nJetAK8;

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
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyTriggerAnalyzerRAW);
