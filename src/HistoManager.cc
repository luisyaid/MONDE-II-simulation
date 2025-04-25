#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
 : fFactoryOn(false)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh

  out.open("monde2_out.txt");  //  Abrir el Archivo 
  /*
  out << "X(mm)\t"<<"Y(mm)\t"<< "PMT1\t"<< "PMT2\t"<<"PMT3\t"<<"PMT4\t"<<"PMT5\t"   
  << "PMT6\t"<< "PMT7\t"<<"PMT8\t"<<"PMT9\t"<<"PMT10\t"                         
  << "PMT11\t"<< "PMT12\t"<<"PMT13\t"<<"PMT14\t"<<"PMT15\t"<<"PMT16\t"<< std::endl;  
  */

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
      
  // Create directories 
  //analysisManager->SetHistoDirectoryName("histo");
  analysisManager->SetNtupleDirectoryName("ntuple");
    
  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile("monde2_out");
  if (! fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open " 
           << analysisManager->GetFileName() << G4endl;
    return;
  }
  
  // Create histograms.
  // Histogram ids are generated automatically starting from 0.
  // The start value can be changed by:
  // analysisManager->SetFirstHistoId(1);  
  
  // id = 0
  //analysisManager->CreateH1("EAbs","Edep in absorber (MeV)", 100, 0., 800*MeV);
  // id = 1
  //analysisManager->CreateH1("EGap","Edep in gap (MeV)", 100, 0., 100*MeV);
  // id = 2
  //analysisManager->CreateH1("LAbs","trackL in absorber (mm)", 100, 0., 1*m);
  // id = 3
  //analysisManager->CreateH1("LGap","trackL in gap (mm)", 100, 0., 50*cm);

  // Create ntuples.
  // Ntuples ids are generated automatically starting from 0.
  // The start value can be changed by:
  // analysisManager->SetFirstMtupleId(1);  

  // Create 1st ntuple (id = 0)
  analysisManager->CreateNtuple("monde2_ntuple", "PosXY and Photoncounts");
  analysisManager->CreateNtupleDColumn("PosX");  // column id = 0
  analysisManager->CreateNtupleDColumn("PosY");  // column id = 1
  analysisManager->CreateNtupleIColumn("sumPMT1");  // column id = 0
  analysisManager->CreateNtupleIColumn("sumPMT2");  // column id = 1
  analysisManager->CreateNtupleIColumn("sumPMT3"); 
  analysisManager->CreateNtupleIColumn("sumPMT4");
  analysisManager->CreateNtupleIColumn("sumPMT5");
  analysisManager->CreateNtupleIColumn("sumPMT6");
  analysisManager->CreateNtupleIColumn("sumPMT7");
  analysisManager->CreateNtupleIColumn("sumPMT8");
  analysisManager->CreateNtupleIColumn("sumPMT9");
  analysisManager->CreateNtupleIColumn("sumPMT10");
  analysisManager->CreateNtupleIColumn("sumPMT11");
  analysisManager->CreateNtupleIColumn("sumPMT12");
  analysisManager->CreateNtupleIColumn("sumPMT13");
  analysisManager->CreateNtupleIColumn("sumPMT14");
  analysisManager->CreateNtupleIColumn("sumPMT15");
  analysisManager->CreateNtupleIColumn("sumPMT16"); // column id = 15
  analysisManager->FinishNtuple();
  // Create 1st ntuple (id = 0)
  /*analysisManager->CreateNtuple("Ntuple1", "Edep");
  analysisManager->CreateNtupleDColumn("Eabs"); // column Id = 0
  analysisManager->CreateNtupleDColumn("Egap"); // column Id = 1
  analysisManager->FinishNtuple();

  // Create 2nd ntuple (id = 1)
  //    
  analysisManager->CreateNtuple("Ntuple2", "TrackL");
  analysisManager->CreateNtupleDColumn("Labs"); // column Id = 0
  analysisManager->CreateNtupleDColumn("Lgap"); // column Id = 1
  analysisManager->FinishNtuple();*/
  
  fFactoryOn = true;       

 /* G4cout << "\n----> Output file is open in " 
         << analysisManager->GetFileName() << "." 
         << analysisManager->GetFileType() << G4endl;*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{

  out.close();//*********************************** cierro el archivo

  if (! fFactoryOn) return;
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
  analysisManager->Write();
  analysisManager->CloseFile(); 
   
  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
      
  delete G4AnalysisManager::Instance();
  fFactoryOn = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
  analysisManager->FillH1(ih, xbin, weight);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Normalize(G4int ih, G4double fac)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
  G4H1* h1 = analysisManager->GetH1(ih);
  if (h1) h1->scale(fac);
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple( G4double posX, G4double posY,
							   G4int sumPMT1, G4int sumPMT2, G4int sumPMT3, G4int sumPMT4,
                               G4int sumPMT5, G4int sumPMT6, G4int sumPMT7, G4int sumPMT8,
                               G4int sumPMT9, G4int sumPMT10, G4int sumPMT11, G4int sumPMT12,
                               G4int sumPMT13, G4int sumPMT14, G4int sumPMT15, G4int sumPMT16 )
{                
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // fill ntuple (id=0)
  analysisManager->FillNtupleDColumn(0, 0, posX);
  analysisManager->FillNtupleDColumn(0, 1, posY);
  analysisManager->FillNtupleIColumn(0, 2, sumPMT1);
  analysisManager->FillNtupleIColumn(0, 3, sumPMT2);
  analysisManager->FillNtupleIColumn(0, 4, sumPMT3);
  analysisManager->FillNtupleIColumn(0, 5, sumPMT4);
  analysisManager->FillNtupleIColumn(0, 6, sumPMT5);
  analysisManager->FillNtupleIColumn(0, 7, sumPMT6);
  analysisManager->FillNtupleIColumn(0, 8, sumPMT7);
  analysisManager->FillNtupleIColumn(0, 9, sumPMT8);
  analysisManager->FillNtupleIColumn(0, 10, sumPMT9);
  analysisManager->FillNtupleIColumn(0, 11, sumPMT10);
  analysisManager->FillNtupleIColumn(0, 12, sumPMT11);
  analysisManager->FillNtupleIColumn(0, 13, sumPMT12);
  analysisManager->FillNtupleIColumn(0, 14, sumPMT13);
  analysisManager->FillNtupleIColumn(0, 15, sumPMT14);
  analysisManager->FillNtupleIColumn(0, 16, sumPMT15);
  analysisManager->FillNtupleIColumn(0, 17, sumPMT16);
  analysisManager->AddNtupleRow(0);
}  

/*
void HistoManager::FillNtuple2(G4double posX, G4double posY)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // fill ntuple (id=0)
  analysisManager->FillNtupleDColumn(0, 0, posX);
  analysisManager->FillNtupleDColumn(0, 1, posY);
  analysisManager->AddNtupleRow(0);
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void HistoManager::PrintStatistic()
{
  if (! fFactoryOn) return;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
  G4cout << "\n ----> print histograms statistic \n" << G4endl;
  for ( G4int i=0; i<analysisManager->GetNofH1s(); ++i ) {
    G4String name = analysisManager->GetH1Name(i);
    G4H1* h1 = analysisManager->GetH1(i);
    
    G4String unitCategory;
    if (name[0U] == 'E' ) unitCategory = "Energy"; 
    if (name[0U] == 'L' ) unitCategory = "Length";
         // we use an explicit unsigned int type for operator [] argument
         // to avoid problems with windows compiler

    G4cout << name
           << ": mean = " << G4BestUnit(h1->mean(), unitCategory) 
           << " rms = " << G4BestUnit(h1->rms(), unitCategory ) 
           << G4endl;
  }
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


