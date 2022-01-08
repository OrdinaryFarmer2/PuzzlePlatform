// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Kismet/KismetMathLibrary.h"

AMovingPlatform::AMovingPlatform()
	: TargetLocation(100.f, 0.f, 0.f)
	, LocationTolerance(1.f)
	, MovingInterpSpeed(5.f)
	, bRoundTripActivated(true)
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	
	bReplicates = true;
	SetReplicatingMovement(true);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	PointA = GetActorLocation();
	PointB = UKismetMathLibrary::TransformLocation(GetActorTransform(), TargetLocation);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority() || bRoundTripActivated == false)
	{
		return;
	}

	const FVector LerpPoint = UKismetMathLibrary::VInterpTo(GetActorLocation(), PointB, DeltaSeconds, MovingInterpSpeed);
	SetActorLocation(LerpPoint);

	if (GetActorLocation().Equals(PointB, LocationTolerance))
	{
		const FVector Temp = PointA;
		PointA = PointB;
		PointB = Temp;
	}
}
