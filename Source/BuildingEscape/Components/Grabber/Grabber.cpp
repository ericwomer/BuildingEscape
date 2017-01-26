// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
  // UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
  
  FindPhysicsHandleComponent();
  SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
  if(PhysicsHandle->GetGrabbedComponent())
  {
    AttachActorToPhysicsHandle();
  }

}

void UGrabber::Grab()
{
  UE_LOG(LogTemp, Warning, TEXT("%s: grab"), *(GetOwner()->GetName()));
  
  FHitResult HitResult = GetFirstPhysicsBodyInReach();
  auto ComponentToGrab = HitResult.GetComponent();
  auto ActorHit = HitResult.GetActor();
  
  if(ActorHit)
  {
    PhysicsHandle->GrabComponentAtLocationWithRotation(
      ComponentToGrab,
      NAME_None,
      ComponentToGrab->GetOwner()->GetActorLocation(),
      ComponentToGrab->GetOwner()->GetActorRotation()
    );
  }
  
}

void UGrabber::Release()
{
  UE_LOG(LogTemp, Warning, TEXT("%s: release"), *(GetOwner()->GetName()));
  
  if(PhysicsHandle->GetGrabbedComponent())
  {
    PhysicsHandle->ReleaseComponent();
  }
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
    UE_LOG(LogTemp, Warning, TEXT("%s, aquired UInputComponent."), *(GetOwner()->GetName()))
    // Bind input action to a method
    // Add a way for pressing to grab and then pressing again to release.
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

  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  FVector LineTraceDirection = PlayerViewPointRotation.Vector();
  FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * LineReachEnd);
  
  // Set up collisions parameters
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
  
  // Line trace/ray cast out to distance
  FHitResult Hit;
  GetWorld()->LineTraceSingleByObjectType(
    OUT Hit,
    PlayerViewPointLocation,
    LineTraceEnd,
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    TraceParameters
  );
  
  return Hit;
}

void UGrabber::AttachActorToPhysicsHandle()
{
  
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  FVector LineTraceDirection = PlayerViewPointRotation.Vector();
  FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * LineReachEnd);
  
  PhysicsHandle->SetTargetLocation(LineTraceEnd);
  PhysicsHandle->SetTargetRotation(PlayerViewPointRotation);

}
