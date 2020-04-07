#include "G4Material.hh"

#include "G4NistManager.hh"
#include "G4Polyhedra.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Text.hh"
#include "G4VisAttributes.hh"

#include <TObject.h>
#include <TFile.h>
//#include <TH1.h>
//#include <TF1.h>
#include <TList.h>
#include <TTree.h>
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include <RunControl.hh>
#include "MVector.hh"
#include <G4AssemblyVolume.hh>
#include <string>
using namespace std;

class Stilbene {
public:
  G4LogicalVolume* Crystall;
  G4LogicalVolume* Assembly;
  
  G4LogicalVolume* ExternalCover_cylinder;
  G4LogicalVolume* ExternalCover_bottom;
  G4LogicalVolume* ExternalCover_back;
  G4AssemblyVolume* Cover;
  
  Stilbene();
  
  void PlaceCartesian(string name, G4RotationMatrix rotm1,
		      G4ThreeVector pos,  G4LogicalVolume *logicWorld,
		      int CopyNo);
  
  void Place(string name, G4RotationMatrix rotm1, double r, double phi,
	     double theta,  G4LogicalVolume *logicWorld, int CopyNo);
	
};

class LaBr {
public:
  G4LogicalVolume* Crystall;
  G4LogicalVolume* Assembly;
  
  G4LogicalVolume* ExternalCover_cylinder;
  G4LogicalVolume* ExternalCover_bottom;
  G4LogicalVolume* ExternalCover_back;
  G4AssemblyVolume* Cover;
  
  LaBr();
  
  void PlaceCartesian(string name, G4RotationMatrix rotm1,
		      G4ThreeVector pos,  G4LogicalVolume *logicWorld,
		      int CopyNo);
  
  void Place(string name, G4RotationMatrix rotm1, double r, double phi,
	     double theta,  G4LogicalVolume *logicWorld, int CopyNo);
	
};

class Source {
public:
  G4LogicalVolume* ActivSource;
  G4LogicalVolume* SourceHolder;

  G4AssemblyVolume* Cover;

  G4LogicalVolume* Assembly;
  
  Source();
  
  void PlaceCartesian(string name, G4RotationMatrix rotm1,
		      G4ThreeVector pos,  G4LogicalVolume *logicWorld,
		      int CopyNo);
  
  void Place(string name, G4RotationMatrix rotm1, double r, double phi,
	     double theta,  G4LogicalVolume *logicWorld, int CopyNo);
	
};


class ORTEC_GMX30_83_PL_S
{
	public:
	G4LogicalVolume* Crystall;
	//G4LogicalVolume* Cover;
	G4LogicalVolume* LHole;
	G4LogicalVolume* ExternalCover_cylinder;
	G4LogicalVolume* ExternalCover_bottom;
	G4AssemblyVolume* Cover;
	G4Tubs* HPGe;
	G4Tubs* Hole;
	ORTEC_GMX30_83_PL_S();
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
	
};

class B117LeadPlate
{
	public:
	G4LogicalVolume* Plate;
	B117LeadPlate(float x=30*cm,float y=15*cm,float z=2.5*cm);
	B117LeadPlate(string type_of_plate);
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
	G4LogicalVolume* GetPointer();
};
class B117HPGeTable
{
	public:
	G4LogicalVolume* Plate;
	G4LogicalVolume* table_legs[4];
	G4AssemblyVolume* table;
	B117HPGeTable();
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
	
};
class B117ConcreteBlock
{
	public:
	G4LogicalVolume* Block;
	B117ConcreteBlock(float xdim=50/2*cm,float ydim=20/2*cm,float zdim=20/2*cm);
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
};
class Coordinates
{
	public:
	float v_c[3];
	float a[3];
	string order;
	Coordinates(float x,float y,float z,string ord="",float a1=0,float a2=0,float a3=0);
	Coordinates();
	G4ThreeVector GetG4ThreeVector();
	G4RotationMatrix GetG4RotationMatrix();
	G4RotationMatrix* GetPointerToG4RotationMatrix();
	//Coordinates operator = (Coordinates c1);
};
class Shield
{
	public:
	vector<G4LogicalVolume*> Blocks;
	G4AssemblyVolume* shield;
	Shield(vector<Coordinates> g4tf);
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
};
class DiamantBGO
{
	public:
	G4LogicalVolume* Crystall;
	G4LogicalVolume* Assembly;
	//G4LogicalVolume* Cover;
	G4LogicalVolume* ExternalCover_cylinder1;
	G4LogicalVolume* ExternalCover_cylinder2;
	G4LogicalVolume* ExternalCover_bottom;
	G4AssemblyVolume* Cover;
	DiamantBGO();
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
	
};
class B117NaI
{
	public:
	G4LogicalVolume* Crystall;
	G4LogicalVolume* Assembly;
	//G4LogicalVolume* Cover;
	G4LogicalVolume* ExternalCover_hexagonal_prism;
	G4LogicalVolume* ExternalCover_bottom;
	G4AssemblyVolume* Cover;
	B117NaI();
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
	
};
class B117PlywoodSheet
{
	public:
	G4LogicalVolume* Plywood;
	B117PlywoodSheet(float length=150*cm,float width=150*cm,float thickness=2*cm);
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
};

/*class B117Ing27Holder
{
	public:
	B117Ing27Holder();
	G4LogicalVolume* table_legs[4];
	void PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo);
	void Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo);
};*/
