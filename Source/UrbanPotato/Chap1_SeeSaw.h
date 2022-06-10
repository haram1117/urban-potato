// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_widget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Chap1_SeeSaw.generated.h"

class AItem;
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
	UNPC_widget* NPCWidget_BP;
	UPROPERTY(BlueprintReadWrite)
	int DiceNum = 29;
	int dicePosIndex = 0;
	int TotalDiceValue = 0;
	UPROPERTY(BlueprintReadWrite)
	TArray<int> DicesValue;
	UPROPERTY(BlueprintReadWrite)
	bool AllDiceOnSeeSaw = false;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* SeeSawCamera;
	UPROPERTY(BlueprintReadWrite)
	bool IsSeeSawFinished = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItem* FerrisWheelKey;
	TArray<AActor*> ferris_array;

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
	int GetDiceValue(int value);
	UFUNCTION(BlueprintCallable)
	void SetDiceValue(int index, int value);
	void SetBodyRotation();
	void SeeSawClear();
	UFUNCTION(BlueprintImplementableEvent)
	void DicesWidgetOff();
};
