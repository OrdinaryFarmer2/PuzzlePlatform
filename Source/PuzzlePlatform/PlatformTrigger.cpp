// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"
#include "GameFramework/Character.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetBoxExtent(FVector(50.f, 50.f, 16.f));
	SetRootComponent(TriggerVolume);

	PressurePad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressuredPad"));
	PressurePad->SetupAttachment(TriggerVolume);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerVolumeBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTriggerVolumeEndOverlap);

	if (LinkedMovingPlatform.IsValid())
	{
		LinkedMovingPlatform.Get()->DeactivateRoundTrip();
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnTriggerVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor);

	if (OverlappingCharacter == nullptr)
	{
		return;
	}
	
	if (LinkedMovingPlatform.IsValid())
	{
		LinkedMovingPlatform.Get()->ActivateRoundTrip();
	}
}

void APlatformTrigger::OnTriggerVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OverlappingCharacters;	
	TriggerVolume->GetOverlappingActors(OverlappingCharacters, ACharacter::StaticClass());

	if (OverlappingCharacters.Num() > 0)
	{
		return;
	}
	
	if (LinkedMovingPlatform.IsValid())
	{
		LinkedMovingPlatform.Get()->DeactivateRoundTrip();
	}
}
