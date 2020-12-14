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
  edm::EDGetTokenT<edm::TriggerResults> trgresultsHLT2Token_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWToken_;

  edm::Service<TFileService> fs;
  TH1F* h_eventRate_pT;
  TH1F* h_nMu;
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
MyTriggerAnalyzerRAW::MyTriggerAnalyzerRAW(const edm::ParameterSet& iConfig)
{

  trgresultsORIGToken_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT") );
  trgresultsHLT2Token_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT2") );
  trigobjectsRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT2"));

  h_eventRate_pT = fs->make<TH1F>("eventRate","",100,0,100);
  h_nMu = fs->make<TH1F>("nMu","",10,0,10);
}


MyTriggerAnalyzerRAW::~MyTriggerAnalyzerRAW()
{
 
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

   bool passHLT_DoubleMu33NoFiltersNoVtxDisplaced(false);
   //bool passHLT_DoubleMu16NoFiltersNoVtxDisplaced_PFHT30(false);

   edm::Handle<edm::TriggerResults> trigResults;
   iEvent.getByToken(trgresultsORIGToken_, trigResults);
   if( !trigResults.failedToGet() ) {
     int N_Triggers = trigResults->size();
     const edm::TriggerNames &trigName = iEvent.triggerNames(*trigResults);
     
     for(int i_Trig=0; i_Trig<N_Triggers; ++i_Trig) {
       if(trigResults.product()->accept(i_Trig)) {
	 //std::cout<<trigName.triggerName(i_Trig);
	 TString TrigPath = trigName.triggerName(i_Trig);
	 if(TrigPath.Index("HLT_DoubleMu33NoFiltersNoVtxDisplaced_v")>=0) passHLT_DoubleMu33NoFiltersNoVtxDisplaced=true;
       }
     }
     if(passHLT_DoubleMu33NoFiltersNoVtxDisplaced) std::cout<<"Trigger HLT_DoubleMu33NoFiltersNoVtxDisplaced found"<<std::endl;
   }
   /*
   edm::Handle<edm::TriggerResults> trigResults2;
   iEvent.getByToken(trgresultsHLT2Token_, trigResults2);
   if( !trigResults2.failedToGet() ) {
     int N_Triggers = trigResults2->size();
     const edm::TriggerNames &trigName = iEvent.triggerNames(*trigResults2);
     
     for(int i_Trig=0; i_Trig<N_Triggers; ++i_Trig) {
       if(trigResults2.product()->accept(i_Trig)) {
	 //std::cout<<trigName.triggerName(i_Trig);
	 TString TrigPath = trigName.triggerName(i_Trig);
	 if(TrigPath.Index("HLT_DoubleMu16NoFiltersNoVtxDisplaced_PFHT30_v")>=0) passHLT_DoubleMu16NoFiltersNoVtxDisplaced_PFHT30=true;
       }
     }
     if(passHLT_DoubleMu16NoFiltersNoVtxDisplaced_PFHT30) std::cout<<"Trigger HLT_DoubleMu16NoFiltersNoVtxDisplaced_PFHT30 found"<<std::endl;
   }
   */

   int nMu = 0;
   double minpT = -1;
   edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
   iEvent.getByToken(trigobjectsRAWToken_ ,triggerObjectsSummary);
   trigger::TriggerObjectCollection selectedObjects;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltL3fDimuonL1f0L2NVf16L3NoFiltersNoVtxFiltered16Displaced","","HLT2") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       nMu = keys.size();
       if(nMu>=2) {
	 trigger::TriggerObject foundObject = (allTriggerObjects)[keys[0]];
	 minpT = foundObject.pt();
	 for (size_t j = 1; j < keys.size(); j++) {
	   foundObject = (allTriggerObjects)[keys[j]];
	   if(foundObject.pt()<minpT) minpT = foundObject.pt();
	   //cout <<"object found, printing pt, eta, phi: " <<foundObject.pt()<<", "<<foundObject.eta()<<", "<< foundObject.phi() <<endl;
	 }
       }
     }
   }
   h_nMu->Fill(nMu);
   if(nMu>=2) h_eventRate_pT->Fill(minpT);   
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
