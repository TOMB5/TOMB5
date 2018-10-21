#ifndef LARA_H
#define LARA_H

#include "SPECTYPES.H"

#define LARA_FREEFALL_SPEED 131

enum lara_anim_state
{
	STATE_LARA_WALK_FORWARD = 0,
	STATE_LARA_RUN_FORWARD = 1,
	STATE_LARA_STOP = 2,
	STATE_LARA_JUMP_FORWARD = 3,
	STATE_LARA_POSE = 4,
	STATE_LARA_RUN_BACK = 5,
	STATE_LARA_TURN_RIGHT_SLOW = 6,
	STATE_LARA_TURN_LEFT_SLOW = 7,
	STATE_LARA_DEATH = 8,
	STATE_LARA_FREEFALL = 9,
	STATE_LARA_HANG = 10,
	STATE_LARA_REACH = 11,
	STATE_LARA_SPLAT = 12,
	STATE_LARA_UNDERWATER_STOP = 13,
	STATE_LARA_GRAB_TO_FALL = 14,
	STATE_LARA_JUMP_PREPARE = 15,
	STATE_LARA_WALK_BACK = 16,
	STATE_LARA_UNDERWATER_FORWARD = 17,
	STATE_LARA_UNDERWATER_INERTIA = 18,
	STATE_LARA_GRABBING = 19,
	STATE_LARA_TURN_FAST = 20,
	STATE_LARA_WALK_RIGHT = 21,
	STATE_LARA_WALK_LEFT = 22,
	STATE_LARA_ROLL_BACKWARD = 23,
	STATE_LARA_SLIDE_FORWARD = 24,
	STATE_LARA_JUMP_BACK = 25,
	STATE_LARA_JUMP_LEFT = 26,
	STATE_LARA_JUMP_RIGHT = 27,
	STATE_LARA_JUMP_UP = 28,
	STATE_LARA_FALL_BACKWARD = 29,
	STATE_LARA_SHIMMY_LEFT = 30,
	STATE_LARA_SHIMMY_RIGHT = 31,
	STATE_LARA_SLIDE_BACK = 32,
	STATE_LARA_ONWATER_STOP = 33,
	STATE_LARA_ONWATER_FORWARD = 34,
	STATE_LARA_UNDERWATER_DIVING = 35,
	STATE_LARA_PUSHABLE_PUSH = 36,
	STATE_LARA_PUSHABLE_PULL = 37,
	STATE_LARA_PUSHABLE_GRAB = 38,
	STATE_LARA_PICKUP = 39,
	STATE_LARA_SWITCH_DOWN = 40,
	STATE_LARA_SWITCH_UP = 41,
	STATE_LARA_INSERT_KEY = 42,
	STATE_LARA_INSERT_PUZZLE = 43,
	STATE_LARA_WATER_DEATH = 44,
	STATE_LARA_ROLL_FORWARD = 45,
	STATE_LARA_BOULDER_DEATH = 46,
	STATE_LARA_ONWATER_BACK = 47,
	STATE_LARA_ONWATER_LEFT = 48,
	STATE_LARA_ONWATER_RIGHT = 49,
	STATE_LARA_USE_MIDAS = 50,
	STATE_LARA_DIE_MIDAS = 51,
	STATE_LARA_SWANDIVE_BEGIN = 52,
	STATE_LARA_SWANDIVE_END = 53,
	STATE_LARA_HANDSTAND = 54,
	STATE_LARA_ONWATER_EXIT = 55,
	STATE_LARA_LADDER_IDLE = 56,
	STATE_LARA_LADDER_UP = 57,
	STATE_LARA_LADDER_LEFT = 58,
	STATE_LARA_LADDER_END = 59,
	STATE_LARA_LADDER_RIGHT = 60,
	STATE_LARA_LADDER_DOWN = 61,
	STATE_LARA_NULL_62 = 62,
	STATE_LARA_NULL_63 = 63,
	STATE_LARA_NULL_64 = 64,
	STATE_LARA_WADE_FORWARD = 65,
	STATE_LARA_UNDERWATER_TURNAROUND = 66,
	STATE_LARA_FLARE_PICKUP = 67,
	STATE_LARA_JUMP_ROLL = 68,
	STATE_LARA_NULL_69 = 69,
	STATE_LARA_ZIPLINE_RIDE = 70,
	STATE_LARA_CROUCH_IDLE = 71,
	STATE_LARA_CROUCH_ROLL = 72,
	STATE_LARA_SPRINT = 73,
	STATE_LARA_SPRINT_ROLL = 74,
	STATE_LARA_MONKEYSWING_IDLE = 75,
	STATE_LARA_MONKEYSWING_FORWARD = 76,
	STATE_LARA_MONKEYSWING_LEFT = 77,
	STATE_LARA_MONKEYSWING_RIGHT = 78,
	STATE_LARA_MONKEYSWING_TURNAROUND = 79,
	STATE_LARA_CRAWL_IDLE = 80,
	STATE_LARA_CRAWL_FORWARD = 81,
	STATE_LARA_MONKEYSWING_TURN_LEFT = 82,
	STATE_LARA_MONKEYSWING_TURN_RIGHT = 83,
	STATE_LARA_CRAWL_TURN_LEFT = 84,
	STATE_LARA_CRAWL_TURN_RIGHT = 85,
	STATE_LARA_CRAWL_BACK = 86,
	STATE_LARA_CLIMB_TO_CRAWL = 87,
	STATE_LARA_CRAWL_TO_CLIMB = 88,
	STATE_LARA_MISC_CONTROL = 89,
	STATE_LARA_ROPE_TURN_LEFT = 90,
	STATE_LARA_ROPE_TURN_RIGHT = 91,
	STATE_LARA_GIANT_BUTTON_PUSH = 92,
	STATE_LARA_TRAPDOOR_FLOOR_OPEN = 93,
	STATE_LARA_FREEFALL_BIS = 94,
	STATE_LARA_ROUND_HANDLE = 95,
	STATE_LARA_COGWHEEL = 96,
	STATE_LARA_LEVERSWITCH_PUSH = 97,
	STATE_LARA_HOLE = 98,
	STATE_LARA_POLE_IDLE = 99,
	STATE_LARA_POLE_UP = 100,
	STATE_LARA_POLE_DOWN = 101,
	STATE_LARA_POLE_TURN_LEFT = 102,
	STATE_LARA_POLE_TURN_RIGHT = 103,
	STATE_LARA_PULLEY = 104,
	STATE_LARA_CROUCH_TURN_LEFT = 105,
	STATE_LARA_CROUCH_TURN_RIGHT = 106,
	STATE_LARA_CLIMB_CORNER_LEFT_OUTER = 107,
	STATE_LARA_CLIMB_CORNER_RIGHT_OUTER = 108,
	STATE_LARA_CLIMB_CORNER_LEFT_INNER = 109,
	STATE_LARA_CLIMB_CORNER_RIGHT_INNER = 110,
	STATE_LARA_ROPE_IDLE = 111,
	STATE_LARA_ROPE_CLIMB_UP = 112,
	STATE_LARA_ROPE_CLIMB_DOWN = 113,
	STATE_LARA_ROPE_SWING = 114,
	STATE_LARA_LADDER_TO_HANDS = 115,
	STATE_LARA_POSITION_CORRECTOR = 116,
	STATE_LARA_DOUBLEDOORS_PUSH = 117,
	STATE_LARA_DOZY = 118,
	STATE_LARA_TIGHTROPE_IDLE = 119,
	STATE_LARA_TIGHTROPE_TURNAROUND = 120,
	STATE_LARA_TIGHTROPE_FORWARD = 121,
	STATE_LARA_TIGHTROPE_BALANCING_LEFT = 122,
	STATE_LARA_TIGHTROPE_BALANCING_RIGHT = 123,
	STATE_LARA_TIGHTROPE_ENTER = 124,
	STATE_LARA_TIGHTROPE_EXIT = 125,
	STATE_LARA_DOVESWITCH = 126,
	STATE_LARA_TIGHTROPE_RESTORE_BALANCE = 127,
	STATE_LARA_BARS_SWING = 128,
	STATE_LARA_BARS_JUMP = 129,
	STATE_LARA_UNKNOWN_130 = 130,
	STATE_LARA_RADIO_LISTENING = 131,
	STATE_LARA_RADIO_OFF = 132,
	STATE_LARA_UNKNOWN_133 = 133,
	STATE_LARA_UNKNOWN_134 = 134,
	STATE_LARA_UNKNOWN_135 = 135,
	STATE_LARA_UNUSED16 = 136,
	STATE_LARA_PICKUP_FROM_CHEST = 137,
	STATE_LARA_UNKNOWN_138 = 138,

	NUM_LARA_STATES
};

enum lara_anim
{
	ANIMATION_LARA_RUN = 0,                                     // Run 
	ANIMATION_LARA_WALK_FORWARD = 1,                            // Walk 
	ANIMATION_LARA_END_WALK_RIGHT = 2,                          // Walk > stand (right foot moved first) 
	ANIMATION_LARA_END_WALK_LEFT = 3,                           // Walk > stand (left foot moved first) 
	ANIMATION_LARA_WALK_TO_RUN_RIGHT = 4,                       // Walk > Run (right foot moved first) 
	ANIMATION_LARA_WALK_TO_RUN_LEFT = 5,                        // Walk > Run (left foot moved first) 
	ANIMATION_LARA_STAY_TO_RUN = 6,                             // Stand > run 
	ANIMATION_LARA_RUN_TO_WALK_RIGHT = 7,                       // Run > walk (left foot first) 
	ANIMATION_LARA_RUN_TO_STAY_LEFT = 8,                        // Run > stand (left food first) 
	ANIMATION_LARA_RUN_TO_WALK_LEFT = 9,                        // Run > walk (right foot first) 
	ANIMATION_LARA_RUN_TO_STAY_RIGHT = 10,                      // Run > stand (right foot first) 
	ANIMATION_LARA_STAY_SOLID = 11,                             // Stand still (used as a link between many standing animations) 
	ANIMATION_LARA_TURN_RIGHT_SLOW = 12,                        // Turn right on the spot, small turn 
	ANIMATION_LARA_TURN_LEFT_SLOW = 13,                         // Turn left on the spot, small turn 
	ANIMATION_LARA_LANDING_FORWARD_BOTH = 14,                   // Forward jump/fall (less than 7 clicks high) > land (to a standstill), first part > ANIMATION_LARA_LANDING_FORWARD_BOTH_CONTINUE 
	ANIMATION_LARA_LANDING_FORWARD_BOTH_CONTINUE = 15,          // Land (after jump/fall less that 7 clicks high), second part > stand still (from ANIMATION_LARA_LANDING_FORWARD_BOTH) 
	ANIMATION_LARA_JUMPING_FORWARD_RIGHT = 16,                  // Run > take off for forward jump (right foot first) > ANIMATION_LARA_START_FLY_FORWARD_RIGHT 
	ANIMATION_LARA_START_FLY_FORWARD_RIGHT = 17,                // Running take off for forward jump (left foot first) > forward jump 
	ANIMATION_LARA_JUMPING_FORWARD_LEFT = 18,                   // Run > take off for forward jump (left foot first) > ANIMATION_LARA_START_FLY_FORWARD_LEFT 
	ANIMATION_LARA_START_FLY_FORWARD_LEFT = 19,                 // Running take off for forward jump (right foot first) > forward jump 
	ANIMATION_LARA_WALK_FORWARD_BEGIN = 20,                     // Stand > walk forwards, first part > ANIMATION_LARA_WALK_FORWARD_BEGIN_CONTINUE 
	ANIMATION_LARA_WALK_FORWARD_BEGIN_CONTINUE = 21,            // Walk forwards, second part > walk (from ANIMATION_LARA_WALK_FORWARD_BEGIN) 
	ANIMATION_LARA_START_FREE_FALL = 22,                        // Jump > fall 
	ANIMATION_LARA_FREE_FALL_LONG = 23,                         // Fall 
	ANIMATION_LARA_LANDING_HARD = 24,                           // Jump/fall (more than 7 clicks) > crouching landing > stand 
	ANIMATION_LARA_LANDING_DEATH = 25,                          // Fall > die (break neck) 
	ANIMATION_LARA_STAY_TO_GRAB = 26,                           // Stand > take off for upward jump to grab 
	ANIMATION_LARA_STAY_TO_GRAB_CONTINUE = 27,                  // Jump upwards to grab 
	ANIMATION_LARA_TRY_HANG_VERTICAL = 28,                      // Jump upwards 
	ANIMATION_LARA_BEGIN_HANGING_VERTICAL = 29,                 // Grab (after upward jump to grab) > hang by the hands 
	ANIMATION_LARA_STOP_HANG_VERTICAL = 30,                     // Hang by the hands > fall 
	ANIMATION_LARA_LANDING_LIGHT = 31,                          // Land after upward jump > stand 
	ANIMATION_LARA_SMASH_JUMP = 32,                             // Jump > hit something while in the air, first part > ANIMATION_LARA_SMASH_JUMP_CONTINUE 
	ANIMATION_LARA_SMASH_JUMP_CONTINUE = 33,                    // Hit something while in the air, second part > fall (from ANIMATION_LARA_SMASH_JUMP) 
	ANIMATION_LARA_FREE_FALL_FORWARD = 34,                      // Downward curve during long jump, first part (not used?) > ANIMATION_LARA_FREE_FALL_MIDDLE 
	ANIMATION_LARA_FREE_FALL_MIDDLE = 35,                       // Downward curve during long jump, second part (not used?) (from ANIMATION_LARA_FREE_FALL_FORWARD) 
	ANIMATION_LARA_FREE_FALL_LONG_NO_HURT = 36,                 // Downward curve during long jump > fall 
	ANIMATION_LARA_HANG_TO_RELEASE = 37,                        // Hang by the hands > fall (great fall) (not used?) 
	ANIMATION_LARA_STOP_WALK_BACK_RIGHT = 38,                   // Walk backwards > stand (right foot moved first) 
	ANIMATION_LARA_STOP_WALK_BACK_LEFT = 39,                    // Walk backwards > stand (left foot moved first) 
	ANIMATION_LARA_WALK_BACK = 40,                              // Walk backwards 
	ANIMATION_LARA_START_WALK_BACK = 41,                        // Stand > walk backwards 
	ANIMATION_LARA_CLIMB_3CLICK = 42,                           // Climb block (3 clicks high) 
	ANIMATION_LARA_CLIMB_3CLICK_END_RUNNING = 43,               // Stand (after jumping to a higher point) > run (not used?) 
	ANIMATION_LARA_ROTATE_RIGHT = 44,                           // Turn right on the spot, large turn 
	ANIMATION_LARA_JUMPING_FORWARD_TO_FREEFALL = 45,            // Jump forwards > fall (?) 
	ANIMATION_LARA_FLY_FORWARD_TRY_TO_HANG = 46,                // Forward jump trying to grab > land (not used?) 
	ANIMATION_LARA_ROLL_ALTERNATE = 47,                         // Roll (not used?) 
	ANIMATION_LARA_ROLL_END_ALTERNATE = 48,                     // Roll > stand (not used?) 
	ANIMATION_LARA_FREE_FALL_NO_HURT = 49,                      // Jump forwards > fall (at earlier stage of jump) (not used?) 
	ANIMATION_LARA_CLIMB_2CLICK = 50,                           // Climb block (2 clicks high) 
	ANIMATION_LARA_CLIMB_2CLICK_END = 51,                       // Climb block (2 clicks high) > stand 
	ANIMATION_LARA_CLIMB_2CLICK_END_RUNNING = 52,               // Stand (after climbing block 2 clicks high) > run 
	ANIMATION_LARA_WALL_SMASH_LEFT = 53,                        // Run > hit wall (left foot first) > stand 
	ANIMATION_LARA_WALL_SMASH_RIGHT = 54,                       // Run > hit wall (right foot first) > stand 
	ANIMATION_LARA_RUN_UP_STEP_RIGHT = 55,                      // Ascend block (1 click high) running (left foot first) 
	ANIMATION_LARA_RUN_UP_STEP_LEFT = 56,                       // Ascend block (1 click high) running (right foot first) 
	ANIMATION_LARA_WALK_UP_STEP_RIGHT = 57,                     // Ascend block (1 click high) walking (left foot first) 
	ANIMATION_LARA_WALK_UP_STEP_LEFT = 58,                      // Ascend block (1 click high) walking (right foot first) 
	ANIMATION_LARA_WALK_DOWN_LEFT = 59,                         // Descend block (1 click high) walking (right foot moved first) 
	ANIMATION_LARA_WALK_DOWN_RIGHT = 60,                        // Descend block (1 click high) walking (left foot moved first) 
	ANIMATION_LARA_WALK_DOWN_BACK_LEFT = 61,                    // Descend block (1 click high) walking backwards (left foot moved first) 
	ANIMATION_LARA_WALK_DOWN_BACK_RIGHT = 62,                   // Descend block (1 click high) walking backwards (right foot moved first) 
	ANIMATION_LARA_PULL_SWITCH_DOWN = 63,                       // Activate (lower) horizontal switch 
	ANIMATION_LARA_PULL_SWITCH_UP = 64,                         // Deactivate (raise) horizontal switch 
	ANIMATION_LARA_WALK_LEFT = 65,                              // Sidestep left 
	ANIMATION_LARA_WALK_LEFT_END = 66,                          // Sidestep left > stand 
	ANIMATION_LARA_WALK_RIGHT = 67,                             // Sidestep right 
	ANIMATION_LARA_WALK_RIGHT_END = 68,                         // Sidestep right > stand 
	ANIMATION_LARA_ROTATE_LEFT = 69,                            // Turn left on the spot, large turn 
	ANIMATION_LARA_SLIDE_FORWARD = 70,                          // Slide forwards down steep slope (3 clicks high) 
	ANIMATION_LARA_SLIDE_FORWARD_END = 71,                      // Slide forwards down steep slope (3 clicks high) > stumbling landing, first part > ANIMATION_LARA_SLIDE_FORWARD_STOP 
	ANIMATION_LARA_SLIDE_FORWARD_STOP = 72,                     // Stumbling landing (after sliding forwards down slope), second part > stand (from ANIMATION_LARA_SLIDE_FORWARD_END) 
	ANIMATION_LARA_STAY_JUMP_SIDES = 73,                        // Stand > take off for jump in all directions 
	ANIMATION_LARA_JUMP_BACK_BEGIN = 74,                        // Take off for backward jump 
	ANIMATION_LARA_JUMP_BACK = 75,                              // Jump backwards 
	ANIMATION_LARA_JUMP_FORWARD_BEGIN = 76,                     // Standing take off for forward jump 
	ANIMATION_LARA_CONTINUE_FLY_FORWARD = 77,                   // Jump forwards 
	ANIMATION_LARA_JUMP_LEFT_BEGIN = 78,                        // Take off for sideways jump left 
	ANIMATION_LARA_JUMP_LEFT = 79,                              // Jump sideways left 
	ANIMATION_LARA_JUMP_RIGHT_BEGIN = 80,                       // Take off for sideways jump right 
	ANIMATION_LARA_JUMP_RIGHT = 81,                             // Jump sideways right 
	ANIMATION_LARA_LANDING_MIDDLE = 82,                         // Crouching landing after jump in all directions > stand 
	ANIMATION_LARA_FORWARD_TO_FREE_FALL = 83,                   // Jump backwards > fall 
	ANIMATION_LARA_LEFT_TO_FREE_FALL = 84,                      // Jump sideways left > fall 
	ANIMATION_LARA_RIGHT_TO_FREE_FALL = 85,                     // Jump sideways right > fall 
	ANIMATION_LARA_UNDERWATER_SWIM_FORWARD = 86,                // Float-swim in deepsea suit (Deepsea Dive) 
	ANIMATION_LARA_UNDERWATER_SWIM_SOLID = 87,                  // Motionless underwater (driven only by momentum) in deepsea suit (used as a link between swimming animations) (Deepsea Dive) 
	ANIMATION_LARA_RUN_BACK_BEGIN = 88,                         // Stand > take off for backward hop 
	ANIMATION_LARA_RUN_BACK = 89,                               // Hop backwards 
	ANIMATION_LARA_RUN_BACK_END = 90,                           // Hop backwards > stand 
	ANIMATION_LARA_TRY_HANG_VERTICAL_BEGIN = 91,                // Take off for upward jump 
	ANIMATION_LARA_LANDING_FROM_RUN = 92,                       // Jump forwards > running landing > run 
	ANIMATION_LARA_FREE_FALL_BACK = 93,                         // Downward curve during long jump, second part (with less momentum than ANIMATION_LARA_FREE_FALL_MIDDLE?) - not used? 
	ANIMATION_LARA_FLY_FORWARD_TRY_HANG = 94,                   // Jump forwards (at late stage during jump) > grab 
	ANIMATION_LARA_TRY_HANG_SOLID = 95,                         // Grab during forward jump 
	ANIMATION_LARA_HANG_IDLE = 96,                              // Grab in mid-air > hang by the hands at wall 
	ANIMATION_LARA_CLIMB_ON = 97,                               // Hang by the hands > pull up > stand 
	ANIMATION_LARA_FREE_FALL_TO_LONG = 98,                      // Failed attempt to grab during forward jump > fall 
	ANIMATION_LARA_FALL_CROUCHING_LANDING = 99,                 // Fall > crouching landing 
	ANIMATION_LARA_FREE_FALL_TO_SIDE_LANDING = 100,             // Downward curve during long jump > grab~ 
	ANIMATION_LARA_FREE_FALL_TO_SIDE_LANDING_ALTERNATE = 101,   // Downward curve during long jump (with less momentum than ANIMATION_LARA_FREE_FALL_TO_SIDE_LANDING) > grab (not used?) 
	ANIMATION_LARA_CLIMB_ON_END = 102,                          // Pull up (after hanging by the hands) > stand 
	ANIMATION_LARA_STAY_IDLE = 103,                             // Stand still (breathing) 
	ANIMATION_LARA_START_SLIDE_BACKWARD = 104,                  // Land on steep slope (3 clicks high) > slide backwards down 
	ANIMATION_LARA_SLIDE_BACKWARD = 105,                        // Slide backwards down steep slope (3 clicks high) 
	ANIMATION_LARA_SLIDE_BACKWARD_END = 106,                    // Slide backwards down steep slope (3 clicks high) > stumbling landing > stand 
	ANIMATION_LARA_UNDERWATER_SWIM_TO_IDLE = 107,               // Stop swimming underwater in deepsea suit (at start or end of float-swimming animation) > drift underwater (Deepsea Dive) 
	ANIMATION_LARA_UNDERWATER_IDLE = 108,                       // Drift underwater in deepsea suit (Deepsea Dive) 
	ANIMATION_LARA_UNDERWARER_IDLE_TO_SWIM = 109,               // Drift underwater in deepsea suit > swim underwater (Deepsea Dive) 
	ANIMATION_LARA_ONWATER_IDLE = 110,                          // Tread water on water surface 
	ANIMATION_LARA_CLIMB_OUT_OF_WATER = 111,                    // Pull out of water (onto ledge 1 click above the water surface) > stand 
	ANIMATION_LARA_FREE_FALL_TO_UNDERWATER = 112,               // Fall/jump into water > swim underwater 
	ANIMATION_LARA_ONWATER_DIVE_ALTERNATE = 113,                // Tread water on water surface > dive > swim underwater (not used?) 
	ANIMATION_LARA_UNDERWATER_TO_ONWATER = 114,                 // Swim underwater > break water surface > tread water on water surface (?) 
	ANIMATION_LARA_ONWATER_DIVE = 115,                          // Swim forwards on water surface > dive > swim underwater 
	ANIMATION_LARA_ONWATER_SWIM_FORWARD = 116,                  // Swim forwards on water surface 
	ANIMATION_LARA_ONWATER_SWIM_FORWARD_TO_IDLE = 117,          // Swim forwards on water surface > tread water on water surface 
	ANIMATION_LARA_ONWATER_IDLE_TO_SWIM = 118,                  // Tread water on water surface > swim forwards on water surface 
	ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE = 119,     // Fall/jump into water > swim underwater (not used?) 
	ANIMATION_LARA_START_OBJECT_MOVING = 120,                   // Stand > ready to push/pull pushable 
	ANIMATION_LARA_STOP_OBJECT_MOVING = 121,                    // Ready to push/pull pushable > stand 
	ANIMATION_LARA_OBJECT_PULL = 122,                           // Pull pushable 
	ANIMATION_LARA_OBJECT_PUSH = 123,                           // Push pushable 
	ANIMATION_LARA_UNDERWATER_DEATH = 124,                      // Drown/die underwater – with convulsions (Deepsea Dive) 
	ANIMATION_LARA_AH_FORWARD = 125,                            // Jerk backwards hurt (standing) 
	ANIMATION_LARA_AH_BACKWARD = 126,                           // Jerk forwards hurt (standing) 
	ANIMATION_LARA_AH_LEFT = 127,                               // Jerk right hurt (standing) 
	ANIMATION_LARA_AH_RIGHT = 128,                              // Jerk left hurt (standing) 
	ANIMATION_LARA_UNDERWATER_SWITCH = 129,                     // Pull underwater switch at wall 
	ANIMATION_LARA_UNDERWATER_PICKUP = 130,                     // Swimming pickup in deepsea suit (right hand) (Deepsea Dive) 
	ANIMATION_LARA_USE_KEY = 131,                               // Use key 
	ANIMATION_LARA_ONWATER_DEATH = 132,                         // Die on the water surface (less dramatic than ANIMATION_LARA_UNDERWATER_DEATH) 
	ANIMATION_LARA_RUN_TO_DIE = 133,                            // Run > die 
	ANIMATION_LARA_USE_PUZZLE = 134,                            // Insert puzzle item 
	ANIMATION_LARA_PICKUP = 135,                                // Standing pickup from floor (right hand) 
	ANIMATION_LARA_CLIMB_LEFT = 136,                            // Shimmy left 
	ANIMATION_LARA_CLIMB_RIGHT = 137,                           // Shimmy right 
	ANIMATION_LARA_STAY_TO_DEATH = 138,                         // Stand > die 
	ANIMATION_LARA_SQUASH_BOULDER = 139,                        // Crushed by boulder 
	ANIMATION_LARA_ONWATER_IDLE_TO_SWIM_BACK = 140,             // Tread water on water surface > swim backwards on water surface 
	ANIMATION_LARA_ONWATER_SWIM_BACK = 141,                     // Swim backwards on water surface 
	ANIMATION_LARA_ONWATER_SWIM_BACK_TO_IDLE = 142,             // Swim backwards on water surface > tread water on water surface 
	ANIMATION_LARA_ONWATER_SWIM_LEFT = 143,                     // Swim sideways left on water surface 
	ANIMATION_LARA_ONWATER_SWIM_RIGHT = 144,                    // Swim sideways right on water surface 
	ANIMATION_LARA_JUMP_TO_DEATH = 145,                         // Land after jump/fall > die (?) 
	ANIMATION_LARA_ROLL_BEGIN = 146,                            // Stand > roll, first part > ANIMATION_LARA_ROLL_CONTINUE 
	ANIMATION_LARA_ROLL_CONTINUE = 147,                         // Roll, second part (from ANIMATION_LARA_ROLL_BEGIN) > ANIMATION_LARA_ROLL_END 
	ANIMATION_LARA_ROLL_END = 148,                              // Roll, third part > stand (from ANIMATION_LARA_ROLL_CONTINUE) 
	ANIMATION_LARA_SPIKED = 149,                                // Impaled on spikes 
	ANIMATION_LARA_OSCILLATE_HANG_ON = 150,                     // Grab in mid-air > hang by the hands in free air (swinging forth and back) 
	ANIMATION_LARA_LANDING_ROLL = 151,                          // Swan dive > rolling landing 
	ANIMATION_LARA_FISH_TO_UNDERWATER1 = 152,                   // Swan dive > shoot through water at sloped angle (at early stage in swan dive) 
	ANIMATION_LARA_FREE_FALL_FISH = 153,                        // Swan dive > dive headfirst 
	ANIMATION_LARA_FISH_TO_UNDERWATER2 = 154,                   // Swan dive > shoot through water vertically (at later stage in swan dive) 
	ANIMATION_LARA_FREE_FALL_FISH_TO_DEATH = 155,               // Swan dive > die (break neck) 
	ANIMATION_LARA_START_FLY_LIKE_FISH_LEFT = 156,              // Run > swan dive (right foot first) 
	ANIMATION_LARA_START_FLY_LIKE_FISH_RIGHT = 157,             // Run > swan dive (left foot first) 
	ANIMATION_LARA_FREE_FALL_FISH_START = 158,                  // Swan dive 
	ANIMATION_LARA_CLIMB_ON2 = 159,                             // Hang by the hands > hand stand > stand 
	ANIMATION_LARA_STAND_TO_LADDER = 160,                       // Stand in water or under low ceiling > ascend ladder (without the jump and grab) 
	ANIMATION_LARA_LADDER_UP = 161,                             // Ascend ladder 
	ANIMATION_LARA_LADDER_UP_STOP_RIGHT = 162,                  // Ascend ladder > hang still on ladder (right foot higher) 
	ANIMATION_LARA_LADDER_UP_STOP_LEFT = 163,                   // Ascend ladder > hang still on ladder (left foot higher) 
	ANIMATION_LARA_LADDER_IDLE = 164,                           // Hang still on ladder 
	ANIMATION_LARA_LADDER_UP_START = 165,                       // Hang still on ladder > ascend ladder 
	ANIMATION_LARA_LADDER_DOWN_STOP_LEFT = 166,                 // Descend ladder > hang still on ladder (left foot higher) 
	ANIMATION_LARA_LADDER_DOWN_STOP_RIGHT = 167,                // Descend ladder > hang still on ladder (right foot higher) 
	ANIMATION_LARA_LADDER_DOWN = 168,                           // Descend ladder 
	ANIMATION_LARA_LADDER_DOWN_START = 169,                     // Hang still on ladder > descend ladder 
	ANIMATION_LARA_LADDER_RIGHT = 170,                          // Climb sideways right on ladder 
	ANIMATION_LARA_LADDER_LEFT = 171,                           // Climb sideways left on ladder 
	ANIMATION_LARA_LADDER_HANG = 172,                           // Hang by the hands on ladder 
	ANIMATION_LARA_LADDER_HANG_TO_IDLE = 173,                   // Hang by the hands on ladder > gain footing on ladder 
	ANIMATION_LARA_LADDER_TO_STAND = 174,                       // Hang still on ladder > pull up > stand 
	ANIMATION_LARA_UNKNOWN_175 = 175,                           // ??? > stand still 
	ANIMATION_LARA_ONWATER_TO_WADE_SHALLOW = 176,               // Swim forwards on water surface > wade (the depth change is very small) (?) 
	ANIMATION_LARA_WADE = 177,                                  // Wade 
	ANIMATION_LARA_RUN_TO_WADE_LEFT = 178,                      // Run > wade (left foot first) 
	ANIMATION_LARA_RUN_TO_WADE_RIGHT = 179,                     // Run > wade (right foot first) 
	ANIMATION_LARA_WADE_TO_RUN_LEFT = 180,                      // Wade > run (left foot first) 
	ANIMATION_LARA_WADE_TO_RUN_RIGHT = 181,                     // Wade > run (right foot first) 
	ANIMATION_LARA_LADDER_BACKFLIP_START = 182,                 // Hang still on ladder > jump backwards off ladder, first part > ANIMATION_LARA_LADDER_BACKFLIP_END 
	ANIMATION_LARA_LADDER_BACKFLIP_END = 183,                   // Jump backwards off ladder, second part > jump backwards (from ANIMATION_LARA_LADDER_BACKFLIP_START) 
	ANIMATION_LARA_WADE_TO_STAY_RIGHT = 184,                    // Wade > stand (right foot first) 
	ANIMATION_LARA_WADE_TO_STAY_LEFT = 185,                     // Wade > stand (left foot first) 
	ANIMATION_LARA_STAY_TO_WADE = 186,                          // Stand > wade 
	ANIMATION_LARA_LADDER_UP_HANDS = 187,                       // Hang by the hands on ladder > ascend ladder with the the hands only 
	ANIMATION_LARA_LADDER_DOWN_HANDS = 188,                     // Hang by the hands on ladder > descend ladder with the hands only 
	ANIMATION_LARA_FLARE_THROW = 189,                           // Throw flare away (standing) 
	ANIMATION_LARA_ONWATER_TO_WADE_DEEP = 190,                  // Swim forwards on water surface > wade (the depth transition is greater) (?) 
	ANIMATION_LARA_ONWATER_TO_LAND_LOW = 191,                   // Pull out of water (onto ledge even with the water surface) > stand 
	ANIMATION_LARA_UNDERWATER_TO_WADE = 192,                    // Swim underwater > stand in shallow water 
	ANIMATION_LARA_ONWATER_TO_WADE = 193,                       // Tread water on water surface > stand in shallow water 
	ANIMATION_LARA_LADDER_TO_HANDS_DOWN = 194,                  // Hang still on ladder > descend ladder > hang by the hands 
	ANIMATION_LARA_SWITCH_SMALL_DOWN = 195,                     // Activate horizontal lever switch (electrical switch) 
	ANIMATION_LARA_SWITCH_SMALL_UP = 196,                       // Deactivate horizontal lever switch (electrical switch) 
	ANIMATION_LARA_BUTTON_PUSH = 197,                           // Push small button 
	ANIMATION_LARA_UNDERWATER_SWIM_TO_STILL_HUDDLE = 198,       // Stop swimming underwater in deepsea suit (in middle stage of float-swimming animation) > drift underwater (Deepsea Dive) 
	ANIMATION_LARA_UNDERWATER_SWIM_TO_STILL_SPRAWL = 199,       // Stop swimming underwater in deepsea suit (in late stage of float-swimming animation) > drift underwater (Deepsea Dive) 
	ANIMATION_LARA_UNDERWATER_SWIM_TO_STILL_MEDIUM = 200,       // Stop swimming underwater in deepsea suit (in early stage of float-swimming animation) > drift underwater (Deepsea Dive) 
	ANIMATION_LARA_LADDER_TO_HANDS_RIGHT = 201,                 // Climb sideways right on ladder > hang by the hands 
	ANIMATION_LARA_LADDER_TO_HANDS_LEFT = 202,                  // Climb sideways left on ladder > hang by the hands 
	ANIMATION_LARA_UNDERWATER_ROLL_BEGIN = 203,                 // Roll underwater, first part > ANIMATION_LARA_UNDERWATER_ROLL_END 
	ANIMATION_LARA_FLARE_PICKUP = 204,                          // Pick up flare from floor while standing (left hand) 
	ANIMATION_LARA_UNDERWATER_ROLL_END = 205,                   // Roll underwater, second part > drift underwater (from ANIMATION_LARA_UNDERWATER_ROLL_BEGIN) 
	ANIMATION_LARA_UNDERWATER_FLARE_PICKUP = 206,               // Pick up flare while swimming in deepsea suit (left hand) (Russia-levels) 
	ANIMATION_LARA_RUNNING_JUMP_ROLL_BEGIN = 207,               // Jump forwards with backtwist (after running takeoff), first part > ANIMATION_LARA_RUNNING_JUMP_ROLL_END 
	ANIMATION_LARA_SOMERSAULT = 208,                            // Somersault during swan dive 
	ANIMATION_LARA_RUNNING_JUMP_ROLL_END = 209,                 // Jump forwards with backtwist (after running takeoff), second part (from ANIMATION_LARA_RUNNING_JUMP_ROLL_BEGIN) 
	ANIMATION_LARA_STANDING_JUMP_ROLL_BEGIN = 210,              // Jump forwards with backtwist (after standing takeoff), first part > ANIMATION_LARA_STANDING_JUMP_ROLL_END 
	ANIMATION_LARA_STANDING_JUMP_ROLL_END = 211,                // Jump forwards with backtwist (after standing takeoff), second part (from ANIMATION_LARA_STANDING_JUMP_ROLL_BEGIN) 
	ANIMATION_LARA_BACKWARDS_JUMP_ROLL_BEGIN = 212,             // Jump backwards with forward twist, first part > ANIMATION_LARA_BACKWARDS_JUMP_ROLL_END 
	ANIMATION_LARA_BACKWARDS_JUMP_ROLL_END = 213,               // Jump backwards with forward twist, second part (from ANIMATION_LARA_BACKWARDS_JUMP_ROLL_BEGIN) 
	ANIMATION_LARA_TR345_ZIPLINE_GRAB = 214,                    // Stand > grab zipline 
	ANIMATION_LARA_TR345_ZIPLINE_RIDE = 215,                    // Ride zipline 
	ANIMATION_LARA_TR345_ZIPLINE_FALL = 216,                    // Fall off zipline 
	ANIMATION_LARA_TR345_STAND_TO_CROUCH = 217,                 // Stand > crouch 
	ANIMATION_LARA_CROUCH_ROLL_FORWARD_BEGIN = 218,             // Crouch with right elbow on knee > take off for crouched roll (not used) 
	ANIMATION_LARA_CROUCH_ROLL_FORWARD_CONTINUE = 219,          // Crouched roll (not used) 
	ANIMATION_LARA_CROUCH_ROLL_FORWARD_END = 220,               // Crouched roll > crouch 
	ANIMATION_LARA_CROUCH_TO_STAND = 221,                       // Crouch > stand 
	ANIMATION_LARA_CROUCH_IDLE = 222,                           // Crouch 
	ANIMATION_LARA_SPRINT = 223,                                // Sprint 
	ANIMATION_LARA_RUN_TO_SPRINT_LEFT = 224,                    // Run > sprint (left foot first) 
	ANIMATION_LARA_RUN_TO_SPRINT_RIGHT = 225,                   // Run > sprint (right foot first) 
	ANIMATION_LARA_SPRINT_SLIDE_STAND_RIGHT = 226,              // Sprint > skidding halt > stand (right foot first) 
	ANIMATION_LARA_SPRINT_SLIDE_STAND_RIGHT_BETA = 227,         // ??? > stand (right foot first) (not used) 
	ANIMATION_LARA_SPRINT_SLIDE_STAND_LEFT = 228,               // Sprint > skidding halt > stand (left foot first) 
	ANIMATION_LARA_SPRINT_SLIDE_STAND_LEFT_BETA = 229,          // ??? > stand (left foot first) (not used) 
	ANIMATION_LARA_SPRINT_TO_ROLL_LEFT = 230,                   // Sprint > take off for sprinting roll (left foot first) > ANIMATION_LARA_SPRINT_ROLL_LEFT_TO_RUN 
	ANIMATION_LARA_SPRINT_TO_ROLL_LEFT_BETA = 231,              // Stumbling takeoff for sprinting roll (not used) (?) 
	ANIMATION_LARA_SPRINT_ROLL_LEFT_TO_RUN = 232,               // Sprinting roll > run (from ANIMATION_LARA_SPRINT_TO_ROLL_LEFT) 
	ANIMATION_LARA_MONKEY_GRAB = 233,                           // Grab monkey-bars during jump 
	ANIMATION_LARA_MONKEY_IDLE = 234,                           // Hang still by the hands in free air (from monkey-bars or wafer thin ledge) 
	ANIMATION_LARA_MONKEY_FALL = 235,                           // Hang still by the hands in free air (from monkey-bars or wafer thin ledge) > fall 
	ANIMATION_LARA_MONKEY_FORWARD = 236,                        // Monkey-swing forwards 
	ANIMATION_LARA_MONKEY_STOP_LEFT = 237,                      // Monkey-swing forwards > hang still from monkey-bars (left hand first) 
	ANIMATION_LARA_MONKEY_STOP_RIGHT = 238,                     // Monkey-swing forwards > hang still from monkey-bars (right hand first) 
	ANIMATION_LARA_MONKEY_IDLE_TO_FORWARD_LEFT = 239,           // Hang still from monkey-bars > monkey-swing forwards (left hand moved first) 
	ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_BEGIN = 240,        // Sprint > take off for sprinting roll, first part (not used) (?) > ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_CONTINUE 
	ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_CONTINUE = 241,     // Take off for sprinting roll, second part (not used) (?) (from ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_BEGIN) > ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_END 
	ANIMATION_LARA_SPRINT_TO_ROLL_ALTERNATE_END = 242,          // Sprinting roll > run (not used) (?) 
	ANIMATION_LARA_SPRINT_TO_RUN_LEFT = 243,                    // Sprint > run (left foot first) 
	ANIMATION_LARA_SPRINT_TO_RUN_RIGHT = 244,                   // Sprint > run (right foot first) 
	ANIMATION_LARA_CROUCH_PREPARE = 245,                        // 'Springy' crouch (used as a link to and from crouching animations) 
	ANIMATION_LARA_SLIDE_FORWARD_TO_RUN = 246,                  // Slide forwards down steep slope (3 clicks high) > stumbling landing > run 
	ANIMATION_LARA_CROUCH_ROLL_FORWARD_BEGIN_ALTERNATE = 247,   // Crouch > take off for crouching roll (not used) 
	ANIMATION_LARA_JUMP_FORWARD_BEGIN_TO_GRAB = 248,            // Jump forwards > grab (at early stage during jump) 
	ANIMATION_LARA_JUMP_FORWARD_END_TO_GRAB = 249,              // Jump forwards > grab (at middle stage during jump) 
	ANIMATION_LARA_RUN_TO_GRAB_RIGHT = 250,                     // Grab during running takeoff (right foot first) (?) 
	ANIMATION_LARA_RUN_TO_GRAB_LEFT = 251,                      // Grab during running takeoff (left foot first) (?) 
	ANIMATION_LARA_MONKEY_IDLE_TO_FORWARD_RIGHT = 252,          // Hang still from monkey-bars > monkey-swing forwards (right hand moved first) 
	ANIMATION_LARA_MONKEY_STRAFE_LEFT = 253,                    // Shimmy left 
	ANIMATION_LARA_MONKEY_STRAFE_LEFT_END = 254,                // Shimmy (left) > hang still by the hands (?) 
	ANIMATION_LARA_MONKEY_STRAFE_RIGHT = 255,                   // Shimmy right 
	ANIMATION_LARA_MONKEY_STRAFE_RIGHT_END = 256,               // Shimmy (right) > hang still by the hands (not used) (?) 
	ANIMATION_LARA_MONKEY_TURN_AROUND = 257,                    // Turn around at the spot while hanging from monkey-bars (not used) (?) 
	ANIMATION_LARA_CROUCH_TO_CRAWL_BEGIN = 258,                 // Crouch > crawl position, first part > ANIMATION_LARA_CROUCH_TO_CRAWL_CONTINUE 
	ANIMATION_LARA_CRAWL_TO_CROUCH_BEGIN = 259,                 // Crawl position > crouch, first part > ANIMATION_LARA_CRAWL_TO_CROUCH_END 
	ANIMATION_LARA_CRAWL_FORWARD = 260,                         // Crawl forwards 
	ANIMATION_LARA_CRAWL_IDLE_TO_FORWARD = 261,                 // Crawl position > crawl forwards 
	ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_BEGIN_RIGHT = 262,     // Crawl forwards > crawl position, first part (right foot first) > ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_END_RIGHT 
	ANIMATION_LARA_CRAWL_IDLE = 263,                            // Crawl position 
	ANIMATION_LARA_CROUCH_TO_CRAWL_END = 264,                   // Crouch > crawl position, third part (from ANIMATION_LARA_CROUCH_TO_CRAWL_CONTINUE) 
	ANIMATION_LARA_CROUCH_IDLE_SMASH = 265,                     // 'Slightly springy' crouch (not used?) 
	ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_END_RIGHT = 266,       // Crawl forwards > crawl position, second part (from ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_BEGIN_RIGHT) 
	ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_BEGIN_LEFT = 267,      // Crawl forwards > crawl position, first part (left foot first) > ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_END_LEFT 
	ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_END_LEFT = 268,        // Crawl forwards > crawl positon, second part (from ANIMATION_LARA_CRAWL_FORWARD_TO_IDLE_BEGIN_LEFT) 
	ANIMATION_LARA_CRAWL_TURN_LEFT = 269,                       // Crawl position > turn left crawling 
	ANIMATION_LARA_CRAWL_TURN_RIGHT = 270,                      // Crawl position > turn right crawling 
	ANIMATION_LARA_MONKEY_TURN_LEFT = 271,                      // Hang still from monkey-bars > turn left hanging from monkey-bars 
	ANIMATION_LARA_MONKEY_TURN_RIGHT = 272,                     // Hang still from monkey-bars > turn right hanging from monkey-bars 
	ANIMATION_LARA_CROUCH_TO_CRAWL_CONTINUE = 273,              // Crouch > crawl position, second part (from ANIMATION_LARA_CROUCH_TO_CRAWL_BEGIN) > ANIMATION_LARA_CROUCH_TO_CRAWL_END 
	ANIMATION_LARA_CRAWL_TO_CROUCH_END = 274,                   // Crawl position > crouch, second part (from ANIMATION_LARA_CRAWL_TO_CROUCH_BEGIN) 
	ANIMATION_LARA_CRAWL_IDLE_TO_BACKWARD = 275,                // Crawl > crawl backwards 
	ANIMATION_LARA_CRAWL_BACKWARD = 276,                        // Crawl backwards 
	ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_BEGIN_RIGHT = 277,    // Crawl backwards > crawl position, first part (right foot moved first) > ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_END_RIGHT 
	ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_END_RIGHT = 278,      // Crawl backwards > crawl position, second part (from ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_BEGIN_RIGHT) 
	ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_BEGIN_LEFT = 279,     // Crawl backwards > crawl position, first part (left foot moved first) > ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_END_LEFT 
	ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_END_LEFT = 280,       // Crawl backwards > crawl position, second part (from ANIMATION_LARA_CRAWL_BACKWARD_TO_IDLE_BEGIN_LEFT) 
	ANIMATION_LARA_CRAWL_TURN_LEFT_END = 281,                   // Turn left crawling > crawl position 
	ANIMATION_LARA_CRAWL_TURN_RIGHT_END = 282,                  // Turn right crawling > crawl position 
	ANIMATION_LARA_MONKEY_TURN_LEFT_EARLY_END = 283,            // Turn left hanging from monkey-bars > hang still from monkey-bars (at early stage during turn) 
	ANIMATION_LARA_MONKEY_TURN_LEFT_LATE_END = 284,             // Turn left hanging from monkey-bars > hang still from monkey-bars (at late stage during turn) 
	ANIMATION_LARA_MONKEY_TURN_RIGHT_EARLY_END = 285,           // Turn right hanging from monkey-bars > hang still from monkey-bars (early stage during turn) 
	ANIMATION_LARA_MONKEY_TURN_RIGHT_LATE_END = 286,            // Turn right hanging from monkey-bars > hang still from monkey-bars (at late stage during turn) 
	ANIMATION_LARA_HANG_TO_CROUCH_BEGIN = 287,                  // Hang by the hands > pull up > crouch, first part > ANIMATION_LARA_HANG_TO_CROUCH_END 
	ANIMATION_LARA_HANG_TO_CROUCH_END = 288,                    // Crouch, second part (after pulling up from hanging by the hands) (from ANIMATION_LARA_HANG_TO_CROUCH_BEGIN) 
	ANIMATION_LARA_CRAWL_TO_HANG_BEGIN = 289,                   // Crawl position > climb down > hang by the hands, first part >ANIMATION_LARA_CRAWL_TO_HANG_CONTINUE 
	ANIMATION_LARA_CRAWL_TO_HANG_CONTINUE = 290,                // Hang by the hands, second part (after climbing down from crawl position) (from ANIMATION_LARA_CRAWL_TO_HANG_BEGIN) > ANIMATION_LARA_CRAWL_TO_HANG_END 
	ANIMATION_LARA_CROUCH_PICKUP = 291,                         // Crouching pickup (right hand) 
	ANIMATION_LARA_CRAWL_PICKUP = 292,                          // Crawling pickup (not used) 
	ANIMATION_LARA_CROUCH_SMASH_FORWARD = 293,                  // Jerk forwards hurt (chrouching) 
	ANIMATION_LARA_CROUCH_SMASH_BACKWARD = 294,                 // Jerk backwards hurt (chrouching) 
	ANIMATION_LARA_CROUCH_SMASH_RIGHT = 295,                    // Jerk right hurt (chrouching) 
	ANIMATION_LARA_CROUCH_SMASH_LEFT = 296,                     // Jerk left hurt (chrouching) 
	ANIMATION_LARA_CRAWL_SMASH_FORWARD = 297,                   // Jerk forwards hurt (crawling) 
	ANIMATION_LARA_CRAWL_SMASH_BACKWARD = 298,                  // Jerk backwards hurt (crawling) 
	ANIMATION_LARA_CRAWL_SMASH_RIGHT = 299,                     // Jerk right hurt (crawling) 
	ANIMATION_LARA_CRAWL_SMASH_LEFT = 300,                      // Jerk left hurt (crawling) 
	ANIMATION_LARA_CRAWL_DEATH = 301,                           // Crawl > die 
	ANIMATION_LARA_CRAWL_TO_HANG_END = 302,                     // Hang by the hands (after climbing down from crawl position), third part (from ANIMATION_LARA_CRAWL_TO_HANG_CONTINUE) 
	ANIMATION_LARA_CROUCH_ABORT = 303,                          // About to crouch > stand (cancelling a stand > crouch command) 
	ANIMATION_LARA_RUN_TO_CROUCH_LEFT_BEGIN = 304,              // Run > crouch, first part (left foot first) > ANIMATION_LARA_RUN_TO_CROUCH_LEFT_END 
	ANIMATION_LARA_RUN_TO_CROUCH_RIGHT_BEGIN = 305,             // Run > crouch, first part (right foot first) > ANIMATION_LARA_RUN_TO_CROUCH_RIGHT_END 
	ANIMATION_LARA_RUN_TO_CROUCH_LEFT_END = 306,                // Crouch, second part (after running) > crouch (from ANIMATION_LARA_RUN_TO_CROUCH_LEFT_BEGIN) 
	ANIMATION_LARA_RUN_TO_CROUCH_RIGHT_END = 307,               // Crouch, second part (after running) > crouch (from ANIMATION_LARA_RUN_TO_CROUCH_RIGHT_BEGIN) 
	ANIMATION_LARA_SPRINT_TO_ROLL_RIGHT = 308,                  // Sprint > take off for sprinting roll (right foot first) > ANIMATION_LARA_SPRINT_ROLL_RIGHT_TO_RUN 
	ANIMATION_LARA_SPRINT_ROLL_RIGHT_TO_RUN = 309,              // Sprinting roll > run (from ANIMATION_LARA_SPRINT_TO_ROLL_RIGHT) 
	ANIMATION_LARA_SPRINT_TO_CROUCH_LEFT = 310,                 // Sprint > small roll > crouch (left foot first) 
	ANIMATION_LARA_SPRINT_TO_CROUCH_RIGHT = 311,                // Sprint > small roll > crouch (right foot first) 
	ANIMATION_LARA_CROUCH_PICKUP_FLARE = 312,                   // Pick up flare while crouching (left hand) 
	ANIMATION_LARA_DOOR_OPEN_FORWARD = 313,                     // Use doorknob to open door and push it open 
	ANIMATION_LARA_DOOR_OPEN_BACK = 314,                        // Use doorknob to open door and pull it open 
	ANIMATION_LARA_DOOR_KICK = 315,                             // Kick door open 
	ANIMATION_LARA_GIANT_BUTTON_PUSH = 316,                     // Push Sequence button 
	ANIMATION_LARA_FLOOR_TRAPDOOR_OPEN = 317,                   // Open trapdoor in floor 
	ANIMATION_LARA_CEILING_TRAPDOOR_OPEN = 318,                 // Grab (after upward jump) and open trapdoor in ceiling* 
	ANIMATION_LARA_ROUND_HANDLE_GRAB_CLOCKWISE = 319,           // Stand > grab turn handle (clockwise) 
	ANIMATION_LARA_ROUND_HANDLE_GRAB_COUNTERCLOCKWISE = 320,    // Stand > grab turn handle (counter-clockwise) 
	ANIMATION_LARA_COGWHEEL_PULL = 321,                         // Pull cog wheel 
	ANIMATION_LARA_COGWHEEL_GRAB = 322,                         // Stand > grab cog wheel 
	ANIMATION_LARA_COGWHEEL_UNGRAB = 323,                       // Let go of cog wheel > stand 
	ANIMATION_LARA_LEVERSWITCH_PUSH = 324,                      // Use lever switch 
	ANIMATION_LARA_HOLE_GRAB = 325,                             // Use hole-in-wall switch/pickup 
	ANIMATION_LARA_STAY_TO_POLE_GRAB = 326,                     // Stand > climb onto vertical pole 
	ANIMATION_LARA_POLE_JUMP = 327,                             // Jump off vertical pole 
	ANIMATION_LARA_POLE_IDLE = 328,                             // Hang still on vertical pole 
	ANIMATION_LARA_POLE_CLIMB_UP = 329,                         // Climb vertical pole 
	ANIMATION_LARA_POLE_FALL = 330,                             // Hang still on vertical pole > fall 
	ANIMATION_LARA_JUMP_FORWARD_TO_POLE_GRAB = 331,             // Jump forwards > grab and climb onto vertical pole 
	ANIMATION_LARA_POLE_TURN_LEFT_BEGIN = 332,                  // Hang still on vertical pole > turn clockwise on vertical pole 
	ANIMATION_LARA_POLE_TURN_RIGHT_BEGIN = 333,                 // Hang still on vertical pole > turn counter-clockwise on vertical pole 
	ANIMATION_LARA_POLE_IDLE_TO_CLIMB_DOWN = 334,               // Hang still on vertical pole > slide down vertical pole 
	ANIMATION_LARA_POLE_CLIMB_DOWN = 335,                       // Slide down vertical pole 
	ANIMATION_LARA_POLE_CLIMB_DOWN_TO_IDLE = 336,               // Slide down vertical pole > hang still on vertical pole 
	ANIMATION_LARA_JUMP_UP_TO_POLE_GRAB = 337,                  // Jump upwards > grab and climb onto vertical pole 
	ANIMATION_LARA_POLE_CLIMB_UP_INBETWEEN = 338,               // Climb vertical pole > hang still on vertical pole 
	ANIMATION_LARA_PULLEY_GRAB = 339,                           // Stand > grab pulley 
	ANIMATION_LARA_PULLEY_PULL = 340,                           // Pull pulley 
	ANIMATION_LARA_PULLEY_UNGRAB = 341,                         // Let go of pulley 
	ANIMATION_LARA_POLE_GRAB_TO_STAY = 342,                     // Hang still on vertical pole > put feet on floor > stand 
	ANIMATION_LARA_POLE_TURN_LEFT = 343,                        // Turn clockwise on vertical pole (not used?) 
	ANIMATION_LARA_POLE_TURN_LEFT_END = 344,                    // Turn clockwise on vertical pole > hang still on vertical pole 
	ANIMATION_LARA_POLE_TURN_RIGHT = 345,                       // Turn counter-clockwise on vertical pole (not used?) 
	ANIMATION_LARA_POLE_TURN_RIGHT_END = 346,                   // Turn counter-clockwise on vertical pole > hang still on vertical pole 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_BEGIN = 347,         // Push turn handle (clockwise), first part > ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_CONTINUE 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_CONTINUE = 348,      // Push turn handle (clockwise), second part (from ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_BEGIN) 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_END = 349,           // Push turn handle (clockwise) > stand 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_BEGIN = 350,          // Push turn handle (counter-clockwise), first part > ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_BEGIN 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_CONTINUE = 351,       // Push turn handle (counter-clockwise), second part (from ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_END) 
	ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_END = 352,            // Push turn handle (counter-clockwise) > stand 
	ANIMATION_LARA_CROUCH_TURN_LEFT = 353,                      // Crouch > turn left crouching 
	ANIMATION_LARA_CROUCH_TURN_RIGHT = 354,                     // Crouch > turn right crouching 
	ANIMATION_LARA_HANG_AROUND_LEFT_OUTER_BEGIN = 355,          // Shimmy around left outer corner, first part > ANIMATION_LARA_HANG_AROUND_LEFT_OUTER_END 
	ANIMATION_LARA_HANG_AROUND_LEFT_OUTER_END = 356,            // Shimmy around left outer corner, second part (from ANIMATION_LARA_HANG_AROUND_LEFT_OUTER_BEGIN) 
	ANIMATION_LARA_HANG_AROUND_RIGHT_OUTER_BEGIN = 357,         // Shimmy around right outer corner, first part > ANIMATION_LARA_HANG_AROUND_RIGHT_OUTER_END 
	ANIMATION_LARA_HANG_AROUND_RIGHT_OUTER_END = 358,           // Shimmy around right outer corner, second part (from ANIMATION_LARA_HANG_AROUND_RIGHT_OUTER_BEGIN) 
	ANIMATION_LARA_HANG_AROUND_LEFT_INNER_BEGIN = 359,          // Shimmy around left inner corner, first part > ANIMATION_LARA_HANG_AROUND_LEFT_INNER_END 
	ANIMATION_LARA_HANG_AROUND_LEFT_INNER_END = 360,            // Shimmy around left inner corner, second part (from ANIMATION_LARA_HANG_AROUND_LEFT_INNER_BEGIN) 
	ANIMATION_LARA_HANG_AROUND_RIGHT_INNER_BEGIN = 361,         // Shimmy around right inner corner, first part > ANIMATION_LARA_HANG_AROUND_RIGHT_INNER_END 
	ANIMATION_LARA_HANG_AROUND_RIGHT_INNER_END = 362,           // Shimmy around right inner corner, second part (from ANIMATION_LARA_HANG_AROUND_RIGHT_INNER_BEGIN) 
	ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_BEGIN = 363,        // Climb sideways on ladder around left outer corner, first part > ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_END 
	ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_END = 364,          // Climb sideways on ladder around left outer corner, second part (from ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_BEGIN) 
	ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_BEGIN = 365,       // Climb sideways on ladder around right outer corner, first part > ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_END 
	ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_END = 366,         // Climb sideways on ladder around right outer corner, second part (from ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_BEGIN) 
	ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_BEGIN = 367,        // Climb sideways on ladder around left inner corner, first part > ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_END 
	ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_END = 368,          // Climb sideways on ladder around left inner corner, second part (from ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_BEGIN) 
	ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_BEGIN = 369,       // Climb sideways on ladder around right inner corner, first part > ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_END 
	ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_END = 370,         // Climb sideways on ladder around right inner corner, second part (from ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_BEGIN) 
	ANIMATION_LARA_MONKEY_TO_ROPE_BEGIN = 371,                  // Hang from monkey-bars/jump upwards > grab rope (?) 
	ANIMATION_LARA_TRAIN_DEATH = 372,                           // Fall off train > die 
	ANIMATION_LARA_MONKEY_TO_ROPE_END = 373,                    // Loose momentum on rope > wrap legs around rope > hang still on rope 
	ANIMATION_LARA_ROPE_IDLE = 374,                             // Hang still on rope 
	ANIMATION_LARA_ROPE_DOWN_BEGIN = 375,                       // Hang still on rope > slide down rope 
	ANIMATION_LARA_ROPE_UP = 376,                               // Climb rope 
	ANIMATION_LARA_ROPE_IDLE_TO_SWING_SOFT = 377,               // Hang still on rope > begin to swing with still some momentum left (no kick necessary)(?) 
	ANIMATION_LARA_ROPE_GRAB_TO_FALL = 378,                     // Have just grabbed rope > fall (?) 
	ANIMATION_LARA_ROPE_JUMP_TO_GRAB = 379,                     // Jump forwards > grab rope 
	ANIMATION_LARA_ROPE_IDLE_TO_BACKFLIP = 380,                 // Somersault from rope to ledge? (not used) 
	ANIMATION_LARA_ROPE_SWING_TO_FALL_SEMIFRONT = 381,          // Swing on rope > fall (when Lara is in the fore end of the swing - haft past four o'clock)(?) 
	ANIMATION_LARA_ROPE_SWING_TO_FALL_MIDDLE = 382,             // Swing on rope> fall (when Lara is in the middle of the swing) (?) 
	ANIMATION_LARA_ROPE_SWING_TO_FALL_BACK = 383,               // Swing on rope > fall (when Lara is in the back end of the swing) (?) 
	ANIMATION_LARA_ROPE_DOWN = 384,                             // Slide down rope 
	ANIMATION_LARA_ROPE_DOWN_TO_IDLE = 385,                     // Slide down rope > hang still on rope 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_BACK = 386,           // Swing on rope > jump off to grab ledge (when Lara is in the back end of the swing) 
	ANIMATION_LARA_ROPE_IDLE_TO_SWING = 387,                    // Hang still on rope > give a kick to gain momentum to swing (begin to swing) 
	ANIMATION_LARA_ROPE_IDLE_TO_SWING_SEMIMIDDLE = 388,         // Swing on rope> fall (when Lara is just before the middle of the swing - 7 o'clock) (?) 
	ANIMATION_LARA_ROPE_IDLE_TO_SWING_HALFMIDDLE = 389,         // Swing on rope> fall (when Lara is just before the middle of the swing - half past six o'clock) (?) 
	ANIMATION_LARA_ROPE_SWING_TO_FALL_FRONT = 390,              // Swing on rope > fall (when Lara is in the fore end of the swing - 5 o'clock) (?) 
	ANIMATION_LARA_ROPE_GRAB_TO_FALL_ALTERNATE = 391,           // Have just grabbed rope > fall (same animation as ANIMATION_LARA_ROPE_GRAB_TO_FALL?) (?) 
	ANIMATION_LARA_ROPE_TURN_CLOCKWISE = 392,                   // Turn clockwise on rope 
	ANIMATION_LARA_ROPE_TURN_COUNTER_CLOCKWISE = 393,           // Turn counter-clockwise on rope 
	ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD = 394,           // Swing forwards on rope with much momentum 
	ANIMATION_LARA_ROPE_LADDER_TO_HANDS_DOWN_ALTERNATE = 395,   // Hang still on ladder > abandon footing > hang by the hands alone (not used) (?) 
	ANIMATION_LARA_ROPE_SWING_BACK_CONTINUE = 396,              // Swing backwards on rope, second part (from ANIMATION_LARA_ROPE_SWING_BACK_BEGIN) > ANIMATION_LARA_ROPE_SWING_BACK_END 
	ANIMATION_LARA_ROPE_SWING_BACK_END = 397,                   // Swing backwards on rope, third part (from ANIMATION_LARA_ROPE_SWING_BACK_CONTINUE) 
	ANIMATION_LARA_ROPE_SWING_BACK_BEGIN = 398,                 // Swing backwards on rope, first part > ANIMATION_LARA_ROPE_SWING_BACK_CONTINUE 
	ANIMATION_LARA_ROPE_SWING_FORWARD_SOFT = 399,               // Swing forwards on rope with little momentum (?) 
	ANIMATION_LARA_WATERSKIN_EMPTY = 400,                       // Empty waterskin 
	ANIMATION_LARA_WATERSKIN_FILL = 401,                        // Fill waterskin 
	ANIMATION_LARA_WATERSKIN_POUR_ON_SCALE = 402,               // Pour waterskin on scale 
	ANIMATION_LARA_DOOR_OPEN_CROWBAR = 403,                     // Open door with crowbar 
	ANIMATION_LARA_ROPE_SWING_FORWARD_HARD = 404,               // Reach fore end of swing on rope with very much momentum 
	ANIMATION_LARA_ROPE_CHANGE_ROPE = 405,                      // Swing on rope and grab a new rope? (not used?) 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_FRONT2 = 406,         // Swing on rope > jump off to grab ledge (when Lara is in the fore end of the swing - 4 o'clock) 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_MIDDLE = 407,         // Swing on rope > jump off to grab ledge (when Lara is right in the middle of the swing) 
	ANIMATION_LARA_ROPE_SWING_BLOCK = 408,                      // Swing forth and back with almost no momentum (Lara is too high on the rope?) 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_SEMIMIDDLE = 409,     // Swing on rope > jump off to grab ledge (when Lara is just before the middle of the swing) 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_FRONT3 = 410,         // Swing on rope > jump off to grab ledge (when Lara is in the fore end of the swing - 5 o'clock) 
	ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_FRONT1 = 411,         // Swing on rope > jump off to grab ledge (when Lara is in the fore end of the swing - 3 o'clock) 
	ANIMATION_LARA_DOUBLEDOORS_PUSH = 412,                      // Push double doors 
	ANIMATION_LARA_BIG_BUTTON_PUSH = 413,                       // Push big button 
	ANIMATION_LARA_JUMPSWITCH = 414,                            // Pull jumpswitch 
	ANIMATION_LARA_UNDERWATER_PULLEY = 415,                     // Pull underwater switch in the ceiling 
	ANIMATION_LARA_UNDERWATER_DOOR_OPEN = 416,                  // Open underwater_door 
	ANIMATION_LARA_PUSHABLE_PUSH_TO_STAND = 417,                // Push pushable > stand 
	ANIMATION_LARA_PUSHABLE_PULL_TO_STAND = 418,                // Pull pushable > stand 
	ANIMATION_LARA_CROWBAR_USE_ON_WALL = 419,                   // Use crowbar to get puzzle item from wall 
	ANIMATION_LARA_CROWBAR_USE_ON_FLOOR = 420,                  // Use crowbar to activate broken leverswitch (Desert Railroad) 
	ANIMATION_LARA_CRAWL_JUMP_DOWN = 421,                       // Roll forwards out of crawlspace (not used) 
	ANIMATION_LARA_HARP_PLAY = 422,                             // Play harp (The Lost Library) 
	ANIMATION_LARA_PUT_TRIDENT = 423,                           // Place trident on Poseidon statue (Temple of Poseidon) 
	ANIMATION_LARA_PICKUP_PEDESTAL_HIGH = 424,                  // Standing pickup from high pedestal (Lara's height) 
	ANIMATION_LARA_PICKUP_PEDESTAL_LOW = 425,                   // Standing pickup from low pedestal (waist-height) 
	ANIMATION_LARA_ROTATE_SENET = 426,                          // Play game of senet (Tomb of Semerkhet) 
	ANIMATION_LARA_TORCH_LIGHT_1 = 427,                         // Light torch with flame 0-1 clicks high 
	ANIMATION_LARA_TORCH_LIGHT_2 = 428,                         // Light torch with flame 2-3 clicks high 
	ANIMATION_LARA_TORCH_LIGHT_3 = 429,                         // Light torch with flame 4-5 clicks high 
	ANIMATION_LARA_TORCH_LIGHT_4 = 430,                         // Light torch with flame 6-7 clicks high 
	ANIMATION_LARA_TORCH_LIGHT_5 = 431,                         // Light torch with flame higher than 7 clicks 
	ANIMATION_LARA_DETONATOR_USE = 432,                         // use mine detector 
	ANIMATION_LARA_CORRECT_POSITION_FRONT = 433,                // Small steps forward to correct Lara's position (hardcoded, used to put line up Lara in front of switches and puzzles) 
	ANIMATION_LARA_CORRECT_POSITION_LEFT = 434,                 // Small steps to the left to corrcts Lara's position 
	ANIMATION_LARA_CORRECT_POSITION_RIGHT = 435,                // Small steps to the right to correct Lara's position 
	ANIMATION_LARA_CROWBAR_USE_ON_FLOOR_FAIL = 436,             // Use crowbar to break train link? (not used) 
	ANIMATION_LARA_USE_KEYCARD = 437,                           // Use swipe card 
	ANIMATION_LARA_DEATH_BLOWUP = 438,                          // Blown up by mine 
	ANIMATION_LARA_PICKUP_SARCOPHAGUS = 439,                    // Pickup from sarcophagus 
	ANIMATION_LARA_DRAG = 440,                                  // Dragging dead body (City of the Dead) 
	ANIMATION_LARA_BINOCULARS = 441,                            // Look through binoculars (not used) 
	ANIMATION_LARA_DEATH_BIG_SCORPION = 442,                    // Picked up and tossed away by big scorpion 
	ANIMATION_LARA_ELEVATOR_RECOVER = 443,                      // Lara painfully gets to her feet after fall in elevator (VCI-levels) 
	ANIMATION_LARA_BEETLE_PUT = 444,                            // Wind up beetle > put beetle on floor 
	ANIMATION_LARA_DOZY = 445,                                  // DOZY Animation 
	ANIMATION_LARA_TIGHTROPE_WALK = 446,                        // Walk on tightrope 
	ANIMATION_LARA_TIGHTROPE_WALK_TO_STAND = 447,               // Walk on tightrope > stand on tightrope 
	ANIMATION_LARA_TIGHTROPE_STAND = 448,                       // Stand on tightrope 
	ANIMATION_LARA_TIGHTROPE_WALK_TO_STAND_CAREFUL = 449,       // Walk on tightrope > tread carefully > stand on tightrope 
	ANIMATION_LARA_TIGHTROPE_STAND_TO_WALK = 450,               // Stand on tightrope > walk on tightrope 
	ANIMATION_LARA_TIGHTROPE_TURN = 451,                        // Turn around on tightrope 
	ANIMATION_LARA_TIGHTROPE_LOOSE_LEFT = 452,                  // Stand on tightrope > loose balance and lean left 
	ANIMATION_LARA_TIGHTROPE_RECOVER_LEFT = 453,                // Lean left on tightrope > regain balance and stand on tightrope 
	ANIMATION_LARA_TIGHTROPE_FALL_LEFT = 454,                   // Fall off tightrope (to the left) 
	ANIMATION_LARA_TIGHTROPE_LOOSE_RIGHT = 455,                 // Stand on tightrope > loose balance and lean right 
	ANIMATION_LARA_TIGHTROPE_RECOVER_RIGHT = 456,               // Lean right on tightrope > regain balance and stand on tightrope 
	ANIMATION_LARA_TIGHTROPE_FALL_RIGHT = 457,                  // Fall off tightrope (to the right) 
	ANIMATION_LARA_TIGHTROPE_START = 458,                       // Stand > walk out on tightrope 
	ANIMATION_LARA_TIGHTROPE_FINISH = 459,                      // Walk off tightrope > stand 
	ANIMATION_LARA_DOVESWITCH_TURN = 460,                       // Examine and turn doveswitch (Rome-levels) 
	ANIMATION_LARA_BARS_GRAB = 461,                             // Jump forwards > grab horizontal pole 
	ANIMATION_LARA_BARS_SWING = 462,                            // Swing around horizontal pole 
	ANIMATION_LARA_BARS_JUMP = 463,                             // Jump off horizontal pole 
	ANIMATION_LARA_LOOT_CABINET = 464,                          // Open cabinet and search it 
	ANIMATION_LARA_LOOT_DRAWER = 465,                           // Open drawer and search it 
	ANIMATION_LARA_LOOT_SHELF = 466,                            // Search shelves 
	ANIMATION_LARA_RADIO_BEGIN = 467,                           // Stand > put hand to headgear to listen (VCI-levels) 
	ANIMATION_LARA_RADIO_IDLE = 468,                            // Hold hand on headgear and listen (VCI-levels) 
	ANIMATION_LARA_RADIO_END = 469,                             // Remove hand from headgear > stand (VCI-levels) 
	ANIMATION_LARA_VALVE_TURN = 470,                            // Turn valve wheel 
	ANIMATION_LARA_CROWBAR_USE_ON_WALL2 = 471,                  // Pull object off wall (to use as crowbar) 
	ANIMATION_LARA_LOOT_CHEST = 472,                            // Kneel to open box and pick up item (VCI-levels) 
	ANIMATION_LARA_LADDER_TO_CROUCH = 473,                      // Climb wall > pull up in crawlspace 

	NUM_LARA_ANIMS
};

enum lara_mesh
{
	LM_HIPS = 0,
	LM_LTHIGH = 1,
	LM_LSHIN = 2,
	LM_LFOOT = 3,
	LM_RTHIGH = 4,
	LM_RSHIN = 5,
	LM_RFOOT = 6,
	LM_TORSO = 7,
	LM_RINARM = 8,
	LM_ROUTARM = 9,
	LM_RHAND = 10,
	LM_LINARM = 11,
	LM_LOUTARM = 12,
	LM_LHAND = 13,
	LM_HEAD = 14,

	NUM_LARA_MESHES
};

enum lara_joint
{
	LJ_HIPS = 0,
	LJ_LTHIGH = 1,
	LJ_LSHIN = 2,
	LJ_LFOOT = 3,
	LJ_RTHIGH = 4,
	LJ_RSHIN = 5,
	LJ_RFOOT = 6,
	LJ_TORSO = 7,
	LJ_RINARM = 9,
	LJ_ROUTARM = 10,
	LJ_RHAND = 11,
	LJ_LINARM = 12,
	LJ_LOUTARM = 13,
	LJ_LHAND = 14,
	LJ_HEAD = 8,
};

enum lara_draw_type
{
	LARA_NORMAL = 1,
	LARA_YOUNG = 2,
	LARA_BUNHEAD = 3,
	LARA_CATSUIT = 4,
	LARA_DIVESUIT = 5,
	LARA_INVISIBLE = 7
};

enum lara_water_status
{
	LW_ABOVE_WATER = 0,
	LW_UNDERWATER = 1,
	LW_SURFACE = 2,
	LW_FLYCHEAT = 3
};

enum lara_gun_status
{
	LG_NO_ARMS = 0,
	LG_HANDS_BUSY = 1,
	LG_DRAW_GUNS = 2,
	LG_UNDRAW_GUNS = 3,
	LG_READY = 4,
	LG_FLARE = 5,
};

extern short angle; // offset 0xA0650
extern short elevation; // offset 0xA0652
extern struct ITEM_INFO* lara_item; // offset 0xA2048
extern unsigned short DashTimer; // offset 0xA2044
extern struct lara_info lara; // offset 0xA57DC

extern void(*lara_control_routines[])(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void(*lara_collision_routines[])(struct ITEM_INFO* item, struct COLL_INFO* coll);

extern void lara_as_pbleapoff(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_parallelbars(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_trfall(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_trwalk(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_trpose(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void GetTighRopeFallOff(long Regularity);
extern void LookLeftRight();
extern void LookUpDown();
extern void ResetLook();
extern void lara_col_jumper(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_default_col(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_wade(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_fastdive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_swandive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_roll2(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_roll(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_slideback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_fallback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_leftjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_rightjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_backjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_slide(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_stepleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_back(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_compress(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_land(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_splat(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_fastfall(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_death(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_turn_l(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_turn_r(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_fastback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_pose(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_run(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_walk(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_pulley(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_turnswitch(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_controlledl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_controlled(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_deathslide(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_wade(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_waterout(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_gymnast(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_fastdive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_swandive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_special(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_usepuzzle(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_usekey(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_switchoff(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_switchon(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_pickupflare(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_pickup(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_ppready(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_pullblock(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_pushblock(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_slideback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_fallback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_leftjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_rightjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_backjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_slide(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_stepleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_fastturn(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_fastturn(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_null(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_back(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_compress(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_splat(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_intcornerr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_intcornerl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_extcornerr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_extcornerl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void SetCornerAnim(struct ITEM_INFO* item, struct COLL_INFO* coll, short rot, short flip);
extern void lara_col_hangright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hangright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_hangleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hangleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_hang(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hang(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int CanLaraHangSideways(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle);
extern void lara_void_func(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_fastfall(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_death(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_turn_l(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_turn_r(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_fastback(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_run(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_walk(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_reach(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_reach(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_upjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_upjump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_stop(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_stop(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbroped(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbrope(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_ropefwd(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_roper(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_ropel(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_rope(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_rope(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void ApplyVelocityToRope(int node, unsigned short angle, unsigned short n);
extern void UpdateRopeSwing(struct ITEM_INFO* item);
extern void JumpOffRope(struct ITEM_INFO* item);
extern void FallFromRope(struct ITEM_INFO* item);
extern void lara_col_poledown(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_poleup(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_poleright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_poleleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_polestat(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hangturnr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_hangturnlr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hangturnl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_monkeyr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_monkeyr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_monkeyl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_monkeyl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern short TestMonkeyRight(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern short TestMonkeyLeft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern short GetDirOctant(long rot);
extern void MonkeySwingSnap(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void MonkeySwingFall(struct ITEM_INFO* item);
extern void lara_col_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_dash(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_dash(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_crawl2hang(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_all4turnr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_all4turnlr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_all4turnl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_duck(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_duck(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_ducklr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_duckr(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_duckl(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void LaraAboveWater(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int TestHangSwingIn(struct ITEM_INFO* item, short angle);
extern int LaraHangLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraHangRightCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int IsValidHangPos(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraHangTest(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void SnapLaraToEdgeOfBlock(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle);
extern int LaraTestHangOnClimbWall(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void LaraSlideEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void LaraDeflectEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_slide_slope(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void LaraCollideStop(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int TestWall(struct ITEM_INFO* item, long front, long right, long down);
extern int TestLaraVault(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraTestClimbStance(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraTestEdgeCatch(struct ITEM_INFO* item, struct COLL_INFO* coll, long* edge);
extern int LaraDeflectEdgeDuck(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraDeflectEdge(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraHitCeiling(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraLandedBad(struct ITEM_INFO* l, struct COLL_INFO* coll);
extern int LaraFallen(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int TestLaraSlide(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern short LaraCeilingFront(struct ITEM_INFO* item, short ang, long dist, long h);
extern short LaraFloorFront(struct ITEM_INFO* item, short ang, long dist);
extern void GetLaraCollisionInfo(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int GetLaraJointPos(struct PHD_VECTOR* arg1, long arg2);
extern void AnimateLara(struct ITEM_INFO* item);
extern void SetLaraUnderwaterNodes();
extern void SetPendulumVelocity(int x, int y, int z);
extern void LaraClimbRope(struct ITEM_INFO* item, struct COLL_INFO* coll); // 0xC (RelocPtr + 0x28)
extern void FireChaff();
extern void GetLaraJointPosRot(struct PHD_VECTOR *a1, int a2, int a3, struct SVECTOR *a4);
extern void DoSubsuitStuff();

#endif