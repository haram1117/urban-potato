// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "Item.h"
#include "Components/Button.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpEnd);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::RunStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::RunEnd);
}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(FVector(1, 0, 0), value);	
}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(FVector(0, 1, 0), value);
}

void APlayerCharacter::JumpStart()
{
	bPressedJump = true;
}

void APlayerCharacter::JumpEnd()
{
	bPressedJump = false;
}

void APlayerCharacter::RunStart()
{
	bPressedRun = true;
	GetCharacterMovement()->MaxWalkSpeed = 2000;
}

void APlayerCharacter::RunEnd()
{
	bPressedRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayerCharacter::AddtoItemInventory(int itemID)
{
	itemInventory.Add(itemID);
	FItemStruct* ItemStruct = itemDatabase->FindRow<FItemStruct>(*FString::FromInt(itemID), TEXT(""));
	// UE_LOG(LogTemp, Log, TEXT("%d 추가 되었습니다."), itemID);
	//
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %s 가 추가되었습니다. "), *ItemStruct->itemName));
	PlayerController->SetSlotImage(ItemStruct);
}

void APlayerCharacter::SetPlayerController(AMyPlayerController* player_Controller)
{
	PlayerController = player_Controller;
}
