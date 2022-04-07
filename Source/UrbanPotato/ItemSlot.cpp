// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"

#include "PlayerCharacter.h"

bool UItemSlot::IsEmpty()
{
	return IsEmptySlot;
}

FItemStruct* UItemSlot::GetSlotItem()
{
	return slotItem;
}

void UItemSlot::SetSlotItem(FItemStruct* _slotItem)
{
	slotItem = _slotItem;
	IsEmptySlot = false;
	_slotItem->itemClass.GetDefaultObject()->ItemSlot = this;
	SetSlotIcon();
}

void UItemSlot::SetSlotIcon()
{
	WidgetStyle.Normal.SetResourceObject(slotItem->itemImage);
	WidgetStyle.Hovered.SetResourceObject(slotItem->itemImage);
	WidgetStyle.Pressed.SetResourceObject(slotItem->itemImage);
}


void UItemSlot::SetUsingItem()
{
	if(!IsEmptySlot)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if(IsUsingItemSlot)
		{
			PlayerCharacter->UsingItem = nullptr;
			IsUsingItemSlot = false;
		}
		else
		{
			PlayerCharacter->UsingItem = slotItem->itemClass.GetDefaultObject(); // 사용자 선택
			IsUsingItemSlot = true;
		}
	}
}

void UItemSlot::ResetSlotIcon()
{
	WidgetStyle.Normal.SetResourceObject(nullptr);
	WidgetStyle.Hovered.SetResourceObject(nullptr);
	WidgetStyle.Pressed.SetResourceObject(nullptr);
}

void UItemSlot::RemoveSlotItem()
{
	slotItem = nullptr;
	IsEmptySlot = true;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->UsingItem = nullptr;
	this->SetToolTip(nullptr);
	ResetSlotIcon();
}
