// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "itemPanel.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API UitemPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	void Update();
	void SetItemInfo(FItemStruct* ItemStruct);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* ItemPanel;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DescText;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemCount;
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_ItemIcon;
private:
	FItemStruct* ItemStruct;
};

inline void UitemPanel::NativeConstruct()
{
	Super::NativeConstruct();
}