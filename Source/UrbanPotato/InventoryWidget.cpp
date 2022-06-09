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

	TextBlocks.Add(text0);
	TextBlocks.Add(text1);
	TextBlocks.Add(text2);
	TextBlocks.Add(text3);
	TextBlocks.Add(text4);
	TextBlocks.Add(text5);
	TextBlocks.Add(text6);
	TextBlocks.Add(text7);
	TextBlocks.Add(text8);
	TextBlocks.Add(text9);
	InitColor = text0->ColorAndOpacity;
	UBlueprintGeneratedClass* BPCWidget_itemTooltipClass = LoadObject<UBlueprintGeneratedClass>(NULL, TEXT("WidgetBlueprint'/Game/Base/Widgets/BP_ItemPanel.BP_ItemPanel_C'"), NULL, LOAD_None, NULL);
	widget_itemTooltipClass = Cast<UClass>(BPCWidget_itemTooltipClass);
}

void UInventoryWidget::SetCharacterUsingItem(int slotID)
{
	if(Buttons[slotID] != nullptr)
	{
		ReSetTextBlockColor();
		Buttons[slotID]->SetUsingItem(slotID);
	}
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
			Cast<UitemPanel>(ItemSlot->ToolTipWidget)->SetItemInfo(ItemSlot->GetSlotItem());
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

void UInventoryWidget::ReSetTextBlockColor()
{
	for (auto Text : TextBlocks)
	{
		Text->SetColorAndOpacity(InitColor);
	}
}