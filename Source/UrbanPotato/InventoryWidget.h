// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	class UButton* SlotButton;
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* ItemPanel;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DescText;
	
	UFUNCTION(BlueprintCallable)
	void ShowItemDesc();

	UFUNCTION(BlueprintCallable)
	void HideItemDesc();

	void SetDescText(FString itemName, FString descText);
};
