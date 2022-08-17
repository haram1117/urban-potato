// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "Item.h"
#include "itemPanel.h"
#include "NPC_dialog.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SoundEvent.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
class AMyPlayerController;
DECLARE_DELEGATE_OneParam(FPlayDialogDelegate, AMyPlayerController*);

UCLASS()
class URBANPOTATO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	AMyPlayerController();
	virtual void OnPossess(APawn* InPawn) override;
public:
	UPROPERTY(BlueprintReadWrite)
	UInventoryWidget* InventoryWidget;
	UitemPanel* itemPanel;
	UPROPERTY(BlueprintReadOnly)
	UNPC_dialog* dialogWidget;

	
	// SoundEvent* soundEvent;
	//
	SoundEvent* sound_event;
	
	void SetSlotItemToEmptySlot(FItemStruct* ItemStruct);
	FPlayDialogDelegate playDialog_delegate;
};
