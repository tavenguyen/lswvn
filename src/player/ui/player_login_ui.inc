#if defined player_auth_ui_included
	#endinput
#endif

#define player_auth_ui_included

const PLAYER_LOGIN_UI_MAX = 14;

enum {
	PLAYER_AUTH_LOGIN_UNSUCCESS,
	PLAYER_AUTH_LOGIN_SUCCESS
}

static PlayerText:LoginUI[MAX_PLAYERS][PLAYER_LOGIN_UI_MAX] = {PlayerText:INVALID_PLAYER_TEXT_DRAW, ...};
new Map:m_playerLoginSuccess;

stock PlayerLogin_ShowUI(playerid) {
	LoginUI[playerid][0] = CreatePlayerTextDraw(playerid, 359.134429, 150.140502, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][0], 0.000000, 15.733338);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][0], 457.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][0], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][0], 208);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][0], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][0], 1);

    LoginUI[playerid][1] = CreatePlayerTextDraw(playerid, 165.301086, 149.740478, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][1], 0.000000, 15.763358);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][1], 353.301116, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][1], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][1], 208);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][1], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][1], 1);

    LoginUI[playerid][2] = CreatePlayerTextDraw(playerid, 120.366355, 86.055473, "mdl-2000:login");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][2], 389.000000, 273.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][2], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][2], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][2], 0);

    LoginUI[playerid][3] = CreatePlayerTextDraw(playerid, 365.701080, 193.318588, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][3], 0.000000, 1.233332);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][3], 448.701080, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][3], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][3], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][3], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][3], 1);

    LoginUI[playerid][4] = CreatePlayerTextDraw(playerid, 365.701080, 212.664138, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][4], 0.000000, 1.233332);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][4], 448.701080, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][4], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][4], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][4], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][4], 1);

    LoginUI[playerid][5] = CreatePlayerTextDraw(playerid, 365.700958, 212.775405, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][5], 0.000000, 1.200000);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][5], 375.499969, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][5], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][5], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][5], -2883329);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][5], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][5], 1);

    LoginUI[playerid][6] = CreatePlayerTextDraw(playerid, 365.734283, 193.477767, "box");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][6], 0.000000, 1.206001);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][6], 375.599853, 0.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][6], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][6], -1);
    PlayerTextDrawUseBox(playerid, LoginUI[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, LoginUI[playerid][6], -2883329);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][6], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][6], 1);

    LoginUI[playerid][7] = CreatePlayerTextDraw(playerid, 393.199920, 233.399932, "mdl-2000:login_button");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][7], 29.000000, 8.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][7], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][7], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][7], 0);
    PlayerTextDrawSetSelectable(playerid, LoginUI[playerid][7], true);

    LoginUI[playerid][8] = CreatePlayerTextDraw(playerid, 94.633300, -32.681526, "mdl-2000:logo");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][8], 462.000000, 285.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][8], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][8], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][8], 0);

    LoginUI[playerid][9] = CreatePlayerTextDraw(playerid, 365.767730, 193.433395, "mdl-2000:account");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][9], 8.000000, 11.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][9], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][9], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][9], 0);

    LoginUI[playerid][10] = CreatePlayerTextDraw(playerid, 364.534332, 210.496444, "mdl-2000:password");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][10], 12.000000, 16.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][10], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][10], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][10], 0);

    LoginUI[playerid][11] = CreatePlayerTextDraw(playerid, 262.067840, 109.370361, "mdl-2000:des");
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][11], 375.000000, 233.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][11], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][11], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][11], 0);

    LoginUI[playerid][12] = CreatePlayerTextDraw(playerid, 379.667633, 195.077789, "Tai_khoan");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][12], 0.160666, 0.807703);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][12], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][12], -2139062017);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][12], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][12], 1);

    LoginUI[playerid][13] = CreatePlayerTextDraw(playerid, 380.000854, 214.293792, "Nhap_mat_khau");
    PlayerTextDrawLetterSize(playerid, LoginUI[playerid][13], 0.160666, 0.807703);
    PlayerTextDrawTextSize(playerid, LoginUI[playerid][13], 447.000000, 3.000000);
    PlayerTextDrawAlignment(playerid, LoginUI[playerid][13], 1);
    PlayerTextDrawColor(playerid, LoginUI[playerid][13], -2139062017);
    PlayerTextDrawSetShadow(playerid, LoginUI[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, LoginUI[playerid][13], 255);
    PlayerTextDrawFont(playerid, LoginUI[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, LoginUI[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, LoginUI[playerid][13], true);

	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));

	PlayerTextDrawSetString(playerid, LoginUI[playerid][12], name);
	for(new i = 0; i < PLAYER_LOGIN_UI_MAX; i++) PlayerTextDrawShow(playerid, LoginUI[playerid][i]);
	SelectTextDraw(playerid, 0xAFAFAFAA);
	return true;
}

stock PlayerLogin_HideUI(playerid) {
    for(new i = 0; i < PLAYER_LOGIN_UI_MAX; i++) {
        PlayerTextDrawHide(playerid, LoginUI[playerid][i]);
        PlayerTextDrawDestroy(playerid, LoginUI[playerid][i]);
        LoginUI[playerid][i] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    }

    CancelSelectTextDraw(playerid);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
	m_playerLoginSuccess = map_new();
	return 1;
}

hook OnPlayerDisconnect(playerid) {
    if(map_valid(m_playerLoginSuccess) && map_has_key(m_playerLoginSuccess, playerid)) {
        map_remove(m_playerLoginSuccess, playerid);
        if(!map_size(m_playerLoginSuccess)) {
            map_delete(m_playerLoginSuccess);
            m_playerLoginSuccess = Map:0;
        }
    } 
    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
	if(playertextid == LoginUI[playerid][13]) {
		Dialog_Show(playerid, PlayerLoginDialog, DIALOG_STYLE_PASSWORD, "Account Login", "Hay nhap mat khau cua ban vao day de tham gia vao may chu: ", "Accept", "Close");
	} 

	if(playertextid == LoginUI[playerid][7]) {
		if(map_valid(m_playerLoginSuccess) && map_has_key(m_playerLoginSuccess, playerid)) {
			new success = map_get(m_playerLoginSuccess, playerid);
			if(success == PLAYER_AUTH_LOGIN_SUCCESS) {
				CallLocalFunction("Player_OnCharRetrived", "i", playerid);

				map_remove(m_playerLoginSuccess, playerid);
				if(!map_size(m_playerLoginSuccess)) {
					map_delete(m_playerLoginSuccess);
					m_playerLoginSuccess = Map:0;
				}
			} else {
				Player_Msg(playerid, -1, "Sai mat khau, vui long thu lai.");
			}
		}
	}
	return 1;
}