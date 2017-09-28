// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ArchivaFirstPersonChara.generated.h"


/**
* @class AArchivaFirstPersonChara
* ������ ��Ʈ���� �� �ִ� 1��Ī ������ ������ Character
*/

UCLASS()
class ARCHIVA_API AArchivaFirstPersonChara : public ACharacter
{
	GENERATED_BODY()

public:

	/**
	* �⺻ ������ Constructor
	* Sets default values for this character's properties
	*/
	AArchivaFirstPersonChara();


	/**
	* �⺻ ������ BeginPlay
	* Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;
	
	/**
	* �⺻ ������ Tick
	* Called every frame
	*/
	virtual void Tick( float DeltaSeconds ) override;


	/**
	* ���� �Է��� ó���ϴ� Key Binding ����
	* Called to bind functionality to input
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	/**
	* Handles input for moving forward and backward.
	*/
	UFUNCTION(BlueprintCallable, Category = "ArchivaFirstPerson")
	void MoveForward(float Value); /**< ������ ���� ó�� */

	/**
	* Handles input for moving right and left.
	*/
	UFUNCTION(BlueprintCallable, Category = "ArchivaFirstPerson")
	void MoveRight(float Value); /**< ������ ���� ó�� */

	/**
	* Sets jump flag when key is pressed.
	*/
	UFUNCTION(BlueprintCallable, Category = "ArchivaFirstPerson")
	void StartJump(); /**< ���� ���� ó�� */

	/**
	* Clears jump flag when key is released.
	*/
	UFUNCTION(BlueprintCallable, Category = "ArchivaFirstPerson")
	void StopJump(); /**< ���� �ߴ� ó�� */

};
