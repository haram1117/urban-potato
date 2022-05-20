// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_widget.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API UNPC_widget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TotalDiceValueText;

public:
	void Update(int value);
};
