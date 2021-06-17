﻿// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_3DX_NAVLIB

#include "Misc/App.h"
#include "Navlib/TDxNavContext.h"

#include "SpaceMouseReader.h"

FTDxNavContextBase::FTDxNavContextBase()
{
}

FTDxNavContextBase::~FTDxNavContextBase()
{
    using namespace navlib;
    if(Navlib) NlClose(Navlib);
}

void FTDxNavContextBase::Open()
{
    using namespace navlib;

    TArray<accessor_t> Accessors;
    
    AddActiveAccessor(Accessors);
    AddFocusAccessor(Accessors);
    AddMotionAccessor(Accessors);
    AddCoordinateSystemAccessor(Accessors);
    AddDevicePresentAccessor(Accessors);
    AddEventsKeyPressAccessor(Accessors);
    AddEventsKeyReleaseAccessor(Accessors);
    AddTransactionAccessor(Accessors);
    AddFrameTimeAccessor(Accessors);
    AddFrameTimingSourceAccessor(Accessors);
    AddViewAffineAccessor(Accessors);
    AddViewConstructionPlaneAccessor(Accessors);
    AddViewExtentsAccessor(Accessors);
    AddViewFovAccessor(Accessors);
    AddViewFrustumAccessor(Accessors);
    AddViewPerspectiveAccessor(Accessors);
    AddViewRotatableAccessor(Accessors);
    AddViewTargetAccessor(Accessors);
    AddViewsFrontAccessor(Accessors);
    AddPivotPositionAccessor(Accessors);
    AddPivotUserAccessor(Accessors);
    AddPivotVisibleAccessor(Accessors);
    AddHitLookfromAccessor(Accessors);
    AddHitDirectionAccessor(Accessors);
    AddHitApertureAccessor(Accessors);
    AddHitLookatAccessor(Accessors);
    AddHitSelectionOnlyAccessor(Accessors);
    AddSelectionAffineAccessor(Accessors);
    AddSelectionEmptyAccessor(Accessors);
    AddSelectionExtentsAccessor(Accessors);
    AddModelExtentsAccessor(Accessors);
    AddPointerPositionAccessor(Accessors);
    AddCommandsTreeAccessor(Accessors);
    AddCommandsActiveSetAccessor(Accessors);
    AddCommandsActiveCommandAccessor(Accessors);
    AddImagesAccessor(Accessors);
    AddSettingsAccessor(Accessors);
    AddSettingsChangedAccessor(Accessors);

    OnPreOpen(Accessors);

    nlCreateOptions_t Options
    {
        sizeof(nlCreateOptions_t),
        true,
        nlOptions_t::none
    };

    if(auto CreationError = NlCreate(
        &Navlib,
        TCHAR_TO_ANSI(*GetProfileName()),
        Accessors.GetData(),
        Accessors.Num(),
        &Options
    )) {
        UE_LOG(LogSmReader, Error, TEXT("Could not connect to 3DxWare Navlib, %l"), CreationError)
        Navlib = {};
        return;
    }

    OnPostOpen();
}

void FTDxNavContext::OnPostOpen()
{
    OnCoordinateSystemGet(CoordinateSystem);
    OnViewsFrontGet(ViewsFront);
    OnFrameTimeGet(FrameTime);
    OnFrameTimingSourceGet(FrameTimingSource);
}

void FTDxNavContext::OnCoordinateSystemGet(FCoordinateSystemProperty& InValue)
{
    InValue.SetUE({
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {-1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    });
}

void FTDxNavContext::OnViewsFrontGet(FViewsFrontProperty& InValue)
{
    InValue.SetUE(FMatrix::Identity);
}

void FTDxNavContext::OnFrameTimeGet(FFrameTimeProperty& InValue)
{
    InValue.SetUE(FApp::GetCurrentTime());
}

void FTDxNavContext::OnFrameTimingSourceGet(FFrameTimingSourceProperty& InValue)
{
    InValue.Set(1); // 0 = SpaceMouse, 1 = Application
}

#endif
