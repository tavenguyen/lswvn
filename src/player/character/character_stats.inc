#if defined character_included
	#endinput
#endif

#define character_included

stock Character_GetSize(account_id) {
    new Task:t = task_new();

    new query[86 + 11 - 2 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT COUNT(character_id) AS res FROM character_stats WHERE `account_id` = %d LIMIT 1", account_id);
    mysql_pquery(MySQL_Connection(), query, #Character_OnSizeGet, #d, _:t);
    return t;
}

stock Task:Character_NameValid(const name[]) {
    new Task:t = task_new();

    new query[58 + MAX_PLAYER_NAME - 2 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT name FROM character_stats WHERE name = '%e' LIMIT 1", name);
    mysql_pquery(MySQL_Connection(), query, #Character_OnNameValid, #d, _:t);
    return t;
}

stock Task:Character_Add(account_id, const name[], size = sizeof(name), age, gender, skin) {
    new Task:t = task_new();
    task_unblock(1);

    new character_size = await Character_GetSize(account_id),
        query[300];
    
    mysql_format(MySQL_Connection(), query, sizeof(query), "INSERT INTO character_stats VALUES (%d, %d, '%e', %d, %d, %d)", account_id, character_size, name, age, gender, skin);
    mysql_pquery(MySQL_Connection(), query, #Character_OnAdd, #d, _:t);
    return t;
}

stock Task:Character_GetSkin(account_id, character_id) {
    new Task:t = task_new();
    
    new query[90 + 11 + 11 - 4 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT `skin` FROM character_stats WHERE `account_id` = %d AND `character_id` = %d LIMIT 1", account_id, character_id);
    mysql_pquery(MySQL_Connection(), query, #Character_OnSkinGet, #d, _:t);
    return t;
}

stock Task:Character_SetSkin(account_id, character_id, skinid) {
    new Task:t = task_new();
    
    new query[90 + 11 + 11 - 4 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "UPDATE character_stats SET skin = %d WHERE `account_id` = %d AND `character_id` = %d", skinid, account_id, character_id);
    mysql_pquery(MySQL_Connection(), query, #Character_OnSkinSet, #d, _:t);
    return t;
}

stock Task:Character_GetName(account_id, character_id) {   
    new Task:t = task_new();

    new query[90 + 11 + 11 - 4 + 1];
    mysql_format(MySQL_Connection(), query, sizeof query, "SELECT `name` FROM character_stats WHERE `account_id` = %d AND `character_id` = %d LIMIT 1", account_id, character_id);
    mysql_pquery(MySQL_Connection(), query, #Character_OnNameSet, #d, _:t);
    return t;
}

forward Character_OnSizeGet(Task:t);
public Character_OnSizeGet(Task:t) {
    new count;
    cache_get_value_name_int(0, "res", count);
    task_set_result(t, count);
    return 1;
}

forward Character_OnNameValid(Task:t);
public Character_OnNameValid(Task:t) {
    task_set_result(t, cache_num_rows());
    return 1;
}

forward Character_OnAdd(Task:t);
public Character_OnAdd(Task:t) {
    task_set_result(t, cache_affected_rows());
    return 1;
}

forward Character_OnSkinGet(Task:t);
public Character_OnSkinGet(Task:t) {
    new skinid;
    cache_get_value_name_int(0, "skin", skinid);
    task_set_result(t, skinid);
    return 1;
}

forward Character_OnSkinSet(Task:t);
public Character_OnSkinSet(Task:t) {
    task_set_result(t, cache_affected_rows());
    return 1;
}

forward Character_OnNameSet(Task:t);
public Character_OnNameSet(Task:t) {
    new name[MAX_PLAYER_NAME];  
    cache_get_value_name(0, "name", name);
    task_set_result_str(t, name);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    mysql_query(MySQL_Connection(), 
        "CREATE TABLE IF NOT EXISTS character_stats (\
        created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
	    modified_date TIMESTAMP NULL ON UPDATE CURRENT_TIMESTAMP,\
        account_id INT UNSIGNED,\
        character_id INT UNSIGNED,\
        name VARCHAR(32) NOT NULL,\
        age INT UNSIGNED,\
        gender TINYINT UNSIGNED,\
        skin TINYINT UNSIGNED,\
        UNIQUE unique_accounts(character_id, name),\
        FOREIGN KEY (account_id) REFERENCES player_auth(id) ON UPDATE CASCADE ON DELETE CASCADE)\
    ", false);
    printf("[player/character] Loaded!");
    return 1;
}