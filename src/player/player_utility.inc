#if defined player_utility_included
	#endinput
#endif

#define player_utility_included

stock Player_Kick(playerid, const msg[]) {
    SendClientMessage(playerid, -1, msg);
    task_unblock(1);
    await task_ms(5);
    Kick(playerid);
    return 1;
}

stock Player_ClearChat(playerid) {
    new i = 0;
    while(i++ < 50) {
        SendClientMessage(playerid, -1, "");
    } 
    return 1;
}