SSAnne_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SSAnne_Exterior_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

@ Kanto-Verse: Joey starts the game at (41, 25), just off the S.S. AQUA (see WarpToTruck in new_game.c).
@ Maps always load with the player facing south, so turn him north there.
SSAnne_Exterior_OnWarp::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 0, SSAnne_Exterior_EventScript_TryFaceNorthOnArrival
	.2byte 0

SSAnne_Exterior_EventScript_TryFaceNorthOnArrival::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 41, SSAnne_Exterior_EventScript_EndOnWarp
	goto_if_ne VAR_0x8005, 25, SSAnne_Exterior_EventScript_EndOnWarp
	turnobject LOCALID_PLAYER, DIR_NORTH
SSAnne_Exterior_EventScript_EndOnWarp::
	end

SSAnne_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
	end

SSAnne_Exterior_OnFrame::
	.2byte 0

SSAnne_Exterior_ExitSSAnne::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_le VAR_0x8005, 6, SSAnne_Exterior_WalkDown
	call_if_ge VAR_0x8005, 7, SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_RG_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	warp MAP_VERMILION_CITY, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_WalkDown::
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
