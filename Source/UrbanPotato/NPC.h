// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithInteractions.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class URBANPOTATO_API ANPC : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();
	UWidgetComponent* widget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(BlueprintReadWrite)
	bool isWidgetVisible = false;
	UPROPERTY(BlueprintReadWrite)
	bool avoidStart = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Talk();
	UFUNCTION(BlueprintCallable)
	void WidgetOff();
	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AvoidCharacter();

};
