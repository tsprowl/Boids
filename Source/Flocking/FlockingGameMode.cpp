// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FlockingGameMode.h"
#include "FlockingCharacter.h"
#include "FlockingManager.h"
#include "UObject/ConstructorHelpers.h"

AFlockingGameMode::AFlockingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AFlockingGameMode::BeginPlay(){
	    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UFlockingManager>();
    Manager->Init(GetWorld(), AgentMesh);
}

void AFlockingGameMode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	Manager->Flock();
}
