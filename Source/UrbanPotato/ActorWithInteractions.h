// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ActorWithInteractions.generated.h"
class APlayerCharacter;
UCLASS()
class URBANPOTATO_API AActorWithInteractions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithInteractions();
	UWidgetComponent* widget;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(BlueprintReadOnly)
	bool isWidgetVisible = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Interaction();

};
