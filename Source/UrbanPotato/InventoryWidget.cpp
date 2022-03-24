// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "PlayerCharacter.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UInventoryWidget::ShowItemDesc()
{
	ItemPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::HideItemDesc()
{
	ItemPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::SetDescText(FString itemName, FString descText)
{
	ItemName->SetText(FText::FromString(itemName));
	DescText->SetText(FText::FromString(descText));
}

void UInventoryWidget::SetCharacterUsingItem()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->usingItemButtonNum = 0;
	int itemID = PlayerCharacter->itemInventory[PlayerCharacter->usingItemButtonNum];
	TSubclassOf<AItem> itemClass = PlayerCharacter->FindItemFromRow(itemID)->itemClass;
	PlayerCharacter->UsingItem = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->CastAItem(itemClass);
	UE_LOG(LogTemp, Error, TEXT("%d"), PlayerCharacter->UsingItem->itemID);
}
