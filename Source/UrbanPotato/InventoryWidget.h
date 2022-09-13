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
	
	/**
	 * @brief Inventory의 ItemSlot Container
	 */
	UPROPERTY(EditAnywhere)
	TArray<UItemSlot*> Buttons;
	
	/**
	 * @brief Inventory의 textBlock(SlotNum) Container
	 */
	TArray<UTextBlock*> TextBlocks;
	
	/**
	 * @brief ToolTip Widget Class
	 */
	UClass* widget_itemTooltipClass;
	
	/**
	 * @brief Inventory Slot Num 텍스트 기본 색상
	 */
	FSlateColor InitColor;
	
	/**
	 * @brief 해당 Slot 선택 시 Inventory Slot Num 텍스트 색상
	 */
	FSlateColor UsingColor;
	
	// TSubclassOf<UitemPanel> itempanel;

	/**
	 * @brief 각 Slot Button Initialization
	 */
	void ButtonsInitialize();

	/**
	 * @brief 캐릭터의 현재 사용 아이템 Set
	 * @param slotID 사용할 아이템의 SlotID
	 */
	UFUNCTION(BlueprintCallable)
	void SetCharacterUsingItem(int slotID);

	/**
	 * @brief 아이템 획득/사용에 따른 Slot 변화 Update
	 * @param slotIndex Update할 해당 Slot Index 
	 */
	void UpdateSlot(int slotIndex);
	
	/**
	 * @brief 비 선택 시 모든 TextBlock의 색상 기본값 복원
	 */
	void ReSetTextBlockColor();

};