#include "G4VSensitiveDetector.hh"
#include <fstream>

class GammaMomentumSD : public G4VSensitiveDetector {
public:
    GammaMomentumSD(const G4String& name);
    virtual ~GammaMomentumSD();

    virtual void Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    virtual void EndOfEvent(G4HCofThisEvent*);

private:
    std::ofstream outfile;
};
