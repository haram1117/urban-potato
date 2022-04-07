// Fill out your copyright notice in the Description page of Project Settings.


#include "MapAreaTrigger.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void AMapAreaTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnActorEndOverlap.AddDynamic(this, &AMapAreaTrigger::OnEndOverlapActor);

}

void AMapAreaTrigger::OnEndOverlapActor(AActor* Overlapped, AActor* Other)
{
	AActor* player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Other == player)
	{
		UE_LOG(LogTemp, Error, TEXT("hi2"));
		player->Destroy();
	}
}
