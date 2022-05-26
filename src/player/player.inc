#if defined player_included
	#endinput
#endif

#define player_included

#define enable_register_mode

#include <a_mysql>
#include <PawnPlus>
#include <easyDialog>
#include <samp_bcrypt>
#include <zmessage>
#include <YSI_Coding\y_unique>

// Legacy
#include <camera_styles>
#include <loading_screen>

#include "ui/player_login_ui.inc"

#include "player_utility.inc"
#include "player_auth.inc"

#include "character/character_stats.inc"

#include "player_spawn_area.inc"

#include <YSI_Coding\y_hooks>
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new actorid = GetPlayerTargetDynamicActor(playerid);
	if(IsValidDynamicActor(actorid)) {
		if(newkeys & KEY_YES) {
			CallLocalFunction(#ActorTargeted_ShowMenu, #ii, playerid, actorid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
    return 1;
}