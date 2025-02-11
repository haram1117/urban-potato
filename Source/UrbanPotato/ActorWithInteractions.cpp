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
		if(isClear)
			return;
		// widget->SetVisibility(true);
		// isWidgetVisible = true;
		WidgetOn();
		PlayerCharacter->SetInteractActorInBoundary(this);
	}
}

void AActorWithInteractions::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if(OtherActor == Cast<AActor>(PlayerCharacter) && isWidgetVisible)
	{
		if(isClear)
			return;
		// widget->SetVisibility(false);
		// isWidgetVisible = false;
		WidgetOff();
		PlayerCharacter->UnSetInteractActorInBoundary(this);
	}
}

// Called every frame
void AActorWithInteractions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorWithInteractions::WidgetOff()
{
	widget->SetVisibility(false);
	isWidgetVisible = false;
	GaugeWidgetOff();
}

void AActorWithInteractions::WidgetOn()
{
	widget->SetVisibility(true);
	isWidgetVisible = true;
}

