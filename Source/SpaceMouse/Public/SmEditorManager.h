// Copyright 1998-2019 David Morasz All Rights Reserved.

#pragma once

#include "SpaceMouseManager.h"
#include "Misc/App.h"
#include "Input/Events.h"
#include "TimerManager.h"

struct FInputActionKeyMapping;
class FEditorViewportClient;

class SPACEMOUSE_API FSmEditorManager : public FSpaceMouseManager
{
private:

	FTimerDelegate OnTickDel;

	bool bWasOrbitCamera = false;
	bool bWasRealtime = false;
	float LastOrbitDistance = 300;

	FEditorViewportClient* ActiveViewportClient = nullptr;
	FString focusedVpType = "";

	static FKeyEvent GetKeyEventFromKey(const FInputActionKeyMapping& mapping);
	static bool UseForceSetView(FEditorViewportClient* cvp);
	FVector GetOrbitingPosDeltaOffset(FRotator rotDelta);

public:

	static bool bStarted;

	int LastErrorCode = 0;

	FSmEditorManager() : FSpaceMouseManager() { }

	virtual void Initialize() override
	{
		FSpaceMouseManager::Initialize();

		OnTickDel = OnTickDel.CreateLambda([this]()
		{
			Tick(FApp::GetDeltaTime());
		});
		bWasOrbitCamera = false;
		bWasRealtime = false;
	}

	virtual void Tick(float DeltaSecs) override;
	void Start();
	void LearnButtonMappings();
	void LearnButtonMapping(int& target);
	void ManageActiveViewport();
	void MoveActiveViewport(FVector trans, FRotator rot);
	const bool IsActiveViewportInvalid(const TArray<FEditorViewportClient*>& AllViewportClients);
};
