#pragma once
#include "CoreMinimal.h"


struct FPropertyChangedEvent;
class CamSettingHook : public FNotifyHook
{
public:
		
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override
	{
		
	}
};