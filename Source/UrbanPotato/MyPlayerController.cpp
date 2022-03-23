// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "PlayerCharacter.h"
#include "Components/Button.h"

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
	PlayerCharacter->SetPlayerController(this);
	InventoryWidget = CreateWidget<UInventoryWidget>(this, PlayerCharacter->inventoryWidget);
	if(InventoryWidget != nullptr)
	{
		InventoryWidget->AddToViewport();
	}
}

void AMyPlayerController::SetSlotImage(FItemStruct* ItemStruct)
{
	if(InventoryWidget != nullptr)
	{
		InventoryWidget->SlotButton->WidgetStyle.Normal.SetResourceObject(ItemStruct->itemImage);
		InventoryWidget->SlotButton->WidgetStyle.Hovered.SetResourceObject(ItemStruct->itemImage);
		InventoryWidget->SetDescText(ItemStruct->itemName, ItemStruct->itemDescription);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HI"));
	}
}
