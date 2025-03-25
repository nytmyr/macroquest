// MQ2VegasLoot.cpp : Defines the entry point for the DLL application.
//

#include <mq/Plugin.h>

PreSetup("MQ2VegasLoot");
PLUGIN_VERSION(0.1);

bool bInitDone = false;

namespace DefaultSettings {
	constexpr bool AutoLootOnKills						= true;
	constexpr bool CharacterSpecificSettings			= false;
	constexpr bool AutoSaveNewItems						= true;
	constexpr bool LootSaveOnlyItems					= false;	
	constexpr int CorpseCheckRadius						= 100;
	constexpr int CorpseCheckRadiusIncrements			= 100;
	constexpr int MaxCorpseCheckRadius					= 400;
	constexpr int FailedLootCount						= 6;
	constexpr bool AttemptToFixCorpses					= true;
	constexpr bool LootSpellsSongs						= true;
	constexpr int NavTimeoutSeconds						= 20;
	constexpr bool LootNoDrop							= true;
	constexpr bool PlayBeepsOnFullInv					= true;
	constexpr bool PauseOnAggro							= true;
	constexpr int NumberOfBeepsOnFullInv				= 3;
	constexpr bool AnnounceAttemptToLoot				= true;
	constexpr bool AnnounceCorpseFound					= true;
	constexpr bool AnnounceOnFullInv					= true;
	constexpr bool AnnounceAllOnInvFull					= true;
	constexpr bool AnnounceOnNoLootSongSpellConflict	= true;
	constexpr bool AnnounceOnDropConflict				= true;
	constexpr bool AnnounceOnLoreConflict				= true;
	constexpr bool AnnounceSkippedItems					= true;
	constexpr bool AnnounceSkippedCorpse				= true;
	constexpr bool AnnounceNoPathFound					= true;
	constexpr bool AnnounceNoCorpseFound				= true;
	constexpr bool AnnounceNavigation					= true;
	constexpr bool AnnounceStick						= true;
	constexpr bool AnnounceNavTimeout					= true;
	constexpr bool AnnounceEmptyCorpse					= true;
	constexpr bool AnnounceFixCorpseAttempt				= true;
	constexpr bool AnnounceFailedLoot					= true;
	constexpr bool AnnounceTargetLoss					= true;
	constexpr bool AnnouncePause						= true;

	constexpr int START = DefaultSettings::CharacterSpecificSettings;
	constexpr int END = DefaultSettings::AnnouncePause;		// Increment as needed
};

namespace Settings {
	bool bAutoLootOnKills = DefaultSettings::AutoLootOnKills;
	bool bCharacterSpecificSettings = DefaultSettings::CharacterSpecificSettings;
	bool bAutoSaveNewItems = DefaultSettings::AutoSaveNewItems;
	bool bLootSaveOnlyItems = DefaultSettings::LootSaveOnlyItems;
	int iCorpseCheckRadius = DefaultSettings::CorpseCheckRadius;
	int iCorpseCheckRadiusIncrements = DefaultSettings::CorpseCheckRadiusIncrements;
	int iMaxCorpseCheckRadius = DefaultSettings::MaxCorpseCheckRadius;
	int iFailedLootCount = DefaultSettings::FailedLootCount;
	bool bAttemptToFixCorpses = DefaultSettings::AttemptToFixCorpses;
	bool bLootSpellsSongs = DefaultSettings::LootSpellsSongs;
	int iNavTimeoutSeconds = DefaultSettings::NavTimeoutSeconds;
	bool bLootNoDrop = DefaultSettings::LootNoDrop;
	bool bPlayBeepsOnFullInv = DefaultSettings::PlayBeepsOnFullInv;
	bool bPauseOnAggro = DefaultSettings::PauseOnAggro;
	int iNumberOfBeepsOnFullInv = DefaultSettings::NumberOfBeepsOnFullInv;
	bool bAnnounceAttemptToLoot = DefaultSettings::AnnounceAttemptToLoot;
	bool bAnnounceCorpseFound = DefaultSettings::AnnounceCorpseFound;
	bool bAnnounceOnFullInv = DefaultSettings::AnnounceOnFullInv;
	bool bAnnounceAllOnInvFull = DefaultSettings::AnnounceAllOnInvFull;
	bool bAnnounceOnNoLootSongSpellConflict = DefaultSettings::AnnounceOnNoLootSongSpellConflict;
	bool bAnnounceOnDropConflict = DefaultSettings::AnnounceOnDropConflict;
	bool bAnnounceOnLoreConflict = DefaultSettings::AnnounceOnLoreConflict;
	bool bAnnounceSkippedItems = DefaultSettings::AnnounceSkippedItems;
	bool bAnnounceSkippedCorpse = DefaultSettings::AnnounceNoPathFound;
	bool bAnnounceNoPathFound = DefaultSettings::AnnounceNoPathFound;
	bool bAnnounceNoCorpseFound = DefaultSettings::AnnounceNoCorpseFound;
	bool bAnnounceNavigation = DefaultSettings::AnnounceNavigation;
	bool bAnnounceStick = DefaultSettings::AnnounceStick;
	bool bAnnounceNavTimeout = DefaultSettings::AnnounceNavTimeout;
	bool bAnnounceEmptyCorpse = DefaultSettings::AnnounceEmptyCorpse;
	bool bAnnounceFixCorpseAttempt = DefaultSettings::AnnounceFixCorpseAttempt;
	bool bAnnounceFailedLoot = DefaultSettings::AnnounceFailedLoot;
	bool bAnnounceTargetLoss = DefaultSettings::AnnounceTargetLoss;
	bool bAnnouncePause = DefaultSettings::AnnouncePause;
};

PLUGIN_API void InitializePlugin()
{
	DebugSpewAlways("MQ2VegasLoot::Initializing version %f", MQ2Version);

	AddCommand("/autoloot", AutoLootCommand);
}

/**
 * @fn ShutdownPlugin
 *
 * This is called once when the plugin has been asked to shutdown.  The plugin has
 * not actually shut down until this completes.
 */
PLUGIN_API void ShutdownPlugin()
{
	DebugSpewAlways("MQ2VegasLoot::Shutting down");

	RemoveCommand("/autoloot", AutoLootCommand);
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


/**
 * @fn OnPulse
 *
 * This is called each time MQ2 goes through its heartbeat (pulse) function.
 *
 * Because this happens very frequently, it is recommended to have a timer or
 * counter at the start of this call to limit the amount of times the code in
 * this section is executed.
 */
PLUGIN_API void OnPulse()
{
/*
	static std::chrono::steady_clock::time_point PulseTimer = std::chrono::steady_clock::now();
	// Run only after timer is up
	if (std::chrono::steady_clock::now() > PulseTimer)
	{
		// Wait 5 seconds before running again
		PulseTimer = std::chrono::steady_clock::now() + std::chrono::seconds(5);
		DebugSpewAlways("MQ2VegasLoot::OnPulse()");
	}
*/
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

void LoadIni() {
	PCHARINFO pChar = GetCharInfo();

	if (!pChar) {
		return;
	}

	Settings::bCharacterSpecificSettings				= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAutoSaveNewItems 						= GetPrivateProfileBool("Settings", DefaultSettings::AutoSaveNewItems, DefaultSettings::AutoSaveNewItems, INIFileName);
	Settings::bLootSaveOnlyItems						= GetPrivateProfileBool("Settings", DefaultSettings::LootSaveOnlyItems, DefaultSettings::LootSaveOnlyItems, INIFileName);
	Settings::iCorpseCheckRadius						= GetPrivateProfileBool("Settings", DefaultSettings::CorpseCheckRadius, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::iCorpseCheckRadiusIncrements				= GetPrivateProfileBool("Settings", DefaultSettings::CorpseCheckRadiusIncrements, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::iMaxCorpseCheckRadius						= GetPrivateProfileBool("Settings", DefaultSettings::MaxCorpseCheckRadius, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::iFailedLootCount							= GetPrivateProfileBool("Settings", DefaultSettings::FailedLootCount, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAttemptToFixCorpses						= GetPrivateProfileBool("Settings", DefaultSettings::AttemptToFixCorpses, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bLootSpellsSongs							= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::iNavTimeoutSeconds						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bLootNoDrop								= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bPlayBeepsOnFullInv						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::iNumberOfBeepsOnFullInv					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceAttemptToLoot					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceCorpseFound 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceOnFullInv 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceAllOnInvFull 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceOnNoLootSongSpellConflict 		= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceOnDropConflict 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceOnLoreConflict 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceSkippedItems 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceSkippedCorpse 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceNoPathFound 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceNoCorpseFound 					= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceNavigation 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceStick 							= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceNavTimeout 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceEmptyCorpse 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceFixCorpseAttempt 				= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceFailedLoot 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnounceTargetLoss 						= GetPrivateProfileBool("Settings", DefaultSettings::CharacterSpecificSettings, DefaultSettings::CharacterSpecificSettings, INIFileName);
	Settings::bAnnouncePause 							= GetPrivateProfileBool("Settings", DefaultSettings::AnnouncePause, DefaultSettings::AnnouncePause, INIFileName);

}

void AutoLootCommand(PSPAWNINFO pCHAR, PCHAR zLine) {

}