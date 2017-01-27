// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
  
  Owner = GetOwner();
  if(!Owner)
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to set owner!"))
  }
  
  if(!PressurePlate)
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing PressurePlate!"), *GetOwner()->GetName())
  }
  
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
  if(GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO make param
  {
    OnOpen.Broadcast();
  }
  else
  {
    OnClose.Broadcast();
  }
  
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
  float TotalMass = 0.0f;
  // Find array of overlapping actors
  TArray<AActor*> OverlappingActors;
  
  if(!PressurePlate){ return TotalMass; }  
  PressurePlate->GetOverlappingActors(OUT OverlappingActors);
  
  for(const auto* Actor : OverlappingActors)
  {
    TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
  }
  // Iterate through them adding their mass.
  
  return TotalMass;
}
