// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ActorWithInteractions.generated.h"
class APlayerCharacter;
UCLASS()
class URBANPOTATO_API AActorWithInteractions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithInteractions();
	
	/**
	 * @brief 액터 overlap 진입 시 켜지는 Widget
	 */
	UWidgetComponent* widget;
	
	/**
	 * @brief 해당 퍼즐 클리어 여부
	 */
	UPROPERTY(BlueprintReadWrite)
	bool isClear = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	/**
	 * @brief PlayerCharacter
	 */
	APlayerCharacter* PlayerCharacter;
	
	/**
	 * @brief interaction 위젯 visible 여부 (Actor Overlap 여부)
	 */
	UPROPERTY(BlueprintReadWrite)
	bool isWidgetVisible = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief 각 Actor 마다 implement: 캐릭터와의 상호작용 호출 함수
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Interaction();
	
	/**
	 * @brief 게이지 위젯 비활성화 (버튼 인터랙션 시)
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void GaugeWidgetOff();
	
	/**
	 * @brief ActorWithInteraction 위젯 비활성화 (Actor Overlap X)
	 */
	UFUNCTION(BlueprintCallable)
	void WidgetOff();
	
	/**
	 * @brief ActorWithInteraction 위젯 활성화 (Actor Overlap O)
	 */
	UFUNCTION(BlueprintCallable)
	void WidgetOn();

};
