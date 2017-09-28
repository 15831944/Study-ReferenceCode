// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Data/Modeldata.h"

#include "GameFramework/Actor.h"
#include "MyModel.generated.h"

/*
*	@class AMyModel
*	���� �����ϴµ� �ʿ��� �Լ��� �����ϴ� ���� �߿��� Ŭ����
*/

UCLASS()
class ARCHIVA_API AMyModel : public AActor
{
	GENERATED_BODY()
	
protected:	
	/*
	*	RootComponent�μ� ������ǥ�� ��ġ�ǰ�, �����ǥ�� ������ �ȴ�.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Archiva|Model")
	USphereComponent* SphereComponent;

public:
	// Sets default values for this actor's properties
	AMyModel();

	/**
	*	��� Model�� �����ϰ� �ִ� �Լ��μ�, Model�� ���¸� �����ϴ� �Լ�
	*/
	UFUNCTION(BlueprintCallable, Category = "Archiva|Model")
	virtual void Create(FModelData data);
};

