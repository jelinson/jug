#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtDebug>
#include <QDebug>

#define VERBOSE 2
#define NORMAL 1
#define QUIET 0
#define DEBUG_LEVEL VERBOSE

#define IMG_WIDTH 428
#define IMG_HEIGHT 533

#define MIN_SAT_THRES 40
#define MAX_SAT_THRES 255

#define HUE_MARGIN 8

#define N_LIMBS 4

#define SLOPE_RANGE 5

#define CS_WEIGHT 150
#define CS_LIMB_MIN 50
#define CS_LIMB_MAX 200

#define LATERAL_SELF_BALANCE 40
#define AREA_FORCE_SCALING 1
#define PERIMETER_FORCE_SCALING 1


#define IS_ARM(x) ((x == 0) || (x == 1))
#define IS_LEG(x) ((x == 2) || (x == 3))

#define LATTICE_SPACING 10
#define LATTICE_DIM 4

#define MIN_HAND_HOLD_PERIMETER 50
#define MIN_HAND_HOLD_AREA 80

#define MIN_PERIMETER_PER_LIMB 35

#endif // GLOBALS_H
