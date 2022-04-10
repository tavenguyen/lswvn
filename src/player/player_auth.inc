#if defined player_auth_included
	#endinput
#endif

#define player_auth_included

#undef MAX_PLAYER_NAME
#define             MAX_PLAYER_NAME                     32
#define             MAX_PASSWORD_LENGTH                 32

const INVALID_PLAYER_AUTH = -1;

static Map:m_playerAuthProcess;

static enum {
    PLAYER_AUTH_REGISTERATION,
    PLAYER_AUTH_LOGIN
}

static PlayerAuth_ShowRegisteration(playerid, const name[]) {
    new description[250];
    format(description, sizeof(description), 
        "Xin chao '%s' den voi may chu cua chung toi!,\n\
        hay nhap mat khau de tiep tuc qua trinh tao tai khoan:\n\n\
        Gioi han mat khau: Tu 6 - %d ky tu.",
    name, MAX_PASSWORD_LENGTH);

    Dialog_Show(playerid, PlayerPasswordDialog, DIALOG_STYLE_PASSWORD, "Account Management", description, "Accept", "Close");
}

stock Task:PlayerAuth_Add(const name[], const password[]) {
    new Task:t = task_new();

    new query[60 + MAX_PLAYER_NAME + BCRYPT_HASH_LENGTH - 8 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "INSERT INTO player_auth (name, password) VALUES ('%e', '%e')", name, password);
    mysql_pquery(MySQL_Connection(), query, "PlayerAuth_OnRowsAdd", "d", _:t);
    return t;
}

stock Task:PlayerAuth_Remove(id) {
    new Task:t = task_new();

    new query[];
    mysql_format(MySQL_Connection(), query, sizeof(query), "DELETE FROM player_auth WHERE `id` = %d", id);
    mysql_pquery(MySQL_Connection(), query, "PlayerAuth_OnRowRemove", "d", _:t);
    return t;
}

stock Task:PlayerAuth_GetId(const name[]) {
    new Task:t = task_new();

    new query[54 + MAX_PLAYER_NAME - 2 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT `id` FROM player_auth WHERE name = '%e' LIMIT 1", name);
    mysql_pquery(MySQL_Connection(), query, "PlayerAuth_OnIdGet", "ds", _:t, name);
    return t;
}

stock Task:PlayerAuth_GetHash(const name[]) {
    new Task:t = task_new();

    new query[60 + BCRYPT_HASH_LENGTH - 2 + 1];
    mysql_format(MySQL_Connection(), query, sizeof(query), "SELECT `password` FROM player_auth WHERE name = '%e' LIMIT 1", name);
    mysql_pquery(MySQL_Connection(), query, "PlayerAuth_OnHashGet", "d", _:t);
    return t;
}

forward PlayerAuth_OnRowsAdd(Task:t);
public PlayerAuth_OnRowsAdd(Task:t) {
    task_set_result(t, cache_affected_rows());
    return 1;
}

forward PlayerAuth_OnRowRemove(Task:t);
public PlayerAuth_OnRowRemove(Task:t) {
    task_set_result(t, cache_affected_rows());
    return 1;
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

forward PlayerAuth_OnHashGet(Task:t);
public PlayerAuth_OnHashGet(Task:t) {
    if(cache_num_rows() > 0) {
        new hash[BCRYPT_HASH_LENGTH];
        cache_get_value_name(0, "password", hash);
        task_set_result_str(t, hash);
        return 1;
    }
    
    return 1;
}

forward OnPasswordHashed(playerid);
public OnPasswordHashed(playerid) {
    new result[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(result);

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new process = map_get(m_playerAuthProcess, playerid);
    if(process == PLAYER_AUTH_REGISTERATION) {
        task_unblock(1);
        new success = await PlayerAuth_Add(name, result);
        if(success) {
            Player_Msg(playerid, -1, "Tai khoan cua ban da tao thanh cong!");
            Dialog_Show(playerid, PlayerLoginDialog, DIALOG_STYLE_PASSWORD, "Account Login", "Hay nhap mat khau cua ban vao day de tham gia vao may chu: ", "Accept", "Close");
        } else {
            Player_Kick(playerid, "Tai khoan xay ra van de, vui long dang nhap va thu lai.");
        }

        map_remove(m_playerAuthProcess, playerid);
        if(!map_size(m_playerAuthProcess)) {
            map_delete(m_playerAuthProcess);
            m_playerAuthProcess = Map:0;
        }
    }
    return 1;
}

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success) {
    if(success) {
        #if defined player_auth_ui_included
            if(!map_valid(m_playerLoginSuccess)) {
                m_playerLoginSuccess = map_new();
            }

            map_set(m_playerLoginSuccess, playerid, PLAYER_AUTH_LOGIN_SUCCESS);
        #endif

        printf("do game di thang cu");
    } else {
        #if !defined player_auth_ui_included
            Player_Kick(playerid, "[server] Kicked automatically because password was wrong.");
        #else 
            if(!map_valid(m_playerLoginSuccess)) {
                m_playerLoginSuccess = map_new();
            }

            map_set(m_playerLoginSuccess, playerid, PLAYER_AUTH_LOGIN_UNSUCCESS);
        #endif
    }
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    m_playerAuthProcess = map_new();
    mysql_query(MySQL_Connection(), 
        "CREATE TABLE IF NOT EXISTS player_auth (\
        created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
	    modified_date TIMESTAMP NULL ON UPDATE CURRENT_TIMESTAMP,\
        id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,\
        name VARCHAR(32) NOT NULL,\
        password VARCHAR(64) DEFAULT '',\
        UNIQUE player_auth_name(name))\
    ", true);

    printf("[player/player_auth] Loaded!");
    return 1;
}

hook OnPlayerConnect(playerid) {
    wait_ms(1);
    Player_ClearChat(playerid);

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    task_unblock(1);
    new id = await PlayerAuth_GetId(name);
    if(id == INVALID_PLAYER_AUTH) {
        #if !defined enable_register_mode
            Player_Kick(playerid, "May chu khong bat he thong dang ky trong game, vui long dang ky o trang chu.");
        #endif

        PlayerAuth_ShowRegisteration(playerid, name);       
    } else {
        #if !defined player_auth_ui_included
            Dialog_Show(playerid, PlayerLoginDialog, DIALOG_STYLE_PASSWORD, "Account Login", "Hay nhap mat khau cua ban vao day de tham gia vao may chu: ", "Accept", "Close");
        #endif

        #if defined player_auth_ui_included
            PlayerLogin_ShowUI(playerid);
        #endif
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(map_valid(m_playerAuthProcess) && map_has_key(m_playerAuthProcess, playerid)) {
        map_remove(m_playerAuthProcess, playerid);
        if(!map_size(m_playerAuthProcess)) {
            map_delete(m_playerAuthProcess);
            m_playerAuthProcess = Map:0;
        }
    } 
    return 1;
}

Dialog:PlayerPasswordDialog(playerid, response, listitem, inputtext[]) {
    if(response) {
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));

        if(isnull(inputtext) || strlen(inputtext) < 6 || strlen(inputtext) > MAX_PASSWORD_LENGTH) {
            Player_Msg(playerid, -1, "Mat khau khong hop le, vui long thu lai.");
            PlayerAuth_ShowRegisteration(playerid, name);
            return 1;
        }

        if(!map_valid(m_playerAuthProcess)) {
            m_playerAuthProcess = map_new();
        }

        // Hashing password
        map_set(m_playerAuthProcess, playerid, PLAYER_AUTH_REGISTERATION);
        bcrypt_hash(playerid, "OnPasswordHashed", inputtext, BCRYPT_COST);
    } else {
        Player_Kick(playerid, "Ban da huy qua trinh dang ky tai khoan trong may chu, may chu se tu dong da ban ra khoi he thong.");
    }
    return 1;
}

Dialog:PlayerLoginDialog(playerid, response, listitem, inputtext[]) {
    if(response) {
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));

        if(!map_valid(m_playerAuthProcess)) {
            m_playerAuthProcess = map_new();
        }

        map_set(m_playerAuthProcess, playerid, PLAYER_AUTH_LOGIN);
        Player_Msg(playerid, -1, "Ban da nhap mat khau thanh cong");

        new hash[BCRYPT_HASH_LENGTH],
            Task:t = PlayerAuth_GetHash(name),
            Guard:guard = pawn_guard(t);
        
        if(task_valid(t)) {
            await t;
            task_get_result_arr(t, hash);
            if(pawn_guard_valid(guard)) pawn_guard_free(guard);

            bcrypt_verify(playerid, "OnPasswordVerify", inputtext, hash);
        }
    } else {
        #if !defined player_auth_ui_included
            Player_Kick(playerid, "Ban da huy bo qua trinh dang nhap tai khoan, may chu se tu dong da ban ra khoi day.");
        #endif
    }
    return 1;
}