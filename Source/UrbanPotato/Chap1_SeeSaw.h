// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_widget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Chap1_SeeSaw.generated.h"

class AItem;
UCLASS()
class URBANPOTATO_API AChap1_SeeSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChap1_SeeSaw();
	/**
	 * @brief 시소 바디 Static Mesh
	 */
	UStaticMeshComponent* Body;
	
	/**
	 * @brief Overlap Widget Componenet
	 */
	UWidgetComponent* WidgetComponent;

	/**
	 * @brief NPC Overlap Widget Component
	 */
	UWidgetComponent* NPC_widget;

	/**
	 * @brief NPC_widget Blueprint
	 */
	UNPC_widget* NPCWidget_BP;
	
	/**
	 * @brief 주사위 퍼즐 Success 조건
	 */
	UPROPERTY(BlueprintReadWrite)
	int DiceNum = 29;

	/**
	 * @brief interaction 주사위 활성화를 위한 index
	 */
	int dicePosIndex = 0;
	
	/**
	 * @brief 현재 주사위 value
	 */
	int TotalDiceValue = 0;

	/**
	 * @brief 각 주사위 별 value 값
	 */
	UPROPERTY(BlueprintReadWrite)
	TArray<int> DicesValue;

	/**
	 * @brief 모든 주사위가 시소 위에 있는 지 판별
	 */
	UPROPERTY(BlueprintReadWrite)
	bool AllDiceOnSeeSaw = false;
	
	/**
	 * @brief 시소 퍼즐 clear
	 */
	UPROPERTY(BlueprintReadWrite)
	bool IsSeeSawFinished = false;
	
	/**
	 * @brief 관람차 건전지 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItem* FerrisWheelKey;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	/**
	 * @brief 캐릭터와의 interaction 가능 여부 판단
	 */
	UFUNCTION(BlueprintCallable)
	bool CanInteract();

	/**
	 * @brief Set TotalDiceValue
	 * @param index dice Index
	 * @param value dice Value
	 */
	UFUNCTION(BlueprintCallable)
	void SetDiceValue(int index, int value);
	
	/**
	 * @brief 시소 퍼즐 클리어 시 수행
	 */
	void SeeSawClear();
	
	/**
	 * @brief Dice 상호작용 Widget Off
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void DicesWidgetOff();
};
