// Fill out your copyright notice in the Description page of Project Settings.


#include "Chap1_SeeSaw.h"

#include <string>

#include "PlayerCharacter.h"
#include "Widgets/Input/SEditableTextBox.h"
// Sets default values
AChap1_SeeSaw::AChap1_SeeSaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChap1_SeeSaw::BeginPlay()
{
	Super::BeginPlay();
	// MassTable = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("MassTable")));
	Body = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Body")));
	WidgetComponent = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("Widget")));
	NPC_widget = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("NPC_widget")));
	for(int i = 0; i < 6; i++)
	{
		FString diceNum = "Dicepos" + FString::FromInt(i + 1);
		USceneComponent* DicePosition = Cast<USceneComponent>(GetDefaultSubobjectByName(FName(diceNum)));
		DicePositions.Add(DicePosition);
	}
}

// Called every frame
void AChap1_SeeSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChap1_SeeSaw::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if(!AllDiceOnSeeSaw)
			WidgetComponent->SetVisibility(true);
	}
}

void AChap1_SeeSaw::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		WidgetComponent->SetVisibility(false);
	}
}

bool AChap1_SeeSaw::CanInteract()
{
	if(WidgetComponent->IsVisible())
		return true;
	else
	{
		return false;
	}
}

FVector AChap1_SeeSaw::GetRandomDicePos(int value)
{
	FVector dicePos = DicePositions[value]->GetComponentLocation();
	return dicePos;
}


int AChap1_SeeSaw::GetDiceValue(int value)
{
	return DiceNum -= value;
}

void AChap1_SeeSaw::IncreaseDicePosIndex()
{
	dicePosIndex++;
}

int AChap1_SeeSaw::GetDicePosIndex()
{
	return dicePosIndex;
}
