// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
	PlayerCharacter->SetPlayerController(this);
	InventoryWidget = CreateWidget<UInventoryWidget>(this, PlayerCharacter->inventoryWidget);
	ItemPanelWidget = CreateWidget<UitemPanel>(this);
	if(ItemPanelWidget != nullptr)
	{
		ItemPanelWidget->AddToViewport();
		ItemPanelWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(InventoryWidget != nullptr)
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->ButtonsInitialize();
	}
}

void AMyPlayerController::SetSlotImage(FItemStruct* ItemStruct)
{
	if(InventoryWidget != nullptr)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
		InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Normal.SetResourceObject(ItemStruct->itemImage);
		InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Hovered.SetResourceObject(ItemStruct->itemImage);
		InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Pressed.SetResourceObject(ItemStruct->itemImage);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HI"));
	}
}

void AMyPlayerController::SetItemPanel(FString itemName, FString descText)
{
	ItemPanelWidget->ItemName->SetText(FText::FromString(itemName));
	ItemPanelWidget->DescText->SetText(FText::FromString(descText));
}

void AMyPlayerController::ShowItemPanel(int slotID)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
	if(PlayerCharacter->itemInventory.Num() -1 < slotID)
		return;
	FItemStruct* ItemStruct = PlayerCharacter->FindItemFromRow(PlayerCharacter->itemInventory[slotID]);
	SetItemPanel(ItemStruct->itemName, ItemStruct->itemDescription);
	float x;
	float y;
	GetMousePosition(x, y);
	ItemPanelWidget->SetPositionInViewport(FVector2D(x, y));
	ItemPanelWidget->ItemPanel->SetVisibility(ESlateVisibility::Visible);
}

void AMyPlayerController::HideItemPanel(int slotID)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
	if(PlayerCharacter->itemInventory.Num() -1 < slotID)
		return;
	ItemPanelWidget->ItemPanel->SetVisibility(ESlateVisibility::Hidden);
}
