#if defined lsw_mysql_included
	#endinput
#endif

#define lsw_mysql_included

#include <a_mysql>
#include <env>
#include <YSI_Coding\y_hooks>

static MySQL:lswvn_database = MySQL:MYSQL_INVALID_HANDLE;

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle) {
	printf("ERR: Source - OnQueryError [errorid: %d]", errorid);
	printf("ERR: Description - %s", error);
	printf("ERR: Callback - %s", callback);
	printf("ERR: Query - %s", query);
	return 1;
}

// git bash command: 
//  - sampctl p build
//  - export MYSQL_HOST=localhost MYSQL_USER=root MYSQL_PASSWORD=root MYSQL_DATABASE=lswrp (if env doesn't have it.)
//  - sampctl p run
hook OnGameModeInit() {
    new 
        bool:success = true,
        mysql_host[32] = "",
        mysql_user[32] = "",
        mysql_password[32] = "",
        mysql_database[32] = "";

    if(Env_Has("MYSQL_HOST")) {
        Env_Get("MYSQL_HOST", mysql_host);
    } else {
        print("Environment variable `MYSQL_HOST` not set.");
        success = false;
    }

    if(Env_Has("MYSQL_USER")) {
        Env_Get("MYSQL_USER", mysql_user);
    } else {
        print("Environment variable `MYSQL_USER` not set.");
        success = false;
    }

    if(Env_Has("MYSQL_PASSWORD")) {
        Env_Get("MYSQL_PASSWORD", mysql_password);
    } else {
        print("Environment variable `MYSQL_PASSWORD` not set.");
        success = false;
    }

    if(Env_Has("MYSQL_DATABASE")) {
        Env_Get("MYSQL_DATABASE", mysql_database);
    } else {
        print("Environment variable `MYSQL_DATABASE` not set.");
        success = false;
    }

    if(!success) {
        printf("[Unloaded] src/mysql");
        SendRconCommand("exit");
        return 1;
    }

    new MySQLOpt:mysql_option_id = mysql_init_options();
    mysql_set_option(mysql_option_id, POOL_SIZE, 2);
    lswvn_database = mysql_connect(mysql_host, mysql_user, mysql_password, mysql_database, mysql_option_id);
    if(lswvn_database == MySQL:MYSQL_INVALID_HANDLE || mysql_errno(lswvn_database)) {
        new error[100];

        mysql_error(error, sizeof(error));
        printf("[ERROR] #%d '%s'", mysql_errno(lswvn_database), error);
        SendRconCommand("exit");
        return Y_HOOKS_BREAK_RETURN_0;
    }

    printf("[src/mysql] Connected to database server successfully");
    return 1;
}

hook OnGameModeExit() {
    mysql_close(lswvn_database);
    lswvn_database = MySQL:MYSQL_INVALID_HANDLE;
    return 1;
}