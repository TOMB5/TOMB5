# list of functions in codewad

> tip: in mips disasm they are written like this (example):
```mips
lw $v0, RelocPtr+0x70
lw $a3, 0xC($v0)
jalr $a3
```
> the two useful values are `0x70` and `0xC`. Here we write these in the following format: `second (first)`
> example for example above: `0x0C (0x70)` (padding for readability)
> if file is -- it means that the function hasn't yet been moved in its corresponding file and that it is currently in codewad.c
> if address is ? it means that we know the function is there because it's on the pc version, but it's only called from inside code.wad so we don't know its relocptr address
> 'both' means that the entire function is in code.wad, but that it is called using a "gateway" function in main executable
> example: special1_init in main.exe is a function that only contains code for calling code in code.wad
> on pc and mac version, it directly contains the code

| Address | Both | Definition | File |
|---------|------|------------|------|
|`0x0C (0x70)`|-|`void TriggerFontFire(struct ITEM_INFO* item, int a2, int a3)`|EFFECT2|
|`0x0C (0x28)`|-|`void LaraClimbRope(struct ITEM_INFO* item, struct COLL_INFO* coll)`|--|
|`0x10 (0x18)`|-|`void TriggerEngineEffects_CUT()`|--|
|?|-|`void triggerwindowsmash(int item_num)`|--|
|`0x10 (0x28)`|-|`void SetPendulumVelocity(int x, int y, int z)`|LARA|
|`0x0C (0x28)`|-|`void LaraClimbRope(struct ITEM_INFO* item, struct COLL_INFO* coll)`|LARA|
|`0x00 (0xC8)`|-|`void CheckForRichesIllegalDiagonalWalls()`|CAMERA|
|`0x08 (0x34)`|yes|`void special1_init()`|DELTAPAK|
|`0x0C (0x34)`|yes|`void special1_control()`|DELTAPAK|
|`0x10 (0x34)`|yes|`void special1_end()`|DELTAPAK|
|`0x14 (0x34)`|yes|`void special2_init()`|DELTAPAK|
|`0x18 (0x34)`|yes|`void special2_control()`|DELTAPAK|
|`0x1C (0x34)`|yes|`void special2_end()`|DELTAPAK|
|`0x20 (0x34)`|yes|`void special3_init()`|DELTAPAK|
|`0x24 (0x34)`|yes|`void special3_control()`|DELTAPAK|
|`0x28 (0x34)`|yes|`void special3_end()`|DELTAPAK|
|`0x2C (0x34)`|yes|`void special4_init()`|DELTAPAK|
|`0x30 (0x34)`|yes|`void special4_control()`|DELTAPAK|
|`0x34 (0x34)`|yes|`void special4_end()`|DELTAPAK|
|`0x08 (0x20)`|-|`void TriggerHydraMissileFlape(struct PHD_VECTOR* pos, long x, long y, long z)`|EFFECT2|
|`0x08 (0x74)`|-|`void TriggerRomanGodMissileFlame(struct PHD_VECTOR* pos, long fx_number)`|EFFECT2|
|`0x00 (0x8C)`|-|`void TriggerLightning(struct PHD_VECTOR* a1, struct PHD_VECTOR* a2, char a3, int a4, char a5, char a6, char a7)`|TOMB4FX|
|`0x10 (0x80)`|-|`void ClearSpiders()`|EFFECTS|
|?|-|`void TriggerTorpedoSteam(struct PHD_VECTOR *pos, struct PHD_VECTOR *a2, int a3)`|EFFECT2|
|`0x14 (0x18)`|-|`void FireChaff()`|LARA|
|?|-|`void TriggerEngineEffects()`|
|?|-|`void GetLaraJointPosRot(struct PHD_VECTOR *a1, int a2, int a3, struct SVECTOR *a4)`|LARA|
|?|-|`void TriggerSubMist(struct PHD_VECTOR *pos, struct PHD_VECTOR *a4, int a5)`|EFFECT2|
|?|-|`void TriggerEngineEffects()`|EFFECT2|
|?|-|`void DoSubsuitStuff()`|LARA|
|?|-|`void TriggerAirBubbles()`|EFFECT2|
|`0x00 (0xB4)`|-|`void TriggerCoinGlow()`|TOMB4FX|
|`0x24 (0x28)`|-|`void SaveRope()`|ROPE|
|?|-|`void Straighten(struct ROPE_STRUCT* a1, struct PHD_VECTOR* a2, struct PHD_VECTOR* a3, long a4)`|ROEP|
|`0x2C (0x28)`|-|`void StraightenRope(struct ITEM_INFO* item)`|ROPE|
|`0x28 (0x28)`|-|`void LoadRope()`|ROPE|
|`0x00 (0x8C)`|-|? (called in FlameEmitter3Control)|?|
|`0x04 (0x7C)`|-|? (called in SortOutWreckingBallDraw)|?|
|?|-|`void UpdateSpiders()`|CONTROL|
|?|-|`int GetFreeSpider()`|TOMB4FX|

# list of guessed global vars names

basically, if a global variable is only ever used from functions in codewad, then it's not present in the debug symbols and thus we can't know its name so we guess it (and also type)

| Address | Type | Name | Use |
|---------|------|------|-----|
|?|`long`|`next_spider`|In spider-related functions to keep track of next free spider|
|?|`ROPE_STRUCT[12]`|`Ropes`|Ropes|