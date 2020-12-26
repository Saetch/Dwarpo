#pragma once

class Personality {

	//Dwarfs tend to socialize if idling and sanity level low (may be heading to the tavern)
	float baseSocialializingSkill = 1.0f;

	float socializingSkillModifier;

	float baseSanityLevel = 1.0f;

	float sanityLevelModifier;
};