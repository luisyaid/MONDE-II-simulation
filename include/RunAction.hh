#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
//*************************
#include <iostream>
#include <fstream>
//****************************
class G4Run;
class HistoManager;   //--------------------------

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class RunAction : public G4UserRunAction
{
  public:
    RunAction(HistoManager* histo); 
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 

  private:
    HistoManager* fHistoManager; 
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
    
};

#endif
