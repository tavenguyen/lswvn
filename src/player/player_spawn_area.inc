#if defined player_spawn_area_included
	#endinput
#endif

#define player_spawn_area_included

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

static 
    Map:m_playerActorList,
    Map:m_playerText3DList;

static enum _:eActorStatus {
    actorInvalidCharacter = 0,
    actorValidCharacter,
}

stock Task:PlayerSpawnArea_ActorCreate(playerid) {
    if(!map_valid(m_playerActorList)) {
        m_playerActorList = map_new();
    }

    if(map_has_key(m_playerActorList, playerid)) {
        return Task:0;
    }

    new List:list = list_new(),
        Task:t = task_new(),
        name[MAX_PLAYER_NAME];

    GetPlayerName(playerid, name, sizeof(name));
    
    // 'i' as 'character_id' in Character_GetSKin function.
    task_detach();
    task_yield(t);
    new account_id = await PlayerAuth_GetId(name);
    for(new i = 0; i < MAX_ACTORS_SPAWN_AREA; i++) {
        new skinid = await Character_GetSkin(account_id, i);
        new actorid = CreateDynamicActor((skinid == 0 ? ACTORS_SKIN_DEFAULT_CHARACTER : skinid), ActorSpawners[i][x_actor], ActorSpawners[i][y_actor], ActorSpawners[i][z_actor], ActorSpawners[i][a_actor], _, _, playerid, playerid);
        Streamer_SetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID, (skinid == 0 ? actorInvalidCharacter : actorValidCharacter));

        list_add(list, actorid);
        printf("[debug] actorid: %d", actorid);
        map_set(m_playerActorList, playerid, list);
    }
    
    task_set_result(t, 1);
    return Task:0;
}

stock PlayerSpawnArea_ActorDestroy(playerid) {
    if(!map_valid(m_playerActorList) || !map_has_key(m_playerActorList, playerid)) { 
        return 0;
    }

    new List:list = list_new();
    if(map_get_safe(m_playerActorList, playerid, list)) {
        for(new i = 0, j = list_size(list); i < j; i++) {
            new actorid = list_get(list, i);
            if(IsValidDynamicActor(actorid)) DestroyDynamicActor(actorid);
            //printf("[debug] actorid deleted: %d", actorid);
        }
    }

    return 1;
}

stock PlayerSpawnArea_TextCreate(playerid) {
    // If you want to create DynamicText3D, you have to had DynamicActor firstly.
    if(!map_valid(m_playerActorList) || !map_has_key(m_playerActorList, playerid)) {
        return 0;
    }

    if(!map_valid(m_playerText3DList)) {
        m_playerText3DList = map_new();
    }

    // End function if DynamicText had itself.
    if(map_has_key(m_playerText3DList, playerid)) {
        return 0;
    }

    new List:actors_list = list_new();
    map_get_safe(m_playerActorList, playerid, actors_list);
    for(new index = 0, actorid; index < MAX_ACTORS_SPAWN_AREA; index++) {
        actorid = list_get(actors_list, index);
        if(IsValidDynamicActor(actorid)) {
            new Text3D:textid = CreateDynamic3DTextLabel(#character_selection_text, -1, ActorSpawners[index][x_actor], ActorSpawners[index][y_actor], ActorSpawners[index][z_actor] - 1.0, 5.0);
            if(Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID) == actorInvalidCharacter) {
                printf("[debug] actorid: %d has not character index.", actorid);
                UpdateDynamic3DTextLabelText(textid, -1, "Invalid character");
            } else if(Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID) == actorValidCharacter) {
                printf("[debug] actorid: %d has character index.", actorid);

                new name[MAX_PLAYER_NAME];
                GetPlayerName(playerid, name, sizeof name);
                
                task_unblock(1);
                new account_id = await PlayerAuth_GetId(name);
                new Task:t = Character_GetName(account_id, index);

                task_wait(t);
                task_get_result_arr(t, name);
                UpdateDynamic3DTextLabelText(textid, -1, name);
            }
        } else {
            printf("[debug] invalid actorid: %d", actorid);
        }
    }

    return 1;
}

static Player_SpawnOnSelCharacterArea(playerid) {
    new Task:t = task_new();
    t = PlayerSpawnArea_ActorCreate(playerid);
    TogglePlayerSpectating(playerid, false);
	SetSpawnInfo(playerid, 0, 27, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
    TogglePlayerControllable(playerid, false);
    Screen_Loading(playerid, 3);
	Streamer_UpdateEx(playerid, 1435.7620, -1228.3949, 152.4143, playerid, playerid, _, 0);
    SetPlayerFacingAngle(playerid, 178.0979);
    task_detach(); await t;
    PlayerSpawnArea_TextCreate(playerid);
    task_delete(t);
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

    if(map_valid(m_playerText3DList) && map_has_key(m_playerText3DList, playerid)) {
        PlayerSpawnArea_TextDestroy(playerid);
        map_remove(m_playerText3DList, playerid);
        if(!map_size(m_playerText3DList)) {
            map_delete(m_playerText3DList);
            m_playerText3DList = Map:0;
        }
    }
    return 1;
}

hook Player_OnCharRetrived(playerid) {
    PlayerLogin_HideUI(playerid);
    Player_SpawnOnSelCharacterArea(playerid);
    return 1;
}