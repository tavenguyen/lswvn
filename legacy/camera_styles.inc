#if defined camera_styles_included
	#endinput
#endif

#define camera_styles_included

#if !defined _PawnPlus_included
    #include <PawnPlus>
#endif

const MAX_CAMERA_ATTEMPS = 3;

forward CameraOnStyleSet(playerid, Task:t);
public CameraOnStyleSet(playerid, Task:t) {
    wait_ms(1000);
    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);
    z *= (MAX_CAMERA_ATTEMPS * 10.0);
    for(new i = 0; i <= MAX_CAMERA_ATTEMPS; i++) {
        z -= (z / MAX_CAMERA_ATTEMPS);
        SetPlayerCameraPos(playerid, x, y, z);
        SetPlayerCameraLookAt(playerid, x, y, -z);
        wait_ms(1500);
    }

    SetCameraBehindPlayer(playerid);
    task_set_result(t, 1);
    return 1;
}

stock Task:SetCameraStyle(playerid) {
    new Task:t = task_new();
    CallLocalFunction("CameraOnStyleSet", "id", playerid, _:t);
    return t;
}