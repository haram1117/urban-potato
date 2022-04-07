// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSafeArea.h"

#include "PlayerCharacter.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapSafeArea::AMapSafeArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapSafeArea::BeginPlay()
{
	Super::BeginPlay();
	SplineComponent = FindComponentByClass<USplineComponent>();
	
}

void AMapSafeArea::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		int num = SplineComponent->GetNumberOfSplinePoints();
		UE_LOG(LogTemp, Error, TEXT("HIHIHI"));
		FVector tempLoc = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		FVector playerLoc = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
		FRotator playerRot = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorRotation();
		float distance = FVector::Dist(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World), playerLoc);
		float distance1;
		int pointIndex = 0;
		for(int i = 0; i < num; i++)
		{
			distance1 = FVector::Dist(SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World), playerLoc);
			if(distance > distance1)
			{
				distance = distance1;
				pointIndex = i;
			}
		}
		Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetInsideMap(SplineComponent->GetLocationAtSplinePoint(pointIndex, ESplineCoordinateSpace::World), playerRot);
	}
	
}

// Called every frame
void AMapSafeArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

