// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundEvent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

SoundEvent::SoundEvent()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USoundWave> DialogSoundAsset;
		ConstructorHelpers::FObjectFinder<USoundWave> WalkingSoundAsset;
		ConstructorHelpers::FObjectFinder<USoundWave> ClearSoundAsset;
		FConstructorStatics()
			: DialogSoundAsset(TEXT("SoundWave'/Game/Sounds/dialog_SW.dialog_SW'"))
			, WalkingSoundAsset(TEXT("SoundWave'/Game/Sounds/Walk.Walk'"))
			, ClearSoundAsset(TEXT("SoundWave'/Game/Sounds/clearSound.clearSound'"))
		{}
	};

	static FConstructorStatics ConstructorStatics;

	if (ConstructorStatics.DialogSoundAsset.Succeeded())
		DialogSound = ConstructorStatics.DialogSoundAsset.Object;
	if (ConstructorStatics.WalkingSoundAsset.Succeeded())
		WalkingSound = ConstructorStatics.WalkingSoundAsset.Object;
	if (ConstructorStatics.ClearSoundAsset.Succeeded())
		ClearSound = ConstructorStatics.ClearSoundAsset.Object;
}

SoundEvent::~SoundEvent()
{
}

void SoundEvent::PlayDialogSound(AMyPlayerController* PlayerController)
{
	// UGameplayStatics::PlaySound2D(PlayerController, DialogSound);
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-15, 1.0f, FColor::Blue, TEXT("Finally"));
	}
}
