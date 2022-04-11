#if defined player_account_included
	#endinput
#endif

#define player_account_included

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    mysql_query(MySQL_Connection(), 
        "CREATE TABLE IF NOT EXISTS player_character (\
        created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
	    modified_date TIMESTAMP NULL ON UPDATE CURRENT_TIMESTAMP,\
        account_id INT UNSIGNED,\
        character_id INT UNSIGNED,\
        name VARCHAR(32) NOT NULL,\
        UNIQUE unique_accounts(character_id, name),\
        FOREIGN KEY (account_id) REFERENCES player_auth(id) ON UPDATE CASCADE ON DELETE CASCADE)\
    ", false);

    printf("[player/player_account] Loaded!");
    return 1;
}

hook Player_OnCharRetrived(playerid) {
    PlayerLogin_HideUI(playerid);
    Player_SpawnOnSelCharacterArea(playerid);
    return 1;
}