#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"   // this thing adds the tube
#include "G4PVReplica.hh"
#include "G4MaterialTable.hh"
#include "G4Material.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4MaterialTable.hh"
#include "G4OpticalSurface.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  /*fScoringVolume(0)*/ fLXe_mt(NULL)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 80*cm, env_sizeZ = 420*cm;
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //

// *mod 
  G4Material* world_mat = new G4Material("Vacuum",1.,1.01*g/mole,
                          universe_mean_density,kStateGas,0.1*kelvin,
                          1.e-19*pascal);
  // end mod


  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material   
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     


  //*mod
  G4Material* bc408 = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4ThreeVector posbc408 = G4ThreeVector(0, 0, 0);
  //
  // bc408 -- Shape3
  //
  G4double bc408_r_iner = 0.0*cm, bc408_r_outer = 31.5*cm;
  G4double bc408_height = 5.0*cm;
  G4double bc408_phimin = 0.*deg, bc408_phimax = 360.*deg;

  G4Tubs* cilinderbc408 = 
    new G4Tubs("Shape3",
                bc408_r_iner,    // inner radius
                bc408_r_outer,    // outer radius
                bc408_height,    // height
                bc408_phimin, bc408_phimax);  // segment angles

   G4LogicalVolume* bc408_log =                         
    new G4LogicalVolume(cilinderbc408,    //its solid
                        bc408,            //its material
                        "Shape3L");    //its name

    new G4PVPlacement(0,                       //no rotation
                    posbc408,                //at position
                    bc408_log,             //its logical volume
                    "Shape3P",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //------------------
   
    //
    // *mod
    //
    //***Material properties tables

    // Emission Energy Spectrum
  G4double bc408_Emission_Energy[] = { 2.00*eV, 2.87*eV, 2.90*eV, 3.47*eV };
  const G4int nEntries = sizeof(bc408_Emission_Energy)/sizeof(G4double);

  //    REFRACTIVE INDEX 
  G4double bc408_RIND[]  = { 1.58 , 1.58, 1.58, 1.58 };
  assert(sizeof(bc408_RIND) == sizeof(bc408_Emission_Energy));

  //   ABSORCION (LIGHT ATTENUETION LENGTH)
  G4double bc408_ABSL[]  = { 210.*cm, 210.*cm, 210.*cm, 210.*cm };
  assert(sizeof(bc408_ABSL) == sizeof(bc408_Emission_Energy));

  //  SLOWCOMPONENT
  G4double bc408_ScintilFast[] = { 1.00, 1.00, 1.00, 1.00 };
  assert(sizeof(bc408_ScintilFast) == sizeof(bc408_Emission_Energy));

  //  FASTCOMPONENT
  G4double bc408_ScintilSlow[] = { 1.00, 1.00, 1.00, 1.00 };
  assert(sizeof(bc408_ScintilSlow) == sizeof(bc408_Emission_Energy));


  fLXe_mt = new G4MaterialPropertiesTable();
  fLXe_mt->AddProperty("RINDEX",        bc408_Emission_Energy, bc408_RIND,  nEntries);     // Refractive Index
  fLXe_mt->AddProperty("ABSLENGTH",     bc408_Emission_Energy, bc408_ABSL,  nEntries);     // Light Attenuation length
  fLXe_mt->AddProperty("FASTCOMPONENT", bc408_Emission_Energy, bc408_ScintilFast, nEntries);  // Fast Component
  fLXe_mt->AddProperty("SLOWCOMPONENT", bc408_Emission_Energy, bc408_ScintilSlow, nEntries);  // Slow Component
  

  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD",12800./MeV);  // from ref: Detailed Studies of Light 
  fLXe_mt->AddConstProperty("RESOLUTIONSCALE",2.0);            //       Transportin Optical Components of Particle Detectors
  fLXe_mt->AddConstProperty("FASTTIMECONSTANT",2.1*ns);
  fLXe_mt->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  fLXe_mt->AddConstProperty("YIELDRATIO",0.8);

  bc408->SetMaterialPropertiesTable(fLXe_mt);

  // Set the Birks Constant for the LXe scintillator

  bc408->GetIonisation()->SetBirksConstant(0.111*mm/MeV);  // from ref>> http://dx.doi.org/10.1088/1674-1137/34/7/011
                                                          //          
  //
  // *end mod
  //

  //
  // tube -- Shape4
  //
  G4Material* Si = nist->FindOrBuildMaterial("G4_Si");
  G4ThreeVector postube = G4ThreeVector(0, 0, 0);

  //G4double tube_dPhi= 2.* M_PI*rad;
  G4VSolid* tube =
  new G4Tubs("tube", 31.5*cm, 33.0*cm, 5.0*cm, 0., 2.* M_PI*rad);
  G4LogicalVolume* tube_log =
  new G4LogicalVolume(tube, Si, "tubeL", 0, 0, 0);
  /*G4VPhysicalVolume* tube_phys =*/
  new G4PVPlacement(0,G4ThreeVector(0, 0, 0),tube_log,"tubeP", logicWorld, false, 0, checkOverlaps);

  // dividir el tubo --- diferentes detectores
  G4double divided_tube_dPhi= 2.* M_PI*rad/16.0;
  G4VSolid* divided_tube =
  new G4Tubs("divided_tube", 31.5*cm, 33.0*cm, 5.0*cm,
    -divided_tube_dPhi/2, divided_tube_dPhi);   //  .
  G4LogicalVolume* divided_tube_log =
  new G4LogicalVolume(divided_tube, Si, "div_tubeL", 0, 0, 0);
  //G4VPhysicalVolume* divided_tube_phys =
  new G4PVReplica("divided_tube_phys", divided_tube_log, tube_log,
    kPhi, 16, divided_tube_dPhi,0);

  //* end mod
  
  //
  // *mod
  //

  // Visualization attributes
  G4VisAttributes* bc408VisAtt= new G4VisAttributes(G4Colour::Blue());

  bc408_log ->SetVisAttributes(bc408VisAtt);
  
  //
  // *end mod
  //

 // fScoringVolume = bc408_log;  

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
