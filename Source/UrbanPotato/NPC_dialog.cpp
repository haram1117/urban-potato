// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_dialog.h"

#include "MyPlayerController.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UNPC_dialog::StartDialog(FString text)
{
	DialogText->Text = FText::FromString("");
	startFlag = true;
	dialog = text;
	playDialog_delegate.Execute(Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)));
	TextTyping();
}

void UNPC_dialog::EndDialog(float delayTime)
{
	startFlag = false;
	dialog = "";
}
