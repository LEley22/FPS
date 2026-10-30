
#include "primaryGeneratorAction.hh"

primaryGeneratorAction::primaryGeneratorAction() //info in here to allow overrun by macro files
{
    ParticleGun = new G4ParticleGun(1); //no of particles per event

     G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName = "gamma";
    G4ParticleDefinition * particle = particleTable->FindParticle("e-");

   //G4ThreeVector momentum(0.,0.,1.); //momentum direction
   G4ThreeVector momentum(0, -0.2422, 0.9702); //1d arc (0, -0.2506, 0.9681)
   //G4ThreeVector momentum(-0.1439, -0.1454, 0.9789); //ross -0.1472, -0.1485, 0.9779
	

    ParticleGun->SetParticleEnergy(70* keV);
    
    ParticleGun->SetParticleMomentumDirection(momentum);
    ParticleGun->SetParticleDefinition(particle);
}

primaryGeneratorAction::~primaryGeneratorAction()
{

    delete ParticleGun;
}

void primaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
    //random number generator over a circle of radius r (where r is number multiplier in R)
    //G4UniformRand creates uniformly random output over interval 0 to 1
    //assumes therefore perfect electron beam
    //G4double R = ((3*mm)*(pow(G4UniformRand(),0.5)));
    //G4double theta = ((2*M_PI)*(G4UniformRand()));  //COMMENTED OUT BUT KEPT IN CASE CHANGE MIND

    //ParticleGun->SetParticlePosition(G4ThreeVector(0,0,-1*m));
    ParticleGun->SetParticlePosition(G4ThreeVector (0, 249.64*mm, -1*m)); //1d arc
    //ParticleGun->SetParticlePosition(G4ThreeVector(146.978*mm, 148.546*mm, -1*m)); //ross
    ParticleGun->GeneratePrimaryVertex(anEvent);
}
