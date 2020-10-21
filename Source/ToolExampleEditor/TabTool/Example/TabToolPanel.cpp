#include "TabToolPanel.h"

#include "Widgets/Layout/SScrollBox.h"

void TabToolPanel::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;

	if(tool.IsValid())
	{
		// action from tool object
	}

	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(192,192,192,255))
			.Padding(15.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a tab example aaaasdasdasdsad.")))
			]
		]
		
	];
}
