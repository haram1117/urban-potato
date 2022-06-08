// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_dialog.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API UNPC_dialog : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	class UTextBlock* DialogText;
	UPROPERTY(BlueprintReadWrite)
	bool startFlag;
	UPROPERTY(BlueprintReadWrite)
	FString dialog;
	UFUNCTION(BlueprintCallable)
	void StartDialog(FString text);
	UFUNCTION(BlueprintCallable)
	void EndDialog(float delayTime);
	UFUNCTION(BlueprintImplementableEvent)
	void TextTyping();
};
