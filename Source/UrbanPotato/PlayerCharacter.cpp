// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "ActorWithInteractions.h"
#include "Item.h"
#include "ActorWithInteractions.h"
#include "NPC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	if(!forward_Moving && !right_Moving)
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Idle;
	}
	else if(bPressedJump)
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Jump;
	}
	else if(bPressedRun)
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Run;
	}
	else
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Walk;
		UGameplayStatics::PlaySoundAtLocation(this, walkSound, GetActorLocation(), GetActorRotation());
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	_PlayerInputComponent = PlayerInputComponent;
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("1", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<1>);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<2>);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<3>);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<4>);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<5>);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<6>);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<7>);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<8>);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<9>);
	PlayerInputComponent->BindAction("0", IE_Pressed, this, &APlayerCharacter::SetInventory_UsingItem<0>);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::InventoryWidgetSet);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpEnd);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::RunStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::RunEnd);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &APlayerCharacter::Respawn);
	PlayerInputComponent->BindAction("GetItem", IE_Pressed, this, &APlayerCharacter::GetItem);
	PlayerInputComponent->BindAction("Talk", IE_Pressed, this, &APlayerCharacter::Talk);
}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotation()), value);

	if(value == 0)
		forward_Moving = false;
	else
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Walk;
		forward_Moving = true;
	}
}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotation()), value);
	if(value == 0)
		right_Moving = false;
	else
	{
		CharacterMovementEnum = ECharacterMovementEnum::E_Walk;
		right_Moving = true;
	}
}

void APlayerCharacter::JumpStart()
{
	bPressedJump = true;
	CharacterMovementEnum = ECharacterMovementEnum::E_Jump;
}

void APlayerCharacter::JumpEnd()
{
	bPressedJump = false;
	CharacterMovementEnum = ECharacterMovementEnum::E_Idle;
}

void APlayerCharacter::RunStart()
{
	bPressedRun = true;
	GetCharacterMovement()->MaxWalkSpeed = 2000;
	CharacterMovementEnum = ECharacterMovementEnum::E_Run;
}

void APlayerCharacter::RunEnd()
{
	bPressedRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	CharacterMovementEnum = ECharacterMovementEnum::E_Walk;
}

void APlayerCharacter::Turn(float value)
{
	if(!IsInventoryOpened)
		AddControllerYawInput(value);
}

void APlayerCharacter::LookUp(float value)
{
	if(!IsInventoryOpened)
		AddControllerPitchInput(value);
}

void APlayerCharacter::InventoryWidgetSet()
{
	if(!IsInventoryOpened)
	{
		PlayerController->InventoryWidget->AddToViewport();
		PlayerController->bShowMouseCursor = true;
		SetInputMode();
		IsInventoryOpened = true;
	}
	else
	{
		PlayerController->InventoryWidget->RemoveFromViewport();
		PlayerController->bShowMouseCursor = false;
		UnSetInputMode();
		IsInventoryOpened = false;
	}
}

void APlayerCharacter::Talk()
{
	if(NPCInBoundary != nullptr)
	{
		NPCInBoundary->Talk();
	}
}

void APlayerCharacter::CheckAllPuzzlesFinished()
{
	ClearNum++;
	if(ClearNum >= 3)
	{
		PuzzleFinished();
	}
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
		ItemStruct->Item->ChangeItemCount(1);
		inventory.Add(ItemStruct);
		PlayerController->SetSlotItemToEmptySlot(ItemStruct); // 빈 slot에 아이템 넣기
	}else
	{
		FItemStruct* ItemStruct = FindInInventoryWithID(Item->itemID);
		ItemStruct->Item->SetNextItem(Item);
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
	PlayerController->InventoryWidget->ReSetTextBlockColor();
	for (auto Button : PlayerController->InventoryWidget->Buttons)
	{
		if(Button == removeItem->Item->ItemSlot)
		{
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
	if(IsUsingMapArea)
	{
		APlayerCharacter* nowPlayer = this;
		nowPlayer->SetActorLocation(location);
		nowPlayer->SetActorRotation(Rotator);
	}
}
void APlayerCharacter::SetItemInBoundary(AItem* item)
{
	AllWidgetsOff();
	if(ItemInBoundary != nullptr)
		UnSetItemInBoundary(ItemInBoundary);
	
	ItemInBoundary = item;
	item->WidgetOn();
}

void APlayerCharacter::UnSetItemInBoundary(AItem* item)
{
	ItemInBoundary = nullptr;
	item->WidgetOff();
}

void APlayerCharacter::SetNPCInBoundary(ANPC* npc)
{
	if(NPCInBoundary != nullptr)
		UnSetNPCInBoundary(NPCInBoundary);
	NPCInBoundary = npc;
	npc->WidgetOn();
}

void APlayerCharacter::UnSetNPCInBoundary(ANPC* npc)
{
	NPCInBoundary = nullptr;
	npc->WidgetOff();
}

void APlayerCharacter::SetInteractActorInBoundary(AActorWithInteractions* actor)
{
	AllWidgetsOff();
	//만약 ActorInBoundary에 이미 actor가 존재하면
	if(ActorInBoundary != nullptr)
		UnSetInteractActorInBoundary(ActorInBoundary); // 해당 actor unset
	ActorInBoundary = actor; // 현재 boundary에 들어온 actor를 ActorInBoundary로 설정하기
	actor->WidgetOn();
}

void APlayerCharacter::UnSetInteractActorInBoundary(AActorWithInteractions* actor)
{
	ActorInBoundary = nullptr;
	actor->WidgetOff();
}

void APlayerCharacter::SetIsUsingMapArea(bool flag)
{
	IsUsingMapArea = flag;
}

bool APlayerCharacter::GetIsUsingMapArea() const
{
	return IsUsingMapArea;
}

void APlayerCharacter::SetInputModeActive()
{
	IsInputModeActive = true;
	ActiveInputComponent();
}

void APlayerCharacter::SetInputModeInactive()
{
	IsInputModeActive = false;
	InActiveInputComponent();
}

void APlayerCharacter::ActiveInputComponent()
{
	Cast<AActor>(this)->EnableInput(PlayerController);
}

void APlayerCharacter::InActiveInputComponent()
{
	Cast<AActor>(this)->DisableInput(PlayerController);
}

void APlayerCharacter::AllWidgetsOff() const
{
	if(ActorInBoundary != nullptr)
		ActorInBoundary->WidgetOff();
	if(ItemInBoundary != nullptr)
		ItemInBoundary->WidgetOff();
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


