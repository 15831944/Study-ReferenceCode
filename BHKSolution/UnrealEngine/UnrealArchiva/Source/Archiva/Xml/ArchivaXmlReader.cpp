// Fill out your copyright notice in the Description page of Project Settings.

#include "Archiva.h"
#include "Xml/ArchivaXmlReader.h"

UArchivaXmlReader::UArchivaXmlReader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	data = FModelData();
	start = FVector(0);
	end = FVector(0);
}

/*Control �Լ�*/
bool UArchivaXmlReader::ReadXml(class ArchivaGameMode* mode, FString filepath)
{
	this->project = mode;
	this->path = filepath;

	xmlFile = new FXmlFile(*filepath);
	if (xmlFile == nullptr) {
		UE_LOG(MyError, Error, TEXT("UArchivaXmlReader::UArchivaXmlReader(ArchivaGameMode* proj, FString filepath) - Failed to Read XML file."))
		return false;
	}

	//��Ʈ�� �����ϴ����� Ȯ��
	FXmlNode* root = xmlFile->GetRootNode(); //Root ���� Architecture
	if(root == nullptr){
		UE_LOG(MyError, Error, TEXT("UArchivaXmlReader::ReadXML() - No root node."));
		return false;
	}
	
	const TArray<FXmlNode*> NodeList = root->GetChildrenNodes();
	for(int i=0; i < NodeList.Num(); i++)
	{
		FXmlNode* child = NodeList[i];
		FString tagname = child->GetTag();
		//������ ���մ���ó��
		if (tagname.Equals("Room")) { CreateARoom(child); }
		else { UE_LOG(MyLog, Warning, TEXT("Unregistered Tag! - %s"), *tagname); }
	}

	return true;
}

/*Read List*/
void UArchivaXmlReader::CreateARoom(FXmlNode* ARoom) 
{
	const TArray<FXmlNode*> ComponentList = ARoom->GetChildrenNodes();
	for (int i = 0; i < ComponentList.Num(); i++) {
		FXmlNode* child = ComponentList[i];
		FString tagname = ComponentList[i]->GetTag();
		//�������� ���մ��� ó��
		if (tagname.Equals("Walls")) { ReadWalls(child); }
		else if (tagname.Equals("Wall")) { CreateAWall(child); }
		else if (tagname.Equals("Windows")) { ReadWindows(child); }
		else if (tagname.Equals("Slidewindow")) { CreateASlideWindow(child); }
		else if (tagname.Equals("Fixedwindow")) { CreateAFixedWindow(child); }
		else if (tagname.Equals("Statics")) { ReadStatics(child); }
		else if (tagname.Equals("Static") || tagname.Equals("Column") || tagname.Equals("Door") || tagname.Equals("Window")) { CreateAStatic(child); }
		else if (tagname.Equals("Floors")) { ReadFloors(child); }
		else if (tagname.Equals("Floor")) { CreateAFloor(child); }
		else if (tagname.Equals("GlassHandrail")) { CreateAGlassHandrail(child); }
		else if (tagname.Equals("BarHandrail")) { CreateABarHandrail(child); }
		else if (tagname.Equals("PointLight")) { CreateAPointLight(child); }
		else if (tagname.Equals("SkyLight")) { CreateASkyLight(child); }
		else if (tagname.Equals("SpotLight")) { CreateASpotLight(child); }
		else if (tagname.Equals("FullStair")) { CreateAFullStair(child); }
		else if (tagname.Equals("HollowStair")) { CreateAHollowStair(child); }
		else if (tagname.Equals("View")) { CreateAView(child); }
		else if (tagname.Equals("HipRoof")) { CreateAHipRoof(child); }
		else if (tagname.Equals("FlatRoof")) { CreateAFlatRoof(child); }
		else if (tagname.Equals("HollowedMansardRoof")) { CreateAHollowedMansardRoof(child); }
		else { UE_LOG(MyLog, Warning, TEXT("Unregistered Tag! - %s"), *tagname); }
	}
}

void UArchivaXmlReader::ReadStatics(FXmlNode* Statics)
{
	const TArray<FXmlNode*> staticList = Statics->GetChildrenNodes();
	for (int i = 0; i < staticList.Num(); i++) {
		CreateAStatic(staticList[i]);
	}
}
void UArchivaXmlReader::ReadWalls(FXmlNode* Walls)
{
	const TArray<FXmlNode*> wallList = Walls->GetChildrenNodes();
	for (int i = 0; i < wallList.Num(); i++) {
		CreateAWall(wallList[i]);
	}
}
void UArchivaXmlReader::ReadFloors(FXmlNode* Floors)
{
	const TArray<FXmlNode*> floorList = Floors->GetChildrenNodes();
	for (int i = 0; i < floorList.Num(); i++) {
		CreateAFloor(floorList[i]);
	}
}
void UArchivaXmlReader::ReadWindows(FXmlNode* Windows) 
{
	const TArray<FXmlNode*> winList = Windows->GetChildrenNodes();
	for (int i = 0; i < winList.Num(); i++) {
		if (winList[i]->GetTag().Equals("Slidewindow")) {
			CreateASlideWindow(winList[i]);
		}
		else if (winList[i]->GetTag().Equals("Fixedwindow")) {
			CreateAFixedWindow(winList[i]);
		}
	}
}

/*Create List*/
void UArchivaXmlReader::CreateAStatic(FXmlNode* AStatic)
{
	//Static Ÿ���� �´��� Ȯ��
	if(IsModel(AStatic->GetTag()))
	{
		data.name = FName(*AStatic->GetContent());
		data.meshType = AStatic->GetTag();

		//Location ó��
		ApplyLocation(AStatic->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AStatic->FindChildNode("Rotation"));

		data.meshPath = AStatic->FindChildNode("Mesh")->GetContent();

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAWall(FXmlNode* AWall)
{
	//���� ��尡 ��¥ wall���� üũ
	if(IsModel(AWall->GetTag())){
		data.name = FName(*AWall->GetContent());
		data.meshType = AWall->GetTag();

		//���� start ������ �Է¹޴´�.
		FXmlNode* startNode = AWall->FindChildNode("Start");
		if (startNode != nullptr) {
			start.X = FCString::Atof(*startNode->FindChildNode("x")->GetContent());
			start.Y = FCString::Atof(*startNode->FindChildNode("y")->GetContent());
			start.Z = FCString::Atof(*startNode->FindChildNode("z")->GetContent());
		}
		data.placement.SetLocation(start);

		//���� End ������ �Է¹޴´�.
		FXmlNode* endNode = AWall->FindChildNode("End");
		if (endNode != nullptr) {
			end.X = FCString::Atof(*endNode->FindChildNode("x")->GetContent());
			end.Y = FCString::Atof(*endNode->FindChildNode("y")->GetContent());
			end.Z = FCString::Atof(*endNode->FindChildNode("z")->GetContent());
		}

		//���� Start ������ End������ Ȱ���Ͽ� ���� ���̸� ���Ѵ�.
		data.size.X = getLengthFromTwoPoints(start, end);

		//���� ���⸦ ���Ѵ�.
		FRotator rotation = getAngleFromTwoPoints(start, end);
		data.placement.SetRotation(rotation.Quaternion());
		
		//ApplyRotation(AWall->FindChildNode("Rotation"));

		//���� �β��� ���Ѵ�.
		data.size.Y = FCString::Atof(*AWall->FindChildNode("Width")->GetContent());
		data.size.Z = FCString::Atof(*AWall->FindChildNode("Height")->GetContent());

		//���� ������ Hole�� ���Ѵ�.
		FXmlNode* holeNodes = AWall->FindChildNode("Holes");
		if(holeNodes != nullptr) 
		{
			const TArray<FXmlNode*> holeList = holeNodes->GetChildrenNodes();
			for (int i = 0; i < holeList.Num(); i++)
			{
				if (holeList[i]->GetTag().Equals("Hole"))
				{
					FHole hole = FHole();
					hole.position.X = FCString::Atof(*holeList[i]->FindChildNode("x")->GetContent());
					hole.position.Y = FCString::Atof(*holeList[i]->FindChildNode("y")->GetContent());
					hole.length = FCString::Atof(*holeList[i]->FindChildNode("l")->GetContent());
					hole.height = FCString::Atof(*holeList[i]->FindChildNode("h")->GetContent());
					data.holes.Push(hole);
				}
			}
		}

		//���� ������ material�� ���Ѵ�.
		ApplyMaterials(AWall->FindChildNode("Materials"));
		
		//�𵨻���
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateASlideWindow(FXmlNode* ASlidwin){
	//SlideWindow Ÿ���� �´��� Ȯ��
	if (IsModel(ASlidwin->GetTag())) {
		data.name = FName(*ASlidwin->GetContent());
		data.meshType = ASlidwin->GetTag();

		//Location ó��
		ApplyLocation(ASlidwin->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(ASlidwin->FindChildNode("Rotation"));
		//Size ó��
		ApplySize(ASlidwin->FindChildNode("Size"));

		//Frame ó��
		data.frame = FCString::Atof(*ASlidwin->FindChildNode("Frame")->GetContent());

		//Material ó��
		ApplyMaterials(ASlidwin->FindChildNode("Materials"));

		//�𵨻���
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAFixedWindow(FXmlNode* AFixedwin){
	//FixedWindow Ÿ���� �´��� Ȯ��
	if (IsModel(AFixedwin->GetTag())) {
		data.name = FName(*AFixedwin->GetContent());
		data.meshType = AFixedwin->GetTag();

		//Location ó��
		ApplyLocation(AFixedwin->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AFixedwin->FindChildNode("Rotation"));
		//Size ó��
		ApplySize(AFixedwin->FindChildNode("Size"));
		//Frame ó��
		data.frame = FCString::Atof(*AFixedwin->FindChildNode("Frame")->GetContent());
		//Material ó��
		ApplyMaterials(AFixedwin->FindChildNode("Materials"));

		//�𵨻���
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAFloor(FXmlNode* AFloor)
{
	if (IsModel(AFloor->GetTag())) {
		data.name = FName(*AFloor->GetContent());
		data.meshType = AFloor->GetTag();

		//Location ó��
		ApplyLocation(AFloor->FindChildNode("Location"));

		FXmlNode* vertNodes = AFloor->FindChildNode("Vertices");
		if (vertNodes != nullptr) {
			const TArray<FXmlNode*> vertList = vertNodes->GetChildrenNodes();
			for (int i = 0; i < vertList.Num(); i++)
			{
				if (vertList[i]->GetTag().Equals("Vertice"))
				{
					FVector vert = FVector();
					vert.X = FCString::Atof(*vertList[i]->FindChildNode("x")->GetContent());
					vert.Y = FCString::Atof(*vertList[i]->FindChildNode("y")->GetContent());
					vert.Z = FCString::Atof(*vertList[i]->FindChildNode("z")->GetContent());
					data.vertices.Push(vert);
				}
					
			}
		}
		else { UE_LOG(MyLog, Log, TEXT("Floor does not have vertices!")); }

		FXmlNode* moveNode = AFloor->FindChildNode("Move");
		if (moveNode != nullptr)
		{
			data.move.X = FCString::Atof(*moveNode->FindChildNode("x")->GetContent());
			data.move.Y = FCString::Atof(*moveNode->FindChildNode("y")->GetContent());
			data.move.Z = FCString::Atof(*moveNode->FindChildNode("z")->GetContent());
		}
		else { UE_LOG(MyLog, Log, TEXT("Floor does not have move!")); }
		ApplyMaterials(AFloor->FindChildNode("Materials"));

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAGlassHandrail(FXmlNode * Arail)
{
	if(IsModel(Arail->GetTag()))
	{
		data.name = FName(*Arail->GetContent());
		data.meshType = Arail->GetTag();

		FXmlNode* startNode = Arail->FindChildNode("Start");
		if (startNode != nullptr) {
			start.X = FCString::Atof(*startNode->FindChildNode("x")->GetContent());
			start.Y = FCString::Atof(*startNode->FindChildNode("y")->GetContent());
			start.Z = FCString::Atof(*startNode->FindChildNode("z")->GetContent());
		}
		data.placement.SetLocation(start);

		FXmlNode* endNode = Arail->FindChildNode("End");
		if (endNode != nullptr) {
			end.X = FCString::Atof(*endNode->FindChildNode("x")->GetContent());
			end.Y = FCString::Atof(*endNode->FindChildNode("y")->GetContent());
			end.Z = FCString::Atof(*endNode->FindChildNode("z")->GetContent());
		}

		data.size.X = getLengthFromTwoPoints(start, end);

		FRotator rotation = getAngleFromTwoPoints(start, end);
		data.pitch = rotation.Pitch;
		rotation.Pitch = 0;
		data.placement.SetRotation(rotation.Quaternion());

		FXmlNode* intervalNode = Arail->FindChildNode("Interval");
		if(intervalNode != nullptr) {
			data.interval = FCString::Atof(*intervalNode->GetContent());
		}
	
		FXmlNode* heightNode = Arail->FindChildNode("Height");
		if (heightNode != nullptr) {
			data.height = FCString::Atof(*heightNode->GetContent());
		}

		ApplyMaterials(Arail->FindChildNode("Materials"));
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateABarHandrail(FXmlNode * Arail)
{
	if (IsModel(Arail->GetTag()))
	{
		data.name = FName(*Arail->GetContent());
		data.meshType = Arail->GetTag();

		FXmlNode* startNode = Arail->FindChildNode("Start");
		if (startNode != nullptr) {
			start.X = FCString::Atof(*startNode->FindChildNode("x")->GetContent());
			start.Y = FCString::Atof(*startNode->FindChildNode("y")->GetContent());
			start.Z = FCString::Atof(*startNode->FindChildNode("z")->GetContent());
		}
		data.placement.SetLocation(start);

		FXmlNode* endNode = Arail->FindChildNode("End");
		if (endNode != nullptr) {
			end.X = FCString::Atof(*endNode->FindChildNode("x")->GetContent());
			end.Y = FCString::Atof(*endNode->FindChildNode("y")->GetContent());
			end.Z = FCString::Atof(*endNode->FindChildNode("z")->GetContent());
		}

		data.size.X = getLengthFromTwoPoints(start, end);

		FRotator rotation = getAngleFromTwoPoints(start, end);
		data.pitch = rotation.Pitch;
		rotation.Pitch = 0;
		data.placement.SetRotation(rotation.Quaternion());

		FXmlNode* intervalNode = Arail->FindChildNode("Interval");
		if (intervalNode != nullptr) {
			data.interval = FCString::Atof(*intervalNode->GetContent());
		}

		FXmlNode* heightNode = Arail->FindChildNode("Height");
		if (heightNode != nullptr) {
			data.height = FCString::Atof(*heightNode->GetContent());
		}

		ApplyMaterials(Arail->FindChildNode("Materials"));
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAPointLight(FXmlNode * APointLight)
{
	if (IsModel(APointLight->GetTag()))
	{
		data.name = FName(*APointLight->GetContent());
		data.meshType = APointLight->GetTag();

		//Location ó��
		ApplyLocation(APointLight->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(APointLight->FindChildNode("Rotation"));
		
		data.intensity = FCString::Atof(*APointLight->FindChildNode("Intensity")->GetContent());

		FXmlNode* colorNode = APointLight->FindChildNode("Color");
		if(colorNode != nullptr)
		{
			data.red = FCString::Atof(*colorNode->FindChildNode("r")->GetContent());
			data.green = FCString::Atof(*colorNode->FindChildNode("g")->GetContent());
			data.blue = FCString::Atof(*colorNode->FindChildNode("b")->GetContent());
		}

		if(APointLight->FindChildNode("Mesh") != nullptr)
		{
			data.meshPath = APointLight->FindChildNode("Mesh")->GetContent();
		}
		
		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateASkyLight(FXmlNode * ASkyLight)
{
	if (IsModel(ASkyLight->GetTag()))
	{
		data.name = FName(*ASkyLight->GetContent());
		data.meshType = ASkyLight->GetTag();

		//Location ó��
		ApplyLocation(ASkyLight->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(ASkyLight->FindChildNode("Rotation"));

		data.intensity = FCString::Atof(*ASkyLight->FindChildNode("Intensity")->GetContent());

		FXmlNode* colorNode = ASkyLight->FindChildNode("Color");
		if (colorNode != nullptr)
		{
			data.red = FCString::Atof(*colorNode->FindChildNode("r")->GetContent());
			data.green = FCString::Atof(*colorNode->FindChildNode("g")->GetContent());
			data.blue = FCString::Atof(*colorNode->FindChildNode("b")->GetContent());
		}

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateASpotLight(FXmlNode * ASpotLight)
{
	if (IsModel(ASpotLight->GetTag()))
	{
		data.name = FName(*ASpotLight->GetContent());
		data.meshType = ASpotLight->GetTag();

		//Location ó��
		ApplyLocation(ASpotLight->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(ASpotLight->FindChildNode("Rotation"));

		data.intensity = FCString::Atof(*ASpotLight->FindChildNode("Intensity")->GetContent());

		FXmlNode* colorNode = ASpotLight->FindChildNode("Color");
		if (colorNode != nullptr)
		{
			data.red = FCString::Atof(*colorNode->FindChildNode("r")->GetContent());
			data.green = FCString::Atof(*colorNode->FindChildNode("g")->GetContent());
			data.blue = FCString::Atof(*colorNode->FindChildNode("b")->GetContent());
		}

		data.innerCone = FCString::Atof(*ASpotLight->FindChildNode("InnerConeAngle")->GetContent());
		data.outerCone = FCString::Atof(*ASpotLight->FindChildNode("OuterConeAngle")->GetContent());

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAFullStair(FXmlNode * AStair)
{
	if (IsModel(AStair->GetTag()))
	{
		data.name = FName(*AStair->GetContent());
		data.meshType = AStair->GetTag();

		//Location ó��
		ApplyLocation(AStair->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AStair->FindChildNode("Rotation"));

		data.numSteps = FCString::Atof(*AStair->FindChildNode("StepNumber")->GetContent());

		data.stepLength = FCString::Atof(*AStair->FindChildNode("StepLength")->GetContent());
		data.stepWidth = FCString::Atof(*AStair->FindChildNode("StepWidth")->GetContent());
		data.stepHeight = FCString::Atof(*AStair->FindChildNode("StepHeight")->GetContent());

		if(AStair->FindChildNode("Foundation") != nullptr)
			data.addToFirstStep = FCString::Atof(*AStair->FindChildNode("Foundation")->GetContent());

		ApplyMaterials(AStair->FindChildNode("Materials"));

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAHollowStair(FXmlNode * AStair)
{
	if (IsModel(AStair->GetTag()))
	{
		data.name = FName(*AStair->GetContent());
		data.meshType = AStair->GetTag();

		//Location ó��
		ApplyLocation(AStair->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AStair->FindChildNode("Rotation"));

		data.numSteps = FCString::Atof(*AStair->FindChildNode("StepNumber")->GetContent());

		data.stepLength = FCString::Atof(*AStair->FindChildNode("StepLength")->GetContent());
		data.stepWidth = FCString::Atof(*AStair->FindChildNode("Stepwidth")->GetContent());
		data.stepHeight = FCString::Atof(*AStair->FindChildNode("StepHeight")->GetContent());

		ApplyMaterials(AStair->FindChildNode("Materials"));

		project->SpawnModel(data);
		data = FModelData();
	}
}


void UArchivaXmlReader::CreateAView(FXmlNode* AView)
{
	if (IsModel(AView->GetTag()))
	{
		data.name = FName(*AView->GetContent());
		data.meshType = AView->GetTag();

		//Location ó��
		ApplyLocation(AView->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AView->FindChildNode("Rotation"));

		data.CameraNumber = FCString::Atof(*AView->FindChildNode("CameraNumber")->GetContent());

		project->SpawnModel(data);
		data = FModelData();
	}
}

void UArchivaXmlReader::CreateAHipRoof(FXmlNode* AHipRoof)
{
	if (IsModel(AHipRoof->GetTag()))
	{
		data.name = FName(*AHipRoof->GetContent());
		data.meshType = AHipRoof->GetTag();

		//Location ó��
		ApplyLocation(AHipRoof->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AHipRoof->FindChildNode("Rotation"));

		data.height = FCString::Atof(*AHipRoof->FindChildNode("RoofHeight")->GetContent());
		data.sideRafter = FCString::Atof(*AHipRoof->FindChildNode("SideRafter")->GetContent());
		data.mainRafter = FCString::Atof(*AHipRoof->FindChildNode("MainRafter")->GetContent());
		data.ridgeBoard = FCString::Atof(*AHipRoof->FindChildNode("RidgeBoard")->GetContent());

		ApplyMaterials(AHipRoof->FindChildNode("Materials"));

		project->SpawnModel(data);
		data = FModelData();
	}
}
void UArchivaXmlReader::CreateAFlatRoof(FXmlNode * AFlatRoof)
{
	if (IsModel(AFlatRoof->GetTag()))
	{
		data.name = FName(*AFlatRoof->GetContent());
		data.meshType = AFlatRoof->GetTag();

		//Location ó��
		ApplyLocation(AFlatRoof->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(AFlatRoof->FindChildNode("Rotation"));

		data.size.Z = FCString::Atof(*AFlatRoof->FindChildNode("RoofHeight")->GetContent());
		data.size.Y = FCString::Atof(*AFlatRoof->FindChildNode("SideRafter")->GetContent());
		data.size.X = FCString::Atof(*AFlatRoof->FindChildNode("MainRafter")->GetContent());

		ApplyMaterials(AFlatRoof->FindChildNode("Materials"));

		project->SpawnModel(data);
		data = FModelData();
	}
}

void UArchivaXmlReader::CreateAHollowedMansardRoof(FXmlNode * HollowedMansardRoof)
{
	if (IsModel(HollowedMansardRoof->GetTag()))
	{
		data.name = FName(*HollowedMansardRoof->GetContent());
		data.meshType = HollowedMansardRoof->GetTag();

		//Location ó��
		ApplyLocation(HollowedMansardRoof->FindChildNode("Location"));
		//Rotation ó��
		ApplyRotation(HollowedMansardRoof->FindChildNode("Rotation"));
		//Material ó��
		ApplyMaterials(HollowedMansardRoof->FindChildNode("Materials"));

		//Ư���� Param �ޱ�
		data.height = FCString::Atof(*HollowedMansardRoof->FindChildNode("RoofHeight")->GetContent());
		data.sideRafter = FCString::Atof(*HollowedMansardRoof->FindChildNode("ExternSideRafter")->GetContent());
		data.mainRafter = FCString::Atof(*HollowedMansardRoof->FindChildNode("ExternMainRafter")->GetContent());
		data.internSideRafter = FCString::Atof(*HollowedMansardRoof->FindChildNode("InternSideRafter")->GetContent());
		data.internMainRafter = FCString::Atof(*HollowedMansardRoof->FindChildNode("InternMainRafter")->GetContent());

		//����!
		project->SpawnModel(data);
		data = FModelData();
	}
}


/*Apply List*/
void UArchivaXmlReader::ApplyLocation(FXmlNode* loc){
	if (loc != nullptr) {
		FVector location = data.placement.GetLocation();
		location.X = FCString::Atof(*loc->FindChildNode("x")->GetContent());
		location.Y = FCString::Atof(*loc->FindChildNode("y")->GetContent());
		location.Z = FCString::Atof(*loc->FindChildNode("z")->GetContent());
		data.placement.SetLocation(location);
	}
}

void UArchivaXmlReader::ApplyRotation(FXmlNode* rot) {
	if (rot != nullptr) {
		FRotator rotation = data.placement.GetRotation().Rotator();
		rotation.Roll = FCString::Atof(*rot->FindChildNode("r")->GetContent());
		rotation.Pitch = FCString::Atof(*rot->FindChildNode("p")->GetContent());
		rotation.Yaw = FCString::Atof(*rot->FindChildNode("y")->GetContent());
		data.placement.SetRotation(rotation.Quaternion());
	}
}

void UArchivaXmlReader::ApplySize(FXmlNode* sz) {
	if(sz != nullptr) {
		data.size.X = FCString::Atof(*sz->FindChildNode("l")->GetContent());
		data.size.Y = FCString::Atof(*sz->FindChildNode("w")->GetContent());
		data.size.Z = FCString::Atof(*sz->FindChildNode("h")->GetContent());
	}
}

void UArchivaXmlReader::ApplyMaterials(FXmlNode* mat) 
{
	if(mat != nullptr) 
	{
		const TArray<FXmlNode*> matList = mat->GetChildrenNodes();
		for (int i = 0; i < matList.Num(); i++) 
		{
			if (matList[i]->GetTag().Equals("Material")) 
			{
				FMaterialInst info = FMaterialInst();
				info.part = matList[i]->FindChildNode("part")->GetContent();
				info.path = matList[i]->FindChildNode("path")->GetContent();
				info.material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *info.path));
				if (info.material == nullptr) {UE_LOG(MyLog, Error, TEXT("Material does not exist on %s"), *info.path)}
				data.materials.Push(info);
			}
		}
	}
}

bool IsModel(FString ElementName)
{
	std::map<FString, ModelList>::iterator it;
	it = ModelName.find(ElementName);
	if (it != ModelName.end()) {
		return true;
	}
	return false;
}

float getLengthFromTwoPoints(FVector start, FVector end)
{
	float x = start.X - end.X;
	float y = start.Y - end.Y;
	return sqrtf((x*x) + (y*y));
}

FRotator getAngleFromTwoPoints(FVector start, FVector end)
{
	FRotator rotation = FRotator();

	float deltaX = end.X - start.X;
	float deltaY = end.Y - start.Y;
	float deltaZ = end.Z - start.Z;

	rotation.Roll = 0;
	rotation.Pitch =atan2f(deltaZ, sqrtf(deltaX*deltaX + deltaY*deltaY)) * 180 / PI;
	rotation.Yaw = (atan2f(deltaY, deltaX) * 180 / PI);

	return rotation;
}

