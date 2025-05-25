// MQ2VegasLoot.cpp : Defines the entry point for the DLL application.
//

#include <mq/Plugin.h>

PreSetup("MQ2VegasLoot");
PLUGIN_VERSION(0.1);

bool bInitDone								= false;

bool bAnnounceAllOnInvFull					= true;
bool bAnnounceAttemptToLoot					= false;
//bool bAnnounceCorpseFound					= false;
bool bAnnounceEmptyCorpse					= false;
bool bAnnounceFailedLoot					= true;
bool bAnnounceFixCorpseAttempt				= true;
//bool bAnnounceNavTimeout					= true;
//bool bAnnounceNavigation					= true;
//bool bAnnounceNoCorpseFound				= true;
//bool bAnnounceNoPathFound					= true;
bool bAnnounceOnDropConflict				= true;
bool bAnnounceOnFullInv						= true;
bool bAnnounceOnLoreConflict				= true;
bool bAnnounceOnNoLootSongSpellConflict		= true;
//bool bAnnouncePause						= true;
bool bAnnounceSkippedCorpse					= false;
bool bAnnounceSkippedItems					= false;
//bool bAnnounceStick						= true;
//bool bAnnounceTargetLoss					= true;
bool bAttemptToFixCorpses					= true;
bool bAutoLootOnKills						= true;
bool bAutoSaveNewItems						= true;
bool bCharacterSpecificSettings				= false;
bool bLootNoDrop							= true;
bool bLootSaveOnlyItems						= false;
bool bLootSpellsSongs						= true;
//bool bPauseOnAggro						= true;
bool bPlayBeepsOnFullInv					= true;
bool bUseServerNames						= true;
//int bCorpseCheckRadius					= 100;
//int bCorpseCheckRadiusIncrements			= 100;
int bFailedLootCount						= 6;
//int bMaxCorpseCheckRadius					= 400;
//int bNavTimeoutSeconds					= 20;
int bNumberOfBeepsOnFullInv					= 3;

std::string GetPrefix(bool UseServerNames) {
	std::string Prefix = "unknown";
	if (pLocalPC) {
		Prefix = fmt::format("{}_", pLocalPC->Name);

		if (UseServerNames) {
			Prefix = fmt::format("{}_{}", GetServerShortName(), Prefix);
		}
	}
	return Prefix;
}

void LoadIni() {
	PCHARINFO pChar = GetCharInfo();

	if (!pChar) {
		return;
	}

	bUseServerNames							= GetPrivateProfileBool("General", "UseServerNames", bUseServerNames, INIFileName);

	std::string Prefix						= GetPrefix(bUseServerNames);
	std::string strSettings					= Prefix + "Settings";

	bAnnounceAllOnInvFull					= GetPrivateProfileBool(strSettings, "AnnounceAllOnInvFull", true, INIFileName);
	bAnnounceAttemptToLoot					= GetPrivateProfileBool(strSettings, "AnnounceAttemptToLoot", true, INIFileName);
	//bAnnounceCorpseFound					= GetPrivateProfileBool(strSettings, "AnnounceCorpseFound", true, INIFileName);
	bAnnounceEmptyCorpse					= GetPrivateProfileBool(strSettings, "AnnounceEmptyCorpse", true, INIFileName);
	bAnnounceFailedLoot						= GetPrivateProfileBool(strSettings, "AnnounceFixCorpseAttempt", true, INIFileName);
	bAnnounceFixCorpseAttempt				= GetPrivateProfileBool(strSettings, "Enabled", true, INIFileName);
	//bAnnounceNavTimeout					= GetPrivateProfileBool(strSettings, "AnnounceNavTimeout", true, INIFileName);
	//bAnnounceNavigation					= GetPrivateProfileBool(strSettings, "AnnounceNavigation", true, INIFileName);
	//bAnnounceNoCorpseFound				= GetPrivateProfileBool(strSettings, "AnnounceNoCorpseFound", true, INIFileName);
	//bAnnounceNoPathFound					= GetPrivateProfileBool(strSettings, "AnnounceNoPathFound", true, INIFileName);
	bAnnounceOnDropConflict					= GetPrivateProfileBool(strSettings, "AnnounceOnDropConflict", true, INIFileName);
	bAnnounceOnFullInv						= GetPrivateProfileBool(strSettings, "AnnounceOnFullInv", true, INIFileName);
	bAnnounceOnLoreConflict					= GetPrivateProfileBool(strSettings, "AnnounceOnLoreConflict", true, INIFileName);
	bAnnounceOnNoLootSongSpellConflict		= GetPrivateProfileBool(strSettings, "AnnounceOnNoLootSongSpellConflict", true, INIFileName);
	//bAnnouncePause						= GetPrivateProfileBool(strSettings, "AnnouncePause", true, INIFileName);
	bAnnounceSkippedCorpse					= GetPrivateProfileBool(strSettings, "AnnounceSkippedCorpse", true, INIFileName);
	bAnnounceSkippedItems					= GetPrivateProfileBool(strSettings, "AnnounceSkippedItems", true, INIFileName);
	//bAnnounceStick						= GetPrivateProfileBool(strSettings, "AnnounceStick", true, INIFileName);
	//bAnnounceTargetLoss					= GetPrivateProfileBool(strSettings, "AnnounceTargetLoss", true, INIFileName);
	bAttemptToFixCorpses					= GetPrivateProfileBool(strSettings, "AttemptToFixCorpses", true, INIFileName);
	bAutoLootOnKills						= GetPrivateProfileBool(strSettings, "AutoLootOnKills", true, INIFileName);
	bAutoSaveNewItems						= GetPrivateProfileBool(strSettings, "AutoSaveNewItems", true, INIFileName);
	bCharacterSpecificSettings				= GetPrivateProfileBool(strSettings, "CharacterSpecificSettings", true, INIFileName);
	bLootNoDrop								= GetPrivateProfileBool(strSettings, "LootNoDrop", true, INIFileName);
	bLootSaveOnlyItems						= GetPrivateProfileBool(strSettings, "LootSaveOnlyItems", true, INIFileName);
	bLootSpellsSongs						= GetPrivateProfileBool(strSettings, "LootSpellsSongs", true, INIFileName);
	//bPauseOnAggro							= GetPrivateProfileBool(strSettings, "PauseOnAggro", true, INIFileName);
	bPlayBeepsOnFullInv						= GetPrivateProfileBool(strSettings, "PlayBeepsOnFullInv", true, INIFileName);

	//int bCorpseCheckRadius				= GetPrivateProfileInt(strSettings, "CorpseCheckRadius", true, INIFileName);
	//int bCorpseCheckRadiusIncrements		= GetPrivateProfileInt(strSettings, "CorpseCheckRadiusIncrements", true, INIFileName);
	int bFailedLootCount					= GetPrivateProfileInt(strSettings, "FailedLootCount", true, INIFileName);
	//int bMaxCorpseCheckRadius				= GetPrivateProfileInt(strSettings, "MaxCorpseCheckRadius", true, INIFileName);
	//int bNavTimeoutSeconds				= GetPrivateProfileInt(strSettings, "NavTimeoutSeconds", true, INIFileName);
	int bNumberOfBeepsOnFullInv				= GetPrivateProfileInt(strSettings, "NumberOfBeepsOnFullInv", true, INIFileName);

}

void AutoLootCommand(PSPAWNINFO pCHAR, PCHAR zLine) {
	char szTemp[MAX_STRING] = { 0 };
	GetArg(szTemp, zLine, 1);

	if (!_strnicmp(szTemp, "load", 4)) {
		LoadIni();

		return;
	}
}

/**
 * @fn OnWriteChatColor
 *
 * This is called each time WriteChatColor is called (whether by MQ2Main or by any
 * plugin).  This can be considered the "when outputting text from MQ" callback.
 *
 * This ignores filters on display, so if they are needed either implement them in
 * this section or see @ref OnIncomingChat where filters are already handled.
 *
 * If CEverQuest::dsp_chat is not called, and events are required, they'll need to
 * be implemented here as well.  Otherwise, see @ref OnIncomingChat where that is
 * already handled.
 *
 * For a list of Color values, see the constants for USERCOLOR_.  The default is
 * USERCOLOR_DEFAULT.
 *
 * @param Line const char* - The line that was passed to WriteChatColor
 * @param Color int - The type of chat text this is to be sent as
 * @param Filter int - (default 0)
 */
PLUGIN_API void OnWriteChatColor(const char* Line, int Color, int Filter)
{
	// DebugSpewAlways("MQ2VegasLoot::OnWriteChatColor(%s, %d, %d)", Line, Color, Filter);
}

/**
 * @fn OnIncomingChat
 *
 * This is called each time a line of chat is shown.  It occurs after MQ filters
 * and chat events have been handled.  If you need to know when MQ2 has sent chat,
 * consider using @ref OnWriteChatColor instead.
 *
 * For a list of Color values, see the constants for USERCOLOR_. The default is
 * USERCOLOR_DEFAULT.
 *
 * @param Line const char* - The line of text that was shown
 * @param Color int - The type of chat text this was sent as
 *
 * @return bool - Whether to filter this chat from display
 */
PLUGIN_API bool OnIncomingChat(const char* Line, DWORD Color)
{
	// DebugSpewAlways("MQ2VegasLoot::OnIncomingChat(%s, %d)", Line, Color);
	return false;
}

/**
 * @fn OnMacroStart
 *
 * This is called each time a macro starts (ex: /mac somemacro.mac), prior to
 * launching the macro.
 *
 * @param Name const char* - The name of the macro that was launched
 */
PLUGIN_API void OnMacroStart(const char* Name)
{
	// DebugSpewAlways("MQ2VegasLoot::OnMacroStart(%s)", Name);
}

/**
 * @fn OnMacroStop
 *
 * This is called each time a macro stops (ex: /endmac), after the macro has ended.
 *
 * @param Name const char* - The name of the macro that was stopped.
 */
PLUGIN_API void OnMacroStop(const char* Name)
{
	// DebugSpewAlways("MQ2VegasLoot::OnMacroStop(%s)", Name);
}

PLUGIN_API void InitializePlugin() {
	DebugSpewAlways("MQ2VegasLoot::Initializing version %f", MQ2Version);

	AddCommand("/autoloot", AutoLootCommand);
}

PLUGIN_API void ShutdownPlugin() {
	DebugSpewAlways("MQ2VegasLoot::Shutting down");

	RemoveCommand("/autoloot");
}


PLUGIN_API void SetGameState(int GameState) {
	if (GameState == GAMESTATE_INGAME) {
		if (!bInitDone)
			LoadIni();
	}
	else if (GameState != GAMESTATE_LOGGINGIN) {
		if (bInitDone)
			bInitDone = false;
	}
}

PLUGIN_API void OnPulse() {
	static int Pulse = 0;

	if (GetGameState() != GAMESTATE_INGAME)
		return;

	if (!bInitDone)
		return;
}