#include "generator.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>
#include <fstream>

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(2);
    eventCounter = 0;
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "e-";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    G4ThreeVector pos(0., 0., 0.);
    G4double theta = 10.0 * deg;

    
    for (G4int i = 0; i < 501; i++)
    {
        G4double phi = (eventCounter * 5.0 * deg) + (i * 1.8 * deg);
        G4double px = std::sin(theta) * std::cos(phi);
        G4double py = std::sin(theta) * std::sin(phi);
        G4double pz = std::cos(theta);
        G4ThreeVector mom(px, py, pz);

        fParticleGun->SetParticlePosition(pos);
        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleMomentum(600. * keV);
        fParticleGun->SetParticleDefinition(particle);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    
    // outfile.close();
    eventCounter++;
}
