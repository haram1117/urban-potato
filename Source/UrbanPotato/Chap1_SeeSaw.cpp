// Fill out your copyright notice in the Description page of Project Settings.


#include "Chap1_SeeSaw.h"

#include "PlayerCharacter.h"

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
	NPCWidget_BP = Cast<UNPC_widget>(NPC_widget->GetWidget());
	for(int i = 0; i < 6; i++)
	{
		DicesValue.Add(0);
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
		{
			WidgetComponent->SetVisibility(true);
		}
		NPC_widget->SetVisibility(true);
	}
}

void AChap1_SeeSaw::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		WidgetComponent->SetVisibility(false);
		NPC_widget->SetVisibility(false);
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

int AChap1_SeeSaw::GetDiceValue(int value)
{
	return DiceNum -= value;
}

void AChap1_SeeSaw::SetDiceValue(int index, int value)
{
	DicesValue[index] = value;
	int total = 0;
	for(int i = 0; i < 6; i++)
	{
		total += DicesValue[i];
	}
	TotalDiceValue = total;
	NPCWidget_BP->Update(DiceNum - TotalDiceValue);
	SetBodyRotation();
}

void AChap1_SeeSaw::SetBodyRotation()
{
	float difference = DiceNum - TotalDiceValue;
	FRotator Rotator;
	Rotator.Roll = Body->GetComponentRotation().Roll;
	Rotator.Pitch = (-1) * difference/8.0;
	Rotator.Yaw = Body->GetComponentRotation().Yaw;
	
	Body->SetRelativeRotation(Rotator);
}
