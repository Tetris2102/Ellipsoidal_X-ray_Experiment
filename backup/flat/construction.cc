#include "construction.hh"
#include "G4GDMLParser.hh"
#include "G4RotationMatrix.hh"
// #include "GammaMomentumSD.cc"
#include "G4SDManager.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Box *solidWorld = new G4Box("solidWorld", 0.2*m, 0.2*m, 0.2*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Load GDML file
    G4GDMLParser parser;
    parser.Read("../gdmlFiles/setup_flat.gdml");  // for flat
    // parser.Read("setup_curved.gdml");  // for curved

    // Retrieve the target's logical volume
    G4LogicalVolume *logicTarget = parser.GetVolume("target"); // Use the correct name from your GDML file

    if (!logicTarget) {
        G4Exception("MyDetectorConstruction::Construct", "InvalidGDML", FatalException, "Target volume not found in GDML file!");
    }

    G4LogicalVolume *logicDetector = parser.GetVolume("detector");

    if (!logicDetector) {
    G4Exception("MyDetectorConstruction::Construct", "InvalidDetector", FatalException, "Detector volume not found!");
    }

    // Assign the sensitive detector
    // G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    // GammaMomentumSD* gammaSD = new GammaMomentumSD("GammaMomentumSD");
    // sdManager->AddNewDetector(gammaSD);
    // logicDetector->SetSensitiveDetector(gammaSD);

    // Define target rotation
    G4RotationMatrix *rotMatrixTarget = new G4RotationMatrix();
    // rotMatrixTarget->rotateZ(90. * deg);  // for setup_curved.gdml
    rotMatrixTarget->rotateY(90. * deg);  // for setup_flat.gdml
    rotMatrixTarget->rotateX(90. * deg);  // for setup_flat.gdml

    // Define detector rotation
    G4RotationMatrix *rotMatrixDetector = new G4RotationMatrix();
    rotMatrixDetector->rotateX(-50. * deg);

    // Place the imported GDML target in the world
    // G4ThreeVector(0, 0, 0) for target in setup_curved.gdml
    // G4ThreeVector(0, 1.*cm, 5.*cm) for target in setup_flat.gdml
    new G4PVPlacement(rotMatrixTarget, G4ThreeVector(0, 1.*cm, 5.*cm), logicTarget, "physTarget", logicWorld, false, 0, true);
    new G4PVPlacement(rotMatrixDetector, G4ThreeVector(0, 2.*cm, 0), logicDetector, "physDetector", logicWorld, false, 0, true);

    return physWorld;
}
