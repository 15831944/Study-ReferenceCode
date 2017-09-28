// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ArchivaHUD.h"

#include "GameFramework/Actor.h"
#include "ArchivaCamera.generated.h"


/**
* @class AArchivaCamera
* @brief ���๰�� �ٰ������� ���캼 �� �ֵ��� ��ġ�Ǵ� ī�޶�
* 
* ���๰�� �پ��� �������� �� ���� Ȯ���ϱ� ���ؼ��� ���忡 ī�޶� ��ġ�Ͽ�, �ǽð����� �Կ��� �� UI���� �����ش�.
* ī�޶󿡼� �Կ��� �����͸� UI�� ǥ���� �� �ִ� 2D Texture�� ��ȯ�Ͽ� ���ο� �����Ѵ�.
*/

UCLASS()
class ARCHIVA_API AArchivaCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Export, Category = "Archiva|Camera")
	USceneCaptureComponent2D* SceneCapture; /**< ī�޶� ������ ������ �����ϴ� ���� */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Export, Category = "Archiva|Camera")
	UTextureRenderTarget2D* RenderTarget; /**< ī�޶� ���� ������ �ؽ�ó�� ������� �����ϴ� ���� */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Archiva|Camera")
	int32 CameraNumber; /**< ī�޶��� ������ �����ϴ� ���� */
	
	/**
	* ArchivaCamera ��ü�� �ʱ�ȭ�Ѵ�. Constructor�� �� �� �ִ�.
	* @param ObjectInitializer UE4���� Object�� �ʱ�ȭ�ϱ� ���� �ݵ�� �䱸�Ѵ�.
	*/
	AArchivaCamera(const FObjectInitializer& ObjectInitializer);

	/**
	* ������ ���۵Ǿ��� �� �Ǵ� ��ü�� �����Ǿ��� �� ����ȴ�.
	*/
	virtual void BeginPlay() override;
	
	/**
	* �� Tick���� ����ȴ�.
	*/
	virtual void Tick( float DeltaSeconds ) override;

};
