// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "itemPanel.h"
#include "ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	// virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton0;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton1;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton2;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton3;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton4;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton5;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton6;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton7;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton8;
	UPROPERTY(meta=(BindWidget))
	class UItemSlot* SlotButton9;

	
	UPROPERTY(EditAnywhere)
	TArray<UItemSlot*> Buttons;

	UClass* widget_itemTooltipClass;

	
	TSubclassOf<UitemPanel> itempanel;
	void ButtonsInitialize();
	// UFUNCTION(BlueprintCallable)
	// void ShowItemDesc(int slotID);
	//
	// UFUNCTION(BlueprintCallable)
	// void HideItemDesc(int slotID);
	//
	// void SetDescText(FString itemName, FString descText);

	UFUNCTION(BlueprintCallable)
	void SetCharacterUsingItem(int slotID);

	void UpdateSlot(int slotIndex);

};