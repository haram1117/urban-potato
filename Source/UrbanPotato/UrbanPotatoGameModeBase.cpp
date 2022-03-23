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
