#ifndef GammaTrackingAction_h
#define GammaTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include <fstream>

class GammaTrackingAction : public G4UserTrackingAction
{
public:
    GammaTrackingAction();
    virtual ~GammaTrackingAction();
    
    virtual void PreUserTrackingAction(const G4Track*);
    
private:
    std::ofstream outputFile;
};

#endif