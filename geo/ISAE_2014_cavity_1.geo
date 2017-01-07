/**********************************************************************
 *
 * ISAE_2014_cavity_1.geo
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

// parameters
lc = 0.01;
x = 0.2;
y = 0.075;
z = 0.075;
w = 0.075;
// points
// the waveguide
Point(1) = {0.0, y, z, lc};
Point(2) = {0.0, y, -z, lc};
Point(3) = {0.0, -y, -z, lc};
Point(4) = {0.0, -y, z, lc};
Point(5) = {x, y, z, lc};
Point(6) = {x, y, -z, lc};
Point(7) = {x, -y, -z, lc};
Point(8) = {x, -y, z, lc};
Point(9) = {2.0*x, y, z, lc};
Point(10) = {2.0*x, y, -z, lc};
Point(11) = {2.0*x, -y, -z, lc};
Point(12) = {2.0*x, -y, z, lc};
Point(13) = {3.0*x, y, z, lc};
Point(14) = {3.0*x, y, -z, lc};
Point(15) = {3.0*x, -y, -z, lc};
Point(16) = {3.0*x, -y, z, lc};
// the obstacles
Point(17) = {x, y, z-w, lc};
Point(18) = {x, -y, z-w, lc};
Point(19) = {2.0*x, y, -z+w, lc};
Point(20) = {2.0*x, -y, -z+w, lc};
// the lines
Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};
Line(5) = {5, 17};
Line(6) = {17, 6};
Line(7) = {6, 7};
Line(8) = {7, 18};
Line(9) = {18, 8};
Line(10) = {8, 5};
Line(11) = {17, 18};
Line(12) = {9, 19};
Line(13) = {19, 10};
Line(14) = {10, 11};
Line(15) = {11, 20};
Line(16) = {20, 12};
Line(17) = {12, 9};
Line(18) = {19, 20};
Line(19) = {13, 14};
Line(20) = {14, 15};
Line(21) = {15, 16};
Line(22) = {16, 13};
Line(23) = {1, 5};
Line(24) = {2, 6};
Line(25) = {3, 7};
Line(26) = {4, 8};
Line(27) = {5, 9};
Line(28) = {6, 10};
Line(29) = {7, 11};
Line(30) = {8, 12};
Line(31) = {9, 13};
Line(32) = {10, 14};
Line(33) = {11, 15};
Line(34) = {12, 16};
// the surfaces
Line Loop(35) = {4, 23, -10, -26};
Plane Surface(36) = {35};
Line Loop(37) = {1, 24, -6, -5, -23};
Plane Surface(38) = {37};
Line Loop(39) = {24, 7, -25, -2};
Plane Surface(40) = {39};
Line Loop(41) = {26, -9, -8, -25, 3};
Plane Surface(42) = {41};
Line Loop(43) = {10, 5, 11, 9};
Plane Surface(44) = {43};
Line Loop(45) = {10, 27, -17, -30};
Plane Surface(46) = {45};
Line Loop(47) = {6, 28, -13, -12, -27, 5};
Plane Surface(48) = {47};
Line Loop(49) = {28, 14, -29, -7};
Plane Surface(50) = {49};
Line Loop(51) = {30, -16, -15, -29, 8, 9};
Plane Surface(52) = {51};
Line Loop(53) = {18, -15, -14, -13};
Plane Surface(54) = {53};
Line Loop(55) = {17, 31, -22, -34};
Plane Surface(56) = {55};
Line Loop(57) = {12, 13, 32, -19, -31};
Plane Surface(58) = {57};
Line Loop(59) = {32, 20, -33, -14};
Plane Surface(60) = {59};
Line Loop(61) = {34, -21, -33, 15, 16};
Plane Surface(62) = {61};
