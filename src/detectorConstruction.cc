#include "detectorConstruction.hh"
#include "SenDet.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UserLimits.hh"
#include <fstream>
#include <iostream>
#include <string>
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

//G4Array2 detConstruct



detectorConstruction::detectorConstruction()//constructor
{
    Thickness = 6;
    G4RunManager* runManager = G4RunManager::GetRunManager();
    Messenger = new G4GenericMessenger(this, "/detector/", "thickness");
    Messenger->DeclareProperty("thickness", Thickness, "Target thickness");
    runManager->GeometryHasBeenModified();

    DefineMaterials();

}


detectorConstruction::~detectorConstruction() //destructor
{
}


void detectorConstruction::DefineMaterials()
{
    //Manager
    G4NistManager* nist = G4NistManager::Instance();
    //Materials
    air = nist->FindOrBuildMaterial("G4_AIR");
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    Tantalum = nist->FindOrBuildMaterial("G4_Ta");  //tantalum (material)
    Aluminium = nist->FindOrBuildMaterial("G4_Al");  //aluminium (material)
    Titanium = nist->FindOrBuildMaterial("G4_Ti");  //titanium (material)
    Tungsten= nist->FindOrBuildMaterial("G4_W");  //tungsten (material)
    Beryllium = nist->FindOrBuildMaterial("G4_Be");
    Gold = nist->FindOrBuildMaterial("G4_Au");

    //Elements
    Cr = nist->FindOrBuildElement("Cr"); //chromium
    Ni = nist->FindOrBuildElement("Ni");  //nickel
    Mo = nist->FindOrBuildElement("Mo");  //molybdenum
    Mn = nist->FindOrBuildElement("Mn");  //manganese
    O = nist->FindOrBuildElement("O");  //oxygen
    Fe = nist->FindOrBuildElement("Fe");  //iron
    C = nist->FindOrBuildElement("C");  //carbon
    H = nist->FindOrBuildElement("H");  //hydrogen
    Si = nist->FindOrBuildElement("Si");  //hydrogen


    //Mixtures/Compounds etc.
    PMMA = new G4Material("PMMA", 1.19*g/cm3, 3);
    PMMA -> AddElement(C, 5);
    PMMA -> AddElement(O, 2);
    PMMA -> AddElement(H, 8);

    G4double OilDensity = 0.89 * g/cm3;
    Oil = new G4Material("Oil", OilDensity, 2);
    G4int Natoms;
    Oil->AddElement(C, Natoms = 19);
    Oil->AddElement(H, Natoms = 38);

//epoxy

    G4double epoxyDensity = 1.86 * g/cm3;
    epoxy = new G4Material("Epoxy", epoxyDensity, 3);
    epoxy->AddElement(H, Natoms = 19);
    epoxy->AddElement(C, Natoms = 18);
    epoxy->AddElement(O, Natoms = 3);
}


G4VPhysicalVolume * detectorConstruction::Construct()
{

//WORLD CREATION//
    worldSolid = new G4Box("worldSolid", 50*cm, 50*cm, 100.*cm); //name and half size in m

    worldLogic = new G4LogicalVolume(worldSolid,   //call solid
                                     air,         //material to be made of
                                     "worldLogic"); //name

    worldPhysical = new G4PVPlacement(0,    //rotation
                                      G4ThreeVector(0,0,0), //location
                                      worldLogic, //logic volume
                                      "worldPhysical", //name
                                      0, //mother volume (0 as it is mother)
                                      false,
                                      0, //copy number
                                      true); //check overlaps

    // TARGET CREATION
    TargetSolid = new G4Box("TargetSolid", 150*mm, 120*mm, 1.25 * um); //name and half size in m

    TargetLogic = new G4LogicalVolume(TargetSolid,   //call solid
                                       Gold,         //material to be made of
                                       "TargetLogic"); //name

    TargetPhysical = new G4PVPlacement(0,    //rotation
                                        G4ThreeVector(0,0,0*m), //location
                                        TargetLogic, //logic volume
                                        "TargetPhysical", //name
                                        worldLogic, //mother volume (0 as it is mother)
                                        false,
                                        0, //copy number
                                        true); //check overlaps

    PhantomSolid = new G4Box("PhantomSolid", 150*mm, 120*mm, 250 * um); //name and half size in m

    G4cout << "Thickness is " << Thickness << G4endl;

    PhantomLogic = new G4LogicalVolume(PhantomSolid,   //call solid
                                      PMMA,         //material to be made of
                                      "PhantomLogic"); //name

    PhantomPhysical = new G4PVPlacement(0,    //rotation
                                       G4ThreeVector(0,0,251.25*um), //location
                                       PhantomLogic, //logic volume
                                       "PhantomPhysical", //name
                                       worldLogic, //mother volume (0 as it is mother)
                                       false,
                                       0, //copy number
                                       true); //check overlaps

    FilterSolid = new G4Box("FilterSolid", 150*mm, 120*mm, 1.25 * mm); //name and half size in m

    G4cout << "Thickness is " << Thickness << G4endl;

    FilterLogic = new G4LogicalVolume(FilterSolid,   //call solid
                                       Aluminium,         //material to be made of
                                       "FilterLogic"); //name

    FilterPhysical = new G4PVPlacement(0,    //rotation
                                        G4ThreeVector(0,0,1.75125*mm), //location
                                        FilterLogic, //logic volume
                                        "FilterPhysical", //name
                                        worldLogic, //mother volume (0 as it is mother)
                                        false,
                                        0, //copy number
                                        true); //check overlaps




//DETECTOR CREATION
    detSolid = new G4Box("detSolid", 20*cm, 20*cm, 0.5*mm); //name and half size in m
    //to match ipioni (which is 43 x 43 bin with 1cm/pixel you need 43/2 cm widths)


    detLogic = new G4LogicalVolume(detSolid,   //call solid
                                   vacuum,         //material to be made of
                                   "detLogic"); //name

    G4ThreeVector DetPosition = G4ThreeVector(0.,0.,50*mm);
    detPhysical = new G4PVPlacement(0,    //rotation
                                    DetPosition, //location
                                    detLogic, //logic volume
                                    "detPhysical", //name
                                    worldLogic, //mother volume
                                    false,
                                    0, //copy number
                                    true); //check overlaps

//VIS ATTRIBUTES (FOR UI)

    G4VisAttributes* visAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,1.0)); //detector is cyan
    visAtt1->SetForceSolid(true);
    detLogic->SetVisAttributes(visAtt1);

    G4VisAttributes* visAtt2 = new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //target is blue
    visAtt2->SetForceSolid(true);
    PhantomLogic->SetVisAttributes(visAtt2);

    return worldPhysical;
}

void detectorConstruction::ConstructSDandField()
{
    SenDetClass *senDetA  = new SenDetClass("SensitiveDetector");
    detLogic -> SetSensitiveDetector(senDetA);
}
