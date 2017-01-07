/**********************************************************************
 *
 * cube.geo
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
Point(1) = {-lx/2.0,-lx/2.0,-lx/2.0,lc};
Point(2) = {lx/2.0,-lx/2.0,-lx/2.0,lc};
Point(3) = {lx/2.0,lx/2.0,-lx/2.0,lc};
Point(4) = {-lx/2.0,lx/2.0,-lx/2.0,lc};
Point(5) = {-lx/2.0,-lx/2.0,lx/2.0,lc};
Point(6) = {lx/2.0,-lx/2.0,lx/2.0,lc};
Point(7) = {lx/2.0,lx/2.0,lx/2.0,lc};
Point(8) = {-lx/2.0,lx/2.0,lx/2.0,lc};

Point(9) = {lx/2.0, 0, 0,lc};
Point(10) = {-lx/2.0, 0., 0.,lc};
Point(11) = {0, lx/2.0, 0.,lc};
Point(12) = {0, -lx/2.0, 0.,lc};
Point(13) = {0, 0, lx/2.0,lc};
Point(14) = {0, 0, -lx/2.0,lc};

Line(1) = {5, 6};
Line(2) = {6, 12};
Line(3) = {12, 5};
Line(4) = {5, 1};
Line(5) = {1, 12};
Line(6) = {12, 2};
Line(7) = {2, 1};
Line(8) = {6, 2};
Line(9) = {6, 9};
Line(10) = {9, 2};
Line(11) = {9, 3};
Line(12) = {3, 2};
Line(13) = {9, 7};
Line(14) = {7, 3};
Line(15) = {7, 6};
Line(16) = {7, 8};
Line(17) = {8, 13};
Line(18) = {13, 7};
Line(19) = {13, 6};
Line(20) = {13, 5};
Line(21) = {5, 8};
Line(22) = {7, 11};
Line(23) = {11, 3};
Line(24) = {3, 4};
Line(25) = {4, 11};
Line(26) = {11, 8};
Line(27) = {8, 4};
Line(28) = {4, 10};
Line(29) = {10, 8};
Line(30) = {5, 10};
Line(31) = {10, 1};
Line(32) = {1, 4};
Line(33) = {4, 14};
Line(34) = {14, 3};
Line(35) = {14, 2};
Line(36) = {14, 1};
Line Loop(37) = {19, -1, -20};
Plane Surface(38) = {37};
Line Loop(39) = {20, 21, 17};
Plane Surface(40) = {39};
Line Loop(41) = {18, 16, 17};
Plane Surface(42) = {41};
Line Loop(43) = {15, -19, 18};
Plane Surface(44) = {43};
Line Loop(45) = {16, -26, -22};
Plane Surface(46) = {45};
Line Loop(47) = {22, 23, -14};
Plane Surface(48) = {47};
Line Loop(49) = {26, 27, 25};
Plane Surface(50) = {49};
Line Loop(51) = {23, 24, 25};
Plane Surface(52) = {51};
Line Loop(53) = {21, -29, -30};
Plane Surface(54) = {53};
Line Loop(55) = {29, 27, 28};
Plane Surface(56) = {55};
Line Loop(57) = {30, 31, -4};
Plane Surface(58) = {57};
Line Loop(59) = {28, 31, 32};
Plane Surface(60) = {59};
Line Loop(61) = {1, 2, 3};
Plane Surface(62) = {61};
Line Loop(63) = {3, 4, 5};
Plane Surface(64) = {63};
Line Loop(65) = {5, 6, 7};
Plane Surface(66) = {65};
Line Loop(67) = {2, 6, -8};
Plane Surface(68) = {67};
Line Loop(69) = {9, 13, 15};
Plane Surface(70) = {69};
Line Loop(71) = {9, 10, -8};
Plane Surface(72) = {71};
Line Loop(73) = {10, -12, -11};
Plane Surface(74) = {73};
Line Loop(75) = {13, 14, -11};
Plane Surface(76) = {75};
Line Loop(77) = {12, -35, 34};
Plane Surface(78) = {77};
Line Loop(79) = {35, 7, -36};
Plane Surface(80) = {79};
Line Loop(81) = {34, 24, 33};
Plane Surface(82) = {81};
Line Loop(83) = {36, 32, 33};
Plane Surface(84) = {83};
