# List of functions in CODE.WAD

> Tip: In MIPS disassembly external module execution is written like this (example):
```MIPS
lw $v0, RelocPtr+0x70
lw $a3, 0xC($v0)
jalr $a3
```
> The two useful values are `0x70` and `0xC`. Here we write these in the following format: `second (first)`
> example for example above: `0x0C (0x70)` (padding for readability)
> if file is -- it means that the function hasn't yet been moved in its corresponding file and that it is currently in codewad.c
> if address is ? it means that we know the function is there because it's on the pc version, but it's only called from inside code.wad so we don't know its relocptr address
> 'both' means that the entire function is in code.wad, but that it is called using a "gateway" function in main executable
> example: special1_init in main.exe is a function that only contains code for calling code in code.wad
> on pc and mac version, it directly contains the code

> Here is a list of CODE.WAD module names.

```Modules
enum module_indices
{
	MOD_WEATHER,
	MOD_LARA,
	MOD_ROOMLET,
	MOD_UWPARTS,
	MOD_MOVEBLOK,
	MOD_SAS,
	MOD_SUBSUIT,
	MOD_TWOGUN,
	MOD_HYDRA,
	MOD_RAT,
	MOD_ROPE,
	MOD_DEATHSLD,
	MOD_LASERS,
	MOD_TITSEQ,
	MOD_STARS,
	MOD_PIERRE,
	MOD_CROW,
	MOD_HITMAN,
	MOD_LION,
	MOD_IMP,
	MOD_GLADIATR,
	MOD_BAT,
	MOD_DOG,
	MOD_HUSKIE,
	MOD_MAFIA2,
	MOD_SNIPER,
	MOD_WILLWISP,
	MOD_TOWER2,
	MOD_SKELETON,
	MOD_ROMANGOD,
	MOD_SWAMPY,
	MOD_JOBY2,
	MOD_SPIDER,
	MOD_ANDREA2,
	MOD_GUARDIAN,
	MOD_LIGHTNG,
	MOD_CHEF,
	MOD_AUTOGUN,
	MOD_JOBY3,
	MOD_MINISUB,
	MOD_TOWER3,
	MOD_ANDREA1,
	MOD_ANDREA3,
	MOD_ANDY1,
	MOD_ANDY2,
	MOD_ANDY3,
	MOD_TOWER1,
	MOD_JOBY4,
	MOD_JOBY5,
	MOD_LIFTS,
	MOD_T12
};
```

> To obtain the correct module index we do the following as per the example above. 0x70/4=28. 0x70 is divided by 4 because RelocPtr is long* data type, once we use C we need the relative address in multiples of 4. We do the same for the second value which is 0xC/4=3. We now have the following:

```C
RelocPtr[28][3];
```
Which translates to:

```C
RelocPtr[MOD_SKELETON][3];
```

The format is as follows:

```C
RelocPtr[ModuleIndex][FunctionIndex];
```

To call this function in C code we would do the following:

```C
((VOIDFUNCVOID*)RelocPtr[ModuleIndex][FunctionIndex])();
```

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

# List of guessed global variable names

If a global variable is only ever used from functions in CODE.WAD, then it's not present in the debug symbols and thus we can't know its name so we guess it (and also the type).

| Address | Type | Name | Use |
|---------|------|------|-----|
|?|`long`|`next_spider`|In spider-related functions to keep track of next free spider|
|?|`ROPE_STRUCT[12]`|`Ropes`|Ropes|
