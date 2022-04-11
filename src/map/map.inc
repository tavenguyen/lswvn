#if defined map_included
	#endinput
#endif

#define map_included

#include <streamer>

#include "interior/modern_apartment.inc"

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    Interior_ModernApartmentInit();
    printf("[src/map] Loaded!");
    return 1;
}