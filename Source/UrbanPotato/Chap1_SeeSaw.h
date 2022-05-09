// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Chap1_SeeSaw.generated.h"

UCLASS()
class URBANPOTATO_API AChap1_SeeSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChap1_SeeSaw();
	// UStaticMeshComponent* MassTable;
	UStaticMeshComponent* Body;
	UWidgetComponent* WidgetComponent;
	UWidgetComponent* NPC_widget;
	UPROPERTY(BlueprintReadWrite)
	int DiceNum = 29;
	TArray<USceneComponent*> DicePositions;
	int dicePosIndex = 0;
	UPROPERTY(BlueprintReadWrite)
	bool AllDiceOnSeeSaw = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	UFUNCTION(BlueprintCallable)
	bool CanInteract();
	UFUNCTION(BlueprintCallable)
	FVector GetRandomDicePos(int value);
	UFUNCTION(BlueprintCallable)
	int GetDiceValue(int value);
	UFUNCTION(BlueprintCallable)
	void IncreaseDicePosIndex();
	UFUNCTION(BlueprintCallable)
	int GetDicePosIndex();

};
