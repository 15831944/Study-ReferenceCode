// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Model/DynamicModel.h"

#include "GameFramework/Actor.h"
#include "GlassHandrailModel.generated.h"

UCLASS()
class ARCHIVA_API AGlassHandrailModel : public ADynamicModel
{
	GENERATED_BODY()
protected:
	//������ �κ��� �Ӽ���
	float H_length;
	float H_width;
	float H_height;
	//��� �κ��� �Ӽ���
	float P_length;
	float P_width;
	float P_height;
	//���� �κ��� �Ӽ���
	float G_length;
	float G_width;
	float G_height;

	//������ ����
	float angle;

	//Material�� �ֱ� ���� ������
	//handle, pillar, glass

public:
	//�⺻ ������ ���� ���õǴ� �Լ�
	AGlassHandrailModel();
	UFUNCTION(BlueprintCallable, Category = "Archiva|Model")
	virtual void Create(FModelData data) override;

	void CreatePillar(FVector std);
	void CreateGlass(float startP);
	float CalcTrigX(float length);
	float CalcTrigY(float length);
};
