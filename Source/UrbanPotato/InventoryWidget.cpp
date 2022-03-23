// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

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
