#include "GammaTrackingAction.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4EventManager.hh"  // Needed to get event ID

GammaTrackingAction::GammaTrackingAction()
{
    // Open the output file
    outputFile.open("gamma_momenta.csv");
    // Write header
    outputFile << "EventID,TrackID,px (MeV/c),py (MeV/c),pz (MeV/c)\n";
}

GammaTrackingAction::~GammaTrackingAction()
{
    outputFile.close();
}

void GammaTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    // Check if particle is a gamma
    if(track->GetDefinition() == G4Gamma::GammaDefinition())
    {
        // Get current event ID
        G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
        
        // Get momentum components
        G4ThreeVector momentum = track->GetMomentum();
        
        // Write to CSV file
        outputFile << eventID << ","
                  << track->GetTrackID() << ","
                  << momentum.x()/CLHEP::MeV << ","
                  << momentum.y()/CLHEP::MeV << ","
                  << momentum.z()/CLHEP::MeV << "\n";
    }
}