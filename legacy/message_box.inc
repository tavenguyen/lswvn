#if defined message_box_included
	#endinput
#endif

#define message_box_included

#include <a_samp>
#tryinclude <PawnPlus>

#define 			MAX_NOTIFY_LENGTH_INLINE				60
#define  			TOP_LEFT_X 								17.3333
#define   			TOP_LEFT_Y 	 							179.6296

static enum _:eBoxData {
	Float:positionX,
	Float:positionY,
	Float:sizeX,
	Float:sizeY,
}

static const Float:MessageBoxConstant[3][eBoxData] = {
	{12.6000, 162.1516, 80.0000, 32.0000}, // Box Base Outside
	{14.3999, 164.4701, 76.0000, 28.0000}, // Box Base Inside
	{53.5331, 166.9256, 0.0000, 0.0000} // Notify Text Main
};

static enum _:eStatusBoxBase {
	PlayerText:box_base_outside,
	PlayerText:box_base_inside,
}

static enum _:eNotify {
	notify_box_base[eStatusBoxBase],
	PlayerText:notify_text_main,
	PlayerText:notify_TD,
}

static Message_Box_PTD[MAX_PLAYERS][eNotify];

stock MsgBox_ShowForPlayer(playerid, const notify_main[], const message[], time_milliseconds, const max_size = 30) {
	new const size = strlen(message);
	new result[500];
	strcat(result, message);
	format(result, sizeof(result), "%s", MsgBox_ReplaceFindingKeyBy(result, "[endl]", " "));

	new Float:notify_main_posX;	
	if(size <= max_size) {
		MsgBox_SetPTDSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], MessageBoxConstant[0][sizeX], MessageBoxConstant[0][sizeY]);
		MsgBox_SetPTDSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], MessageBoxConstant[1][sizeX], MessageBoxConstant[1][sizeY]);
		notify_main_posX = MessageBoxConstant[2][positionX];
	} else {
		new temp_size = size;
		if(temp_size > MAX_NOTIFY_LENGTH_INLINE) temp_size = 60;
		
		new found_amount;

		format(result, sizeof(result), "%s", MsgBox_MessageSplitProgress(result, found_amount));

		new const Float:constant_value = 1.8, Float:constant_value_y = 8.0,
			Float:calc = constant_value * (temp_size - max_size);

		MsgBox_SetPTDSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], MessageBoxConstant[0][sizeX] + calc, MessageBoxConstant[0][sizeY] + found_amount * constant_value_y);
		MsgBox_SetPTDSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], MessageBoxConstant[1][sizeX] + calc, MessageBoxConstant[1][sizeY] + found_amount * constant_value_y);
		notify_main_posX = ((MessageBoxConstant[0][sizeX] + calc) + MessageBoxConstant[0][positionX]*2)/2.0;
	}
	
	format(result, sizeof(result), "%s", MsgBox_ReplaceFindingKeyBy(result, " ", "_"));
	format(result, sizeof(result), "%s", MsgBox_ReplaceFindingKeyBy(result, "[endl]", " "));
	PlayerTextDrawHide(playerid, Message_Box_PTD[playerid][notify_TD]);
	PlayerTextDrawSetString(playerid, Message_Box_PTD[playerid][notify_TD], result);
	PlayerTextDrawShow(playerid, Message_Box_PTD[playerid][notify_TD]);
	
	format(result, sizeof(result), "%s", MsgBox_ReplaceFindingKeyBy(notify_main, " ", "_"));
	SetNotifyMain(playerid, result, notify_main_posX, MessageBoxConstant[2][positionY]);
	return 1;
}

stock SetNotifyMain(playerid, const text[], const Float:x_pos, const Float:y_pos) {
	if(Message_Box_PTD[playerid][notify_text_main] != PlayerText:INVALID_PLAYER_TEXT_DRAW) {
		PlayerTextDrawHide(playerid, Message_Box_PTD[playerid][notify_text_main]);
		PlayerTextDrawDestroy(playerid, Message_Box_PTD[playerid][notify_text_main]);
	}

	Message_Box_PTD[playerid][notify_text_main] = CreatePlayerTextDraw(playerid, x_pos, y_pos, text); 
	PlayerTextDrawLetterSize(playerid, Message_Box_PTD[playerid][notify_text_main], 0.1566, 0.9943);
	PlayerTextDrawTextSize(playerid, Message_Box_PTD[playerid][notify_text_main], 0.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, Message_Box_PTD[playerid][notify_text_main], 2);
	PlayerTextDrawColor(playerid, Message_Box_PTD[playerid][notify_text_main], -1);
	PlayerTextDrawSetOutline(playerid, Message_Box_PTD[playerid][notify_text_main], 1);
	PlayerTextDrawBackgroundColor(playerid, Message_Box_PTD[playerid][notify_text_main], 255);
	PlayerTextDrawFont(playerid, Message_Box_PTD[playerid][notify_text_main], 3);
	PlayerTextDrawSetProportional(playerid, Message_Box_PTD[playerid][notify_text_main], 1);
	PlayerTextDrawSetShadow(playerid, Message_Box_PTD[playerid][notify_text_main], 0);
	PlayerTextDrawShow(playerid, Message_Box_PTD[playerid][notify_text_main]);
	return 1;
}

stock MsgBox_SetPTDSize(playerid, PlayerText:status, const Float:x_size, const Float:y_size) {
	if(status == PlayerText:INVALID_PLAYER_TEXT_DRAW) {
		return 0;
	}

	printf("%f %f", x_size, y_size);
	PlayerTextDrawHide(playerid, status);
	PlayerTextDrawTextSize(playerid, status, x_size, y_size);
	PlayerTextDrawShow(playerid, status);	
	return 1;
}

stock MsgBox_ReplaceFindingKeyBy(const message[], const finding_string[], const replaced_string[]) {
	new const length = strlen(finding_string);

	new temp[20];
	new List:stored_elemennts = list_new();
	for(new i = 0; i < strlen(message) - length + 1; i++) {
		for(new start = 0; start < length; start++) 
			temp[start] += message[start + i];
		
		if(!strcmp(temp, finding_string, false)) {
			list_add(stored_elemennts, i);
		}

		for(new j = 0; j < length; j++) temp[j] = EOS;
	}

	new result[500];
	strcat(result, message);
	if(!list_size(stored_elemennts)) {
		return result;
	}

	for(new j = 0; j < strlen(message); j++) result[j] = EOS;
	
	new start = list_get(stored_elemennts, 0), end = start + length - 1, count = 0;
	for(new i = 0, index = 0, j = strlen(message); i < j; i++) {
		if(i >= start && i <= end) {
			count = count + 1;
			if(count == list_size(stored_elemennts)) {count -= 1;}
			start = list_get(stored_elemennts, count);
			i = end; 
			end = start + length - 1;
			strcat(result, replaced_string);
			index = strlen(result);
		} else {
			result[index] = message[i];
			index++;
		}
	}

	printf("result: %s | length: %d", result, strlen(result));
	return result;
}

stock MsgBox_MessageSplitProgress(const message[], &found_amount = 0) {
	new const 
		size = strlen(message),
		max_line = (size < MAX_NOTIFY_LENGTH_INLINE ? 1 : (size/MAX_NOTIFY_LENGTH_INLINE) + (size > MAX_NOTIFY_LENGTH_INLINE ? 1 : 0));
	
	new 
		result[500], start = 0, end,
		string_split[16][100];

	for(new i = 1; i <= max_line; i++) {
		end = i * MAX_NOTIFY_LENGTH_INLINE;
		if(end > size) end = size;
		strmid(string_split[i - 1], message, start, end);
		start = end;

		if(i != max_line) {
			strcat(string_split[i - 1], "...[endl]");
			found_amount++;
		}

		strcat(result, string_split[i - 1], 500);
	}

	return result;
}

public OnPlayerConnect(playerid) {
	Message_Box_PTD[playerid][notify_text_main] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
	//-------------------------------------------------------------------------------------------------//

	Message_Box_PTD[playerid][notify_box_base][box_base_outside] = CreatePlayerTextDraw(playerid, MessageBoxConstant[0][positionX], MessageBoxConstant[0][positionY], "LD_SPAC:white"); 
	PlayerTextDrawTextSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], MessageBoxConstant[0][sizeX],  MessageBoxConstant[0][sizeY]);
	PlayerTextDrawAlignment(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 1);
	PlayerTextDrawColor(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 255);
	PlayerTextDrawBackgroundColor(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 255);
	PlayerTextDrawFont(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 4);
	PlayerTextDrawSetProportional(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 0);
	PlayerTextDrawSetShadow(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_outside], 0);

	Message_Box_PTD[playerid][notify_box_base][box_base_inside] = CreatePlayerTextDraw(playerid, MessageBoxConstant[1][positionX], MessageBoxConstant[1][positionY], "LD_SPAC:white"); 
	PlayerTextDrawTextSize(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], MessageBoxConstant[1][sizeX], MessageBoxConstant[1][sizeY]);
	PlayerTextDrawAlignment(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 1);
	PlayerTextDrawColor(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 572465663);
	PlayerTextDrawBackgroundColor(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 255);
	PlayerTextDrawFont(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 4);
	PlayerTextDrawSetProportional(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 0);
	PlayerTextDrawSetShadow(playerid, Message_Box_PTD[playerid][notify_box_base][box_base_inside], 0);

	//-------------------------------------------------------------------------------------------------//
	Message_Box_PTD[playerid][notify_TD] = CreatePlayerTextDraw(playerid, TOP_LEFT_X, TOP_LEFT_Y, "Message_Box_Text");
	PlayerTextDrawLetterSize(playerid, Message_Box_PTD[playerid][notify_TD], 0.1146, 0.8657);
	PlayerTextDrawTextSize(playerid, Message_Box_PTD[playerid][notify_TD], 52.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, Message_Box_PTD[playerid][notify_TD], 1);
	PlayerTextDrawColor(playerid, Message_Box_PTD[playerid][notify_TD], -1);
	PlayerTextDrawBackgroundColor(playerid, Message_Box_PTD[playerid][notify_TD], 255);
	PlayerTextDrawFont(playerid, Message_Box_PTD[playerid][notify_TD], 1);
	PlayerTextDrawSetProportional(playerid, Message_Box_PTD[playerid][notify_TD], 1);
	PlayerTextDrawSetShadow(playerid, Message_Box_PTD[playerid][notify_TD], 0);
	return 1;
}

public OnPlayerDisconnect(playerid, reason) {
	if(Message_Box_PTD[playerid][notify_box_base][box_base_inside] != PlayerText:INVALID_PLAYER_TEXT_DRAW) {
		PlayerTextDrawDestroy(playerid, Message_Box_PTD[playerid][notify_text_main]);
		Message_Box_PTD[playerid][notify_text_main] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
	}

	if(Message_Box_PTD[playerid][notify_box_base][box_base_outside] != PlayerText:INVALID_PLAYER_TEXT_DRAW) {
		PlayerTextDrawDestroy(playerid, Message_Box_PTD[playerid][notify_text_main]);
		Message_Box_PTD[playerid][notify_text_main] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
	}

	if(Message_Box_PTD[playerid][notify_text_main] != PlayerText:INVALID_PLAYER_TEXT_DRAW) {
		PlayerTextDrawDestroy(playerid, Message_Box_PTD[playerid][notify_text_main]);
		Message_Box_PTD[playerid][notify_text_main] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
	}

	if(Message_Box_PTD[playerid][notify_TD] != PlayerText:INVALID_PLAYER_TEXT_DRAW) { 
		PlayerTextDrawDestroy(playerid, Message_Box_PTD[playerid][notify_TD]);
		Message_Box_PTD[playerid][notify_TD] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
	}
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect cb_prefix_OnPlayerConnect
#if defined cb_prefix_OnPlayerConnect
	forward cb_prefix_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect 
	#undef OnPlayerDisconnect
#else 
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect cb_prefix_OnPlayerDisconnect
#if defined cb_prefix_OnPlayerDisconnect
	forward cb_prefix_OnPlayerDisconnect(playerid, reason);
#endif
