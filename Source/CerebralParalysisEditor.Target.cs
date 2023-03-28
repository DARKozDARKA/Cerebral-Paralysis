// Cerebral Paralysis. All right reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class CerebralParalysisEditorTarget : TargetRules
{
	public CerebralParalysisEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CerebralParalysis" } );
	}
}
