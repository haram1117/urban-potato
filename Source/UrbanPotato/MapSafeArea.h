// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "MapSafeArea.generated.h"

UCLASS()
class URBANPOTATO_API AMapSafeArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapSafeArea();
	USplineComponent* SplineComponent;
	APlayerCharacter* PlayerCharacter;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
