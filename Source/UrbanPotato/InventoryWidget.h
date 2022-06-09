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

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text0;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text1;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text2;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text3;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text4;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text5;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text6;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text7;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text8;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* text9;
	
	UPROPERTY(EditAnywhere)
	TArray<UItemSlot*> Buttons;
	TArray<UTextBlock*> TextBlocks;
	UClass* widget_itemTooltipClass;
	FSlateColor InitColor;
	FSlateColor UsingColor;
	
	TSubclassOf<UitemPanel> itempanel;
	void ButtonsInitialize();

	UFUNCTION(BlueprintCallable)
	void SetCharacterUsingItem(int slotID);

	void UpdateSlot(int slotIndex);
	void ReSetTextBlockColor();

};