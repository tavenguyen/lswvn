#if defined player_auth_included
	#endinput
#endif

#define player_auth_included

#undef MAX_PLAYER_NAME
#define             MAX_PLAYER_NAME                 32

const INVALID_PLAYER_AUTH = -1;

stock Task:PlayerAuth_GetId(const name[]) {
    new Task:t = task_new();

    new query[54 + MAX_PLAYER_NAME - 2 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT `id` FROM player_auth WHERE name = '%e' LIMIT 1", name);
    mysql_pquery(MySQL_Connection(), query, "PlayerAuth_OnIdGet", "ds", _:t, name);
    return t;
}

forward PlayerAuth_OnIdGet(Task:t, const name[]);
public PlayerAuth_OnIdGet(Task:t, const name[]) {
    printf("[player/player_auth - mysql debugging] %d mil - %d microsec - player : %s", cache_get_query_exec_time(MILLISECONDS), cache_get_query_exec_time(), name);
    if(cache_num_rows() > 0) {
        new id;
        cache_get_value_name_int(0, "id", id);
        task_set_result(t, id);
        return 1;
    }

    task_set_result(t, INVALID_PLAYER_AUTH);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    mysql_query(MySQL_Connection(), 
        "CREATE TABLE IF NOT EXISTS player_auth (\
        created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
	    modified_date TIMESTAMP NULL ON UPDATE CURRENT_TIMESTAMP,\
        id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,\
        name VARCHAR(32) NOT NULL,\
        password VARCHAR(64) DEFAULT '')\
    ", true);

    printf("[player/player_auth] Loaded!");
    return 1;
}

hook OnPlayerConnect(playerid) {
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    task_unblock(1);
    new id = await PlayerAuth_GetId(name);
    return 1;
}