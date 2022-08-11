// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"


/**
 * 
 */
class URBANPOTATO_API SoundEvent
{
public:
	SoundEvent();
	~SoundEvent();
private:
	/**
	 * @brief Dialog Text 효과음
	 */
	USoundWave* DialogSound;

	/**
	 * @brief 캐릭터가 걸을 때 효과음
	 */
	USoundWave* WalkingSound;

	/**
	 * @brief 퍼즐 클리어 시 효과음
	 */
	USoundWave* ClearSound;

public:
	// void PlayDialogSound(AMyPlayerController* PlayerController);
	
};
