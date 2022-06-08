// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "Item.h"
#include "ActorWithInteractions.h"
#include "GameFramework/CharacterMovementComponent.h"
// #include "Tasks/GameplayTask_SpawnActor.h"

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
	CharacterMesh = GetMesh();
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
	PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &APlayerCharacter::Respawn);
	PlayerInputComponent->BindAction("GetItem", IE_Pressed, this, &APlayerCharacter::GetItem);
}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(FVector(1, 0, 0), value * XAxis);
	if(CharacterMesh == nullptr)
	{
		return;
	}
	if(value > 0)
	{
		FRotator Rotator;
		Rotator.Pitch = 0;
		Rotator.Roll = 0;
		Rotator.Yaw = -90 * XAxis;
		CharacterMesh->SetRelativeRotation(Rotator);
		
	}else if(value < 0)
	{
		FRotator Rotator;
		Rotator.Pitch = 0;
		Rotator.Roll = 0;
		Rotator.Yaw = -270 * XAxis;
		CharacterMesh->SetRelativeRotation(Rotator);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(FVector(0, 1, 0), value * YAxis);
	if(CharacterMesh == nullptr)
	{
		return;
	}
	if(value > 0)
	{
		FRotator Rotator;
		Rotator.Pitch = 0;
		Rotator.Roll = 0;
		if(YAxis == 1)
			Rotator.Yaw = 0;
		else
			Rotator.Yaw = -180;
		CharacterMesh->SetRelativeRotation(Rotator);
		
	}else if(value < 0)
	{
		FRotator Rotator;
		Rotator.Pitch = 0;
		Rotator.Roll = 0;
		if(YAxis == 1)
			Rotator.Yaw = -180;
		else
			Rotator.Yaw = 0;
		CharacterMesh->SetRelativeRotation(Rotator);
	}
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
	if(ActorInBoundary != nullptr)
	{
		ActorInBoundary->Interaction();
	}
	else
	{
		if(UsingItem != nullptr)
		{
			UsingItem->Use();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Nono");
		}
	}
}

void APlayerCharacter::GetItem_Implementation()
{
	if(ItemInBoundary != nullptr)
	{
		AddtoItemInventory(ItemInBoundary);
		ItemInBoundary->ActorDisable();
	}
}


void APlayerCharacter::AddtoItemInventory(AItem* Item)
{
	if(FindInInventoryWithID(Item->itemID) == nullptr) // 새로운 아이템일 경우
	{
		FItemStruct* ItemStruct = itemDatabase->FindRow<FItemStruct>(*FString::FromInt(Item->itemID), TEXT(""));
		ItemStruct->Item = Item;
		// ItemStruct->Item->itemCount++;
		ItemStruct->Item->ChangeItemCount(1);
		inventory.Add(ItemStruct);
		PlayerController->SetSlotItemToEmptySlot(ItemStruct); // 빈 slot에 아이템 넣기
	}else
	{
		FItemStruct* ItemStruct = FindInInventoryWithID(Item->itemID);
		ItemStruct->Item->SetNextItem(Item);
		// ItemStruct->Item->itemCount++;
		ItemStruct->Item->ChangeItemCount(1);
		PlayerController->SetSlotItemToEmptySlot(ItemStruct); // 빈 slot에 아이템 넣기
	}
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
		if(Button == removeItem->Item->ItemSlot)
		{
			// removeItem->Item->ChangeItemCount(-1);
			if(removeItem->Item->next == nullptr) // 남는 템 없음
			{
				Button->RemoveSlotItem();
				inventory.Remove(removeItem);
				break;
			}
			else
			{
				removeItem->Item->ItemSlot->SetIsUsingItemSlot(false);
				UsingItem = nullptr;
				removeItem->Item = removeItem->Item->next;
				PlayerController->SetSlotItemToEmptySlot(removeItem); // Update 용
				return;
			}
		}
	}
}

void APlayerCharacter::Respawn()
{
	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	FVector lastLoc = GetActorLocation();
	lastLoc -= FVector(20, 0, -30);
	APlayerCharacter* nowPlayer = this;
	nowPlayer->SetActorLocation(lastLoc);
}

void APlayerCharacter::GoInsideMap(FVector location, FRotator Rotator)
{
	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerCharacter* nowPlayer = this;
	nowPlayer->SetActorLocation(location);
	nowPlayer->SetActorRotation(Rotator);
}
void APlayerCharacter::SetItemInBoundary(AItem* item)
{
	AItem* tempItem	= ItemInBoundary;
	if(ItemInBoundary != nullptr)
	{
		while(tempItem->nextOverlap != nullptr)
		{
			tempItem = tempItem->nextOverlap;
		}
		tempItem->nextOverlap = item;	
	}
	else
	{
		ItemInBoundary = item;
	}
}

void APlayerCharacter::UnSetItemInBoundary(AItem* item)
{
	AItem* tempItem = ItemInBoundary;
	if(tempItem == nullptr)
		return;
	while (tempItem->nextOverlap != nullptr)
	{
		if(tempItem == item)
		{
			if(item->nextOverlap != nullptr)
			{
				// tempItem->next = item->next;
				tempItem = item->nextOverlap;
			}
			item->nextOverlap = nullptr;
			ItemInBoundary = tempItem;
			return;
		}
		else
		{
			tempItem = tempItem->nextOverlap;
		}
	}
	item->nextOverlap = nullptr;
	ItemInBoundary = nullptr;
}

void APlayerCharacter::SetInteractActorInBoundary(AActorWithInteractions* actor)
{
	AActorWithInteractions* tempActor = ActorInBoundary;
	if(ActorInBoundary != nullptr)
	{
		while(tempActor->nextOverlap != nullptr)
		{
			tempActor = tempActor->nextOverlap;
		}
		tempActor->nextOverlap = actor;	
	}
	else
	{
		ActorInBoundary = actor;
	}
}

void APlayerCharacter::UnSetInteractActorInBoundary(AActorWithInteractions* actor)
{
	AActorWithInteractions* tempActor = ActorInBoundary;
	if(tempActor == nullptr)
		return;
	while (tempActor->nextOverlap != nullptr)
	{
		if(tempActor == actor)
		{
			if(actor->nextOverlap != nullptr)
			{
				// tempActor->next = actor->next;
				tempActor = actor->nextOverlap;
			}
			actor->nextOverlap = nullptr;
			ActorInBoundary = tempActor;
			return;
		}
		else
		{
			tempActor = tempActor->nextOverlap;
		}
	}
	actor->nextOverlap = nullptr;
	ActorInBoundary = nullptr;
}

FItemStruct* APlayerCharacter::FindInInventoryWithID(int id)
{
	for (auto ItemStruct : inventory)
	{
		if(ItemStruct->itemID == id)
			return ItemStruct;
	}
	return nullptr;
}


