#pragma once
#include "DetailsViewObjectFilter.h"


class CamSettingTabFilter : public FDetailsViewObjectFilter
{
public:
	virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects);
};

