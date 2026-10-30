#include "SenDet.hh"

SenDetClass::SenDetClass(G4String name): G4VSensitiveDetector(name)
{}

SenDetClass::~SenDetClass()
{}

G4bool SenDetClass::ProcessHits(G4Step *aStep, G4TouchableHistory * R0hist)
{
    G4Track * track = aStep->GetTrack();
    //track->SetTrackStatus(fStopAndKill); //kill photons after enter detector

    G4StepPoint *preStepPoint = aStep -> GetPreStepPoint(); //enter detector
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //exits detector
    
    G4double edep1 = preStepPoint->GetTotalEnergy(); //get photon energy when it enters step

    G4ThreeVector posPhoton = preStepPoint->GetPosition(); //get photon position when it enters


//    G4cout << "Photon position " << posPhoton << G4endl; //to print pos

    G4AnalysisManager * man = G4AnalysisManager::Instance();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    man->FillNtupleIColumn(0, evt);                 //fill N tuple 
    man->FillNtupleDColumn(1, posPhoton[0]);
    man->FillNtupleDColumn(2, posPhoton[1]);
    man->FillNtupleDColumn(3, posPhoton[2]);
    man->FillNtupleDColumn(4, edep1);  //take INITIAL energy of photon at end (detector is air so should not affect E)
    man->AddNtupleRow(0);
    
    man->FillH1(0, edep1);

    man->FillH2(0, posPhoton[0], posPhoton[1], 0.0); //ID, x, y, weighting

return true;
}
