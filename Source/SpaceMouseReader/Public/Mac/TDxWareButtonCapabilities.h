// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "DeviceTypes/ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxWareButtonCapabilities : public FSmButtonCapabilities
{
public:
    FTDxWareButtonCapabilities()
    {
        // TODO: detect actual device and use those buttons
    }

    virtual void TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data) override;
};
