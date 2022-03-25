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
}

void UInventoryWidget::ShowItemDesc(int slotID)
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ShowItemPanel(slotID);
}

void UInventoryWidget::HideItemDesc(int slotID)
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->HideItemPanel(slotID);
}

void UInventoryWidget::SetDescText(FString itemName, FString descText)
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetItemPanel(itemName, descText);
}

void UInventoryWidget::SetCharacterUsingItem(int slotID)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(PlayerCharacter->itemInventory.Num() -1 < slotID)
		return;
	PlayerCharacter->usingItemButtonNum = slotID;
	int itemID = PlayerCharacter->itemInventory[PlayerCharacter->usingItemButtonNum];
	TSubclassOf<AItem> itemClass = PlayerCharacter->FindItemFromRow(itemID)->itemClass;
	PlayerCharacter->UsingItem = itemClass.GetDefaultObject();
}
