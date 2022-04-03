// Fill out your copyright notice in the Description page of Project Settings.


#include "itemPanel.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UitemPanel::Update()
{
	Image_ItemIcon->SetBrushFromTexture(ItemStruct->itemImage);
	ItemName->SetText(FText::FromString(ItemStruct->itemName));
	DescText->SetText(FText::FromString(ItemStruct->itemDescription));
}

void UitemPanel::SetItemInfo(FItemStruct* Item)
{
	ItemStruct = Item;
	Update();
}
