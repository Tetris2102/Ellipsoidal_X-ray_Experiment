#include "GammaMomentumSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4EventManager.hh"

GammaMomentumSD::GammaMomentumSD(const G4String& name) 
    : G4VSensitiveDetector(name) {
    // outfile.open("momentum_directions.csv");
    // outfile << "px,py,pz\n";
}

GammaMomentumSD::~GammaMomentumSD() {
    outfile.close();
}

G4bool GammaMomentumSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    
    // Check if particle is a gamma quantum
    if (track->GetDefinition()->GetParticleName() == "gamma") {
        // G4ThreeVector momentum = track->GetMomentum();
        // G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
        
        // outfile << momentum.x() << ","
        //         << momentum.y() << ","
        //         << momentum.z() << "\n";
    }
    return true;
}

void GammaMomentumSD::Initialize(G4HCofThisEvent*) {}
void GammaMomentumSD::EndOfEvent(G4HCofThisEvent*) {}
