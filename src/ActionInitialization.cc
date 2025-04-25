#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"
#include "HistoManager.hh"      

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{

  // Histo manager
  HistoManager*  histo = new HistoManager();  //-----------------

  // Actions
  SetUserAction(new RunAction(histo));  // ---------------------

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{

  // Histo manager
  HistoManager*  histo = new HistoManager();

  // Actions 
  PrimaryGeneratorAction* primaryAction = new PrimaryGeneratorAction; // **************
  SetUserAction(primaryAction); //*************************

  RunAction* runAction = new RunAction(histo);
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction(runAction, primaryAction, histo);  // *********************
  SetUserAction(eventAction);
  
  SetUserAction(new SteppingAction(eventAction));  // *** A way to conect classes
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  return new SteppingVerbose();
}