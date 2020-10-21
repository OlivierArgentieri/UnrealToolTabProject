#pragma once
#include "Modules/ModuleInterface.h"
#include <Runtime/Core/Public/Templates/SharedPointer.h>


class IExampleModuleListenerInterface
{
public:
	virtual void OnStartupModule() {};
	virtual void OnShutdownModule() {}
};

class IExampleModuleInterface : public IModuleInterface
{
public:
	void StartupModule() override
	{
		if(!IsRunningCommandlet())
		{
			AddModuleListeners();
			for (int32 _i = 0; _i < ModuleListeners.Num(); ++_i)
			{
				ModuleListeners[_i]->OnStartupModule();
			}
		}
	}

	void ShutdownModule() override
	{
		for (int32 _i =0; _i < ModuleListeners.Num(); ++_i)
		{
			ModuleListeners[_i]->OnShutdownModule();
		}
	}

	virtual void AddModuleListeners() {};

protected:
	TArray<TSharedRef<IExampleModuleListenerInterface>> ModuleListeners;
};