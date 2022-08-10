// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemSlot;
class APlayerCharacter;
UCLASS()
class URBANPOTATO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemSlot* ItemSlot;
	bool isWidgetVisible = false;
	UWidgetComponent* widget;
	UStaticMeshComponent* StaticMeshComponent;
	AItem* next = nullptr;
	AItem* nextOverlap = nullptr;
	int itemCount;
	UPROPERTY(BlueprintReadOnly)
	FRotator InitRotator = FRotator(0, 0, 0);
	UPROPERTY(BlueprintReadWrite)
	FRotator LastRotator;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
	void Use();
	UFUNCTION(BlueprintCallable)
	void ActorEnable(FVector Location, FRotator Rotator);
	UFUNCTION(BlueprintCallable)
	void ActorDisable();
	void SetNextItem(AItem* NextItem);
	void ChangeItemCount(int value);
	void SetItemSlotToEveryItem(UItemSlot* Slot);
	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory_Item(APlayerCharacter* PlayerCharacter);
	AItem* GetNextItem();

	/**
	 * @brief Item의 "줍기 F" 위젯 끄기
	 */
	void WidgetOff();
	
	/**
	 * @brief Item의 "줍기 F" 위젯 켜기
	 */
	void WidgetOn();
};

USTRUCT(Atomic, BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AItem> itemClass;

	AItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* itemImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemDescription;
		
};