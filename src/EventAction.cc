#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "HistoManager.hh"
#include "G4Cons.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction, PrimaryGeneratorAction* primaryAction, HistoManager* histo)
: G4UserEventAction(),
  fRunAction(runAction),fprimaryAction(primaryAction),
  fHistoManager(histo),
  fEdep(0.)
 {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    

  for (G4int i=0; i<16; i++){
          sumPMT[i] = 0; 
          }

  fEdep = 0.;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{   

  PosX = fprimaryAction->GetPosX();
  PosY = fprimaryAction->GetPosY();
  fHistoManager->out<< std::setprecision(3) << PosX/cm <<"\t" << std::setprecision(3) << PosY/cm << "\t";


	for (G4int i=0; i<16; i++){
	        fHistoManager->out << sumPMT[i] << "\t"; 
	        }
	fHistoManager->out << std::endl;
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);

  //
  fHistoManager->FillNtuple(  PosX/cm, PosY/cm, 
                              sumPMT[0],  sumPMT[1],  sumPMT[2],  sumPMT[3],
                              sumPMT[4],  sumPMT[5],  sumPMT[6],  sumPMT[7],
                              sumPMT[8],  sumPMT[9],  sumPMT[10],  sumPMT[11],
                              sumPMT[12],  sumPMT[13],  sumPMT[14],  sumPMT[15] );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......