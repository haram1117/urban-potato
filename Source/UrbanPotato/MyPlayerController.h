// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "Item.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void OnPossess(APawn* InPawn) override;
public:
	
	UInventoryWidget* InventoryWidget;
	void SetSlotImage(FItemStruct* ItemStruct);
	AItem* CastAItem(TSubclassOf<AItem>);
};
