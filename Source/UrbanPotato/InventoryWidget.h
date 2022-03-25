// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "itemPanel.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
	class UButton* SlotButton0;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton1;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton2;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton3;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton4;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton5;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton6;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton7;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton8;
	UPROPERTY(meta=(BindWidget))
	class UButton* SlotButton9;

	UPROPERTY(EditAnywhere)
	TArray<UButton*> Buttons;

	TSubclassOf<UitemPanel> itempanel;
	void ButtonsInitialize();
	UFUNCTION(BlueprintCallable)
	void ShowItemDesc(int slotID);

	UFUNCTION(BlueprintCallable)
	void HideItemDesc(int slotID);

	void SetDescText(FString itemName, FString descText);

	UFUNCTION(BlueprintCallable)
	void SetCharacterUsingItem(int slotID);
};