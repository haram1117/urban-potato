// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ItemSlot.generated.h"
/**
 * 
 */
struct FItemStruct;
UCLASS()
class URBANPOTATO_API UItemSlot : public UButton
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	bool IsEmptySlot;
	bool IsUsingItemSlot = false;
	FItemStruct* slotItem;

public:
	bool IsEmpty();
	FItemStruct* GetSlotItem();
	void SetSlotItem(FItemStruct* _slotItem);
	void SetSlotIcon();
	UFUNCTION(BlueprintCallable)
	void SetUsingItem(int id);
	void ResetSlotIcon();
	UFUNCTION(BlueprintCallable)
	void RemoveSlotItem();
	void SetIsUsingItemSlot(bool value);
};
