// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

// Sets default values
AAgent::AAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = Mesh;
	Velocity = FVector(0.f);

}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAgent::Init(UStaticMeshComponent *mesh, int id){
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector loc = GetActorLocation();
	SetActorLocation(loc + Velocity);
}

