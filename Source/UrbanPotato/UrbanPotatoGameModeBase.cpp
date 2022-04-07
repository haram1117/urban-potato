// Copyright Epic Games, Inc. All Rights Reserved.


#include "UrbanPotatoGameModeBase.h"

#include "MyPlayerController.h"
#include "PlayerCharacter.h"

AUrbanPotatoGameModeBase::AUrbanPotatoGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	DefaultPawnClass = APlayerCharacter::StaticClass();
	GameStateClass = AGameStateBase::StaticClass();
	HUDClass = AHUD::StaticClass();
	PlayerStateClass = APlayerState::StaticClass();
	SpectatorClass = ASpectatorPawn::StaticClass();
	
}

void AUrbanPotatoGameModeBase::PlayerRespawn()
{
	UE_LOG(LogTemp, Log, TEXT("Respawn"));
	AActor* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector respawnLocation = FVector(player->GetActorLocation().X - 10.0f, player->GetActorLocation().Y, player->GetActorLocation().Z);
	FTransform actortransform;
	actortransform.SetLocation(respawnLocation);
	actortransform.SetRotation(player->GetActorRotation().Quaternion());
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	player->Destroy();
	UBlueprintGeneratedClass* BPC_PlayerCharacter = LoadObject<UBlueprintGeneratedClass>(NULL, TEXT("Blueprint'/Game/Base/BP/MyPlayerCharacter.MyPlayerCharacter_C'"), NULL, LOAD_None, NULL);
	// = Cast<APlayerCharacter>(BPC_PlayerCharacter);
	APlayerCharacter* NewPlayerCharacter;
	// NewPlayerCharacter->SetPlayerController(PlayerController);/
	NewPlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(BPC_PlayerCharacter->StaticClass());
	PlayerController->Possess(NewPlayerCharacter);

}
