#if defined loading_screen_included
	#endinput
#endif

#define loading_screen_included

#if !defined _PawnPlus_included
    #include <PawnPlus>
#endif

static PlayerText:ScreenLoading[MAX_PLAYERS] = PlayerText:INVALID_PLAYER_TEXT_DRAW;

stock Task:Screen_Loading(playerid, seconds = 20) {
    new Task:t = task_new();
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
        
        for(new i = 254; i >= 0; i--) {
            PlayerTextDrawBoxColor(playerid, ScreenLoading[playerid], i);
            PlayerTextDrawHide(playerid, ScreenLoading[playerid]);
            PlayerTextDrawShow(playerid, ScreenLoading[playerid]);
            wait_ms(seconds);
        }

        ScreenLoading_Destroy(playerid);
        task_set_result(t, 1);
    }

    return t;
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