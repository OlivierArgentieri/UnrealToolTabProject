#pragma once
#include "DetailsViewObjectFilter.h"


class UCamSettingTabFilterObject;

class CamSettingTabFilter : public FDetailsViewObjectFilter
{
	private:
		UCamSettingTabFilterObject* wrapper;
public:
	void SetWrapper(UCamSettingTabFilterObject* wrapper);
	virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects);
};

