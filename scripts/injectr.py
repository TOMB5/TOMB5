#!/usr/bin/env python

#         _ _                          _            _            
#  ______| (_)_ __ ___   ___ _ __  ___(_) ___  _ __( )__         
# |_  / _` | | '_ ` _ \ / _ \ '_ \/ __| |/ _ \| '_ \/ __|        
#  / / (_| | | | | | | |  __/ | | \__ \ | (_) | | | \__ \        
# /___\__,_|_|_| |_| |_|\___|_| |_|___/_|\___/|_| |_|___/      
#           
#             _       _        _______ _____  
#            (_)     (_)      |__   __|  __ \ 
#             _ _ __  _  ___  ___| |  | |__) |
#            | | '_ \| |/ _ \/ __| |  |  _  / 
#            | | | | | |  __/ (__| |  | | \ \ 
#            |_|_| |_| |\___|\___|_|  |_|  \_\
#                   _/ |                      
#                  |__/                       
#     

# Basically, this takes the original game executable and replaces original
# functions' implementations by ours. For that, it creates a new section in 
# the PE file, put all the functions' code in it, and replaces the first 8
# bytes at the beginning of each function by a "jmp ADDR" where ADDR is the
# address of our implementation of the function. This allows for easier 
# testing of the validity of the functions. 
# Btw it really whips the llama's ass.      

# increment this plz
# rev 1
# 2017-10-22


import json
import os.path
import sys
import pefile
from shutil import copyfile

try:
	import idc
except ImportError:
	print("IDA not detected, restarting with IDA! Make sure that idaq.exe is in PATH!")
	pth = "../build/SPEC_PC/Debug/PCTomb5.exe"
	if not os.path.isfile(pth):
		pth = "../build/SPEC_PC/Debug/PCTOMB5.EXE"
	copyfile(pth, os.path.join(os.getcwd(), "PCTOMB5.EXE"))
	os.system('idaq.exe -A -S"' + "".join(sys.argv) + '" PCTOMB5.EXE')
	with open("output.txt", "r") as f:
		print(f.read())
	exit()

from urllib2 import urlopen
print(os.getcwd())
orig_stdout = sys.stdout
sys.stdout = file("output.txt", "w")

# STEP
#  _ 
# / |
# | |
# | |
# |_|
# 
# Global settings

def isarg(arg, default):
	if any(x for x in idc.ARGV if x.strip().lower() == "+%s" % arg):
		return True
	elif any(x for x in idc.ARGV if x.strip().lower() == "-%s" % arg):
		return False
	else:
		return default

ISSUE_ID = 			46 							# ID of the issue on GitHub (for the API request)
SHOW_WARN = 		isarg("warn", True) 		# Show warnings (error messages)
SHOW_HINT = 		isarg("hint", True) 		# Show hints (e.g. function checked in list but not (F) in file)
SHOW_STATUS = 		isarg("status", False)		# Show status messages (function added successfully yay)
USE_REPR =			isarg("userepr", False)		# Debugging purposes. When outputting a list (e.g. SHOW_UNIMPL), use repr()
EXCLUDED = 			[]							# List of functions that *will* be considered UNIMPLEMENTED, even if they are checked in the list.

# STEP
#  ____  
# |___ \ 
#   __) |
#  / __/ 
# |_____|
# 
# Download the current list

#body = urlopen("https://api.github.com/repos/TOMB5/TOMB5/issues/46").read().decode("utf8")
#issue = json.loads(body)["body"] # loads the Markdown source of the issue

issue = """### GAME
#### BOX.C
- [ ] `AIGuard`
- [ ] `AlertAllGuards`
- [x] `AlertNearbyGuards`
- [ ] `BadFloor`
- [ ] `CalculateTarget`
- [x] `CreatureActive`
- [ ] `CreatureAIInfo`
- [ ] `CreatureAnimation`
- [ ] `CreatureCreature`
- [x] `CreatureDie`
- [ ] `CreatureEffect`
- [ ] `CreatureEffectT`
- [ ] `CreatureFloat`
- [ ] `CreatureJoint`
- [ ] `CreatureKill`
- [ ] `CreatureMood`
- [x] `CreatureTilt`
- [ ] `CreatureTurn`
- [ ] `CreatureUnderwater`
- [ ] `CreatureVault`
- [x] `CreatureYRot`
- [x] `DropBaddyPickups`
- [ ] `EscapeBox`
- [ ] `FindAITargetObject`
- [ ] `GetAITarget`
- [ ] `GetCreatureMood`
- [x] `InitialiseCreature`
- [ ] `MoveCreature3DPos`
- [x] `SameZone`
- [ ] `SearchLOT`
- [ ] `StalkBox`
- [x] `TargetBox`
- [x] `UpdateLOT`
- [x] `ValidBox`
#### CAMERA.C
- [x] `AlterFOV`
- [ ] `BinocularCamera`
- [ ] `CalculateCamera`
- [ ] `CameraCollisionBounds`
- [ ] `ChaseCamera`
- [ ] `CombatCamera`
- [ ] `ConfirmCameraTargetPos`
- [ ] `FixedCamera`
- [x] `InitialiseCamera`
- [ ] `LaraTorch`
- [ ] `LookCamera`
- [ ] `mgLOS`
- [ ] `MoveCamera`
- [ ] `ScreenShake`
- [ ] `UpdateCameraElevation`
#### COLLIDE.C
- [ ] `AIPickupCollision`
- [ ] `CreatureCollision`
- [ ] `GenericSphereBoxCollision`
- [ ] `ItemPushLaraStatic`
- [ ] `LaraBaddieCollision`
- [x] `ShiftItem`
- [ ] `TestBoundsCollideStatic`
- [ ] `TestForObjectOnLedge`
- [ ] `TrapCollision`
- [x] `TriggerLaraBlood`
- [x] `UpdateLaraRoom`
#### CONTROL.C
- [ ] `_TestTriggers`
- [x] `AddFire`
- [x] `AddRoomFlipItems`
- [ ] `AlterFloorHeight`
- [ ] `check_xray_machine_trigger`
- [x] `CheckCutPlayed`
- [ ] `CheckGuardOnTrigger`
- [x] `ClearFires`
- [ ] `ControlPhase`
- [x] `ExplodeItemNode`
- [ ] `FireCrossBowFromLaserSight`
- [x] `FlipMap`
- [x] `GetDoor`
- [x] `GetFloor`
- [x] `GetRandomControl`
- [x] `GetRandomDraw`
- [ ] `GetTargetOnLOS`
- [ ] `GetWaterHeight`
- [x] `InitCutPlayed`
- [ ] `InterpolateAngle`
- [ ] `is_object_in_room`
- [x] `KillMoveEffects`
- [x] `KillMoveItems`
- [x] `LOS`
- [ ] `NeatAndTidyTriggerCutscene`
- [ ] `RefreshCamera`
- [x] `RemoveRoomFlipItems`
- [ ] `ResetGuards`
- [x] `SeedRandomControl`
- [x] `SeedRandomDraw`
- [x] `SetCutNotPlayed`
- [x] `SetCutPlayed`
- [x] `TestTriggers`
- [ ] `TriggerCDTrack`
- [ ] `TriggerNormalCDTrack`
#### DEBRIS.C
- [ ] `GetFreeDebris`
- [ ] `ShatterObject`
- [ ] `TriggerDebris`
#### DELSTUFF.C
- [ ] `CalcLaraMatrices` @Gh0stBlade - WIP
#### DELTAPAK.C
- [x] `andrea1_control`
- [x] `andrea1_end`
- [x] `andrea1_init`
- [ ] `andrea2_control`
- [x] `andrea2_end`
- [x] `andrea2_init`
- [x] `andrea3_control`
- [x] `andrea3_end`
- [x] `andrea3_init`
- [x] `andrea3b_control`
- [x] `andrea3b_end`
- [x] `andrea3b_init`
- [x] `andrea4_control`
- [x] `andrea4_end`
- [x] `andrea4_init`
- [x] `andy10_control`
- [x] `andy10_end`
- [x] `andy10_init`
- [x] `andy11_control`
- [x] `andy11_end`
- [x] `andy11_init`
- [x] `andy1_control`
- [x] `andy1_end`
- [x] `andy1_init`
- [x] `andy2_control`
- [x] `andy2_end`
- [x] `andy2_init`
- [x] `andy3_control`
- [x] `andy3_end`
- [x] `andy3_init`
- [x] `andy4_control`
- [x] `andy4_end`
- [x] `andy4_init`
- [x] `andy4b_control`
- [x] `andy4b_end`
- [x] `andy4b_init`
- [x] `andy5_control`
- [x] `andy5_end`
- [x] `andy5_init`
- [x] `andy6_control`
- [x] `andy6_end`
- [x] `andy6_init`
- [x] `andy7_control`
- [x] `andy7_end`
- [x] `andy7_init`
- [x] `andy8_control`
- [x] `andy8_end`
- [x] `andy8_init`
- [x] `andy9_control`
- [x] `andy9_end`
- [x] `andy9_init`
- [x] `andypew_control`
- [x] `andypew_end`
- [x] `andypew_init`
- [ ] `CalculateObjectLightingLaraCutSeq`
- [x] `cossack_control`
- [x] `cossack_end`
- [x] `cossack_init`
- [x] `cranecut_control`
- [x] `cranecut_end`
- [x] `cranecut_init`
- [x] `Cutanimate`
- [x] `CutLaraBubbles`
- [x] `cutseq_givelara_hk`
- [x] `cutseq_givelara_pistols`
- [x] `cutseq_kill_item`
- [x] `cutseq_malloc`
- [x] `cutseq_removelara_hk`
- [x] `cutseq_removelara_pistols`
- [x] `cutseq_restore_item`
- [ ] `cutseq_shoot_pistols`
- [x] `deal_with_actor_shooting`
- [x] `deal_with_pistols`
- [x] `DelsHandyTeleportLara`
- [x] `DelTorchFlames`
- [x] `do_catapult_meshswap`
- [x] `do_chalk_meshswap`
- [x] `do_clanger_meshswap`
- [x] `do_hammer_meshswap`
- [ ] `do_new_cutscene_camera`
- [x] `do_pierre_gun_meshswap`
- [x] `find_a_fucking_item`
- [x] `finish_cutseq`
- [ ] `frigup_lara`
- [ ] `GetActorJointAbsPosition`
- [ ] `GrabActorMatrix`
- [x] `hamgate_control`
- [x] `hamgate_end`
- [x] `hamgate_init`
- [x] `handle_actor_chatting`
- [ ] `handle_cutseq_triggering`
- [x] `handle_lara_chatting`
- [ ] `init_cutseq_actors`
- [x] `init_cutseq_malloc`
- [x] `init_resident_cutseq`
- [ ] `InitPackNodes`
- [x] `joby10_control`
- [x] `joby10_end`
- [x] `joby10_init`
- [x] `joby2_control`
- [x] `joby2_end`
- [x] `joby2_init`
- [x] `joby3_control`
- [x] `joby3_end`
- [x] `joby3_init`
- [ ] `joby4_control`
- [x] `joby4_end`
- [x] `joby4_init`
- [x] `joby5_control`
- [x] `joby5_end`
- [x] `joby5_init`
- [x] `joby6_control`
- [x] `joby6_end`
- [x] `joby6_init`
- [x] `joby7_control`
- [x] `joby7_end`
- [x] `joby7_init`
- [ ] `joby8_control`
- [x] `joby8_end`
- [x] `joby8_init`
- [x] `joby9_control`
- [x] `joby9_end`
- [x] `joby9_init`
- [ ] `Load_and_Init_Cutseq`
- [x] `monk2_control`
- [x] `monk2_end`
- [x] `monk2_init`
- [x] `ResetCutanimate`
- [x] `richcut1_control`
- [x] `richcut1_end`
- [x] `richcut1_init`
- [ ] `richcut2_control`
- [x] `richcut2_end`
- [x] `richcut2_init`
- [x] `richcut3_control`
- [x] `richcut3_end`
- [x] `richcut3_init`
- [x] `richcut4_control`
- [x] `richcut4_end`
- [x] `richcut4_init`
- [x] `setup_preist_meshswap`
- [ ] `special1_control`
- [ ] `special1_end`
- [ ] `special1_init`
- [ ] `special2_control`
- [ ] `special2_end`
- [ ] `special2_init`
- [ ] `special3_control`
- [ ] `special3_end`
- [ ] `special3_init`
- [ ] `special4_control`
- [ ] `special4_end`
- [ ] `special4_init`
- [ ] `stealth3_end`
- [ ] `stealth3_start`
- [x] `swampy_control`
- [x] `swampy_end`
- [x] `swampy_init`
- [ ] `trigger_title_spotcam`
- [x] `trigger_weapon_dynamics`
- [x] `TriggerActorBlood`
- [x] `TriggerDelBrownSmoke`
- [x] `TriggerDelSmoke`
- [x] `TriggerUnderwaterBlood`
#### DOOR.C
- [ ] `DoorCollision`
- [ ] `DoorControl`
- [ ] `DoubleDoorCollision`
- [ ] `OpenThatDoor`
- [ ] `ProcessClosedDoors`
- [ ] `PushPullKickDoorCollision`
- [ ] `PushPullKickDoorControl`
- [ ] `SequenceDoorControl`
- [ ] `ShutThatDoor`
- [ ] `UnderwaterDoorCollision`
#### DRAW.C
- [ ] `CalculateObjectLightingLara`
- [ ] `UpdateSkyLightning`
#### EFFECT2.C
- [ ] `ControlEnemyMissile`
- [ ] `ControlSmokeEmitter`
- [ ] `DetatchSpark`
- [ ] `KillAllCurrentItems`
- [x] `KillEverything`
- [ ] `TriggerDartSmoke`
- [x] `TriggerGunSmoke`
- [ ] `TriggerSuperJetFlame`
- [ ] `TriggerWaterfallMist`
#### EFFECTS.C
- [x] `ActivateCamera`
- [x] `ActivateKey`
- [ ] `ClearSpidersPatch`
- [x] `ExplosionFX`
- [x] `finish_level_effect`
- [ ] `floor_shake_effect`
- [x] `invisibility_off`
- [x] `invisibility_on`
- [x] `KillActiveBaddies`
- [x] `lara_hands_free`
- [x] `LaraLocation`
- [x] `LaraLocationPad`
- [x] `PoseidonSFX`
- [x] `reset_hair`
- [ ] `ResetTest`
- [x] `RubbleFX`
- [x] `SetFog`
- [x] `shoot_left_gun`
- [x] `shoot_right_gun`
- [ ] `SoundEffects`
- [x] `SoundFlipEffect`
- [x] `SwapCrowbar`
- [x] `TL_1`
- [x] `TL_10`
- [x] `TL_11`
- [x] `TL_12`
- [x] `TL_2`
- [x] `TL_3`
- [x] `TL_4`
- [x] `TL_5`
- [x] `TL_6`
- [x] `TL_7`
- [x] `TL_8`
- [x] `TL_9`
- [x] `turn180_effect`
- [x] `void_effect`
- [ ] `WaterFall`
#### FLMTORCH.C
- [ ] `DoFlameTorch`
- [ ] `FireCollision`
- [ ] `FlameTorchControl`
- [ ] `GetFlameTorch`
- [ ] `TriggerTorchFlame`
#### GAMEFLOW.C
- [ ] `DoGameflow`
- [ ] `DoLevel`
- [ ] `DoTitle`
- [ ] `LoadGameflow`
- [ ] `QuickControlPhase`
#### HAIR.C
- [x] `InitialiseHair`
#### HEALTH.C
- [ ] `AddDisplayPickup`
- [ ] `DrawAirBar`
- [ ] `DrawGameInfo`
- [ ] `DrawHealthBar`
- [ ] `DrawPickups`
- [ ] `FlashIt`
- [x] `InitialisePickUpDisplay`
#### ITEMS.C
- [x] `AddActiveItem`
- [x] `CreateEffect`
- [x] `CreateItem`
- [ ] `EffectNewRoom`
- [x] `InitialiseFXArray`
- [ ] `InitialiseItem`
- [x] `InitialiseItemArray`
- [x] `ItemNewRoom`
- [ ] `KillEffect`
- [ ] `KillItem`
- [ ] `RemoveActiveItem`
- [ ] `RemoveDrawnItem`
#### LARA.C
- [ ] `ApplyVelocityToRope`
- [ ] `CanLaraHangSideways`
- [ ] `FallFromRope`
- [x] `GetDirOctant`
- [x] `GetLaraCollisionInfo`
- [x] `GetTighRopeFallOff`
- [ ] `IsValidHangPos`
- [ ] `JumpOffRope`
- [ ] `lara_as_all4s`
- [x] `lara_as_all4turnl`
- [x] `lara_as_all4turnr`
- [x] `lara_as_back`
- [x] `lara_as_backjump`
- [x] `lara_as_climbrope`
- [ ] `lara_as_climbroped`
- [ ] `lara_as_compress`
- [x] `lara_as_controlled`
- [x] `lara_as_controlledl`
- [x] `lara_as_crawl`
- [ ] `lara_as_crawlb`
- [ ] `lara_as_dash`
- [x] `lara_as_dashdive`
- [x] `lara_as_death`
- [x] `lara_as_deathslide`
- [x] `lara_as_duck`
- [x] `lara_as_duckl`
- [x] `lara_as_duckr`
- [x] `lara_as_extcornerl`
- [x] `lara_as_extcornerr`
- [x] `lara_as_fallback`
- [x] `lara_as_fastback`
- [x] `lara_as_fastdive`
- [x] `lara_as_fastfall`
- [x] `lara_as_fastturn`
- [x] `lara_as_forwardjump`
- [x] `lara_as_gymnast`
- [x] `lara_as_hang`
- [x] `lara_as_hang2`
- [x] `lara_as_hangleft`
- [x] `lara_as_hangright`
- [x] `lara_as_hangturnl`
- [x] `lara_as_hangturnr`
- [x] `lara_as_intcornerl`
- [x] `lara_as_intcornerr`
- [x] `lara_as_leftjump`
- [x] `lara_as_monkey180`
- [x] `lara_as_monkeyl`
- [x] `lara_as_monkeyr`
- [x] `lara_as_monkeyswing`
- [x] `lara_as_null`
- [x] `lara_as_parallelbars`
- [ ] `lara_as_pbleapoff`
- [x] `lara_as_pickup`
- [x] `lara_as_pickupflare`
- [x] `lara_as_poleleft`
- [x] `lara_as_poleright`
- [x] `lara_as_ppready`
- [x] `lara_as_pullblock`
- [x] `lara_as_pulley`
- [x] `lara_as_pushblock`
- [x] `lara_as_reach`
- [x] `lara_as_rightjump`
- [x] `lara_as_rope`
- [x] `lara_as_ropel`
- [x] `lara_as_roper`
- [ ] `lara_as_run`
- [x] `lara_as_slide`
- [x] `lara_as_slideback`
- [x] `lara_as_special`
- [x] `lara_as_splat`
- [x] `lara_as_stepleft`
- [x] `lara_as_stepright`
- [ ] `lara_as_stop`
- [x] `lara_as_swandive`
- [x] `lara_as_switchoff`
- [x] `lara_as_switchon`
- [ ] `lara_as_trfall`
- [x] `lara_as_trpose`
- [x] `lara_as_trwalk`
- [x] `lara_as_turn_l`
- [x] `lara_as_turn_r`
- [x] `lara_as_upjump`
- [x] `lara_as_usekey`
- [x] `lara_as_usepuzzle`
- [x] `lara_as_wade`
- [x] `lara_as_walk`
- [x] `lara_as_waterout`
- [ ] `lara_col_all4s`
- [x] `lara_col_all4turnlr`
- [ ] `lara_col_back`
- [x] `lara_col_backjump`
- [x] `lara_col_compress`
- [ ] `lara_col_crawl`
- [ ] `lara_col_crawl2hang`
- [ ] `lara_col_crawlb`
- [ ] `lara_col_dash`
- [ ] `lara_col_dashdive`
- [x] `lara_col_death`
- [ ] `lara_col_duck`
- [x] `lara_col_ducklr`
- [x] `lara_col_fallback`
- [x] `lara_col_fastback`
- [x] `lara_col_fastdive`
- [x] `lara_col_fastfall`
- [x] `lara_col_fastturn`
- [x] `lara_col_forwardjump`
- [ ] `lara_col_hang`
- [ ] `lara_col_hang2`
- [x] `lara_col_hangleft`
- [x] `lara_col_hangright`
- [x] `lara_col_hangturnlr`
- [x] `lara_col_jumper`
- [x] `lara_col_land`
- [x] `lara_col_leftjump`
- [x] `lara_col_monkey180`
- [x] `lara_col_monkeyl`
- [x] `lara_col_monkeyr`
- [ ] `lara_col_monkeyswing`
- [ ] `lara_col_poledown`
- [ ] `lara_col_polestat`
- [x] `lara_col_poleup`
- [x] `lara_col_pose`
- [ ] `lara_col_reach`
- [x] `lara_col_rightjump`
- [x] `lara_col_roll`
- [x] `lara_col_roll2`
- [x] `lara_col_rope`
- [ ] `lara_col_ropefwd`
- [ ] `lara_col_run`
- [x] `lara_col_slide`
- [x] `lara_col_slideback`
- [x] `lara_col_splat`
- [x] `lara_col_stepleft`
- [x] `lara_col_stepright`
- [x] `lara_col_stop`
- [x] `lara_col_swandive`
- [x] `lara_col_turn_l`
- [x] `lara_col_turn_r`
- [x] `lara_col_turnswitch`
- [ ] `lara_col_upjump`
- [ ] `lara_col_wade`
- [ ] `lara_col_walk`
- [x] `lara_default_col`
- [ ] `lara_slide_slope`
- [x] `lara_void_func`
- [ ] `LaraAboveWater`
- [x] `LaraCeilingFront`
- [x] `LaraCollideStop`
- [x] `LaraDeflectEdge`
- [ ] `LaraDeflectEdgeDuck`
- [ ] `LaraDeflectEdgeJump`
- [x] `LaraFallen`
- [x] `LaraFloorFront`
- [ ] `LaraHangLeftCornerTest`
- [ ] `LaraHangRightCornerTest`
- [ ] `LaraHangTest`
- [x] `LaraHitCeiling`
- [x] `LaraLandedBad`
- [ ] `LaraSlideEdgeJump`
- [ ] `LaraTestClimbStance`
- [ ] `LaraTestEdgeCatch`
- [ ] `LaraTestHangOnClimbWall`
- [x] `LookLeftRight`
- [x] `LookUpDown`
- [x] `MonkeySwingFall`
- [x] `MonkeySwingSnap`
- [x] `ResetLook`
- [x] `SetCornerAnim`
- [ ] `SnapLaraToEdgeOfBlock`
- [ ] `TestHangSwingIn`
- [ ] `TestLaraSlide`
- [ ] `TestLaraVault`
- [x] `TestMonkeyLeft`
- [x] `TestMonkeyRight`
- [ ] `TestWall`
- [ ] `UpdateRopeSwing`
#### LARA1GUN.C
- [ ] `AnimateShotgun`
- [ ] `ControlCrossbow`
- [ ] `CrossbowHitSwitchType78`
- [ ] `DoGrenadeDamageOnBaddie`
- [ ] `draw_shotgun`
- [x] `draw_shotgun_meshes`
- [ ] `FireCrossbow`
- [ ] `FireHK`
- [ ] `FireShotgun`
- [x] `ready_shotgun`
- [ ] `RifleHandler`
- [ ] `TriggerGrapplingEffect`
- [ ] `undraw_shotgun`
- [x] `undraw_shotgun_meshes`
#### LARA2GUN.C
- [ ] `AnimatePistols`
- [x] `draw_pistol_meshes`
- [ ] `draw_pistols`
- [ ] `PistolHandler`
- [ ] `ready_pistols`
- [ ] `set_arm_info`
- [x] `undraw_pistol_mesh_left`
- [x] `undraw_pistol_mesh_right`
- [ ] `undraw_pistols`
#### LARACLMB.C
- [ ] `GetClimbTrigger`
- [x] `lara_as_climbdown`
- [x] `lara_as_climbend`
- [x] `lara_as_climbing`
- [x] `lara_as_climbleft`
- [x] `lara_as_climbright`
- [x] `lara_as_climbstnc`
- [ ] `lara_col_climbdown`
- [x] `lara_col_climbend`
- [ ] `lara_col_climbing`
- [x] `lara_col_climbleft`
- [x] `lara_col_climbright`
- [ ] `lara_col_climbstnc`
- [x] `LaraCheckForLetGo`
- [ ] `LaraClimbLeftCornerTest`
- [ ] `LaraClimbRightCornerTest`
- [ ] `LaraDoClimbLeftRight`
- [ ] `LaraTestClimb`
- [ ] `LaraTestClimbPos`
- [ ] `LaraTestClimbUpPos`
#### LARAFIRE.C
- [ ] `AimWeapon`
- [ ] `CheckForHoldingState`
- [ ] `DoProperDetection`
- [ ] `find_target_point`
- [ ] `FireWeapon`
- [ ] `get_current_ammo_pointer`
- [ ] `HitTarget`
- [ ] `InitialiseNewWeapon`
- [ ] `LaraGetNewTarget`
- [ ] `LaraGun`
- [ ] `LaraTargetInfo`
- [x] `WeaponObject`
- [x] `WeaponObjectMesh`
#### LARAFLAR.C
- [ ] `CreateFlare`
- [ ] `DoFlareInHand`
- [ ] `DoFlareLight`
- [ ] `draw_flare`
- [x] `draw_flare_meshes`
- [ ] `DrawFlareInAir`
- [ ] `FlareControl`
- [x] `ready_flare`
- [ ] `set_flare_arm`
- [ ] `undraw_flare`
- [x] `undraw_flare_meshes`
#### LARAMISC.C
- [ ] `DelAlignLaraToRope`
- [ ] `GetLaraDeadlyBounds`
- [ ] `InitialiseLaraAnims`
- [x] `InitialiseLaraLoad`
- [x] `LaraCheat`
- [ ] `LaraControl`
- [x] `LaraInitialiseMeshes`
#### LARASURF.C
- [x] `lara_as_surfback`
- [x] `lara_as_surfleft`
- [x] `lara_as_surfright`
- [x] `lara_as_surfswim`
- [ ] `lara_as_surftread`
- [x] `lara_col_surfback`
- [x] `lara_col_surfleft`
- [x] `lara_col_surfright`
- [x] `lara_col_surfswim`
- [x] `lara_col_surftread`
- [ ] `LaraSurface`
- [x] `LaraSurfaceCollision`
- [ ] `LaraTestWaterClimbOut`
- [x] `LaraTestWaterStepOut`
#### LARASWIM.C
- [ ] `GetWaterDepth`
- [x] `lara_as_dive`
- [x] `lara_as_glide`
- [x] `lara_as_swim`
- [ ] `lara_as_swimcheat`
- [x] `lara_as_tread`
- [x] `lara_as_uwdeath`
- [x] `lara_as_waterroll`
- [x] `lara_col_dive`
- [x] `lara_col_glide`
- [x] `lara_col_swim`
- [x] `lara_col_tread`
- [x] `lara_col_uwdeath`
- [x] `lara_col_waterroll`
- [ ] `LaraSwimCollision`
- [ ] `LaraTestWaterDepth`
- [ ] `LaraUnderWater`
- [ ] `LaraWaterCurrent`
- [x] `SwimTurn`
- [ ] `SwimTurnSubsuit`
- [ ] `UpdateSubsuitAngles`
#### LOT.C
- [ ] `CreateZone`
- [ ] `DisableBaddieAI`
- [ ] `EnableBaddieAI`
- [x] `InitialiseLOTarray`
- [ ] `InitialiseSlot`
#### MISSILE.C
- [x] `ControlBodyPart`
- [x] `ExplodeFX`
#### NEWINV2.C
- [x] `combine_clothbottle`
- [x] `combine_crossbow_lasersight`
- [x] `combine_HK_SILENCER`
- [x] `combine_KeyItem1`
- [x] `combine_KeyItem2`
- [x] `combine_KeyItem3`
- [x] `combine_KeyItem4`
- [x] `combine_KeyItem5`
- [x] `combine_KeyItem6`
- [x] `combine_KeyItem7`
- [x] `combine_KeyItem8`
- [x] `combine_PickupItem1`
- [x] `combine_PickupItem2`
- [x] `combine_PickupItem3`
- [x] `combine_PickupItem4`
- [x] `combine_PuzzleItem1`
- [x] `combine_PuzzleItem2`
- [x] `combine_PuzzleItem3`
- [x] `combine_PuzzleItem4`
- [x] `combine_PuzzleItem5`
- [x] `combine_PuzzleItem6`
- [x] `combine_PuzzleItem7`
- [x] `combine_PuzzleItem8`
- [x] `combine_revolver_lasersight`
- [x] `combine_these_two_objects`
- [x] `construct_combine_object_list`
- [x] `construct_object_list`
- [x] `convert_invobj_to_obj`
- [x] `convert_obj_to_invobj`
- [x] `DEL_picked_up_object`
- [x] `dels_give_lara_guns_cheat`
- [x] `dels_give_lara_items_cheat`
- [x] `do_debounced_joystick_poo`
- [ ] `do_examine_mode`
- [ ] `do_keypad_mode`
- [ ] `do_playstation_button_prompts_v1`
- [x] `do_stats_mode`
- [x] `do_these_objects_combine`
- [ ] `draw_ammo_selector`
- [ ] `draw_current_object_list`
- [ ] `DrawInventoryItemMe`
- [ ] `DrawThreeDeeObject2D`
- [x] `fade_ammo_selector`
- [x] `go_and_load_game`
- [x] `go_and_save_game`
- [ ] `handle_inventry_menu`
- [x] `handle_object_changeover`
- [x] `have_i_got_item`
- [x] `have_i_got_object`
- [x] `init_keypad_mode`
- [x] `init_new_inventry`
- [x] `insert_object_into_list`
- [x] `insert_object_into_list_v2`
- [x] `is_item_currently_combinable`
- [x] `NailInvItem`
- [x] `remove_inventory_item`
- [ ] `S_CallInventory2`
- [ ] `S_DrawPickup`
- [x] `seperate_object`
- [x] `setup_ammo_selector`
- [x] `setup_objectlist_startposition`
- [x] `setup_objectlist_startposition2`
- [x] `spinback`
- [x] `update_laras_weapons_status`
- [ ] `use_current_item`
#### OBJECTS.C
- [ ] `AnimateWaterfalls`
- [x] `BridgeFlatCeiling`
- [x] `BridgeFlatFloor`
- [x] `BridgeTilt1Ceiling`
- [x] `BridgeTilt1Floor`
- [x] `BridgeTilt2Ceiling`
- [x] `BridgeTilt2Floor`
- [ ] `ControlAnimatingSlots`
- [ ] `ControlTriggerTriggerer`
- [x] `ControlWaterfall`
- [ ] `ControlXRayMachine`
- [ ] `CutsceneRopeControl`
- [ ] `DrawBaddieGunFlash`
- [ ] `EarthQuake`
- [ ] `GetOffset`
- [ ] `HybridCollision`
- [ ] `ParallelBarsCollision`
- [ ] `PoleCollision`
- [x] `SmashObject`
- [x] `SmashObjectControl`
- [ ] `TightRopeCollision`
#### OBJLIGHT.C
- [ ] `ControlBlinker`
- [ ] `ControlColouredLight`
- [ ] `ControlElectricalLight`
- [ ] `ControlPulseLight`
- [ ] `ControlStrobeLight`
- [ ] `TriggerAlertLight`
#### PEOPLE.C
- [ ] `GunHit`
- [ ] `GunMiss`
- [x] `GunShot`
- [ ] `ShotLara`
- [ ] `Targetable`
- [ ] `TargetVisible`
#### PICKUP.C
- [ ] `AnimatingPickUp`
- [ ] `CollectCarriedItems`
- [ ] `FindPlinth`
- [ ] `KeyHoleCollision`
- [ ] `KeyTrigger`
- [x] `MonitorScreenCollision`
- [ ] `PickUpCollision`
- [ ] `PickupTrigger`
- [x] `PuzzleDone`
- [ ] `PuzzleDoneCollision`
- [ ] `PuzzleHoleCollision`
- [ ] `RegeneratePickups`
- [ ] `SearchObjectCollision`
- [ ] `SearchObjectControl`
#### SAVEGAME.C
- [x] `CheckSumValid`
- [x] `ReadSG`
- [x] `RestoreLaraData`
- [ ] `RestoreLevelData`
- [x] `SaveLaraData`
- [ ] `SaveLevelData`
- [x] `sgRestoreGame`
- [ ] `sgSaveGame`
- [x] `WriteSG`
#### SOUND.C
- [x] `SayNo`
- [x] `SOUND_Init`
- [x] `SOUND_Stop`
#### SPHERE.C
- [ ] `TestCollision`
#### SPOTCAM.C
- [ ] `CalculateSpotCams`
- [x] `InitialiseSpotCam`
- [x] `InitSpotCamSequences`
- [x] `Spline`
#### SWITCH.C
- [ ] `CogSwitchCollision`
- [ ] `CogSwitchControl`
- [ ] `CrowbarSwitchCollision`
- [ ] `CrowDoveSwitchCollision`
- [ ] `CrowDoveSwitchControl`
- [ ] `FullBlockSwitchCollision`
- [ ] `FullBlockSwitchControl`
- [ ] `GetKeyTrigger`
- [ ] `GetSwitchTrigger`
- [ ] `JumpSwitchCollision`
- [x] `ProcessExplodingSwitchType8`
- [ ] `PulleyCollision`
- [ ] `RailSwitchCollision`
- [ ] `SwitchCollision`
- [ ] `SwitchCollision2`
- [ ] `SwitchControl`
- [ ] `SwitchTrigger`
- [x] `TestTriggersAtXYZ`
- [x] `TurnSwitchCollision`
- [ ] `TurnSwitchControl`
- [ ] `UnderwaterSwitchCollision`
#### TEXT.C
- [x] `InitFont`
#### TOMB4FX.C
- [ ] `ControlElectricFence`
- [ ] `ControlTeleporter`
- [x] `CreateBubble`
- [x] `DoBloodSplat`
- [x] `DrawLensFlares`
- [ ] `DrawWeaponMissile`
- [ ] `ExplodingDeath2`
- [ ] `Fade`
- [x] `GetFreeBubble`
- [x] `GetFreeShockwave`
- [x] `SetFadeClip`
- [x] `SetScreenFadeIn`
- [x] `SetScreenFadeOut`
- [ ] `SetUpLensFlare`
- [ ] `trig_actor_gunflash`
- [x] `TriggerBlood`
- [x] `TriggerExplosionBubble`
- [x] `TriggerExplosionSmokeEnd`
- [ ] `TriggerFenceSparks`
- [x] `TriggerLaraDrips`
- [x] `TriggerLightningGlow`
- [x] `TriggerShatterSmoke`
- [x] `TriggerShockwave`
- [x] `UpdateFadeClip`
#### TRAPS.C
- [ ] `CeilingTrapDoorCollision`
- [ ] `CloseTrapDoor`
- [ ] `ControlExplosion`
- [ ] `ControlRaisingBlock`
- [ ] `ControlRollingBall`
- [ ] `ControlScaledSpike`
- [ ] `ControlTwoBlockPlatform`
- [ ] `DartEmitterControl`
- [ ] `DartsControl`
- [ ] `DrawScaledSpike`
- [x] `FallingBlock`
- [ ] `FallingBlockCeiling`
- [ ] `FallingBlockCollision`
- [ ] `FallingBlockFloor`
- [ ] `FallingCeiling`
- [ ] `FlameControl`
- [x] `FlameEmitter2Control`
- [ ] `FlameEmitter3Control`
- [ ] `FlameEmitterControl`
- [ ] `FloorTrapDoorCollision`
- [x] `LaraBurn`
- [x] `LavaBurn`
- [ ] `OnTwoBlockPlatform`
- [ ] `OpenTrapDoor`
- [ ] `RollingBallCollision`
- [ ] `TestBoundsCollideTeethSpikes`
- [ ] `TrapDoorCollision`
- [ ] `TrapDoorControl`
- [ ] `TwoBlockPlatformCeiling`
- [ ] `TwoBlockPlatformFloor`
### SPEC_PSX
#### 3D_GEN.C
- [x] `mGetAngle`
- [ ] `phd_InitWindow`
#### 3D_OBJ.C
- [ ] `CreateMonoScreen`
#### CD.C
- [x] `cbvsync`
- [x] `CD_InitialiseReaderPosition`
- [x] `CD_Read`
- [x] `CD_ReaderPositionToCurrent`
- [x] `CD_Seek`
- [x] `CDDA_SetMasterVolume`
- [x] `CDDA_SetVolume`
- [x] `DEL_ChangeCDMode`
- [x] `InitNewCDSystem`
- [x] `S_CDPause`
- [x] `S_CDPlay`
- [ ] `S_CDRestart`
- [ ] `S_CDStop`
- [ ] `S_StartSyncedAudio`
- [ ] `XAReplay`
#### DRAWPHAS.C
- [ ] `DrawPhaseGame`
- [x] `DrawRooms`
- [ ] `MGDrawSprite`
- [ ] `SortOutWreckingBallDraw`
- [x] `UpdateSky`
#### DRAWSPKS.C
- [ ] `S_DrawDarts`
#### FILE.C
- [x] `FILE_Length`
- [x] `FILE_Load`
- [x] `FILE_Read`
- [ ] `RelocateModule`
#### GPU.C
- [x] `clear_a_rect`
- [ ] `do_gfx_debug_mode`
- [x] `GPU_ClearVRAM`
- [ ] `GPU_EndScene`
- [ ] `GPU_FlipNoIdle`
- [ ] `GPU_FlipStory`
- [ ] `GPU_UseOrderingTables`
- [ ] `GPU_UsePolygonBuffers`
#### LOADSAVE.C
- [ ] `DisplayFiles`
- [ ] `LoadGame`
- [ ] `SaveGame`
#### LOAD_LEV.C
- [x] `LOAD_Start`
- [x] `LOAD_Stop`
#### MALLOC.C
- [x] `game_free`
- [x] `game_malloc`
- [x] `init_game_malloc`
- [x] `show_game_malloc_totals`
#### MEMCARD.C
- [ ] `mcClose`
- [ ] `mcDir`
- [x] `mcFormat`
- [x] `mcGetStatus`
- [x] `mcOpen`
#### PROFILE.C
- [ ] `ProfileAddDrawOT`
- [ ] `ProfileAddOT`
- [x] `ProfileCallBack`
- [x] `ProfileInit`
- [ ] `ProfileReadCount`
- [x] `ProfileRGB`
- [ ] `ProfileStartCount`
#### PSOUTPUT.C
- [x] `SetupPadVibration`
- [ ] `VibratePad`
#### PSXINPUT.C
- [ ] `S_UpdateInput`
#### PSXMAIN.C
- [x] `main`
- [x] `VSyncFunc`
#### REQUEST.C
- [ ] `Requester`
#### ROOMLOAD.C
- [ ] `ReloadAnims`
- [x] `S_LoadLevelFile`
#### SPECIFIC.C
- [ ] `DisplayConfig`
- [x] `DisplayStatsUCunt`
- [ ] `DoPauseMenu`
- [x] `gInit`
- [ ] `S_control_screen_position`
- [ ] `S_Death`
- [x] `S_DumpScreen`
- [ ] `S_ExitSystem`
#### SPUSOUND.C
- [x] `SPU_FreeChannel`
- [ ] `SPU_FreeSamples`
- [x] `SPU_Init`"""

# STEP
#  _____ 
# |___ / 
#   |_ \ 
#  ___) |
# |____/ 
# 
# Parsing the issue source (Markdown)

issue = [x for x in issue.replace("\r\n", "\n").split("\n") if x] # get a clean line array without empty ones
functions = []
for x in issue:
	if "###" in x or "[x]" not in x:
		continue

	fname = x[7:x.rfind("`")]

	if SHOW_WARN and fname in functions:
		print("[WARN--------] duplicate function '%s'" % fname)

	functions.append(fname)

# STEP
#  _  _   
# | || |  
# | || |_ 
# |__   _|
#    |_|  
#
# Let the actual shit be done

if SHOW_STATUS:
	print("[--------STAT] Brix are expected to be shat")

exe_name = "PCTomb5.exe"

if not os.path.isfile(os.path.join(os.getcwd(), exe_name)):
	exe_name = "PCTOMB5.EXE"
if not os.path.isfile(os.path.join(os.getcwd(), exe_name)):
	print("[FATAL  ERROR] %s not found -- exiting" % exe_name)
	#exit()

import idautils
funcs=lambda:[(fea,GetFunctionName(fea)) for fea in Functions(SegStart(BeginEA()),SegEnd(BeginEA()))]
from collections import *
fbytes = OrderedDict()
running = 0
for ea, fn in funcs:
	if fn[0] == "_":
		fn = fn[1:]

	if fn not in functions:
		continue

	if SHOW_WARN and fn in fbytes:
		print("[WARN--------] duplicate function '%s' -- ignoring" % fname)
		continue

	bs = [idc.Byte(i) for i in range(ea, FindFuncEnd(ea))]
	fbytes[fn] = (bs, running)
	running += len(bs)








pe = pefile.PE(exe_name)

number_of_section = pe.FILE_HEADER.NumberOfSections
last_section = number_of_section - 1
file_alignment = pe.OPTIONAL_HEADER.FileAlignment
section_alignment = pe.OPTIONAL_HEADER.SectionAlignment


# Quick function to align our values
def align(val_to_align, alignment):
    return ((val_to_align + alignment - 1) / alignment) * alignment

raw_size = align(0x1000, pe.OPTIONAL_HEADER.FileAlignment)
virtual_size = align(0x1000, pe.OPTIONAL_HEADER.SectionAlignment)
raw_offset = align((pe.sections[last_section].PointerToRawData +
                    pe.sections[last_section].SizeOfRawData),
                   pe.OPTIONAL_HEADER.FileAlignment)

virtual_offset = align((pe.sections[last_section].VirtualAddress +
                        pe.sections[last_section].Misc_VirtualSize),
                       pe.OPTIONAL_HEADER.SectionAlignment)


sys.stdout.close()
sys.stdout = orig_stdout
with open("output.txt", "r") as f:
		print(f.read())