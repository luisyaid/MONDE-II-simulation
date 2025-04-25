#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "g4root.hh"
#include <iostream>
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();
   std::ofstream out; //********************* declare the variable ofstream type

    void Book();
    void Save();
    void Normalize(G4int id, G4double fac); 
    void FillNtuple( G4double posX, G4double posY,
                      G4int sumPMT1, G4int sumPMT2, G4int sumPMT3, G4int sumPMT4,
                      G4int sumPMT5, G4int sumPMT6, G4int sumPMT7, G4int sumPMT8,
                      G4int sumPMT9, G4int sumPMT10, G4int sumPMT11, G4int sumPMT12,
                      G4int sumPMT13, G4int sumPMT14, G4int sumPMT15, G4int sumPMT16 );     
    
  private:
    G4bool fFactoryOn;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
