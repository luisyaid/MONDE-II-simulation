#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle source.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
  const G4GeneralParticleSource* GetParticleGun() const { return fParticleSource; }
    //
    inline G4double GetPosX(){return x0;}//Define a mrthod to ask X
    inline G4double GetPosY(){return y0;}//Define a mrthod to ask Y
    //

  private:
    G4GeneralParticleSource*  fParticleSource; 
    G4Box* fEnvelopeBox;
    G4double x0, y0, z0;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
