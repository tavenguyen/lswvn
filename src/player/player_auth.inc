#if defined player_auth_included
	#endinput
#endif

#define player_auth_included

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