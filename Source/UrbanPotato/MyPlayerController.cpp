// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "SoundEvent.h"
#include "PlayerCharacter.h"

AMyPlayerController::AMyPlayerController()
{
	sound_event = new SoundEvent();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(this->GetCharacter());
	PlayerCharacter->SetPlayerController(this);

	playDialog_delegate.BindRaw(sound_event, &SoundEvent::PlayDialogSound);

	
	if(PlayerCharacter->inventoryWidget != nullptr)
		InventoryWidget = CreateWidget<UInventoryWidget>(this, PlayerCharacter->inventoryWidget);
	if(PlayerCharacter->dialogWidget != nullptr)
		dialogWidget = CreateWidget<UNPC_dialog>(this, PlayerCharacter->dialogWidget);
	if(InventoryWidget != nullptr)
	{
		// InventoryWidget->AddToViewport();
		InventoryWidget->ButtonsInitialize();
	}
	if(dialogWidget != nullptr)
	{
		dialogWidget->AddToViewport();
	}
}


void AMyPlayerController::SetSlotItemToEmptySlot(FItemStruct* ItemStruct) const
{
	if(InventoryWidget != nullptr)
	{
		if(ItemStruct->Item->itemCount >= 1) // 이미 아이템 존재 - 해당 슬롯에 넣고 Update()
			{
			for(int i = 0; i < InventoryWidget->Buttons.Num(); i++)
			{
				if(InventoryWidget->Buttons[i]->GetSlotItem() == ItemStruct)
				{
					InventoryWidget->UpdateSlot(i);
					InventoryWidget->Buttons[i]->SetSlotItem(ItemStruct);
					return;
				}
			}
			}
		// 아이템 존재 x -> 새로운 Slot에 넣기
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

void AMyPlayerController::PlaySound(USoundWave* sound) const
{
	UGameplayStatics::PlaySound2D(this, sound);
}
