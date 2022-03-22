// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class URBANPOTATO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bPressedRun = false;
	TArray<int> itemInventory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* itemDatabase;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float value);

	void JumpStart();
	void JumpEnd();

	void RunStart();
	void RunEnd();

	void AddtoItemInventory(int itemID);
	
};
