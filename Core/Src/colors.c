/*
 * colors.c
 *
 *  Created on: Sep 3, 2020
 *      Author: dans
 */

#include "colors.h"


const float fade_array[] = {
1.88160,
1.88136,
1.88067,
1.87951,
1.87789,
1.87580,
1.87326,
1.87027,
1.86682,
1.86292,
1.85857,
1.85379,
1.84856,
1.84291,
1.83682,
1.83032,
1.82340,
1.81608,
1.80835,
1.80023,
1.79172,
1.78284,
1.77358,
1.76397,
1.75400,
1.74368,
1.73304,
1.72206,
1.71078,
1.69918,
1.68730,
1.67512,
1.66267,
1.64996,
1.63700,
1.62379,
1.61035,
1.59668,
1.58281,
1.56874,
1.55447,
1.54004,
1.52543,
1.51067,
1.49576,
1.48072,
1.46555,
1.45027,
1.43489,
1.41942,
1.40386,
1.38824,
1.37255,
1.35681,
1.34102,
1.32521,
1.30937,
1.29351,
1.27766,
1.26180,
1.24596,
1.23014,
1.21434,
1.19859,
1.18287,
1.16721,
1.15161,
1.13607,
1.12061,
1.10523,
1.08993,
1.07472,
1.05961,
1.04460,
1.02970,
1.01491,
1.00025,
0.98570,
0.97128,
0.95699,
0.94284,
0.92882,
0.91495,
0.90122,
0.88764,
0.87421,
0.86094,
0.84782,
0.83485,
0.82205,
0.80941,
0.79694,
0.78463,
0.77248,
0.76051,
0.74870,
0.73706,
0.72559,
0.71429,
0.70316,
0.69220,
0.68141,
0.67080,
0.66035,
0.65007,
0.63997,
0.63003,
0.62026,
0.61066,
0.60123,
0.59196,
0.58286,
0.57392,
0.56515,
0.55654,
0.54809,
0.53979,
0.53166,
0.52368,
0.51586,
0.50819,
0.50068,
0.49331,
0.48609,
0.47902,
0.47210,
0.46532,
0.45868,
0.45219,
0.44583,
0.43961,
0.43352,
0.42757,
0.42175,
0.41606,
0.41050,
0.40507,
0.39976,
0.39457,
0.38950,
0.38456,
0.37973,
0.37502,
0.37042,
0.36593,
0.36156,
0.35730,
0.35314,
0.34909,
0.34514,
0.34130,
0.33756,
0.33392,
0.33038,
0.32694,
0.32359,
0.32033,
0.31717,
0.31410,
0.31112,
0.30823,
0.30543,
0.30272,
0.30009,
0.29754,
0.29508,
0.29270,
0.29040,
0.28818,
0.28603,
0.28397,
0.28198,
0.28007,
0.27824,
0.27648,
0.27479,
0.27317,
0.27163,
0.27015,
0.26875,
0.26742,
0.26616,
0.26496,
0.26383,
0.26277,
0.26178,
0.26085,
0.25999,
0.25920,
0.25847,
0.25780,
0.25720,
0.25666,
0.25619,
0.25578,
0.25543,
0.25515,
0.25493,
0.25477,
0.25468,
0.25465,
0.25468,
0.25477,
0.25493,
0.25515,
0.25543,
0.25578,
0.25619,
0.25666,
0.25720,
0.25780,
0.25847,
0.25920,
0.25999,
0.26085,
0.26178,
0.26277,
0.26383,
0.26496,
0.26616,
0.26742,
0.26875,
0.27015,
0.27163,
0.27317,
0.27479,
0.27648,
0.27824,
0.28007,
0.28198,
0.28397,
0.28603,
0.28818,
0.29040,
0.29270,
0.29508,
0.29754,
0.30009,
0.30272,
0.30543,
0.30823,
0.31112,
0.31410,
0.31717,
0.32033,
0.32359,
0.32694,
0.33038,
0.33392,
0.33756,
0.34130,
0.34514,
0.34909,
0.35314,
0.35730,
0.36156,
0.36593,
0.37042,
0.37502,
0.37973,
0.38456,
0.38950,
0.39457,
0.39976,
0.40507,
0.41050,
0.41606,
0.42175,
0.42757,
0.43352,
0.43961,
0.44583,
0.45219,
0.45868,
0.46532,
0.47210,
0.47902,
0.48609,
0.49331,
0.50068,
0.50819,
0.51586,
0.52368,
0.53166,
0.53979,
0.54809,
0.55654,
0.56515,
0.57392,
0.58286,
0.59196,
0.60123,
0.61066,
0.62026,
0.63003,
0.63997,
0.65007,
0.66035,
0.67080,
0.68141,
0.69220,
0.70316,
0.71429,
0.72559,
0.73706,
0.74870,
0.76051,
0.77248,
0.78463,
0.79694,
0.80941,
0.82205,
0.83485,
0.84782,
0.86094,
0.87421,
0.88764,
0.90122,
0.91495,
0.92882,
0.94284,
0.95699,
0.97128,
0.98570,
1.00025,
1.01491,
1.02970,
1.04460,
1.05961,
1.07472,
1.08993,
1.10523,
1.12061,
1.13607,
1.15161,
1.16721,
1.18287,
1.19859,
1.21434,
1.23014,
1.24596,
1.26180,
1.27766,
1.29351,
1.30937,
1.32521,
1.34102,
1.35681,
1.37255,
1.38824,
1.40386,
1.41942,
1.43489,
1.45027,
1.46555,
1.48072,
1.49576,
1.51067,
1.52543,
1.54004,
1.55447,
1.56874,
1.58281,
1.59668,
1.61035,
1.62379,
1.63700,
1.64996,
1.66267,
1.67512,
1.68730,
1.69918,
1.71078,
1.72206,
1.73304,
1.74368,
1.75400,
1.76397,
1.77358,
1.78284,
1.79172,
1.80023,
1.80835,
1.81608,
1.82340,
1.83032,
1.83682,
1.84291,
1.84856,
1.85379,
1.85857,
1.86292,
1.86682,
1.87027,
1.87326,
1.87580,
1.87789,
1.87951,
1.88067,
1.881
};


uint8_t working_led_ind = 0;