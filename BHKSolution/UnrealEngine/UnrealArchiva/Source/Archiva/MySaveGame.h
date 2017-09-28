// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *	@class UMySaveGame
 *	���� �̿ϼ��̰�, �𵨵����͸� �����ϴ� Ŭ������ Ȱ���ϰ� �ִ�.
 */
UCLASS()
class ARCHIVA_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UMySaveGame();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Archiva|SaveGame")
	TArray<FModelData> ModelDataList;

	UFUNCTION(BlueprintCallable, Category = "Archiva|GameMode")
	void SaveModelData(TArray<FModelData> data);
};
