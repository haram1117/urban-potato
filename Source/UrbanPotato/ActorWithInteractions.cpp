// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithInteractions.h"
#include "PlayerCharacter.h"

// Sets default values
AActorWithInteractions::AActorWithInteractions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorWithInteractions::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	widget = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("Widget")));
}

void AActorWithInteractions::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && !isWidgetVisible)
	{
		widget->SetVisibility(true);
		isWidgetVisible = true;
		PlayerCharacter->SetInteractionActor(this);
	}
}

void AActorWithInteractions::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if(OtherActor == Cast<AActor>(PlayerCharacter) && isWidgetVisible)
	{
		widget->SetVisibility(false);
		isWidgetVisible = false;
		PlayerCharacter->UnSetInteractionActor();
	}
}

// Called every frame
void AActorWithInteractions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

