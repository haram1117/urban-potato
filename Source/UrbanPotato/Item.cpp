// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "PlayerCharacter.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	widget = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("Widget")));
}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && !isWidgetVisible)
	{
		widget->SetVisibility(true);
		isWidgetVisible = true;
		PlayerCharacter->SetItemInBoundary(this);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::ActorEnable()
{
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
}

void AItem::ActorDisable()
{
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
}

void AItem::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && isWidgetVisible)
	{
		widget->SetVisibility(false);
		isWidgetVisible = false;
		PlayerCharacter->UnSetItemInBoundary();
	}
}
