// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "FlockingGameMode.generated.h"

UCLASS(minimalapi)
class AFlockingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFlockingGameMode();
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent * AgentMesh;

	UPROPERTY() UFlockingManager *Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};



