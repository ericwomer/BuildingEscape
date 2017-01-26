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
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
  if(GetTotalMassOfActorsOnPlate() > 50.0f) // TODO make param
  {
    OpenDoor();
    LastDoorOpenTime = GetWorld()->GetTimeSeconds();
  }
  
	// Check to see if its time to close the door.
  float CurrentTime = GetWorld()->GetTimeSeconds();
  
  if((CurrentTime - LastDoorOpenTime) >= DoorCloseDelay)
  {
    CloseDoor();
  }
  
}

void UOpenDoor::OpenDoor()
{
  // Set the door rotation
  Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

}

void UOpenDoor::CloseDoor()
{
  // Set the door rotation
  Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
  
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
  float TotalMass = 0.0f;
  
  // Find array of overlapping actors
  TArray<AActor*> OverlapingActors;
  PressurePlate->GetOverlappingActors(OUT OverlappingActors);
  
  // Iterate through them adding their mass.
  
  return TotalMass;
}
