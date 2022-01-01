#pragma once
#define F_LEFT (120.0lf / 320.0lf)
#define F_RIGHT (200.0lf / 320.0lf)
#define F_TOP (40.0lf / 240.0lf)
#define F_BOT (200.0lf / 240.0lf)

/*
 * Transformation for board:
 * {
 *     { 1/20,  0,    -1/4  , 0},
 *     { 0,    -1/15, -11/15, 0},
 *     { 0,     0,     1    , 0}
 *     { 0,     0,     0    , 1}
 * }
 */