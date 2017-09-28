// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/Modeldata.h"

#include "ArchivaGameMode.h"
#include "Runtime/XmlParser/Public/XmlFile.h"
#include "Runtime/XmlParser/Public/XmlNode.h"

#include "ArchivaXmlReader.generated.h"

/**
*	@class UArchivaXmlReader
*	XML�� �Էµ� �����͸� �а� �𵨿� �ݿ��ϴ� ���
*/
UCLASS()
class ARCHIVA_API UArchivaXmlReader : public UObject
{
GENERATED_BODY()

public:
	//������ ������ ���� ó���ϴ� �Լ�
	void CreateARoom(FXmlNode* ARoom);

	//�߻����� �������� ó���ϴ� �Լ�
	
	void ReadStatics(FXmlNode* statics);
	void ReadWalls(FXmlNode* walls);
	void ReadWindows(FXmlNode* windows);
	void ReadFloors(FXmlNode* floors);

	//��ü���� ���� �����ϴ� �Լ�
	void CreateAStatic(FXmlNode* AStatic);
	void CreateAWall(FXmlNode* AWall);
	void CreateASlideWindow(FXmlNode* ASlidwin);
	void CreateAFixedWindow(FXmlNode* AFixedwin);
	void CreateAFloor(FXmlNode* AFloor);
	void CreateAGlassHandrail(FXmlNode* Arail);
	void CreateABarHandrail(FXmlNode* Arail);
	void CreateAPointLight(FXmlNode* APointLight);
	void CreateASkyLight(FXmlNode* ASkyLight);
	void CreateASpotLight(FXmlNode* ASpotLight);
	void CreateAFullStair(FXmlNode* AStair);
	void CreateAHollowStair(FXmlNode* AStair);
	void CreateAView(FXmlNode* AView);
	void CreateAHipRoof(FXmlNode* AHipRoof);
	void CreateAFlatRoof(FXmlNode* AFlatRoof);
	void CreateAHollowedMansardRoof(FXmlNode* HollowedMansardRoof);

	//�𵨳��� �����ϴ� ��ƮŸ���� �����ϴ� �Լ�
	//((�ڵ��� ���뼺�� ���̱� ���� ����))
	void ApplyLocation(FXmlNode* loc);
	void ApplyRotation(FXmlNode* rot);
	void ApplySize(FXmlNode* sz);
	void ApplyMaterials(FXmlNode* mat);


	class ArchivaGameMode* project;
	class FXmlFile* xmlFile;
	FString path;

	FModelData data;
	FVector start;
	FVector end;

	UArchivaXmlReader(const FObjectInitializer& ObjectInitializer);
	
	/**
	*	������ xml������ �о���� ����
	*	@param mode ������Ʈ ���
	*	@param filepath XML ���� ��ġ
	*/
	UFUNCTION(BlueprintCallable, Category = "Xml")
	bool ReadXml(class ArchivaGameMode* mode, FString filepath);

};

/**
*	ModelData�� ��ϵǾ� �ִ� ������ Ȯ���ϴ� �Լ�
*/
static bool IsModel(FString ElementName);

/*
*	start������ end������ Ȱ���Ͽ�, Length�� ���
*/
static float getLengthFromTwoPoints(FVector start, FVector end);

/**
*	start������ end������ Ȱ���Ͽ�, Angle�� ���
*/
static FRotator getAngleFromTwoPoints(FVector start, FVector end);