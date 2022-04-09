#if defined player_auth_included
	#endinput
#endif

#define player_auth_included

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    printf("[player/player_auth] Loaded!");
    return 1;
}