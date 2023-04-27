// Cerebral Paralysis. All right reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class CerebralParalysisTarget : TargetRules
{
	public CerebralParalysisTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(
			new string[] { "CerebralParalysis" });
	}
}