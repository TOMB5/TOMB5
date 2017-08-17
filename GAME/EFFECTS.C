#include "EFFECTS.H"

long wf;
short next_fx_free;
short next_fx_active;
int number_sound_effects;
struct OBJECT_VECTOR* sound_effects;
struct FX_INFO* effects;