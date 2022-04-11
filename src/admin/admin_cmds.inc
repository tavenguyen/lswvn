#if defined admin_cmds_included
	#endinput
#endif

#define admin_cmds_included

CMD:gotopos(playerid, params[]) {
    new Float:x, Float:y, Float:z, interiorid, worldid;
    if(sscanf(params, "fffI(0)I(0)", x, y, z, interiorid, worldid)) return Player_Msg(playerid, -1, "USAGE: /gotopos [x] [y] [z]");
    SetPlayerPos(playerid, x, y, z);
    SetPlayerInterior(playerid, interiorid);
    SetPlayerVirtualWorld(playerid, worldid);
    return 1;
}