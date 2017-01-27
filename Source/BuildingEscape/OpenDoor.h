// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BuildingEscape.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnOpenRequest );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

  void OpenDoor();
  void CloseDoor();
private:
  AActor* Owner = nullptr;
  
  UPROPERTY(EditAnywhere)
  float OpenAngle = -90.0f;
  
  UPROPERTY(EditAnywhere)
  ATriggerVolume* PressurePlate = nullptr;
  
  UPROPERTY(EditAnywhere)
  float DoorCloseDelay = 1.0f;
  
  UPROPERTY(BlueprintAssignable)
  FOnOpenRequest OnOpenRequest;
  
  float LastDoorOpenTime;
	
  // Returns total mass in KG.
  float GetTotalMassOfActorsOnPlate();
};
