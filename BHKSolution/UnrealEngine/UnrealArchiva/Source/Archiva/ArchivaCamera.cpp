// Fill out your copyright notice in the Description page of Project Settings.

#include "Archiva.h"
#include "ArchivaCamera.h"


/**
* �� Tick���� ī�޶� ��� ����� ������Ʈ�� �� �ֵ���, �ʱ�ȭ�Ѵ�.
*/
AArchivaCamera::AArchivaCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->AttachToComponent(this->GetCameraComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//SceneCapture->CaptureSource = SCS_FinalColorLDR;
	SceneCapture->DetailMode = EDetailMode::DM_High;
	
}

/**
* ī�޶� ���� ����� Texture�� ��ȯ��ų �� �ֵ��� �����Ѵ�.
*/
// Called when the game starts or when spawned
void AArchivaCamera::BeginPlay()
{
	Super::BeginPlay();

	RenderTarget = NewObject<UTextureRenderTarget2D>();
	RenderTarget->InitAutoFormat(512, 512);
	RenderTarget->CompressionSettings = TextureCompressionSettings::TC_EditorIcon;
	RenderTarget->UpdateResource();

	SceneCapture->TextureTarget = RenderTarget;

	//AArchivaHUD* hud = (AArchivaHUD*)GetWorld()->GetFirstPlayerController()->GetHUD();
	//hud->snapShotList.Add(RenderTarget);

}


/**
* �� Tick����, Scene�� �ٽ� ĸ���Ͽ� ����� ���� ȿ���� �ش�.
*/
void AArchivaCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	SceneCapture->UpdateContent();
}
