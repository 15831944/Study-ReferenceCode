// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <map>

#include "Modeldata.generated.h"

/**
*	Model ������ �����ϴ� ����
*	Model ������ �߰��ϰ� �ʹٸ� ���⿡ �߰��ϸ� �ȴ�.
*/
enum class ModelList 
{	
	Dynamic, Static,
	Wall, Floor, Window, Door, Column,
	FixedWindow, SlideWindow, 
	GlassHandrail, BarHandrail,
	FullStair, HollowStair,
	PointLight, SkyLight, SpotLight, 
	View,
	HipRoof, CombinationRoof, FlatRoof, HollowedMansardRoof
};

static std::map<FString, ModelList> ModelName = 
{
	{ "Dynamic", ModelList::Dynamic },
	{ "Static", ModelList::Static },
	{ "Wall", ModelList::Wall },
	{ "Floor", ModelList::Floor },
	{ "Window", ModelList::Window },
	{ "Door", ModelList::Door },
	{ "Column", ModelList::Column },
	{ "Fixedwindow", ModelList::FixedWindow },
	{ "Slidewindow", ModelList::SlideWindow },
	{ "GlassHandrail", ModelList::GlassHandrail },
	{ "BarHandrail", ModelList::BarHandrail },
	{ "PointLight", ModelList::PointLight },
	{ "SkyLight", ModelList::SkyLight },
	{ "SpotLight", ModelList::SpotLight },
	{ "FullStair", ModelList::FullStair },
	{ "HollowStair", ModelList::HollowStair },
	{ "View", ModelList::View },
	{ "HipRoof", ModelList::HipRoof },
	{ "CombinationRoof", ModelList::CombinationRoof },
	{ "FlatRoof", ModelList::FlatRoof },
	{ "HollowedMansardRoof", ModelList::HollowedMansardRoof }
};

USTRUCT()
struct FMaterialInst
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FString part;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FString path;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	UMaterialInterface* material;

	FMaterialInst();
};

USTRUCT()
struct FHole
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FVector2D position;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float length;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float height;

	FHole();	
};


/**
*	�𵨿� ����Ǵ� �����Ͱ� ����, �ߺ� ����Ǵ� ��쵵 ����. 
*	�����ϸ� ����ؼ� �и��ϴ� �� ��õ.
*/
USTRUCT()
struct FModelData
{
public:
	GENERATED_BODY()

	//Common Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FName name = "None";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FString meshType = "None";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FTransform placement = FTransform();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	TArray<FMaterialInst> materials;

	//Static Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FString meshPath;

	//Dynamic Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FVector size;

	//Dynamic Window
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float frame;

	//Extrude Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	TArray<FVector> vertices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	FVector move;

	//Wall Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	TArray<FHole> holes;

	//Rail Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float pitch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float interval;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float height;

	//Light Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float intensity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float red;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float green;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float blue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float innerCone;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float outerCone;

	//Stair Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float stepLength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float stepWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float stepHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float numSteps;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float addToFirstStep;

	//View Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	int32 CameraNumber;

	//HipRoof Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float sideRafter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float mainRafter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float ridgeBoard;
		//roof's height = height

	//FlatRoof data
		//use dynamic model's size var.

	//HollowedMansardRoof
		//externMainRafter = mainRafter
		//externSideRafter = sideRafter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float internMainRafter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|Data")
	float internSideRafter;
		//roof's height = height

	FModelData();

};
