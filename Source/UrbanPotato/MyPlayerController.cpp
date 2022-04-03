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
	// itemPanel = CreateWidget<UitemPanel>(this, PlayerCharacter->ItemPanelWidget);
	// if(itemPanel != nullptr)
	// {
	// 	itemPanel->AddToViewport();
	// 	itemPanel->SetVisibility(ESlateVisibility::Collapsed);
	// }
	if(InventoryWidget != nullptr)
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->ButtonsInitialize();
	}
}

void AMyPlayerController::SetSlotItemToEmptySlot(FItemStruct* ItemStruct)
{
	if(InventoryWidget != nullptr)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
		// InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Normal.SetResourceObject(ItemStruct->itemImage);
		// InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Hovered.SetResourceObject(ItemStruct->itemImage);
		// InventoryWidget->Buttons[PlayerCharacter->itemInventory.Num() - 1]->WidgetStyle.Pressed.SetResourceObject(ItemStruct->itemImage);
		for (int i =0 ; i < InventoryWidget->Buttons.Num(); i++)
		{
			UItemSlot* Slot = InventoryWidget->Buttons[i];
			if(Slot->IsEmpty())
			{
				Slot->SetSlotItem(ItemStruct);
				InventoryWidget->UpdateSlot(i);
				break;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HI"));
	}
}
//
// void AMyPlayerController::SetItemPanel(FString itemName, FString descText)
// {
// 	itemPanel->ItemName->SetText(FText::FromString(itemName));
// 	itemPanel->DescText->SetText(FText::FromString(descText));
// }
//
// void AMyPlayerController::ShowItemPanel(int slotID)
// {
// 	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
// 	if(PlayerCharacter->itemInventory.Num() -1 < slotID)
// 		return;
// 	FItemStruct* ItemStruct = PlayerCharacter->FindItemFromRow(PlayerCharacter->itemInventory[slotID]);
// 	SetItemPanel(ItemStruct->itemName, ItemStruct->itemDescription);
// 	float x;
// 	float y;
// 	GetMousePosition(x, y);
// 	itemPanel->SetPositionInViewport(FVector2D(x, y));
// 	itemPanel->SetVisibility(ESlateVisibility::Visible);
// }

// void AMyPlayerController::HideItemPanel(int slotID)
// {
// 	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
// 	if(PlayerCharacter->itemInventory.Num() -1 < slotID)
// 		return;
// 	itemPanel->SetVisibility(ESlateVisibility::Collapsed);
// }
