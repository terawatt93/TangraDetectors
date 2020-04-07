#include "Detectors.hh"

Stilbene::Stilbene(){
  
  G4NistManager* Nist = G4NistManager::Instance();
  G4Material* Stilbene_mat = Nist->FindOrBuildMaterial("G4_STILBENE");
  G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
  G4Material* Air = Nist->FindOrBuildMaterial("G4_Galactic");
	
  G4Tubs *CrystallG = new G4Tubs("Crystall",0*mm,76/2*mm,50/2*mm,0,360*deg); 
	
  // main case cylinder
  G4Tubs *Cover1=new G4Tubs("Cover1",2+76/2*mm,83.2/2*mm,90/2*mm,0,360*deg);
  // bottom and back
  G4Tubs *Cover2=new G4Tubs("Cover2",0*mm,2+76/2*mm,1*mm,0,360*deg);
  	
  //solid volume which contains all elements of the detector, it is used to
  //"group" all parts of the detector
  G4Tubs *WholeVolume = new G4Tubs("Whole",0*mm,83.2/2*mm,90/2*mm,0,360*deg);
  	
  //create logical volume (shape, visualisation attributes,material)
  Crystall = new G4LogicalVolume(CrystallG,Stilbene_mat,"Stilbene");
 	
  //main case cylinder
  ExternalCover_cylinder = new G4LogicalVolume(Cover1,Al,"Cover1");
  //bottom
  ExternalCover_bottom = new G4LogicalVolume(Cover2,Al,"Cover2");
  //back
  ExternalCover_back = new G4LogicalVolume(Cover2,Al,"Cover3");
 	
  Assembly = new G4LogicalVolume(WholeVolume,Air,"WholeVolume"); 	
}

void Stilbene::PlaceCartesian(string name, G4RotationMatrix rotm1,
			      G4ThreeVector pos,  G4LogicalVolume *logicWorld,
			      int CopyNo){
  //(color,R,G,B,Vis in %)
  G4VisAttributes *CoverColor = new G4VisAttributes(G4Colour(0,1,0,0.2));
  G4VisAttributes *CrystallColor = new G4VisAttributes(G4Colour(0,0,1));
  G4VisAttributes *WholeVolumeVis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
  WholeVolumeVis->SetVisibility(false); 
  Assembly->SetVisAttributes(WholeVolumeVis);

  // position of the main cylinder inside the G4AssemblyVolume
  G4ThreeVector pos2 = G4ThreeVector(0,0,0);
  // position of the bottom inside the G4AssemblyVolume
  G4ThreeVector pos3 = G4ThreeVector(0,0,-(90/2-1)*mm);
  // position of the back tap inside the G4AssemblyVolume
  G4ThreeVector pos4 = G4ThreeVector(0,0,(90/2-1)*mm);
  
  // position of the crystall inside the Assembly
  G4ThreeVector posDet = G4ThreeVector(0,0,-18*mm);
	
  G4RotationMatrix rotm2;
	
  //add visualisation parameters 
  ExternalCover_cylinder->SetVisAttributes(CoverColor);
  ExternalCover_bottom->SetVisAttributes(CoverColor);
  ExternalCover_back->SetVisAttributes(CoverColor);
  Crystall->SetVisAttributes(CrystallColor);
	
  //Collect all parts of the case
  Cover = new G4AssemblyVolume(ExternalCover_cylinder,pos2,&rotm2);
  Cover->AddPlacedVolume(ExternalCover_bottom, pos3,&rotm2);
  Cover->AddPlacedVolume(ExternalCover_back, pos4,&rotm2);
  //And put them to the assembly
  Cover->MakeImprint(Assembly,pos2, &rotm2, 0, true);
  	
  //Place crystall to the assembly
  new G4PVPlacement(G4Transform3D(rotm2,posDet),Crystall,name.c_str(),Assembly,
		    false,CopyNo,true);
  
  //Place everything to the mother volume (in our case, wolrld)
  new G4PVPlacement(G4Transform3D(rotm1,pos),Assembly,name.c_str(),logicWorld,
		    false,1,true);
}

void Stilbene::Place(string name, G4RotationMatrix rotm1, double r, double phi,
		     double theta, G4LogicalVolume *logicWorld, int CopyNo){
  
  double x, y, z;
  x=r*sin(theta)*cos(phi);
  y=r*sin(theta)*sin(phi);
  z=r*cos(theta);
  G4ThreeVector pos = G4ThreeVector(x,y,z);
  PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}

LaBr::LaBr(){
  
  G4NistManager* Nist = G4NistManager::Instance();
  G4Material* LaBr_mat = Nist->FindOrBuildMaterial("G4_LANTHANUM_OXYBROMIDE");
  G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
  G4Material* Air = Nist->FindOrBuildMaterial("G4_Galactic");
	
  G4Tubs *CrystallG = new G4Tubs("Crystall",0*mm,76.2/2*mm,76.2/2*mm,0,360*deg); 
	
  // main case cylinder
  G4Tubs *Cover1=new G4Tubs("Cover1",1+76.2/2*mm,82.5/2*mm,123.5/2*mm,0,360*deg);
  // bottom and back
  G4Tubs *Cover2=new G4Tubs("Cover2",0*mm,1+76.2/2*mm,0.5*mm,0,360*deg);
  	
  //solid volume which contains all elements of the detector, it is used to
  //"group" all parts of the detector
  G4Tubs *WholeVolume = new G4Tubs("Whole",0*mm,82.5/2*mm,123.5/2*mm,0,360*deg);
  	
  //create logical volume (shape, visualisation attributes,material)
  Crystall = new G4LogicalVolume(CrystallG,LaBr_mat,"LaBr");
 	
  //main case cylinder
  ExternalCover_cylinder = new G4LogicalVolume(Cover1,Al,"Cover1");
  //bottom
  ExternalCover_bottom = new G4LogicalVolume(Cover2,Al,"Cover2");
  //back
  ExternalCover_back = new G4LogicalVolume(Cover2,Al,"Cover3");
 	
  Assembly = new G4LogicalVolume(WholeVolume,Air,"WholeVolume"); 	
}

void LaBr::PlaceCartesian(string name, G4RotationMatrix rotm1,
			  G4ThreeVector pos,  G4LogicalVolume *logicWorld,
			  int CopyNo){
  //(color,R,G,B,Vis in %)
  G4VisAttributes *CoverColor = new G4VisAttributes(G4Colour(1,1,1,0.2));
  G4VisAttributes *CrystallColor = new G4VisAttributes(G4Colour(0,0,1));
  G4VisAttributes *WholeVolumeVis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
  WholeVolumeVis->SetVisibility(false); 
  Assembly->SetVisAttributes(WholeVolumeVis);

  // position of the main cylinder inside the G4AssemblyVolume
  G4ThreeVector pos2 = G4ThreeVector(0,0,0);
  // position of the bottom inside the G4AssemblyVolume
  G4ThreeVector pos3 = G4ThreeVector(0,0, -(123.5/2-0.5)*mm);
  // position of the back tap inside the G4AssemblyVolume
  G4ThreeVector pos4 = G4ThreeVector(0,0, (123.5/2-0.5)*mm);
  
  // position of the crystall inside the Assembly
  G4ThreeVector posDet = G4ThreeVector(0,0,-21.65*mm);
  //G4ThreeVector posDet = G4ThreeVector(0,0,-(76.2/2)*mm);
	
  G4RotationMatrix rotm2;
	
  //add visualisation parameters 
  ExternalCover_cylinder->SetVisAttributes(CoverColor);
  ExternalCover_bottom->SetVisAttributes(CoverColor);
  ExternalCover_back->SetVisAttributes(CoverColor);
  Crystall->SetVisAttributes(CrystallColor);
	
  //Collect all parts of the case
  Cover = new G4AssemblyVolume(ExternalCover_cylinder,pos2,&rotm2);
  Cover->AddPlacedVolume(ExternalCover_bottom, pos3,&rotm2);
  Cover->AddPlacedVolume(ExternalCover_back, pos4,&rotm2);
  //And put them to the assembly
  Cover->MakeImprint(Assembly,pos2, &rotm2, 0, true);
  	
  //Place crystall to the assembly
  new G4PVPlacement(G4Transform3D(rotm2,posDet),Crystall,name.c_str(),Assembly,
		    false,CopyNo,true);
  
  //Place everything to the mother volume (in our case, wolrld)
  new G4PVPlacement(G4Transform3D(rotm1,pos),Assembly,name.c_str(),logicWorld,
		    false,1,true);
}

void LaBr::Place(string name, G4RotationMatrix rotm1, double r, double phi,
		 double theta, G4LogicalVolume *logicWorld, int CopyNo){
  
  double x, y, z;
  x=r*sin(theta)*cos(phi);
  y=r*sin(theta)*sin(phi);
  z=r*cos(theta);
  G4ThreeVector pos = G4ThreeVector(x,y,z);
  PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}

Source::Source(){
  
  G4NistManager* Nist = G4NistManager::Instance();
  G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
  G4Material* Air = Nist->FindOrBuildMaterial("G4_Galactic");

  G4String name, symbol;
  G4double a, z;  
  G4double density = 1.39*g/cm3;
  G4int nel=3;
  
  a = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
  a = 12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
  a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);
  
  G4Material* Kapton = new G4Material(name="Kapton", density, nel);
  Kapton->AddElement(elO,2);
  Kapton->AddElement(elC,5);
  Kapton->AddElement(elH,4);

  G4Tubs *SourceGeom = new G4Tubs("ActivSource",0*mm,18./2*mm,1./2*mm,0,360*deg);
  G4Tubs *Cover1 = new G4Tubs("Cover1",18./2*mm,25./2*mm,3./2*mm,0,360*deg);
  
  //solid volume which contains all elements of the source, it is used to
  //"group" all parts of the source
  G4Tubs *WholeVolume = new G4Tubs("Whole",0*mm,25./2*mm,3./2*mm,0,360*deg);
  	
  //create logical volume (shape, visualisation attributes,material)
  ActivSource = new G4LogicalVolume(SourceGeom,Kapton,"Source");
 	
  //main case cylinder
  SourceHolder = new G4LogicalVolume(Cover1,Al,"Cover1");
  
  Assembly = new G4LogicalVolume(WholeVolume,Air,"WholeVolume"); 	
}

void Source::PlaceCartesian(string name, G4RotationMatrix rotm1,
			    G4ThreeVector pos,  G4LogicalVolume *logicWorld,
			    int CopyNo){
  //(color,R,G,B,Vis in %)
  G4VisAttributes *CoverColor = new G4VisAttributes(G4Colour(0,0,0));
  G4VisAttributes *SourceColor = new G4VisAttributes(G4Colour(1,1,0));
  G4VisAttributes *WholeVolumeVis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
  WholeVolumeVis->SetVisibility(false); 
  Assembly->SetVisAttributes(WholeVolumeVis);

  // position of the crystall inside the Assembly
  G4ThreeVector posSource = G4ThreeVector(0,0,0);
  	
  G4RotationMatrix rotm2;
	
  //add visualisation parameters 
  ActivSource->SetVisAttributes(SourceColor);
  SourceHolder->SetVisAttributes(CoverColor);
	
  //Collect all parts of the case
  Cover = new G4AssemblyVolume(ActivSource,posSource,&rotm2);
  Cover->AddPlacedVolume(SourceHolder, posSource,&rotm2);
  
  //And put them to the assembly
  Cover->MakeImprint(Assembly, posSource, &rotm2, 0, true);
  	
  //Place crystall to the assembly
  new G4PVPlacement(G4Transform3D(rotm2,posSource),ActivSource,name.c_str(),Assembly,
		    false,CopyNo,true);
  
  //Place everything to the mother volume (in our case, wolrld)
  new G4PVPlacement(G4Transform3D(rotm1,pos),Assembly,name.c_str(),logicWorld,
		    false,CopyNo,true);
}

void Source::Place(string name, G4RotationMatrix rotm1, double r, double phi,
		   double theta, G4LogicalVolume *logicWorld, int CopyNo){
  
  double x, y, z;
  x=r*sin(theta)*cos(phi);
  y=r*sin(theta)*sin(phi);
  z=r*cos(theta);
  G4ThreeVector pos = G4ThreeVector(x,y,z);
  PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}

ORTEC_GMX30_83_PL_S::ORTEC_GMX30_83_PL_S()
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* mat = Nist->FindOrBuildMaterial("G4_Ge");
	G4Material* vacuum = Nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
	HPGe = new G4Tubs("HPGe", 0*mm, 57.5*mm/2, 66.6*mm/2, 0, 360*deg);
	Hole = new G4Tubs("Hole", 0*mm, 9.9*mm/2, 58.9*mm/2, 0, 360*deg);
	G4Tubs *Cover1=new G4Tubs("Cover1", 40*mm, 41.2*mm,  66.6*mm/2+3*mm, 0, 360*deg);
	G4Tubs *Cover2=new G4Tubs("Cover2", 0*mm, 41.2*mm, 0.4*mm, 0, 360*deg);
	Crystall = new G4LogicalVolume(HPGe,mat,"HPGe"); 
	LHole = new G4LogicalVolume(Hole,vacuum,"Hole"); 
	ExternalCover_cylinder = new G4LogicalVolume(Cover1,Al,"Cover1"); 
	ExternalCover_bottom = new G4LogicalVolume(Cover2,Al,"Cover2"); 
	
	G4VisAttributes *VisAttHole = new G4VisAttributes(G4Colour(0,0,0));
	G4VisAttributes *VisAttCrystall = new G4VisAttributes(G4Colour(0,0,1));
	LHole->SetVisAttributes(VisAttHole);
	Crystall->SetVisAttributes(VisAttCrystall);
	cout<<"HPGE_Constructor\n";
}
void ORTEC_GMX30_83_PL_S::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	G4ThreeVector pos2 = G4ThreeVector(0,0,0);
	G4ThreeVector pos3 = G4ThreeVector(0,0, 66.6*mm/2+3.4*mm);
	G4RotationMatrix rotm2;
	Cover=new G4AssemblyVolume(ExternalCover_cylinder,pos2,&rotm2);
	
	Cover->AddPlacedVolume(ExternalCover_bottom, pos3,&rotm2);
	
	Cover->MakeImprint (logicWorld,pos, &rotm1, 0, true);
	new G4PVPlacement(G4Transform3D(rotm2,G4ThreeVector(0,0,-3.85*mm)),LHole,name.c_str(),Crystall,false,CopyNo,true);
	new G4PVPlacement(G4Transform3D(rotm1,pos),Crystall,name.c_str(),logicWorld,false,CopyNo,true);
}

void ORTEC_GMX30_83_PL_S::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
B117LeadPlate::B117LeadPlate(float x,float y,float z)
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* mat = Nist->FindOrBuildMaterial("G4_Pb");
	G4Box *p=new G4Box("LeadPlate",x/2,y/2,z/2);
	Plate = new G4LogicalVolume(p,mat,"LeadPlate");
	G4VisAttributes *VisAttPlate = new G4VisAttributes(G4Colour(0.4,0.4,0.4));
	Plate->SetVisAttributes(VisAttPlate);
}
B117LeadPlate::B117LeadPlate(string type_of_plate)
{
	if(type_of_plate=="plate")
	{
		B117LeadPlate();
	}
	else if(type_of_plate=="brick")
	{
		B117LeadPlate(20*cm,10*cm,4.5*cm);
	}
	
}
void B117LeadPlate::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	new G4PVPlacement(G4Transform3D(rotm1,pos),Plate,name.c_str(),logicWorld,false,CopyNo,true);
}
void B117LeadPlate::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
G4LogicalVolume* B117LeadPlate::GetPointer()
{
	return Plate;
}
B117HPGeTable::B117HPGeTable()
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
	G4Material* Fe = Nist->FindOrBuildMaterial("G4_Fe");
	G4Box *plate=new G4Box("Plate",98/2*cm,57/2*cm,5/2*mm);
	G4Tubs *leg=new G4Tubs("Cover2", 2.1*cm, 2.42*cm, 44.5*cm/2, 0, 360*deg); 
	Plate=new G4LogicalVolume(plate,Al,"Plate");
	G4VisAttributes *VisAttLegs = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes *VisAttPlate = new G4VisAttributes(G4Colour(1,1,1));
	Plate->SetVisAttributes(VisAttPlate);
	for(unsigned int i=0;i<4;i++)
	{
		table_legs[i]=new G4LogicalVolume(leg,Fe,"Tube");
		table_legs[i]->SetVisAttributes(VisAttLegs);
	}	
}
void B117HPGeTable::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	G4ThreeVector pos2 = G4ThreeVector(0,0,0);
	G4ThreeVector pos_l[4];
	name+="";//тоько чтобы убрать warning
	pos_l[0] = G4ThreeVector(39*cm,18.5*cm, (-22.25-0.5)*cm);
	pos_l[1] = G4ThreeVector(-39*cm,18.5*cm, (-22.25-0.5)*cm);
	pos_l[2] = G4ThreeVector(39*cm,-18.5*cm, (-22.25-0.5)*cm);
	pos_l[3] = G4ThreeVector(-39*cm,-18.5*cm, (-22.25-0.5)*cm);
	G4RotationMatrix rotm2;
	table = new G4AssemblyVolume(Plate,pos2,&rotm2);
	for(unsigned int i=0;i<4;i++)
	{
		table -> AddPlacedVolume(table_legs[i], pos_l[i],&rotm2);
	}
	table->MakeImprint(logicWorld,pos, &rotm1,CopyNo,true);	
	
}
void B117HPGeTable::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
B117ConcreteBlock::B117ConcreteBlock(float xdim,float ydim,float zdim)
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* Concrete = Nist->FindOrBuildMaterial("G4_CONCRETE");
	G4Box *block = new G4Box("block",xdim,ydim,zdim);
	Block = new G4LogicalVolume(block,Concrete,"block"); 
}
void B117ConcreteBlock::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	new G4PVPlacement(G4Transform3D(rotm1,pos),Block,name.c_str(),logicWorld,false,CopyNo,true);
}
void B117ConcreteBlock::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
Coordinates::Coordinates()
{
	v_c[0]=1;
	v_c[1]=1;
	v_c[2]=1;
}
Coordinates::Coordinates(float x,float y,float z,string ord,float a1,float a2,float a3)
{
	G4RotationMatrix r;
	v_c[0]=x;
	v_c[1]=y;
	v_c[2]=z;
	order=ord;
	a[0]=a1;
	a[1]=a2;
	a[2]=a3;
}

G4ThreeVector Coordinates::GetG4ThreeVector()
{
	G4ThreeVector vv(v_c[0],v_c[1],v_c[2]);
	return vv;
}

G4RotationMatrix Coordinates::GetG4RotationMatrix()
{
	G4RotationMatrix mtx;
	for(unsigned int i=0;i<order.size();i++)
	{
		if((order[i]=='x')||(order[i]=='X'))
		{
			mtx.rotateX(a[i]);
		}
		else if((order[i]=='y')||(order[i]=='Y'))
		{
			mtx.rotateY(a[i]);
		}
		else if((order[i]=='z')||(order[i]=='Z'))
		{
			mtx.rotateZ(a[i]);
		}
	}
	return mtx;
}
G4RotationMatrix* Coordinates::GetPointerToG4RotationMatrix()
{
	G4RotationMatrix *mtx=new G4RotationMatrix();
	for(unsigned int i=0;i<order.size();i++)
	{
		if((order[i]=='x')||(order[i]=='X'))
		{
			mtx->rotateX(a[i]);
		}
		else if((order[i]=='y')||(order[i]=='Y'))
		{
			mtx->rotateY(a[i]);
		}
		else if((order[i]=='z')||(order[i]=='Z'))
		{
			mtx->rotateZ(a[i]);
		}
	}
	return mtx;
}
Shield::Shield(vector<Coordinates> g4tf)
{
	B117LeadPlate *p=new B117LeadPlate();
	if(g4tf.size()>0)
	{
		G4ThreeVector v=g4tf[0].GetG4ThreeVector();
		shield = new G4AssemblyVolume(p->GetPointer(),v,g4tf[0].GetPointerToG4RotationMatrix());
	}
	for(unsigned int i=1;i<g4tf.size();i++)
	{
	//	B117LeadPlate *p=new B117LeadPlate();
		G4ThreeVector v=g4tf[i].GetG4ThreeVector();
		shield->AddPlacedVolume(p->GetPointer(),v,g4tf[i].GetPointerToG4RotationMatrix());
	}	
}
void Shield::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	name+="";
	shield->MakeImprint(logicWorld,pos, &rotm1,CopyNo,true);	
}
void Shield::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
DiamantBGO::DiamantBGO()
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* BGO_mat = Nist->FindOrBuildMaterial("G4_BGO");
	G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
	G4Material* Air = Nist->FindOrBuildMaterial("G4_Galactic");
	
	G4Tubs *CrystallG = new G4Tubs("Crystall", 0*mm, 77.5/2*mm,  65/2*mm, 0, 360*deg);
	
	G4Tubs *Cover1=new G4Tubs("Cover1", 42.5*mm, 44.5*mm,  255*mm/2, 0, 360*deg);//главный цилиндр оболочки
	G4Tubs *Cover2=new G4Tubs("Cover2", 42.5*mm, 43.1*mm, 23/2*mm, 0, 360*deg);//цилиндр дна
	G4Tubs *Cover3=new G4Tubs("Cover3", 0*mm, 43.1*mm, 1*mm, 0, 360*deg);//дно
	
	G4Tubs *WholeVolume=new G4Tubs("Whole", 0*mm, 90/2*mm, 281/2*mm, 0, 360*deg);//полный объем
	
	Crystall = new G4LogicalVolume(CrystallG,BGO_mat,"BGO"); 
	
	ExternalCover_cylinder1 = new G4LogicalVolume(Cover1,Al,"Cover1"); 
	ExternalCover_cylinder2 = new G4LogicalVolume(Cover2,Al,"Cover2"); 
	ExternalCover_bottom = new G4LogicalVolume(Cover3,Al,"Cover3"); 
	
	Assembly = new G4LogicalVolume(WholeVolume,Air,"WholeVolume");
	
}
void DiamantBGO::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	G4VisAttributes *CoverColor = new G4VisAttributes(G4Colour(1,0.6,0));
	G4VisAttributes *CrystallColor = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes *WholeVolumeVis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
	WholeVolumeVis->SetVisibility(false); 
	Assembly->SetVisAttributes(WholeVolumeVis);

	G4ThreeVector pos2 = G4ThreeVector(0,0,-6.25*mm);
	G4ThreeVector pos3 = G4ThreeVector(0,0, (139-6.25)*mm);
	G4ThreeVector pos4 = G4ThreeVector(0,0, (151.5-6.25)*mm);
	G4ThreeVector pos5 = G4ThreeVector(0,0, (111-12.5)*mm);
	
	G4RotationMatrix rotm2;
	
	ExternalCover_cylinder1->SetVisAttributes(CoverColor);
	ExternalCover_cylinder2->SetVisAttributes(CoverColor);
	ExternalCover_bottom->SetVisAttributes(CoverColor);
	Crystall->SetVisAttributes(CrystallColor);
	
	Cover=new G4AssemblyVolume(ExternalCover_cylinder1,pos2,&rotm2);
	Cover->AddPlacedVolume(ExternalCover_cylinder2, pos3,&rotm2);
	Cover->AddPlacedVolume(ExternalCover_bottom, pos4,&rotm2);
	Cover->MakeImprint (Assembly,pos2, &rotm2, 0, true);
	//Cover->MakeImprint (logicWorld,pos, &rotm1, 0, true);
	
	new G4PVPlacement(G4Transform3D(rotm2,pos5),Crystall,name.c_str(),Assembly,false,CopyNo,true);
	new G4PVPlacement(G4Transform3D(rotm1,pos),Assembly,name.c_str(),logicWorld,false,1,true);
}
void DiamantBGO::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
B117NaI::B117NaI()
{
	G4NistManager* Nist = G4NistManager::Instance();
	G4Material* NaI_mat = Nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	G4Material* Al = Nist->FindOrBuildMaterial("G4_Al");
	
	G4int	numSide=6;
	G4int	numZPlanes=2;
	double  zPlane[] = {-100*mm,100*mm};
	double  rInner[] = {0*mm,0*mm};
	double  rOuter[] = {39*mm,39*mm};

	G4Polyhedra* solidNaI = new G4Polyhedra("NaI",0*deg,360*deg,numSide,numZPlanes,zPlane,rInner,rOuter );	
	Crystall = new G4LogicalVolume(solidNaI,NaI_mat,"NaI");
	
	double  zPlaneCover1[] = {-100*mm,100*mm};
	double  rInnerCover1[] = {40*mm,40*mm};
	double  rOuterCover1[] = {42.5*mm,42.5*mm};
		
	G4Polyhedra* solidPolyhedra = new G4Polyhedra("Cover",0*deg,360*deg,numSide,numZPlanes,zPlaneCover1,rInnerCover1,rOuterCover1);	
	ExternalCover_hexagonal_prism = new G4LogicalVolume(solidPolyhedra,Al,"Cover");
	
	double  zPlaneCover2[] = {-0.75*mm,0.75*mm};
	double  rInnerCover2[] = {0*mm,0*mm};
	double  rOuterCover2[] = {42.5*mm,42.5*mm};
	
	G4Polyhedra* solidPolyhedraBottom = new G4Polyhedra("Cover",0*deg,360*deg,numSide,numZPlanes,zPlaneCover2,rInnerCover2,rOuterCover2);	
	ExternalCover_bottom = new G4LogicalVolume(solidPolyhedraBottom,Al,"Cover");
	
	double  zPlaneCover3[] = {-104*mm,104*mm};
	double  rInnerCover3[] = {0*mm,0*mm};
	double  rOuterCover3[] = {43*mm,43*mm};
	
	G4Polyhedra *WholeVolume = new G4Polyhedra("Cover",0*deg,360*deg,numSide,numZPlanes,zPlaneCover3,rInnerCover3,rOuterCover3);	
	G4Material* Air = Nist->FindOrBuildMaterial("G4_Galactic");
	Assembly = new G4LogicalVolume(WholeVolume,Air,"WholeVolume");
}
void B117NaI::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	G4VisAttributes *CoverColor = new G4VisAttributes(G4Colour(0.3,0.3,0.3));
	G4VisAttributes *CrystallColor = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes *WholeVolumeVis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
	WholeVolumeVis->SetVisibility(false); 
	Assembly->SetVisAttributes(WholeVolumeVis);
	Crystall->SetVisAttributes(CrystallColor);
	ExternalCover_hexagonal_prism->SetVisAttributes(CoverColor);
	ExternalCover_bottom->SetVisAttributes(CoverColor);
	
	G4ThreeVector pos2 = G4ThreeVector(0,0,0*mm);
	G4ThreeVector pos3 = G4ThreeVector(0,0, 101.5*mm);
	G4RotationMatrix rotm2;
	
	Cover=new G4AssemblyVolume(ExternalCover_hexagonal_prism,pos2,&rotm2);
	Cover->AddPlacedVolume(ExternalCover_bottom, pos3,&rotm2);	
	Cover->MakeImprint (Assembly,pos2, &rotm2, 0, true);
	//Cover->MakeImprint (logicWorld,pos2, &rotm2, 0, true);
	new G4PVPlacement(G4Transform3D(rotm2,pos2),Crystall,name.c_str(),Assembly,false,CopyNo,true);
	new G4PVPlacement(G4Transform3D(rotm1,pos),Assembly,name.c_str(),logicWorld,false,1,true);
}
void B117NaI::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
B117PlywoodSheet::B117PlywoodSheet(float length,float width,float thickness)
{
	G4Element* H = new G4Element("Hydrogen","H" ,1.,1.00794*g/mole);
	G4Element* C  = new G4Element("Carbon", "C",   6. , 12.011*g/mole);
	G4Element* O  = new G4Element("Oxygen","O",8.,16.00*g/mole);
	G4Box *sheet = new G4Box("sheet",length/2,width/2,thickness/2);
	G4Material* wood = new G4Material("wood",0.9*g/cm3,3);
	wood->AddElement(H,4);
	wood->AddElement(O,1);
	wood->AddElement(C,2);
	Plywood=new G4LogicalVolume(sheet,wood,"Plywood");
	G4VisAttributes *WoodColor = new G4VisAttributes(G4Colour(0.5,0.36,0));
	Plywood->SetVisAttributes(WoodColor);
}
void B117PlywoodSheet::PlaceCartesian(string name, G4RotationMatrix rotm1, G4ThreeVector pos,  G4LogicalVolume *logicWorld,int CopyNo)
{
	new G4PVPlacement(G4Transform3D(rotm1,pos),Plywood,name.c_str(),logicWorld,false,CopyNo,true);
}
void B117PlywoodSheet::Place(string name, G4RotationMatrix rotm1, double r, double phi, double theta,  G4LogicalVolume *logicWorld,int CopyNo)
{
	double x, y, z;
	x=r*sin(theta)*cos(phi);
	y=r*sin(theta)*sin(phi);
	z=r*cos(theta);
	G4ThreeVector pos = G4ThreeVector(x,y,z);
	PlaceCartesian(name,rotm1,pos,logicWorld,CopyNo);
}
