#include "GammaTrackingAction.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4EventManager.hh"
#include <iostream>  // For error reporting

GammaTrackingAction::GammaTrackingAction()
{
    // Open the output file
    outputFile.open("gamma_momenta.csv");
    if (!outputFile.is_open()) {
        G4cerr << "ERROR: Could not open gamma_momenta.csv for writing!" << G4endl;
        return;
    }
    
    // Write header and immediately flush
    outputFile << "EventID,TrackID,px (MeV/c),py (MeV/c),pz (MeV/c)\n";
    outputFile.flush();
    
    G4cout << "GammaTrackingAction initialized. Output file ready." << G4endl;
}

GammaTrackingAction::~GammaTrackingAction()
{
    if (outputFile.is_open()) {
        outputFile.close();
        G4cout << "GammaTrackingAction finalized. Output file closed." << G4endl;
    }
}

void GammaTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if(track->GetDefinition() == G4Gamma::GammaDefinition())
    {
        if (!outputFile.is_open()) {
            G4cerr << "ERROR: File not open when trying to write gamma data!" << G4endl;
            return;
        }
        
        G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
        G4ThreeVector momentum = track->GetMomentum();
        
        outputFile << eventID << ","
                  << track->GetTrackID() << ","
                  << momentum.x()/CLHEP::MeV << ","
                  << momentum.y()/CLHEP::MeV << ","
                  << momentum.z()/CLHEP::MeV << "\n";
        
        // Optional: flush periodically if you want to see data during long runs
        // if (eventID % 1000 == 0) {
        //     outputFile.flush();
        // }
    }
}