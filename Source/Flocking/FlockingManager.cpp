// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 20

void UFlockingManager::Init(UWorld *world, UStaticMeshComponent *mesh){
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;
    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++){
        if (World != nullptr){
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Y = FMath::Cos(incr * i) * 150.f;
            location.Z = FMath::RandRange(0.f, 10.0f);

            AAgent * agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock(){
    FVector v1, v2, v3, v4;

    AAgent* boid;

    int vlim = 20;

    
    for (int i = 0; i < Agents.Num(); i++){
         boid = Agents[i];

        v1 = rule1(boid);
        v2 = rule2(boid);
        v3 = rule3(boid);
        //v4 = rule4(boid);

        
        boid->Velocity = boid->Velocity + v1 + v2 + v3;
        
        if ((boid->Velocity).Size() > vlim){
            boid->Velocity = (boid->Velocity / boid->Velocity.Size()) * vlim;
       }
       if (boid->GetActorLocation().Z < 1){
           float tempX = boid->GetActorLocation().X;
           float tempY = boid->GetActorLocation().Y;
           float tempZ = boid->GetActorLocation().Z + 5;
           FVector temp = FVector(tempX, tempY, tempZ);
           boid->SetActorLocation(temp);
       }
        boid->GetRootComponent()->SetWorldLocation(boid->GetActorLocation() + boid->Velocity);
        
    }
    


}

FVector UFlockingManager::rule1(AAgent* boid){
    
    FVector vector;
    AAgent * b;
    for (int i = 0; i < Agents.Num(); i++){
        b = Agents[i];

        if (b != boid){
            vector = vector + b->GetActorLocation();
        }
    }

    vector = vector / AGENT_COUNT - 1;

    return (vector - boid->GetActorLocation()) / 100;
}

 
FVector UFlockingManager::rule2(AAgent* boid){

    FVector vector = FVector(0.f);
    AAgent * b;

    for (int i = 0; i < Agents.Num(); i++){
        b = Agents[i];

        if (b != boid){
            if (((b->GetActorLocation() - boid->GetActorLocation()).Size()) < 120){
                vector = vector - (b->GetActorLocation() - boid->GetActorLocation());
            }
        }
    }

    return vector;
}

FVector UFlockingManager::rule3(AAgent* boid){

    FVector vector;
    AAgent * b;

    for (int i = 0; i < Agents.Num(); i++){
        b = Agents[i];

        if (b != boid){
            vector = vector + b->Velocity;
        }
    }

    vector = vector / (AGENT_COUNT - 1);

    return ((vector - boid->Velocity) / 8);
}

FVector UFlockingManager::rule4(AAgent* boid){
    FVector place = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

    //FVector place = GetPlayerPawn()->GetActorLocation();



        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *place.ToString()));


    
    return (place - (boid->GetActorLocation())) / 100;
}
// RULE 3 (boid Q) (MATCH SPEED)

// Vector x

// for each boid b
    // if b != Q
        // x = x + b.velocity

// x = x / n - 1

// return (x = Q.velocity) / 8
