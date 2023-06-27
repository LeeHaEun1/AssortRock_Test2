// Fill out your copyright notice in the Description page of Project Settings.


#include "MathGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMathGameMode::BeginPlay()
{
	{
		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Main", AllActor);

		if (1 != AllActor.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> Main Actor Is nullptr"), __FUNCTION__, __LINE__);
			return;
		}

		MainActor = AllActor[0];
	}

	{
		// 한번에 완벽하게 치려고하지 않는다. 
		// 형태에 가까운 코드를 치고
		// 예외처리는 엄청 신경써서 해준다.
		// 예외에 걸리면 내가 뭘잘못 했는지 알아내게되고
		// 수정해 나가면서 완벽한 코드가 되게 된다.
		
		// 한번에 완벽한 코드를 치려는 사람들의 문제점
		// 그냥 아무것도 안하는것처럼 보인다.
		// 이 스타일의 사람들은 보통 재능이 어마어마합니다.
		// 10분만에 생각완료 20분만에 완벽한 코드 다침.
		// 재능이 없다. => 코드를 그냥 안치고 있다.
		
		// 문제를 쪼개서 하나하나를 대충쳐
		// 이게 동작안하는 상황을 예외를 잘 걸어놓는다.
		// 한발자국도 못나가는 사람이 있고
		// 자신이 무슨 코드를 생각했는지 나

		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Other", AllActor);

		if (1 != AllActor.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> Main Actor Is nullptr"), __FUNCTION__, __LINE__);
			return;
		}

		OtherActor = AllActor[0];
	}

}

void AMathGameMode::Tick(float _Delta) 
{
	if (nullptr == MainActor || nullptr == OtherActor)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == MainActor || nullptr == OtherActor)"), __FUNCTION__, __LINE__);
		return;
	}

	switch (OtherActorState)
	{
	case OtherState::Idle:
		break;
	case OtherState::Trace:
		OtherActor->AddActorLocalOffset(FVector::LeftVector);
		break;
	default:
		break;
	}
	

	// 액터간에 부모자식관계를 맺어줄수 있습니다.
	// MainActor->AddActorLocalOffset(FVector::LeftVector);

	//AActor* Main = nullptr;
	//AActor* Other = nullptr;

	//Other->GetActorLocation();

}