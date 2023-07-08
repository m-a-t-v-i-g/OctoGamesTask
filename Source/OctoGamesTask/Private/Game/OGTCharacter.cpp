// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/OGTCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/OGTInteractionComponent.h"
#include "Components/OGTStateComponent.h"
#include "Game/Interaction/OGTTrigger.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AOGTCharacter::AOGTCharacter()
{
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -96.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	GetCharacterMovement()->MaxAcceleration = 750.0;
	GetCharacterMovement()->BrakingFriction = 8.0;
	GetCharacterMovement()->bUseSeparateBrakingFriction = true;
	GetCharacterMovement()->GroundFriction = 1.5;
	GetCharacterMovement()->MaxWalkSpeed = 340.0;
	GetCharacterMovement()->BrakingDecelerationWalking = 350.0;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0);
	
	StateComponent = CreateDefaultSubobject<UOGTStateComponent>("State Component");

	InteractionComponent = CreateDefaultSubobject<UOGTInteractionComponent>("Interaction Component");
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(98.0, 50.0, 72.0);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default(TEXT("/Game/Blueprints/Player/Input/IMC_Default"));
	DefaultMappingContext = IMC_Default.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Game/Blueprints/Player/Input/Actions/IA_Move"));
	MoveAction = IA_Move.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Look(TEXT("/Game/Blueprints/Player/Input/Actions/IA_Look"));
	LookAction = IA_Look.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Aim(TEXT("/Game/Blueprints/Player/Input/Actions/IA_Aim"));
	AimAction = IA_Aim.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Interact(TEXT("/Game/Blueprints/Player/Input/Actions/IA_Interact"));
	InteractAction = IA_Interact.Object;
	
	PrimaryActorTick.bCanEverTick = true;

}

void AOGTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (GetCameraComponent())
	{
		FieldOfView = GetCameraComponent()->FieldOfView;
	}
}

void AOGTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	UpdateFieldOfView();
}

void AOGTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOGTCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOGTCharacter::Look);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AOGTCharacter::AimPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AOGTCharacter::AimReleased);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AOGTCharacter::CallInteract);
	}
}

void AOGTCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOGTCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * CameraSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * CameraSensitivity);
	}
}

void AOGTCharacter::AimPressed(const FInputActionValue& Value)
{
	if (!StateComponent || !CameraComponent) return;

	GetStateComponent()->SetCharacterState(ECharacterState::Aiming);
	FieldOfView = FieldOfViewMin;
}

void AOGTCharacter::AimReleased(const FInputActionValue& Value)
{
	if (!StateComponent || !CameraComponent) return;

	GetStateComponent()->SetCharacterState(ECharacterState::NotAiming);
	FieldOfView = FieldOfViewMax;
}

void AOGTCharacter::UpdateFieldOfView() const
{
	if (!CameraComponent) return;

	GetCameraComponent()->FieldOfView = UKismetMathLibrary::FInterpTo(GetCameraComponent()->FieldOfView, FieldOfView,
	                                                                  DeltaSeconds, 6.5);

	GEngine->AddOnScreenDebugMessage(20, 1.0, FColor::Cyan,
								 FString::Printf(
									 TEXT("FOV: %f"), CameraComponent->FieldOfView));
}

void AOGTCharacter::CallInteract()
{
	if (!InteractionComponent) return;

	InteractionComponent->CallInteract();
}
