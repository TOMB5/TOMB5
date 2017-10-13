#ifndef LARATWOGUN_H
#define LARATWOGUN_H

#include "SPECTYPES.H"

extern void AnimatePistols(int weapon_type);
extern void PistolHandler(int weapon_type);
extern void undraw_pistol_mesh_right(int weapon_type);
extern void undraw_pistol_mesh_left(int weapon_type);
extern void draw_pistol_meshes(int weapon_type);
extern void ready_pistols(int weapon_type);
extern void undraw_pistols(int weapon_type);
extern void draw_pistols(int weapon_type);
extern void set_arm_info(lara_arm* arm, int frame);

#endif