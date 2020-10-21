// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ToolExampleEditorTarget : TargetRules
{
	public ToolExampleEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "ToolExample" } );
		ExtraModuleNames.AddRange( new string[] { "ToolExampleEditor" } );
	}
}
