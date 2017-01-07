/**********************************************************************
 *
 * pyramid_reflector.geo
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

lc = 0.000986159401316;
lx = 0.42;
ly = 0.42;
lz = 0.42;
Point(1) = {0,0,0,lc};
Point(2) = {lx,0,0,lc};
Point(3) = {0,ly,0,lc};
Point(4) = {0,0,lz,lc};
Point(5) = {-lx,0,0,lc};
Point(6) = {0,-ly,0,lc};
Line(1) = {1, 6};
Line(2) = {1, 2};
Line(3) = {1, 3};
Line(4) = {1, 5};
Line(5) = {4, 1};
Line(6) = {4, 6};
Line(7) = {4, 2};
Line(8) = {4, 3};
Line(9) = {4, 5};
Line(10) = {5, 6};
Line(11) = {6, 2};
Line(12) = {2, 3};
Line(13) = {3, 5};
Line Loop(14) = {4, 10, -1};
Plane Surface(15) = {14};
Line Loop(16) = {1, 11, -2};
Plane Surface(17) = {16};
Line Loop(18) = {2, 12, -3};
Plane Surface(19) = {18};
Line Loop(20) = {3, 13, -4};
Plane Surface(21) = {20};
Line Loop(22) = {5, 1, -6};
Plane Surface(23) = {22};
Line Loop(24) = {5, 2, -7};
Plane Surface(25) = {24};
Line Loop(26) = {5, 3, -8};
Plane Surface(27) = {26};
Line Loop(28) = {5, 4, -9};
Plane Surface(29) = {28};
