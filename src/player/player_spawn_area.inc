#if defined player_account_included
	#endinput
#endif

#define player_account_included

#define         MAX_ACTORS_SPAWN_AREA                   3
#define         ACTORS_SKIN_DEFAULT_CHARACTER           27

static enum ActorSpawnerEnum {
    Float:x_actor, 
    Float:y_actor,
    Float:z_actor,
    Float:a_actor,
}

static ActorSpawners[][ActorSpawnerEnum] = {
    {1434.5022, -1231.0056, 152.3983, 359.7087},
    {1435.6450, -1231.0045, 152.3983, 359.7087},
    {1436.9015, -1230.9994, 152.3983, 356.9293}
};

new Map:m_playerActorList;

stock Task:PlayerSpawnArea_ActorCreate(playerid) {
    if(!map_valid(m_playerActorList)) {
        m_playerActorList = map_new();
    }

    if(map_has_key(m_playerActorList, playerid)) {
        return Task:0;
    }

    new Task:t = task_new(),
        List:list = list_new(),
        name[MAX_PLAYER_NAME];

    task_unblock(1);
    GetPlayerName(playerid, name, sizeof(name));
    
    // 'i' as 'character_id' in Character_GetSKin function.
    new account_id = await PlayerAuth_GetId(name);
    for(new i = 0; i < MAX_ACTORS_SPAWN_AREA; i++) {
        new skinid = await Character_GetSkin(account_id, i);
        new actorid = CreateActor((skinid == 0 ? ACTORS_SKIN_DEFAULT_CHARACTER : skinid), ActorSpawners[i][x_actor], ActorSpawners[i][y_actor], ActorSpawners[i][z_actor], ActorSpawners[i][a_actor]);
        
        list_add(list, actorid);
        //printf("[debug] actorid: %d", actorid);
        map_set(m_playerActorList, playerid, list);
    }

    return Task:t;
}

stock PlayerSpawnArea_ActorDestroy(playerid) {
    if(!map_valid(m_playerActorList) || !map_has_key(m_playerActorList, playerid)) { 
        return 0;
    }

    new List:list = list_new();
    if(map_get_safe(m_playerActorList, playerid, list)) {
        for(new i = 0, j = list_size(list); i < j; i++) {
            new actorid = list_get(list, i);
            DestroyActor(actorid);
            //printf("[debug] actorid deleted: %d", actorid);
        }
    }

    return 1;
}

static Player_SpawnOnSelCharacterArea(playerid) {
    TogglePlayerSpectating(playerid, false);
    PlayerSpawnArea_ActorCreate(playerid);
	SetSpawnInfo(playerid, 0, 27, 1434.5022, -1231.0056, 152.3983, 0.0, 0, 0, 0, 0, 0, 0);
    TogglePlayerControllable(playerid, false);
	SpawnPlayer(playerid);
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerInterior(playerid, playerid);
	TogglePlayerControllable(playerid, true);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    printf("[player/player_spawn_area] Loaded");
    m_playerActorList = map_new();
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(map_valid(m_playerActorList) && map_has_key(m_playerActorList, playerid)) {
        PlayerSpawnArea_ActorDestroy(playerid);
        map_remove(m_playerActorList, playerid);
        if(!map_size(m_playerActorList)) {
            map_delete(m_playerActorList);
            m_playerActorList = Map:0;
        }
    }
    return 1;
}

hook Player_OnCharRetrived(playerid) {
    PlayerLogin_HideUI(playerid);
    Player_SpawnOnSelCharacterArea(playerid);
    return 1;
}