/**********************************************************************
 *
 * cubi.geo
 *
 * Copyright (C) 2016 Idesbald Van den Bosch
 *
 * This file is part of Puma-EM.
 * 
 * Puma-EM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Puma-EM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Puma-EM.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Suggestions/bugs : <vandenbosch.idesbald@gmail.com>
 *
 **********************************************************************/

lc = 0.0141411536792;
lx = 0.2;
ly = 0.2;
lz = 0.2;

Point(1) = {lx/2.0, ly/2.0, -lz/2.0, lc};
Point(2) = {-lx/2.0, ly/2.0, -lz/2.0, lc};
Point(3) = {lx/2.0, -ly/2.0, -lz/2.0, lc};
Point(4) = {-lx/2.0, -ly/2.0, -lz/2.0, lc};
Point(5) = {-lx/2.0, -ly/2.0, -lz/2.0, lc};
Point(6) = {0, 0, -lz/2.0, lc};
Point(7) = {0, -ly/2.0, -lz/2.0, lc};
Point(8) = {0, 0, 0, lc};
Point(9) = {0, -ly/2.0, 0, lc};
Point(10) = {lx/2.0, -ly/2.0, 0, lc};
Point(11) = {lx/2.0, 0, 0, lc};
Point(12) = {-lx/2.0, 0, -lz/2.0, lc};
Point(13) = {lx/2.0, 0, -lz/2.0, lc};
Point(14) = {0, ly/2.0, -lz/2.0, lc};
Point(15) = {0, ly/2.0, 0, lc};
Point(16) = {lx/2.0, ly/2.0, 0, lc};
Point(17) = {0, 0, lz/2.0, lc};
Point(18) = {lx/2.0, 0, lz/2.0, lc};
Point(19) = {lx/2.0, ly/2.0, lz/2.0, lc};
Point(20) = {0, ly/2.0, lz/2.0, lc};
Line (7) = {7, 9};
Line (8) = {9, 8};
Line (9) = {8, 6};
Line (10) = {6, 7};
Line (13) = {8, 11};
Line (14) = {11, 10};
Line (15) = {10, 9};
Line (18) = {10, 3};
Line (19) = {7, 3};
Line (22) = {7, 5};
Line (23) = {5, 12};
Line (24) = {12, 6};
Line (25) = {8, 12};
Line (31) = {14, 2};
Line (32) = {2, 12};
Line (33) = {14, 15};
Line (34) = {15, 8};
Line (35) = {15, 2};
Line (44) = {3, 13};
Line (45) = {13, 1};
Line (46) = {1, 14};
Line (48) = {16, 15};
Line (49) = {11, 16};
Line (50) = {16, 1};
Line (51) = {11, 13};
Line (58) = {18, 11};
Line (59) = {18, 19};
Line (60) = {19, 20};
Line (61) = {20, 17};
Line (62) = {17, 18};
Line (63) = {17, 8};
Line (64) = {20, 15};
Line (65) = {19, 16};
Line Loop (1000012) = {8, 9, 10, 7};
Plane Surface (12) = {1000012};
Line Loop (1000017) = {13, 14, 15, 8};
Plane Surface (17) = {1000017};
Line Loop (1000021) = {19, -18, 15, -7};
Plane Surface (21) = {1000021};
Line Loop (1000027) = {22, 23, 24, 10};
Plane Surface (27) = {1000027};
Line Loop (1000029) = {25, 24, -9};
Plane Surface (29) = {1000029};
Line Loop (1000039) = {35, -31, 33};
Plane Surface (39) = {1000039};
Line Loop (1000043) = {25, -32, -35, 34};
Plane Surface (43) = {1000043};
Line Loop (1000053) = {14, 18, 44, -51};
Plane Surface (53) = {1000053};
Line Loop (1000055) = {49, 50, -45, -51};
Plane Surface (55) = {1000055};
Line Loop (1000057) = {48, -33, -46, -50};
Plane Surface (57) = {1000057};
Line Loop (1000067) = {58, -13, -63, 62};
Plane Surface (67) = {1000067};
Line Loop (1000069) = {61, 63, -34, -64};
Plane Surface (69) = {1000069};
Line Loop (1000071) = {60, 64, -48, -65};
Plane Surface (71) = {1000071};
Line Loop (1000073) = {59, 65, -49, -58};
Plane Surface (73) = {1000073};
Line Loop (1000075) = {60, 61, 62, 59};
Plane Surface (75) = {1000075};
