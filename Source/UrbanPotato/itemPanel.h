// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "itemPanel.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API UitemPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* ItemPanel;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DescText;
};
