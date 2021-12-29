// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	/** 도착할 목적지입니다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving", meta=(AllowPrivateAccess="true", MakeEditWidget="true"))
	FVector TargetLocation;

	/** 타겟위치까지 갔을 때, 현재 위치와 목적지와의 거리오차 허용치입니다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving", meta=(AllowPrivateAccess="true", MakeEditWidget="true"))
	float LocationTolerance;

	/** 이동 보간 속도입니다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving", meta=(AllowPrivateAccess="true"))
	float MovingInterpSpeed;

	FVector PointA;

	FVector PointB;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};
