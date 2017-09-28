// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Model/DynamicModel.h"

#include "GameFramework/Actor.h"
#include "FloorModel.generated.h"

UCLASS()
class ARCHIVA_API AFloorModel : public ADynamicModel
{
	GENERATED_BODY()
protected:
	TArray<FVector> floor;

	//top, side, bottom
	
public:	
	AFloorModel();

	UFUNCTION(BlueprintCallable, Category = "Archiva|Model")
	virtual void Create(FModelData data) override;

	void Extrude(TArray<FVector> bottom, FVector m);

	/*�簢���� ����� ����, �߽����� �������� ���� | ��� | ���� | �Ͽ� ������ �������� ã�´�. */
	TArray<FVector> FindPosSqud(FVector std);
	/*�����¿� ��ǥ�� ã�� �Լ�*/
	FVector FindPoint(FVector std, FVector2D direction);
	/*ã�� �簢���� �������� Ȯ���ϴ� �Լ�*/
	bool isInside(FVector mid);
};
