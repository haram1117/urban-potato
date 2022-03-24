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
	
}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	PlayerCharacter->AddtoItemInventory(itemID);
	Destroy();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::GetItem()
{
	
}

void AItem::TakeOut()
{
}
