#if defined player_utility_included
	#endinput
#endif

#define player_utility_included

stock Player_Msg(playerid, color, const msg[]) {
    ZMsg_SendClientMessage(playerid, color, msg);
    return 1;
}

stock Player_Kick(playerid, const msg[]) {
    Player_Msg(playerid, -1, msg);
    task_unblock(1);
    await task_ms(5);
    Kick(playerid);
    return 1;
}

stock Player_ClearChat(playerid) {
    new i = 0;
    while(i++ < 50) {
        Player_Msg(playerid, -1, "");
    } 
    return 1;
}