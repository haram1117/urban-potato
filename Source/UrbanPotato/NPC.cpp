// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	widget = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("Widget")));

}

void ANPC::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && !isWidgetVisible)
	{
		PlayerCharacter->SetNPCInBoundary(this);
	}
}

void ANPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && isWidgetVisible)
	{
		PlayerCharacter->UnSetNPCInBoundary(this);
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::WidgetOff()
{
	widget->SetVisibility(false);
	isWidgetVisible = false;
}

void ANPC::WidgetOn()
{
	widget->SetVisibility(true);
	isWidgetVisible = true;
}

