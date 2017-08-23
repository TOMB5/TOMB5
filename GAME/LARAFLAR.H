#ifndef LARAFLAR_H
#define LARAFLAR_H

#include "SPECTYPES.H"

extern void FlareControl(short item_number);
extern void ready_flare();
extern void undraw_flare_meshes();
extern void draw_flare_meshes();
extern void undraw_flare();
extern void draw_flare();
extern void set_flare_arm(int frame);
extern void CreateFlare(short object, int thrown);
extern void DrawFlareInAir(struct ITEM_INFO *item);
extern void DoFlareInHand(int flare_age);
extern int DoFlareLight(struct PHD_VECTOR *pos, int flare_age);

#endif