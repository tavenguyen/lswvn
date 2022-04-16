#if defined loading_screen_included
	#endinput
#endif

#define loading_screen_included

#if !defined _PawnPlus_included
    #include <PawnPlus>
#endif

static PlayerText:ScreenLoading[MAX_PLAYERS] = PlayerText:INVALID_PLAYER_TEXT_DRAW;

stock Screen_Loading(playerid, seconds = 2) {
    if(ScreenLoading[playerid] == PlayerText:INVALID_PLAYER_TEXT_DRAW) {
        ScreenLoading[playerid] = CreatePlayerTextDraw(playerid, 0.8999, 1.3888, "Loading_Screen"); 
        PlayerTextDrawLetterSize(playerid, ScreenLoading[playerid], 0.0000, 49.2999);
        PlayerTextDrawTextSize(playerid, ScreenLoading[playerid], 641.0000, 0.0000);
        PlayerTextDrawAlignment(playerid, ScreenLoading[playerid], 1);
        PlayerTextDrawColor(playerid, ScreenLoading[playerid], -1);
        PlayerTextDrawUseBox(playerid, ScreenLoading[playerid], 1);
        PlayerTextDrawBoxColor(playerid, ScreenLoading[playerid], 255);
        PlayerTextDrawBackgroundColor(playerid, ScreenLoading[playerid], 255);
        PlayerTextDrawFont(playerid, ScreenLoading[playerid], 0);
        PlayerTextDrawSetProportional(playerid, ScreenLoading[playerid], 1);
        PlayerTextDrawSetShadow(playerid, ScreenLoading[playerid], 0);
        
        task_detach();
        task_yield(1);
        
        PlayerTextDrawShow(playerid, ScreenLoading[playerid]);
        if(seconds > 2) {
            wait_ms(seconds*1000 - 2000);
        }
        
        new value = 255;
        for(new i = 8; i >= 0; i--) {
            PlayerTextDrawBoxColor(playerid, ScreenLoading[playerid], value);
            PlayerTextDrawHide(playerid, ScreenLoading[playerid]);
            PlayerTextDrawShow(playerid, ScreenLoading[playerid]);
            wait_ms(250);
            value = (value >> 1);
        }

        ScreenLoading_Destroy(playerid);
    }

    return 1;
}

stock ScreenLoading_Destroy(playerid) {
    if(ScreenLoading[playerid] != PlayerText:INVALID_PLAYER_TEXT_DRAW) {
        PlayerTextDrawHide(playerid, ScreenLoading[playerid]);
        PlayerTextDrawDestroy(playerid, ScreenLoading[playerid]);
        ScreenLoading[playerid] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    }

    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason) {
    ScreenLoading_Destroy(playerid);
    return 1;
}