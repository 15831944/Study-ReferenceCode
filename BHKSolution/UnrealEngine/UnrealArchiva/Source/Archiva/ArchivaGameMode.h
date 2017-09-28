// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/Modeldata.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/GameMode.h"
#include "ArchivaGameMode.generated.h"

/**
* @class ArchivaGameMode
* �������Ʈ������ Model�� Ȱ���� �� �ֵ���, GameMode�� ����� ���´�.
* ���ο� ���� �����ϰ� ���� ���⿡ �߰��ؾ� �������Ʈ�� Ȱ���� �� �ִ�.
*/

UCLASS()
class ARCHIVA_API ArchivaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	/*�������Ʈ�� ȣȯ�ϱ� ���� �𵨸��*/
	//Primitive
	TSubclassOf<class AMyModel> BP_MyModel;
	TSubclassOf<class AMyModel> BP_DynamicModel;
	TSubclassOf<class AMyModel> BP_StaticModel;

	//Basic
	TSubclassOf<class AMyModel> BP_FloorModel;
	TSubclassOf<class AMyModel> BP_WallModel;

	//Roof
	TSubclassOf<class AMyModel> BP_HipRoofModel;
	TSubclassOf<class AMyModel> BP_CombinationRoofModel;
	TSubclassOf<class AMyModel> BP_FlatRoofModel;
	TSubclassOf<class AMyModel> BP_HollowedMansardRoofModel;

	//Handrail
	TSubclassOf<class AMyModel> BP_BarHandrailModel;
	TSubclassOf<class AMyModel> BP_GlassHandrailModel;

	//Window
	TSubclassOf<class AMyModel> BP_FixedWindowModel;
	TSubclassOf<class AMyModel> BP_SlideWindowModel;

	//Stair
	TSubclassOf<class AMyModel> BP_FullStairModel;
	TSubclassOf<class AMyModel> BP_HollowStairModel;

	//Light
	TSubclassOf<class AMyModel> BP_PointLightModel;
	TSubclassOf<class AMyModel> BP_SkyLightModel;
	TSubclassOf<class AMyModel> BP_SpotLightModel;

	//ETC
	TSubclassOf<class AMyModel> BP_ColumnModel;
	TSubclassOf<class AMyModel> BP_DoorModel;
	TSubclassOf<class AMyModel> BP_WindowModel;

	//Camera
	TSubclassOf<class AArchivaCamera> BP_ArchivaCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|GameMode")
	TArray<AArchivaCamera*> CameraList; /**< �ʿ� �߰��� ī�޶� ��� ����*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|GameMode")
	TArray<AMyModel*> ModelList; /**< �ʿ� �߰��� �� ����*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|GameMode")
	TArray<FModelData> ModelDataList; /**< �ʿ� �߰��� ���� ������ ����. ���� ��ε��� ����, ���� �����͸� �����ϰ� �ٽ� �ε��� �� Ȱ���Ѵ�.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|GameMode")
	class UArchivaXmlReader* xmlReader; /**< xml �����͸� �д� ���*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|GameMode")
	FString userDir; /**< �� �����Ͱ� ����� xml ���� ��ġ */
	/**
	*	���α׷� ���� ��, ���� ���� ����Ǵ� �Լ��μ� main�� �����ϴ�.
	*	�ٸ� ��Ÿ���� Construction ��Ʈ���� ����ȴ�.
	*/
	ArchivaGameMode(const FObjectInitializer& ObjectInitializer);

	/**
	*	Actor�� SpawnModel�ϱ� ���� ������ �����ϴ� Helper �Լ�
	*	@param name �ʿ� �����ϴ� ���� �̸�
	*/
	FActorSpawnParameters SpawnInformation(FName name);
	/**
	*	���������� Actor�� SpawnModel�ϴ� �Լ���.
	*	ModelData �ҽ��ڵ忡 �ִ� �� ����� Ȱ���Ͽ�,
	*	SpawnModel�� ���� �����Ѵ�.
	*	(!Construction Ÿ�ӿ� �������� ������ ������ �� �� �ִ�.)
	* @param data ���� �����ϴµ� �ʿ��� ������ �����ϴ� ����ü
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	void SpawnModel(FModelData data);

	/**
	*	PlayerController�� ī�޶� ���ϴ� ������ ������ �� �ֵ��� �ϴ� �Լ�
	*	��ġ�Ǵ� ����, ScreenShot�� ����ϰ� HUD�� ����Ʈ�� ������Ʈ �Ѵ�.
	*	ī�޶�� �⺻������ Pin����� �ϰ� ������, ������ �̵��ϴ� ������ �ȴ�.
	* @param loc ī�޶� ������ ��ġ
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	void SpawnCamera(FTransform loc);

	/**
	*	PlayerController�� ī�޶� �ε巴�� ��ȯ�ϴ� �Լ�
	*	@param player ī�޶� ��ȯ�Ϸ��� �÷��̾�
	*	@param ī�޶� ID �ѹ�
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	void ChangeCamera(APlayerController* palyer, int num);

	/**
	* ��� ���� Ư�� XML ���Ϸ� �ʱ�ȭ
	* @param path �ʱ�ȭ�� XML ���� ��ġ
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	void ResetModel(FString path);

	/**
	* Gets all the files in a given directory.
	* @param directory The full path of the directory we want to iterate over.
	* @param fullpath Whether the returned list should be the full file paths or just the filenames.
	* @param onlyFilesStartingWith Will only return filenames starting with this string. Also applies onlyFilesEndingWith if specified.
	* @param onlyFilesEndingWith Will only return filenames ending with this string (it looks at the extension as well!). Also applies onlyFilesStartingWith if specified.
	* @return A list of files (including the extension).
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	static TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath = true, const FString onlyFilesStartingWith = TEXT(""), const FString onlyFilesEndingWith = TEXT(""));

};
