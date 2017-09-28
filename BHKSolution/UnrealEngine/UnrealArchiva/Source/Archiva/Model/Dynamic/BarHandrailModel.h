// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Model/DynamicModel.h"

#include "GameFramework/Actor.h"
#include "BarHandrailModel.generated.h"

UCLASS()
class ARCHIVA_API ABarHandrailModel : public ADynamicModel
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
	//�� �κ��� �Ӽ���
	float B_height;
	float B_width;
	//��ջ��� ����
	float interval;
	//������ ����
	float angle;

	//Material�� �ֱ� ���� ������
	//bar, pillar, handle

public:
	//�⺻ ������ ���� ���õǴ� �Լ�
	ABarHandrailModel();
	
	UFUNCTION(BlueprintCallable, Category = "Archiva|Model")
	virtual void Create(FModelData data) override;

	void CreatePillar(FVector std);
	void CreateBar(float pos);

	float CalcTrigX(float length);
	float CalcTrigY(float length);
};
