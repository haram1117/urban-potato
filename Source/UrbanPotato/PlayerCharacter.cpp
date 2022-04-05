// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "Item.h"
#include "UrbanPotatoGameModeBase.h"
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
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerCharacter::Interact);
	// PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &APlayerCharacter::Respawn);
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

void APlayerCharacter::Interact()
{
	if(UsingItem != nullptr)
		UsingItem->Use();
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Nono");
	}
}

void APlayerCharacter::AddtoItemInventory(int itemID)
{
	// itemInventory.Add(itemID);
	FItemStruct* ItemStruct = itemDatabase->FindRow<FItemStruct>(*FString::FromInt(itemID), TEXT(""));
	inventory.Add(ItemStruct);
	PlayerController->SetSlotItemToEmptySlot(ItemStruct); // 빈 slot에 아이템 넣기
}

void APlayerCharacter::SetPlayerController(AMyPlayerController* player_Controller)
{
	PlayerController = player_Controller;
}

FItemStruct* APlayerCharacter::FindItemFromRow(int itemID)
{
	FItemStruct* ItemStruct = itemDatabase->FindRow<FItemStruct>(*FString::FromInt(itemID), TEXT(""));
	return ItemStruct;
}

void APlayerCharacter::RemoveFromItemInventory(FItemStruct* removeItem)
{
	for (auto Button : PlayerController->InventoryWidget->Buttons)
	{
		if(Button->GetSlotItem() == removeItem)
		{
			Button->RemoveSlotItem();
			inventory.Remove(removeItem);
			break;
		}
	}
}

void APlayerCharacter::Respawn(AActor* actor)
{
	AUrbanPotatoGameModeBase* GameModeBase = Cast<AUrbanPotatoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	// UE_LOG(LogTemp, Log, TEXT("Respawn"));
	// FVector respawnLocation = FVector(this->GetActorLocation().X - 10.0f, this->GetActorLocation().Y, this->GetActorLocation().Z);
	// FTransform actortransform;
	// actortransform.SetLocation(respawnLocation);
	// actortransform.SetRotation(this->GetActorRotation().Quaternion());
	// GameModeBase->RestartPlayerAtTransform(PlayerController, actortransform);
	GameModeBase->PlayerRespawn();
}

void APlayerCharacter::Respawn()
{
	AUrbanPotatoGameModeBase* GameModeBase = Cast<AUrbanPotatoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBase->PlayerRespawn();
	
}


