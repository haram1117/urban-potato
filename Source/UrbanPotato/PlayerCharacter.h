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
class ANPC;
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
	
	/**
	 * @brief 캐릭터 mesh
	 */
	USkeletalMeshComponent* CharacterMesh;
	
	/**
	 * @brief 플레이어 걸을 때 Sound
	 */
	UPROPERTY(EditAnywhere)
	USoundBase* walkSound;
	
	/**
	 * @brief 사용하고 있는 item
	 */
	UPROPERTY(BlueprintReadOnly)
	AItem* UsingItem;

	/**
	 * @brief Overlap된 ActorWithInteractions
	 */
	AActorWithInteractions* ActorInBoundary;

	/**
	 * @brief overlap된 Item
	 */
	AItem* ItemInBoundary;

	/**
	 * @brief overlap된 NPC
	 */
	ANPC* NPCInBoundary;

	/**
	 * @brief 가장 늦게 바운더리된 Category (0: ActorWithInteraction, 1: Item, 2: NPC)
	 */
	int BoundaryCategory;

	/**
	 * @brief 사용하고 있는 Item Inventory Slot Num
	 */
	int usingItemButtonNum;

	/**
	 * @brief item ID를 담아둘 inventory array
	 */
	TArray<int> itemInventory;

	/**
	 * @brief item Struct를 담아둘 inventory array
	 */
	TArray<FItemStruct*> inventory;

	/**
	 * @brief 캐릭터 회전을 위한 X축 부호
	 */
	int XAxis = 1;

	/**
	 * @brief 캐릭터 회전을 위한 Y축 부호
	 */
	int YAxis = 1;

	/**
	 * @brief 체크 포인트 index 저장
	 */
	int Splinepoint = 0;

	
	/**
	 * @brief 캐릭터의 현재 상태 Enum
	 */
	UPROPERTY(BlueprintReadWrite)
	ECharacterMovementEnum CharacterMovementEnum = ECharacterMovementEnum::E_Idle;
	
	/**
	 * @brief 현재 스테이지의 퍼즐 클리어 횟수
	 */
	int ClearNum = 0;

	/**
	 * @brief inventory opened 여부
	 */
	bool IsInventoryOpened = false;

	bool forward_Moving = false;
	bool right_Moving = false;
	
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

	void InventoryWidgetSet();

	void Talk();
	
	template<int32 slotNum>
	void SetInventory_UsingItem();

	UFUNCTION(BlueprintCallable)
	void CheckAllPuzzlesFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void PuzzleFinished();
	
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

	void Respawn();

	void GoInsideMap(FVector location, FRotator Rotator);

	void SetItemInBoundary(AItem* item);
	void UnSetItemInBoundary(AItem* item);

	void SetNPCInBoundary(ANPC* npc);
	void UnSetNPCInBoundary(ANPC* npc);
	
	void SetInteractActorInBoundary(AActorWithInteractions* actor);
	UFUNCTION(BlueprintCallable)
	void UnSetInteractActorInBoundary(AActorWithInteractions* actor);

	void AllWidgetsOff() const;
	
	FItemStruct* FindInInventoryWithID(int id);
};

template <int32 slotNum>
void APlayerCharacter::SetInventory_UsingItem()
{
	if(slotNum == 0)
		PlayerController->InventoryWidget->SetCharacterUsingItem(9);
	else
		PlayerController->InventoryWidget->SetCharacterUsingItem(slotNum - 1);
}
