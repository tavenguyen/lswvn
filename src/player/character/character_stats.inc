#if defined character_included
	#endinput
#endif

#define character_included

stock Character_GetSize(account_id) {
    new Task:t = task_new();

    new query[86 + 11 - 2];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT COUNT(character_id) AS res FROM character_stats WHERE `account_id` = %d LIMIT 1", account_id);
    mysql_pquery(MySQL_Connection(), query, "Character_OnSizeGet", "d", _:t);
    return t;
}

forward Character_OnSizeGet(Task:t);
public Character_OnSizeGet(Task:t) {
    new count;
    cache_get_value_name_int(0, "res", count);
    task_set_result(t, count);
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