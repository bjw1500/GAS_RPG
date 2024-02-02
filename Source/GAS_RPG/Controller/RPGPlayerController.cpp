// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerController.h"
#include "Input/RPGInputComponent.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SplineComponent.h"
#include "RPGGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

ARPGPlayerController::ARPGPlayerController()
{
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");

}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerInputContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//뒤에 숫자는 입력 우선 순위.
		Subsystem->AddMappingContext(PlayerInputContext, 0);
	}

	bShowMouseCursor = true;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	URPGInputComponent* RPGInputComponent = CastChecked<URPGInputComponent>(InputComponent);
	if(RPGInputComponent)
	{ 
		RPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::Move);


		/*
			InputConfig DataAsset을 이용해서 액션 바인딩을 해준다.
				마우스 오른쪽 클릭 액션
				마우스 왼쪽 클릭 액션.
				1,2,3,4 버튼 액션.
		*/
		RPGInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}

}

void ARPGPlayerController::Tick(float DeltaSeconds)
{
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	/*
	플레이어 틱(Player Tick)
 
		플레이어 컨트롤러는 액터 클래스에서 상속받는 Tick() 함수 외에 PlayerTick() 이라는 별도의 틱 함수를 하나 더 가진다. 
		일반 Tick() 함수는 어디서나 작동하는 반면에, 
		PlayerTick() 함수는 Player Controller에 PlayerInput 객체가 있는 경우에만 호출된다. 
		따라서 로컬로 제어되는 Player Controller에서만 플레이어 틱이 호출된다. 
		이 말인 즉슨, 만약 멀티플레이 게임이라면 자기 자신의 플레이어 컨트롤러에서만 플레이어 틱이 호출된다는 것이다.
	*/
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();

}

void ARPGPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

URPGAbilitySystemComponent* ARPGPlayerController::GetASC()
{
	if (RPGASC == nullptr)
	{
		RPGASC = Cast<URPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}


	return RPGASC;
}

void ARPGPlayerController::AutoRun()
{
	if(bAutoRunning == false)
		return;

	if (APawn* ControllerPawn = GetPawn())
	{
		/*Spline 안에 있는 Vector들 중에서 제일 가까운 Vector찾기.*/
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);

		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControllerPawn->AddMovementInput(Direction);
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAccepttanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


void ARPGPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	//커서에 찍힌게 없으면 리턴.
	if(CursorHit.bBlockingHit == false)
		return;

	LastActor = ThisActor;
	ThisActor = Cast<IMonsterInterface>(CursorHit.GetActor());

	/*
		커서 이벤트 경우의 수
		1.Last Actor = null && This Actor = null
			X
		2.Last Actor && This Actor = null
			Un Last Actor
		3.	Last Actor = null && This Actor
			HighLight This Actor
		4.Last Actor && This Actor
			Un Last Actor, Highlight this Actor;
		5.Last Actor == This Actor
			X
	*/

	if (LastActor == nullptr && ThisActor == nullptr)
	{

	}
	else if (LastActor && ThisActor == nullptr)
	{
		LastActor->UnHighlightActor();
	}
	else if (LastActor == nullptr && ThisActor)
	{
		ThisActor->HighlightActor();
	}
	else if (LastActor && ThisActor)
	{
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();

	}
	else if(LastActor == ThisActor)
	{
		
	}

}


void ARPGPlayerController::Move(const FInputActionValue& InputActionValue)
{

	APawn* ControlledPawn = GetPawn();
	if (IsValid(ControlledPawn) ==  true)
	{
		FVector2D MovementVector = InputActionValue.Get<FVector2D>();
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Horizontal = MovementVector.X;
		//Vertical = MovementVector.Y;

		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::Printf(TEXT("%d %d"), MovementVector.Y, MovementVector.X));
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}

}

void ARPGPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *InputTag.ToString());
	if(GetASC() == nullptr)
		return;

	//GetASC()->AbilityInputTagPressed(InputTag);

	if (InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor != nullptr ? true : false;
		bAutoRunning = false;
	}

}	

void ARPGPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
	//마우스 왼쪽 클릭이 아니라면.
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	//타겟이 존재한다면 움직이는 왼쪽 클릭 버튼 이벤트 실행하지 말고, Ability를 실행한다.
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		//마우스 왼쪽 클릭 이벤트.
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination);
			if(NavPath == nullptr)
				return;

			Spline->ClearSplinePoints();
			for (const FVector& V : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(V, ESplineCoordinateSpace::World);
				DrawDebugSphere(GetWorld(), V, 8.f, 8, FColor::Green,false, 5.f);
			}
			CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
			bAutoRunning = true;

		}

		FollowTime = 0;
		bTargeting = false;
	}

}

void ARPGPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *InputTag.ToString());
	//if (GetASC() == nullptr)
	//	return;

	//GetASC()->AbilityInputTagHeld(InputTag);

	//들어온 이벤트의 태그가 왼쪽 클릭이 아니라면.
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	//마우스 왼쪽 클릭 이벤트라면 여기까지 진입.
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if(GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation());
			ControlledPawn->AddMovementInput(WorldDirection);
		}

	}
}
