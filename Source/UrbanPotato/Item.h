// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemSlot;
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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetItem();
	UFUNCTION(BlueprintImplementableEvent)
	void Use();
	virtual void TakeOut();
};

USTRUCT(Atomic, BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AItem> itemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* itemImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemDescription;
		
};