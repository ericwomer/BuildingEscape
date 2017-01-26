// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
  
  FindPhysicsHandleComponent();
  SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
  if(PhysicsHandle->GetGrabbedComponent())
  {
    PhysicsHandle->SetTargetLocation(GetReachLineEnd());
  }
}

void UGrabber::Grab()
{
  FHitResult HitResult = GetFirstPhysicsBodyInReach();
  auto ComponentToGrab = HitResult.GetComponent(); // Mesh in our case
  auto ActorHit = HitResult.GetActor();
  
  if(ActorHit)
  {
    PhysicsHandle->GrabComponent( // AtLocationWithRotation(
      ComponentToGrab,
      NAME_None, // No bones needed.
      ComponentToGrab->GetOwner()->GetActorLocation(),
      true // ComponentToGrab->GetOwner()->GetActorRotation()
    );
  }
}

void UGrabber::Release()
{
  PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
  // Look for attached physics handle
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if(!PhysicsHandle)
  {
    UE_LOG(LogTemp, Error, TEXT("%s, failed to aquire UPhysicsHandleComponent!"), *(GetOwner()->GetName()))
  }
}

void UGrabber::SetupInputComponent()
{
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if(InputComponent)
  {
    InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("%s, failed to aquire UInputComponent!"), *(GetOwner()->GetName()))
  }
}

//
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
  // Line trace/ray cast out to distance
  FHitResult HitResult;
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
  GetWorld()->LineTraceSingleByObjectType(
    OUT HitResult,
    GetReachLineStart(),
    GetReachLineEnd(),
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    TraceParameters
  );
  return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}
