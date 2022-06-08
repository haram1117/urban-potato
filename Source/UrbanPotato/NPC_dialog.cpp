// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_dialog.h"

#include "Components/TextBlock.h"

void UNPC_dialog::StartDialog(FString text)
{
	DialogText->Text = FText::FromString("");
	startFlag = true;
	dialog = text;
	UE_LOG(LogTemp, Error, TEXT("%s"), *text);
	TextTyping();
}

void UNPC_dialog::EndDialog(float delayTime)
{
	startFlag = false;
	dialog = "";
}
