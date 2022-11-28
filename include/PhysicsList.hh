#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"

class PhysicsListMessenger;

class PhysicsList : public G4VUserPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();

public:
  virtual void ConstructParticle();
  virtual void ConstructProcess();

  virtual void SetCuts();

  void ConstructDecay();
  void ConstructEM();
  void ConstructOp();
  void ConstructNeutron();

  void SetVerbose(G4int);
  void SetNbOfPhotonsCerenkov(G4int);
  void SetThermalPhysics(G4bool flag) {fThermal = flag;};  
 
private:
  G4int                fVerboseLebel;
  PhysicsListMessenger* fMessenger;
  G4int fMaxNumPhotonStep;
  G4bool  fThermal;
};

#endif /* PhysicsList_h */
