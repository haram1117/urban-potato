// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "InventoryWidget.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class URBANPOTATO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam(FInputRespawnDelegate, AActor* actor);
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> inventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UitemPanel> ItemPanelWidget;
	// UInventoryWidget* Inventory;
	/**
	 * @brief 사용하고 있는 item
	 */
	AItem* UsingItem;
	int usingItemButtonNum;
	TArray<int> itemInventory;
	TArray<FItemStruct*> inventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bPressedRun = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* itemDatabase;
	AMyPlayerController* PlayerController; 
	

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

	void Interact();
	
	void AddtoItemInventory(int itemID);

	void SetPlayerController(AMyPlayerController* Controller);

	FItemStruct* FindItemFromRow(int itemID);
	
	void RemoveFromItemInventory(FItemStruct* removeItem);

	void Respawn(AActor* actor);
	void Respawn();
};
