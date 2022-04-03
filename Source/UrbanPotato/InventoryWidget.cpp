// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "PlayerCharacter.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UInventoryWidget::ButtonsInitialize()
{
	Buttons.Add(SlotButton0);
	Buttons.Add(SlotButton1);
	Buttons.Add(SlotButton2);
	Buttons.Add(SlotButton3);
	Buttons.Add(SlotButton4);
	Buttons.Add(SlotButton5);
	Buttons.Add(SlotButton6);
	Buttons.Add(SlotButton7);
	Buttons.Add(SlotButton8);
	Buttons.Add(SlotButton9);
	UBlueprintGeneratedClass* BPCWidget_itemTooltipClass = LoadObject<UBlueprintGeneratedClass>(NULL, TEXT("WidgetBlueprint'/Game/Base/Widgets/BP_ItemPanel.BP_ItemPanel_C'"), NULL, LOAD_None, NULL);
	widget_itemTooltipClass = Cast<UClass>(BPCWidget_itemTooltipClass);
}

// void UInventoryWidget::ShowItemDesc(int slotID)
// {
// 	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ShowItemPanel(slotID);
// }
//
// void UInventoryWidget::HideItemDesc(int slotID)
// {
// 	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->HideItemPanel(slotID);
// }
//
// void UInventoryWidget::SetDescText(FString itemName, FString descText)
// {
// 	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetItemPanel(itemName, descText);
// }

void UInventoryWidget::SetCharacterUsingItem(int slotID)
{
	if(Buttons[slotID] != nullptr)
		Buttons[slotID]->SetUsingItem();
}

void UInventoryWidget::UpdateSlot(int slotIndex)
{
	UItemSlot* ItemSlot;
	ItemSlot = Buttons[slotIndex];
	if(ItemSlot->IsEmpty())
	{
		ItemSlot->SetToolTip(nullptr);
	}
	else
	{
		if(ItemSlot->ToolTipWidget != nullptr) //툴팁 이미 생성되어있음
		{
			// 툴팁 정보만 변경
		}
		else
		{
			UitemPanel* UitemPanel;
			UitemPanel = CreateWidget<class UitemPanel>(this, widget_itemTooltipClass);
			UitemPanel->SetItemInfo(ItemSlot->GetSlotItem());
			ItemSlot->SetToolTip(UitemPanel);
		}
	}
}


