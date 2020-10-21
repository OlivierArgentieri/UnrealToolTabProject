#pragma once

#include "../ExampleTabToolBase.h"

class TabTool : public FExampleTabToolBase
{
public:
	virtual ~TabTool(){}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	virtual void Initialize() override;
	
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& _tabSpawnArgs) override;
	
};