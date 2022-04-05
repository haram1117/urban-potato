// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "MapAreaTrigger.generated.h"

/**
 * 
 */
UCLASS()
class URBANPOTATO_API AMapAreaTrigger : public ATriggerVolume
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnEndOverlapActor(AActor* Overlapped, AActor* Other);
	
};
