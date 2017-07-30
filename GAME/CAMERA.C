#include "CAMERA.H"

#include "CD.H"
#include "DELTAPAK.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"

#include "3D_GEN.H"

#include <assert.h>
#include <math.h>
#include <stddef.h>

long BinocularRange;
long BinocularOn;
long BinocularOldCamera;
long LaserSight;
long InfraRed;
char SniperCount;
char SniperCamActive;
long ExittingBinos;
long TooFarCount;
long CombatShift;
unsigned char camerasnaps;
unsigned char TargetSnaps;
char TLFlag;
char LSHKShotsFired;
char LSHKTimer;
struct CAMERA_INFO camera;
char UseForcedFixedCamera;
struct GAME_VECTOR ForcedFixedCamera;
long NumFixedCameras;
int number_cameras;
struct PHD_VECTOR CamOldPos;
struct SHATTER_ITEM ShatterItem;
struct GAME_VECTOR static_lookcamp;
struct GAME_VECTOR static_lookcamt;
struct OLD_CAMERA old_cam;
struct GAME_VECTOR last_ideal;
struct GAME_VECTOR last_target;

short rcossin_tbl[] =
{
	0, 4096, 6, 4096, 13, 4096, 19, 4096, 25, 4096, 31, 4096, 38, 4096, 44, 4096,
	50, 4096, 57, 4096, 63, 4096, 69, 4095, 75, 4095, 82, 4095, 88, 4095, 94, 4095,
	101, 4095, 107, 4095, 113, 4094, 119, 4094, 126, 4094, 132, 4094, 138, 4094, 144, 4093,
	151, 4093, 157, 4093, 163, 4093, 170, 4092, 176, 4092, 182, 4092, 188, 4092, 195, 4091,
	201, 4091, 207, 4091, 214, 4090, 220, 4090, 226, 4090, 232, 4089, 239, 4089, 245, 4089,
	251, 4088, 257, 4088, 264, 4088, 270, 4087, 276, 4087, 283, 4086, 289, 4086, 295, 4085,
	301, 4085, 308, 4084, 314, 4084, 320, 4083, 326, 4083, 333, 4082, 339, 4082, 345, 4081,
	351, 4081, 358, 4080, 364, 4080, 370, 4079, 376, 4079, 383, 4078, 389, 4077, 395, 4077,
	401, 4076, 408, 4076, 414, 4075, 420, 4074, 426, 4074, 433, 4073, 439, 4072, 445, 4072,
	451, 4071, 458, 4070, 464, 4070, 470, 4069, 476, 4068, 483, 4067, 489, 4067, 495, 4066,
	501, 4065, 508, 4064, 514, 4064, 520, 4063, 526, 4062, 533, 4061, 539, 4060, 545, 4060,
	551, 4059, 557, 4058, 564, 4057, 570, 4056, 576, 4055, 582, 4054, 589, 4053, 595, 4053,
	601, 4052, 607, 4051, 613, 4050, 620, 4049, 626, 4048, 632, 4047, 638, 4046, 644, 4045,
	651, 4044, 657, 4043, 663, 4042, 669, 4041, 675, 4040, 682, 4039, 688, 4038, 694, 4037,
	700, 4036, 706, 4035, 713, 4034, 719, 4032, 725, 4031, 731, 4030, 737, 4029, 744, 4028,
	750, 4027, 756, 4026, 762, 4024, 768, 4023, 774, 4022, 781, 4021, 787, 4020, 793, 4019,
	799, 4017, 805, 4016, 811, 4015, 818, 4014, 824, 4012, 830, 4011, 836, 4010, 842, 4008,
	848, 4007, 854, 4006, 861, 4005, 867, 4003, 873, 4002, 879, 4001, 885, 3999, 891, 3998,
	897, 3996, 904, 3995, 910, 3994, 916, 3992, 922, 3991, 928, 3989, 934, 3988, 940, 3987,
	946, 3985, 953, 3984, 959, 3982, 965, 3981, 971, 3979, 977, 3978, 983, 3976, 989, 3975,
	995, 3973, 1001, 3972, 1007, 3970, 1014, 3969, 1020, 3967, 1026, 3965, 1032, 3964, 1038, 3962,
	1044, 3961, 1050, 3959, 1056, 3958, 1062, 3956, 1068, 3954, 1074, 3953, 1080, 3951, 1086, 3949,
	1092, 3948, 1099, 3946, 1105, 3944, 1111, 3943, 1117, 3941, 1123, 3939, 1129, 3937, 1135, 3936,
	1141, 3934, 1147, 3932, 1153, 3930, 1159, 3929, 1165, 3927, 1171, 3925, 1177, 3923, 1183, 3921,
	1189, 3920, 1195, 3918, 1201, 3916, 1207, 3914, 1213, 3912, 1219, 3910, 1225, 3909, 1231, 3907,
	1237, 3905, 1243, 3903, 1249, 3901, 1255, 3899, 1261, 3897, 1267, 3895, 1273, 3893, 1279, 3891,
	1285, 3889, 1291, 3887, 1297, 3885, 1303, 3883, 1309, 3881, 1315, 3879, 1321, 3877, 1327, 3875,
	1332, 3873, 1338, 3871, 1344, 3869, 1350, 3867, 1356, 3865, 1362, 3863, 1368, 3861, 1374, 3859,
	1380, 3857, 1386, 3854, 1392, 3852, 1398, 3850, 1404, 3848, 1409, 3846, 1415, 3844, 1421, 3842,
	1427, 3839, 1433, 3837, 1439, 3835, 1445, 3833, 1451, 3831, 1457, 3828, 1462, 3826, 1468, 3824,
	1474, 3822, 1480, 3819, 1486, 3817, 1492, 3815, 1498, 3812, 1503, 3810, 1509, 3808, 1515, 3805,
	1521, 3803, 1527, 3801, 1533, 3798, 1538, 3796, 1544, 3794, 1550, 3791, 1556, 3789, 1562, 3787,
	1567, 3784, 1573, 3782, 1579, 3779, 1585, 3777, 1591, 3775, 1596, 3772, 1602, 3770, 1608, 3767,
	1614, 3765, 1620, 3762, 1625, 3760, 1631, 3757, 1637, 3755, 1643, 3752, 1648, 3750, 1654, 3747,
	1660, 3745, 1666, 3742, 1671, 3739, 1677, 3737, 1683, 3734, 1689, 3732, 1694, 3729, 1700, 3727,
	1706, 3724, 1711, 3721, 1717, 3719, 1723, 3716, 1729, 3713, 1734, 3711, 1740, 3708, 1746, 3705,
	1751, 3703, 1757, 3700, 1763, 3697, 1768, 3695, 1774, 3692, 1780, 3689, 1785, 3686, 1791, 3684,
	1797, 3681, 1802, 3678, 1808, 3675, 1813, 3673, 1819, 3670, 1825, 3667, 1830, 3664, 1836, 3661,
	1842, 3659, 1847, 3656, 1853, 3653, 1858, 3650, 1864, 3647, 1870, 3644, 1875, 3642, 1881, 3639,
	1886, 3636, 1892, 3633, 1898, 3630, 1903, 3627, 1909, 3624, 1914, 3621, 1920, 3618, 1925, 3615,
	1931, 3612, 1936, 3609, 1942, 3606, 1947, 3603, 1953, 3600, 1958, 3597, 1964, 3594, 1970, 3591,
	1975, 3588, 1981, 3585, 1986, 3582, 1992, 3579, 1997, 3576, 2002, 3573, 2008, 3570, 2013, 3567,
	2019, 3564, 2024, 3561, 2030, 3558, 2035, 3555, 2041, 3551, 2046, 3548, 2052, 3545, 2057, 3542,
	2062, 3539, 2068, 3536, 2073, 3532, 2079, 3529, 2084, 3526, 2090, 3523, 2095, 3520, 2100, 3516,
	2106, 3513, 2111, 3510, 2117, 3507, 2122, 3504, 2127, 3500, 2133, 3497, 2138, 3494, 2143, 3490,
	2149, 3487, 2154, 3484, 2159, 3481, 2165, 3477, 2170, 3474, 2175, 3471, 2181, 3467, 2186, 3464,
	2191, 3461, 2197, 3457, 2202, 3454, 2207, 3450, 2213, 3447, 2218, 3444, 2223, 3440, 2228, 3437,
	2234, 3433, 2239, 3430, 2244, 3426, 2249, 3423, 2255, 3420, 2260, 3416, 2265, 3413, 2270, 3409,
	2276, 3406, 2281, 3402, 2286, 3399, 2291, 3395, 2296, 3392, 2302, 3388, 2307, 3385, 2312, 3381,
	2317, 3378, 2322, 3374, 2328, 3370, 2333, 3367, 2338, 3363, 2343, 3360, 2348, 3356, 2353, 3352,
	2359, 3349, 2364, 3345, 2369, 3342, 2374, 3338, 2379, 3334, 2384, 3331, 2389, 3327, 2394, 3323,
	2399, 3320, 2405, 3316, 2410, 3312, 2415, 3309, 2420, 3305, 2425, 3301, 2430, 3297, 2435, 3294,
	2440, 3290, 2445, 3286, 2450, 3282, 2455, 3279, 2460, 3275, 2465, 3271, 2470, 3267, 2475, 3264,
	2480, 3260, 2485, 3256, 2490, 3252, 2495, 3248, 2500, 3244, 2505, 3241, 2510, 3237, 2515, 3233,
	2520, 3229, 2525, 3225, 2530, 3221, 2535, 3217, 2540, 3214, 2545, 3210, 2550, 3206, 2555, 3202,
	2559, 3198, 2564, 3194, 2569, 3190, 2574, 3186, 2579, 3182, 2584, 3178, 2589, 3174, 2594, 3170,
	2598, 3166, 2603, 3162, 2608, 3158, 2613, 3154, 2618, 3150, 2623, 3146, 2628, 3142, 2632, 3138,
	2637, 3134, 2642, 3130, 2647, 3126, 2652, 3122, 2656, 3118, 2661, 3114, 2666, 3110, 2671, 3106,
	2675, 3102, 2680, 3097, 2685, 3093, 2690, 3089, 2694, 3085, 2699, 3081, 2704, 3077, 2709, 3073,
	2713, 3068, 2718, 3064, 2723, 3060, 2727, 3056, 2732, 3052, 2737, 3048, 2741, 3043, 2746, 3039,
	2751, 3035, 2755, 3031, 2760, 3026, 2765, 3022, 2769, 3018, 2774, 3014, 2779, 3009, 2783, 3005,
	2788, 3001, 2792, 2997, 2797, 2992, 2802, 2988, 2806, 2984, 2811, 2979, 2815, 2975, 2820, 2971,
	2824, 2967, 2829, 2962, 2833, 2958, 2838, 2953, 2843, 2949, 2847, 2945, 2852, 2940, 2856, 2936,
	2861, 2932, 2865, 2927, 2870, 2923, 2874, 2918, 2878, 2914, 2883, 2910, 2887, 2905, 2892, 2901,
	2896, 2896, 2901, 2892, 2905, 2887, 2910, 2883, 2914, 2878, 2918, 2874, 2923, 2870, 2927, 2865,
	2932, 2861, 2936, 2856, 2940, 2852, 2945, 2847, 2949, 2843, 2953, 2838, 2958, 2833, 2962, 2829,
	2967, 2824, 2971, 2820, 2975, 2815, 2979, 2811, 2984, 2806, 2988, 2802, 2992, 2797, 2997, 2792,
	3001, 2788, 3005, 2783, 3009, 2779, 3014, 2774, 3018, 2769, 3022, 2765, 3026, 2760, 3031, 2755,
	3035, 2751, 3039, 2746, 3043, 2741, 3048, 2737, 3052, 2732, 3056, 2727, 3060, 2723, 3064, 2718,
	3068, 2713, 3073, 2709, 3077, 2704, 3081, 2699, 3085, 2694, 3089, 2690, 3093, 2685, 3097, 2680,
	3102, 2675, 3106, 2671, 3110, 2666, 3114, 2661, 3118, 2656, 3122, 2652, 3126, 2647, 3130, 2642,
	3134, 2637, 3138, 2632, 3142, 2628, 3146, 2623, 3150, 2618, 3154, 2613, 3158, 2608, 3162, 2603,
	3166, 2598, 3170, 2594, 3174, 2589, 3178, 2584, 3182, 2579, 3186, 2574, 3190, 2569, 3194, 2564,
	3198, 2559, 3202, 2555, 3206, 2550, 3210, 2545, 3214, 2540, 3217, 2535, 3221, 2530, 3225, 2525,
	3229, 2520, 3233, 2515, 3237, 2510, 3241, 2505, 3244, 2500, 3248, 2495, 3252, 2490, 3256, 2485,
	3260, 2480, 3264, 2475, 3267, 2470, 3271, 2465, 3275, 2460, 3279, 2455, 3282, 2450, 3286, 2445,
	3290, 2440, 3294, 2435, 3297, 2430, 3301, 2425, 3305, 2420, 3309, 2415, 3312, 2410, 3316, 2405,
	3320, 2399, 3323, 2394, 3327, 2389, 3331, 2384, 3334, 2379, 3338, 2374, 3342, 2369, 3345, 2364,
	3349, 2359, 3352, 2353, 3356, 2348, 3360, 2343, 3363, 2338, 3367, 2333, 3370, 2328, 3374, 2322,
	3378, 2317, 3381, 2312, 3385, 2307, 3388, 2302, 3392, 2296, 3395, 2291, 3399, 2286, 3402, 2281,
	3406, 2276, 3409, 2270, 3413, 2265, 3416, 2260, 3420, 2255, 3423, 2249, 3426, 2244, 3430, 2239,
	3433, 2234, 3437, 2228, 3440, 2223, 3444, 2218, 3447, 2213, 3450, 2207, 3454, 2202, 3457, 2197,
	3461, 2191, 3464, 2186, 3467, 2181, 3471, 2175, 3474, 2170, 3477, 2165, 3481, 2159, 3484, 2154,
	3487, 2149, 3490, 2143, 3494, 2138, 3497, 2133, 3500, 2127, 3504, 2122, 3507, 2117, 3510, 2111,
	3513, 2106, 3516, 2100, 3520, 2095, 3523, 2090, 3526, 2084, 3529, 2079, 3532, 2073, 3536, 2068,
	3539, 2062, 3542, 2057, 3545, 2052, 3548, 2046, 3551, 2041, 3555, 2035, 3558, 2030, 3561, 2024,
	3564, 2019, 3567, 2013, 3570, 2008, 3573, 2002, 3576, 1997, 3579, 1992, 3582, 1986, 3585, 1981,
	3588, 1975, 3591, 1970, 3594, 1964, 3597, 1958, 3600, 1953, 3603, 1947, 3606, 1942, 3609, 1936,
	3612, 1931, 3615, 1925, 3618, 1920, 3621, 1914, 3624, 1909, 3627, 1903, 3630, 1898, 3633, 1892,
	3636, 1886, 3639, 1881, 3642, 1875, 3644, 1870, 3647, 1864, 3650, 1858, 3653, 1853, 3656, 1847,
	3659, 1842, 3661, 1836, 3664, 1830, 3667, 1825, 3670, 1819, 3673, 1813, 3675, 1808, 3678, 1802,
	3681, 1797, 3684, 1791, 3686, 1785, 3689, 1780, 3692, 1774, 3695, 1768, 3697, 1763, 3700, 1757,
	3703, 1751, 3705, 1746, 3708, 1740, 3711, 1734, 3713, 1729, 3716, 1723, 3719, 1717, 3721, 1711,
	3724, 1706, 3727, 1700, 3729, 1694, 3732, 1689, 3734, 1683, 3737, 1677, 3739, 1671, 3742, 1666,
	3745, 1660, 3747, 1654, 3750, 1648, 3752, 1643, 3755, 1637, 3757, 1631, 3760, 1625, 3762, 1620,
	3765, 1614, 3767, 1608, 3770, 1602, 3772, 1596, 3775, 1591, 3777, 1585, 3779, 1579, 3782, 1573,
	3784, 1567, 3787, 1562, 3789, 1556, 3791, 1550, 3794, 1544, 3796, 1538, 3798, 1533, 3801, 1527,
	3803, 1521, 3805, 1515, 3808, 1509, 3810, 1503, 3812, 1498, 3815, 1492, 3817, 1486, 3819, 1480,
	3822, 1474, 3824, 1468, 3826, 1462, 3828, 1457, 3831, 1451, 3833, 1445, 3835, 1439, 3837, 1433,
	3839, 1427, 3842, 1421, 3844, 1415, 3846, 1409, 3848, 1404, 3850, 1398, 3852, 1392, 3854, 1386,
	3857, 1380, 3859, 1374, 3861, 1368, 3863, 1362, 3865, 1356, 3867, 1350, 3869, 1344, 3871, 1338,
	3873, 1332, 3875, 1327, 3877, 1321, 3879, 1315, 3881, 1309, 3883, 1303, 3885, 1297, 3887, 1291,
	3889, 1285, 3891, 1279, 3893, 1273, 3895, 1267, 3897, 1261, 3899, 1255, 3901, 1249, 3903, 1243,
	3905, 1237, 3907, 1231, 3909, 1225, 3910, 1219, 3912, 1213, 3914, 1207, 3916, 1201, 3918, 1195,
	3920, 1189, 3921, 1183, 3923, 1177, 3925, 1171, 3927, 1165, 3929, 1159, 3930, 1153, 3932, 1147,
	3934, 1141, 3936, 1135, 3937, 1129, 3939, 1123, 3941, 1117, 3943, 1111, 3944, 1105, 3946, 1099,
	3948, 1092, 3949, 1086, 3951, 1080, 3953, 1074, 3954, 1068, 3956, 1062, 3958, 1056, 3959, 1050,
	3961, 1044, 3962, 1038, 3964, 1032, 3965, 1026, 3967, 1020, 3969, 1014, 3970, 1007, 3972, 1001,
	3973, 995, 3975, 989, 3976, 983, 3978, 977, 3979, 971, 3981, 965, 3982, 959, 3984, 953,
	3985, 946, 3987, 940, 3988, 934, 3989, 928, 3991, 922, 3992, 916, 3994, 910, 3995, 904,
	3996, 897, 3998, 891, 3999, 885, 4001, 879, 4002, 873, 4003, 867, 4005, 861, 4006, 854,
	4007, 848, 4008, 842, 4010, 836, 4011, 830, 4012, 824, 4014, 818, 4015, 811, 4016, 805,
	4017, 799, 4019, 793, 4020, 787, 4021, 781, 4022, 774, 4023, 768, 4024, 762, 4026, 756,
	4027, 750, 4028, 744, 4029, 737, 4030, 731, 4031, 725, 4032, 719, 4034, 713, 4035, 706,
	4036, 700, 4037, 694, 4038, 688, 4039, 682, 4040, 675, 4041, 669, 4042, 663, 4043, 657,
	4044, 651, 4045, 644, 4046, 638, 4047, 632, 4048, 626, 4049, 620, 4050, 613, 4051, 607,
	4052, 601, 4053, 595, 4053, 589, 4054, 582, 4055, 576, 4056, 570, 4057, 564, 4058, 557,
	4059, 551, 4060, 545, 4060, 539, 4061, 533, 4062, 526, 4063, 520, 4064, 514, 4064, 508,
	4065, 501, 4066, 495, 4067, 489, 4067, 483, 4068, 476, 4069, 470, 4070, 464, 4070, 458,
	4071, 451, 4072, 445, 4072, 439, 4073, 433, 4074, 426, 4074, 420, 4075, 414, 4076, 408,
	4076, 401, 4077, 395, 4077, 389, 4078, 383, 4079, 376, 4079, 370, 4080, 364, 4080, 358,
	4081, 351, 4081, 345, 4082, 339, 4082, 333, 4083, 326, 4083, 320, 4084, 314, 4084, 308,
	4085, 301, 4085, 295, 4086, 289, 4086, 283, 4087, 276, 4087, 270, 4088, 264, 4088, 257,
	4088, 251, 4089, 245, 4089, 239, 4089, 232, 4090, 226, 4090, 220, 4090, 214, 4091, 207,
	4091, 201, 4091, 195, 4092, 188, 4092, 182, 4092, 176, 4092, 170, 4093, 163, 4093, 157,
	4093, 151, 4093, 144, 4094, 138, 4094, 132, 4094, 126, 4094, 119, 4094, 113, 4095, 107,
	4095, 101, 4095,  94, 4095,  88, 4095,  82, 4095,  75, 4095,  69, 4096,  63, 4096,  57,
	4096, 50,  4096,  44, 4096,  38, 4096,  31, 4096,  25, 4096,  19, 4096,  13, 4096,   6,
	0
};

void InitialiseCamera()//25AAC, 25CB8 (F)
{
	//We won't actually use this yet since lara_item is not inited.
	return;
	camera.pos.x = lara_item->pos.x_pos;
	camera.pos.y = lara_item->pos.y_pos - 1024;
	camera.pos.z = lara_item->pos.z_pos - 100;
	camera.pos.room_number = lara_item->room_number;

	camera.target.x = lara_item->pos.x_pos;
	camera.target.y = lara_item->pos.y_pos - 1024;
	camera.target.z = lara_item->pos.z_pos;
	camera.target.room_number = lara_item->room_number;

	last_target.x = lara_item->pos.x_pos;
	last_target.y = lara_item->pos.y_pos - 1024;
	last_target.z = lara_item->pos.z_pos;
	last_target.room_number = lara_item->room_number;
	
	camera.shift = lara_item->pos.y_pos - 1024;
	camera.target_distance = 1536;
	camera.number_frames = 1;
	camera.speed = 1;
	camera.flags = 1;
	camera.item = NULL;
	camera.type = CHASE_CAMERA;
	camera.bounce = 0;
	camera.number = -1;
	camera.fixed_camera = 0;

	AlterFOV(16380);
	UseForcedFixedCamera = 0;

	CalculateCamera();
	return;
}

void AlterFOV(short fov)//77BD8, 79C1C
{
	CurrentFov = fov;

	short* rcossin_ptr = &rcossin_tbl[((fov + ((fov << 16) >> 31) >> 3) & 0x3FFC) / sizeof(short)];
	//short* rcossin_ptr = &rcossin_tbl[((fov + ((fov << 16) >> 31) >> 3) & 0x3FFC) / sizeof(short)];
	phd_persp = ((rcossin_ptr[1] << 8) / rcossin_ptr[0]);
	///ctc2	$a0, $26 //?unknown instruction
}

void CalculateCamera()//27DA0(<), 27FAC(!)
{
	//We don't actually use this since lara_item is not inited.
	//Also, GetBoundsAccurate is not implemented.
	return;

	struct ITEM_INFO* item;
	short* bounds;
	short tilt;
	short change;
	long shift;
	long fixed_camera;
	long y;
	long gotit;
	struct OBJECT_VECTOR* fixed;
	struct PHD_VECTOR v;

	SniperOverlay = 0;
	camerasnaps = 0;

	CamOldPos.x = camera.pos.x;
	CamOldPos.y = camera.pos.y;
	CamOldPos.z = camera.pos.z;

	if (BinocularRange > 0)
	{
		BinocularOn = 1;
		BinocularCamera(lara_item);

		if (BinocularRange > 0)
		{
			return;
		}
	}

	//loc_27E14
	if (BinocularOn == 1)
	{
		BinocularOn = -8;
	}

	//loc_27E28
	camera.type = FIXED_CAMERA;
	if (!UseForcedFixedCamera && camera.old_type != FIXED_CAMERA)
	{
		camera.speed = 1;
	}

	//loc_27E4C
	if (gfCurrentLevel == 1 && XATrack == 51)
	{
		if (camera.underwater > 0 && GLOBAL_playing_cutseq == 0 && savegame.VolumeCD > 0)
		{
			CDDA_SetMasterVolume(savegame.VolumeCD);
		}

		//loc_27EBC
		TLFlag = 1;
	}
	else
	{
		//loc_27EC8
		if (TLFlag != 1 || camera.underwater == 0)
		{
			//loc_27EEC
			TLFlag = 0;
		}
		else
		{
			camera.underwater = 0;
		}
	}

	//loc_27EF0
	if (gfCurrentLevel != 6)
	{
		//Camera is in a water room, play water sound effect.
		if (room[camera.pos.room_number].flags & 1)
		{
			//SoundEffect(0, 60, 2);//a0, a1, a2
			if (camera.underwater > 0)
			{
				if (GLOBAL_playing_cutseq == 0 && TLFlag == 0)
				{
					CDDA_SetMasterVolume(savegame.VolumeCD / 16);
				}

				//loc_27F88
				camera.underwater = 1;
			}
		}
		else
		{
			//loc_27F94
			if (camera.underwater > 0)
			{
				if (GLOBAL_playing_cutseq == 0 && TLFlag == 0 && savegame.VolumeCD > 0)
				{
					CDDA_SetMasterVolume(savegame.VolumeCD);
				}

				//loc_27FE4
				camera.underwater = 0;
			}
		}
	}

	//loc_27FE8
	if (camera.type == CINEMATIC_CAMERA)
	{
		do_new_cutscene_camera();
		return;
	}

	//loc_28008
	fixed_camera = 0;//$s5
	if (camera.item != NULL)
	{
		if (camera.type == FIXED_CAMERA || camera.type == HEAVY_CAMERA)
		{
			//loc_2802C
			fixed_camera = 1;
		}
	}

	//^ VERIFIED
	//loc_28030
   //If fixed camera is not enabled, always point the camera at lara.
   //Otherwise it's pointed at the camera's item;
	if (fixed_camera == 0)
	{
		item = lara_item;
	}
	else
	{
		item = camera.item;
	}

	//loc_28040
	bounds = GetBoundsAccurate(item);
	y = (item->pos.y_pos + ((bounds[2] + bounds[3]) / 2)) - 256;//$s4

	if (camera.item != NULL && fixed_camera == 0)
	{
		//Dist
		//FIXME: long mSqrt(long); , check args
		shift = sqrt((camera.item->pos.z_pos - item->pos.z_pos) * (camera.item->pos.z_pos - item->pos.z_pos) + (camera.item->pos.x_pos - item->pos.x_pos) * (camera.item->pos.x_pos - item->pos.x_pos));

		//FIXME: phd_atan_asm(); , check args
		change = atan2((item->pos.z_pos - camera.item->pos.z_pos), (item->pos.x_pos - camera.item->pos.x_pos)) - camera.item->pos.y_rot;
		change *= 65536;

		bounds = GetBoundsAccurate(camera.item);
		//FIXME: phd_atan_asm(); , check args $a0, $a1
		//phd_atan_asm(shift, (camera.item->pos.y_pos + ((((bounds[2] + bounds[3]) + (bounds[2] + bounds[3])) >> 31) >> 1)) - y); 

		int v0 = atan2(shift, (camera.item->pos.y_pos + ((((bounds[2] + bounds[3]) + (bounds[2] + bounds[3])) >> 31) >> 1)) - y);
		v0 <<= 16;
		tilt = v0 >> 17;//a3

		int v1 = change >> 17;

		v0 = ((change >> 17) + 9099) & 0xFFFF;
		v0 = v0 < 0x4717 ? 1 : 0;
		if (v0 != 0)
		{
			S_Warn("[CalculateCamera] - Unimplemented case!\n");
			assert(0);//unfinished case
			v0 = tilt < -0x3C6D ? 1 : 0;
			if (v0 == 0)
			{
				v0 = tilt < 0x3C6D ? 1 : 0;
				if (v0 != 0)
				{
					struct lara_info* a2 = &lara;
					int a1 = lara.water_surface_dist;
					v1 -= a1;
					v1 <<= 16;
					change = v1 >> 16;
					
					int a0 = change < 0x2D9 ? 1 : 0;
					int t0 = v0;

					if (a0 == 0)
					{
						v0 = a1 + 0x2D8;
					}
					else
					{
						//loc_28178
#if 0
						slti	$v0, $s0, -0x2D8
						bnez	$v0, loc_28188
						addiu	$v0, $a1, -0x2D8
						addu	$v0, $s0, $a1
#endif
					}

					//loc_28188
#if 0
					loc_28188:
							 sh	$v0, 0xA8($a2)
								 addiu	$a1, $t0, 0x57DC
								 lhu	$a0, 0xAA($a1)
								 lhu	$v1, 0xA8($a1)
								 subu	$v0, $a3, $a0
								 sll	$v0, 16
								 sra	$s0, $v0, 16
								 slti	$v0, $s0, 0x2D9
								 bnez	$v0, loc_281B8
								 sh	$v1, 0xAE($a1)
								 j	loc_281C8
								 addiu	$v0, $a0, 0x2D8

								 loc_281B8:
							 slti	$v0, $s0, -0x2D8
								 bnez	$v0, loc_281C8
								 addiu	$v0, $a0, -0x2D8
								 addu	$v0, $s0, $a0

								 loc_281C8 :
							 sh	$v0, 0xAA($a1)
								 addiu	$v1, $t0, 0x57DC
								 lhu	$a0, 0xAA($v1)
								 lw	$a1, 0x1E44($gp)
								 li	$v0, 2
								 sw	$v0, 0x1E08($gp)
								 sh	$a0, 0xB0($v1)
								 lw	$v0, 0x84($a1)
								 nop
								 ori	$v0, 0x40
								 sw	$v0, 0x84($a1)
#endif

				}//loc_281F4
			}//loc_281F4
		}//loc_281F4
	}

	//loc_281F4
	if ((camera.type - LOOK_CAMERA) < 2)
	{
		if (camera.type == COMBAT_CAMERA)
		{
			last_target.x = camera.target.x;
			last_target.y = camera.target.y;
			last_target.z = camera.target.z;
			last_target.room_number = camera.target.room_number;
		}

		//loc_28234
		camera.target.room_number = item->room_number;

		if (camera.fixed_camera == 0 && BinocularOn < 0)
		{
			//loc_28258
			camera.target.y = y;
			camera.speed = 1;
		}
		else
		{
			//loc_28268
			camera.target.y = ((y - camera.target.y) / 4) + camera.target.y;

			if (camera.type == LOOK_CAMERA)
			{
				//loc_28290
				camera.speed = 4;
			}
			else
			{
				//loc_28290
				camera.speed = 8;
			}
		}

		//loc_28294
		camera.fixed_camera = 0;

		if (camera.type == LOOK_CAMERA)
		{
			LookCamera(item);
		}
		else
		{
			CombatCamera(item);
		}
	}
	else
	{
		////loc_282C8
		last_target.x = camera.target.x;
		last_target.y = camera.target.y;
		last_target.z = camera.target.z;
		last_target.room_number = camera.target.room_number;

		y = camera.target.y;//$s4

		camera.target.room_number = item->room_number;

		gotit = 0;
		if (camera.type != CHASE_CAMERA && camera.flags != 3)
		{
			fixed = &camera.fixed[camera.number];//a0

			SniperCamActive = fixed->flags & 3;

			//Look at lara joint 7.
			if (fixed->flags & 2)
			{
				v.x = 0;
				v.y = 0;
				v.z = 0;

				//v = GetLaraJointPos(7);//$a1

				camera.target.x = v.z;
				camera.target.y = v.y;
				camera.target.z = v.x;

				gotit = 1;
			}
		}

		//loc_28370
		if (gotit == 0)
		{
			int v1 = (((bounds[0] + bounds[4]) + bounds[4]) + bounds[5]) / 4;
			camera.target.x = ((rcossin_tbl[((item->pos.y_rot >> 2) & 0x3FFC) / sizeof(short)] * v1) >> 12) + item->pos.x_pos;
			camera.target.z = ((rcossin_tbl[(((item->pos.y_rot >> 3) | 1) << 1) / sizeof(short)] * v1) >> 12) + item->pos.z_pos;

			if (item->object_number == LARA)
			{
				ConfirmCameraTargetPos();
			}
		}

		//loc_28418
		if (camera.fixed_camera != fixed_camera)
		{
			SniperCount = 30;
			camera.fixed_camera = 1;
			camera.speed = 1;
		}
		else
		{
			//loc_28440
			camera.fixed_camera = 0;
		}

		//loc_28444
		if (camera.speed != 1 && camera.old_type != LOOK_CAMERA && BinocularOn >= 0)
		{
			if (TargetSnaps < 9)
			{
				//loc_28494
				camera.target.x = ((camera.target.x - last_target.x) / 4) + camera.target.x;
				camera.target.y = ((camera.target.y - last_target.y) / 4) + camera.target.y;
				camera.target.z = ((camera.target.z - last_target.z) / 4) + last_target.z;
			}
			else
			{
				TargetSnaps = 0;
			}
		}

		//loc_284DC
		//GetFloor(camera.target.x, camera.target.y, camera.target.z, camera.target.room_number);//$a0, $a1, $a2, $a3

		long v0 = camera.target.x - last_target.x;
		if (v0 < 0)
		{
			v0 = -v0;
		}

		//loc_28510
		if (v0 < 4)
		{
			int v00 = camera.target.y - last_target.y;

			if (v00 < 0)
			{
				v00 = -v00;
			}

			//loc_28560:
			if (v00 < 4)
			{
				camera.target.x = last_target.x;
				camera.target.y = last_target.y;
				camera.target.z = last_target.z;
			}

		}

		//loc_28578
		if (camera.type != CHASE_CAMERA)
		{
			if (camera.flags != 3)
			{
				FixedCamera();
			}
		}//loc_28598
		else
		{
			ChaseCamera(item);
		}
	}

	//loc_285B0
	camera.fixed_camera = fixed_camera;
	camera.last = camera.number;

	if (camera.type == HEAVY_CAMERA && camera.timer != -1)
	{
		return;
	}

	//loc_285DC
	camera.speed = 10;
	camera.type = CHASE_CAMERA;
	camera.number = -1;

	camera.target_elevation = 0;
	camera.target_angle = 0;
	camera.target_distance = 1536;
	camera.flags = 0;

	camera.lara_node = -1;
	camera.last_item = item;
	camera.item = NULL;

	return;
}

void LookCamera(struct ITEM_INFO* item)
{
	S_Warn("[LookCamera] - Unimplemented!\n");
}

void CombatCamera(struct ITEM_INFO* item)
{
	S_Warn("[CombatCamera] - Unimplemented!\n");
}

void FixedCamera()
{
	S_Warn("[FixedCamera] - Unimplemented!\n");
}

void ChaseCamera(struct ITEM_INFO* item)
{
	S_Warn("[ChaseCamera] - Unimplemented!\n");
}

void BinocularCamera(struct ITEM_INFO* item)
{
	S_Warn("[BinocularCamera] - Unimplemented!\n");
}

void ConfirmCameraTargetPos()
{
	S_Warn("[ConfirmCameraTargetPos] - Unimplemented!\n");
}