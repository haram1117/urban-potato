// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "PlayerCharacter.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	widget = Cast<UWidgetComponent>(GetDefaultSubobjectByName(TEXT("Widget")));
	StaticMeshComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mesh")));
}


void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && !isWidgetVisible)
	{
		PlayerCharacter->SetItemInBoundary(this);
	}
}

void AItem::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(OtherActor == Cast<AActor>(PlayerCharacter) && isWidgetVisible)
	{
		PlayerCharacter->UnSetItemInBoundary(this);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::ActorEnable(FVector Location, FRotator Rotator)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	this->SetActorLocationAndRotation(Location, Rotator);
	
	this->SetActorHiddenInGame(false);
	StaticMeshComponent->SetEnableGravity(true);
	this->SetActorEnableCollision(true);
	
	PlayerCharacter->RemoveFromItemInventory(this->ItemSlot->GetSlotItem());
}

void AItem::ActorDisable()
{
	LastRotator = GetActorRotation();
	this->SetActorHiddenInGame(true);
	StaticMeshComponent->SetEnableGravity(false);
	this->SetActorEnableCollision(false);
}

void AItem::SetNextItem(AItem* NextItem)
{
	AItem* nextTemp = next;
	if(nextTemp == nullptr)
	{
		next = NextItem;
		return;
	}
	while(nextTemp->next != nullptr)
	{
		nextTemp = nextTemp->GetNextItem();
	}
	nextTemp->next = NextItem;
}

void AItem::ChangeItemCount(int value)
{
	AItem* temp = this;
	while (temp != nullptr)
	{
		temp->itemCount += value;
		temp = temp->next;
	}
}

void AItem::SetItemSlotToEveryItem(UItemSlot* Slot)
{
	AItem* temp = this;
	while (temp != nullptr)
	{
		temp->ItemSlot = Slot;
		temp = temp->next;
	}
}

void AItem::RemoveFromInventory_Item(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->RemoveFromItemInventory(this->ItemSlot->GetSlotItem());
}

AItem* AItem::GetNextItem()
{
	return next;
}

void AItem::WidgetOff()
{
	widget->SetVisibility(false);
	isWidgetVisible = false;
}

void AItem::WidgetOn()
{
	widget->SetVisibility(true);
	isWidgetVisible = true;
}

