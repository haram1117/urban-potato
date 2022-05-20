// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_widget.h"

#include "Components/TextBlock.h"

void UNPC_widget::Update(int value)
{
	TotalDiceValueText->SetText(FText::FromString(FString::FromInt(value)));
}
