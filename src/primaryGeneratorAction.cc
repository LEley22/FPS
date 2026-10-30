
#include "primaryGeneratorAction.hh"

primaryGeneratorAction::primaryGeneratorAction() //info overruns macro files
{
    ParticleGun = new G4ParticleGun(1); //no of particles per event

     G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();

    G4ParticleDefinition * particle = particleTable->FindParticle("e-"); //primary particle electron

   G4ThreeVector momentum(0.,0.,1.); //momentum direction

    ParticleGun->SetParticleEnergy(70* keV); //set beam energy
    
    ParticleGun->SetParticleMomentumDirection(momentum);  //initialise
    ParticleGun->SetParticleDefinition(particle);
}

primaryGeneratorAction::~primaryGeneratorAction()
{

    delete ParticleGun;
}

void primaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
	// Generate random position uniformly within a circle of radius 3 mm
	G4double R = (3*mm) * pow(G4UniformRand(), 0.5);
	G4double theta = (2*M_PI) * G4UniformRand();
	
	// Convert polar coordinates to Cartesian coordinates
	G4double X = R * cos(theta);
	G4double Y = R * sin(theta);
	
	// Set particle starting position
	ParticleGun->SetParticlePosition(G4ThreeVector(X, Y, -1*m));

    ParticleGun->GeneratePrimaryVertex(anEvent);
}
