#include "PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleSource(0), 
  fEnvelopeBox(0),

  x0(0*cm), y0(0*cm), z0(-7.0*cm) //Define the particle source position
{
  fParticleSource  = new G4GeneralParticleSource();
  // Set position for the sake of the Javier Code
  fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(x0, y0, z0)); // Particle position
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Generate the primary vertex
  fParticleSource->GeneratePrimaryVertex(anEvent);

  // Invert the direction of the generated particle to point towards the positive z-direction
  G4PrimaryVertex* primaryVertex = anEvent->GetPrimaryVertex();
  if (primaryVertex) {
    G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
    if (primaryParticle) {
      G4ThreeVector momentumDirection = primaryParticle->GetMomentumDirection();
      primaryParticle->SetMomentumDirection(G4ThreeVector(momentumDirection.x(), momentumDirection.y(), -momentumDirection.z()));
    }
  }
// Redefine paticle source position for the sake of the anger histograms
  fParticleSource->SetParticlePosition(G4ThreeVector(x0,y0,z0));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......