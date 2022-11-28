// Arapuca simulation
// Authors: L. Paulucci & F. Marinho
// Date: 20th September 2016
//
// Added modifications should be reported in arapuca.cc header comments

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "RunAction.hh"
#include "g4root.hh"

RunAction::RunAction(DetectorConstruction* det) 
:fDetector(det)
{   
  fSaveRndm = 0;  
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{  
  
  // Get/create analysis manager
  G4cout << "##### Create analysis manager " << "  " << this << G4endl;
  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  G4cout << "Using " << man->GetType() << " analysis manager" << G4endl;

  // Open an output file
  man->OpenFile("arapuca");
  man->SetFirstNtupleId(1);

  //Declare ntuples
  //
  // Create 1st ntuple (id = 1)
  //
  man->CreateNtuple("ntuple", "data");
  man->CreateNtupleIColumn("evt");
  man->CreateNtupleIColumn("pdg");
  man->CreateNtupleIColumn("id");
  man->CreateNtupleIColumn("mid");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("de");
  man->CreateNtupleDColumn("e");
  man->CreateNtupleIColumn("vol");
  man->CreateNtupleIColumn("volrep");
  man->CreateNtupleIColumn("mvol");
  man->CreateNtupleIColumn("mvolrep");
  man->CreateNtupleIColumn("inter");
  man->CreateNtupleDColumn("time");
  man->FinishNtuple();
  // Create 2nd ntuple (id = 2)
  //
  man->CreateNtuple("photon", "positions");
  man->CreateNtupleDColumn("cap_x");
  man->CreateNtupleDColumn("cap_y");
  man->CreateNtupleDColumn("cap_z");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->FinishNtuple();
  // Create 3rd ntuple (id = 3)
  //
  man->CreateNtuple("electron", "positions");
  man->CreateNtupleDColumn("cap_x");
  man->CreateNtupleDColumn("cap_y");
  man->CreateNtupleDColumn("cap_z");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->FinishNtuple();

  man->SetNtupleActivation(true);

  G4int nvols = 710;
  G4int hv_id = man->CreateH1("hv","",nvols+1,-0.5,nvols+0.5);
  G4int gamma_en = man->CreateH1("ncap_gamma_e", "", 100, 0, 10);
  G4int op_wl = man->CreateH1("op_wl", "", 100, 0, 300);

  /*
  man->CreateNtuple("photons", "photons");
  man->CreateNtupleIColumn("evt");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("photon_hits");
  */

  // save Rndm status
  if (fSaveRndm > 0)
    { 
      CLHEP::HepRandom::showEngineStatus();
      CLHEP::HepRandom::saveEngineStatus("beginOfRun.rndm");
    }
 
  fNumEvent = 0;
  
}

void RunAction::EndOfRunAction(const G4Run* /*aRun*/)
{     
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  // save Rndm status
  if (fSaveRndm == 1)
  { 
    CLHEP::HepRandom::showEngineStatus();
    CLHEP::HepRandom::saveEngineStatus("endOfRun.rndm");
  }   
  
  G4cout << G4endl;    
        
  man->Write();
  man->CloseFile();
  
  delete G4AnalysisManager::Instance();

}
