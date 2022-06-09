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

class AMapSafeArea;
class AActorWithInteractions;
UENUM(BlueprintType)
enum class ECharacterMovementEnum : uint8
{
	E_Idle,
	E_Walk,
	E_Jump,
	E_Run
};
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
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNPC_dialog> dialogWidget;
	USkeletalMeshComponent* CharacterMesh;
	// UInventoryWidget* Inventory;
	/**
	 * @brief 사용하고 있는 item
	 */
	UPROPERTY(BlueprintReadOnly)
	AItem* UsingItem;
	int usingItemButtonNum;
	TArray<int> itemInventory;
	TArray<FItemStruct*> inventory;
	AActorWithInteractions* InteractActor;
	AItem* ItemInBoundary;
	AActorWithInteractions* ActorInBoundary;
	int XAxis = 1;
	int YAxis = 1;
	int Splinepoint = 0;
	UPROPERTY(BlueprintReadWrite)
	ECharacterMovementEnum CharacterMovementEnum = ECharacterMovementEnum::E_Idle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bPressedRun = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* itemDatabase;
	AMyPlayerController* PlayerController; 
	AMapSafeArea* MapSafeArea;

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

	void Turn(float value);
	void LookUp(float value);

	void ShowInventory();
	void HideInventory();

	UFUNCTION(BlueprintImplementableEvent)
	void SetInputMode();
	UFUNCTION(BlueprintImplementableEvent)
	void UnSetInputMode();
	void Interact();

	UFUNCTION(BlueprintNativeEvent)
	void GetItem();
	
	void AddtoItemInventory(AItem* Item);

	void SetPlayerController(AMyPlayerController* Controller);

	FItemStruct* FindItemFromRow(int itemID);
	
	void RemoveFromItemInventory(FItemStruct* removeItem);

	// void Respawn(AActor* actor);
	void Respawn();

	void GoInsideMap(FVector location, FRotator Rotator);

	void SetItemInBoundary(AItem* item);
	void UnSetItemInBoundary(AItem* item);

	void SetInteractActorInBoundary(AActorWithInteractions* actor);
	UFUNCTION(BlueprintCallable)
	void UnSetInteractActorInBoundary(AActorWithInteractions* actor);

	FItemStruct* FindInInventoryWithID(int id);
};
