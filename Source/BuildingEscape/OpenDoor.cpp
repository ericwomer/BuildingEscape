// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
  Owner = GetOwner();
  
  FString ObjectName = Owner->GetName();
  FString ObjectPos = Owner->GetActorLocation().ToString(); // "X=Something; Y=Something else, etc;";
  FString ObjectRot = Owner->GetTransform().GetRotation().ToString();
  
  FRotator NewRotation = FRotator(0.0f, -90.0f, 0.0f);
  
  UE_LOG(LogTemp, Warning, TEXT("%s is at %s, rotation is %s"), *ObjectName, *ObjectPos, *ObjectRot);
	// ...
  
  Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

