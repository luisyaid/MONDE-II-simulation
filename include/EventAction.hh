#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class PrimaryGeneratorAction; //**************************
class HistoManager; 

/// Event action class
///

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction, PrimaryGeneratorAction* primaryAction, HistoManager* histo); //*****************************
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    //*****************************************************
    inline void AddCountPMT(G4int NoPMT) { sumPMT[NoPMT] = sumPMT[NoPMT] + 1 ;}
    

    //****************************************************
  private:
    RunAction* fRunAction;
    PrimaryGeneratorAction* fprimaryAction;
    HistoManager* fHistoManager;

    G4double     fEdep;
  //******************
    G4int CopyNumber;
    G4double PosX, PosY;
    G4int sumPMT[16]; 
  //******************  

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
