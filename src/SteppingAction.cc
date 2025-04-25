#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4StepPoint.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4VProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  
  G4StepPoint* point1 = step->GetPreStepPoint();
  G4StepPoint* point2 = step->GetPostStepPoint();

  G4ThreeVector pos1 = point1->GetPosition();
  G4ThreeVector pos2 = point2->GetPosition();

  const G4VTouchable* touch2 = point2->GetTouchable();

  G4VPhysicalVolume* volume1 = point1->GetPhysicalVolume();  
  G4VPhysicalVolume* volume2 = point2->GetPhysicalVolume();   
 
  G4ParticleDefinition* particleType = step->GetTrack()->GetDefinition();

  if( volume1->GetName() == "Shape3P" && volume2->GetName() == "divided_tube_phys" &&
   particleType == G4OpticalPhoton::OpticalPhotonDefinition()){
    G4int copyNo = touch2->GetCopyNumber(0);
    //G4cout << "Numero de Copia: "<< copyNo << G4endl;

    fEventAction->AddCountPMT(copyNo); 
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  G4Track* theTrack = step->GetTrack();

//2da via
       G4String procName = point2->GetProcessDefinedStep()->GetProcessName();
     if(theTrack->GetParentID() == 0 && procName == "hadElastic"){
          G4cout << "->Position PostStep : "<< point2->GetPosition() << G4endl; 
          G4cout << "->Position theTrack : "<< theTrack->GetPosition() << G4endl; 
     }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......