// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

// TODO: Toss object with left mouse button, with direction and force.
// Leave objects rotaion to where it is.
// Rotate object with mouse key, may have to use a toggle system
//  may have to rotate the object its self on its local axis(?)
// Set/drop with right mouse.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
  
private:

  UPROPERTY(EditAnyWhere)
  float LineReachEnd = 100.0f;
  
  UPhysicsHandleComponent* PhysicsHandle = nullptr;
  UInputComponent* InputComponent = nullptr;
  
  // Raycast and grab whats in reach
  void Grab();
  
  // If object in possession, release that object.
  void Release();
  
  // Find (assumed) attached UPhysicsHandleComponent
  void FindPhysicsHandleComponent();
  
  // Setup (assumed) attached UInputComponent
  void SetupInputComponent();
  
  // Return hit for first physics body in reach
  const FHitResult GetFirstPhysicsBodyInReach();
  
  // Attach the actor in reach to the PhysicsHandle Component
  void AttachActorToPhysicsHandle();
};
