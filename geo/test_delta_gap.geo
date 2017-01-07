/**********************************************************************
 *
 * test_delta_gap.geo
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
ly = 0.1;
lz = 0.2;
Point(1) = {-lx,-ly/2.0,0.0,lc};
Point(2) = {0.0,-ly/2.0,0.0,lc};
Point(3) = {0.0,ly/2.0,0.0,lc};
Point(4) = {-lx,ly/2.0,0.0,lc};
Point(5) = {lx,-ly/2.0,0.0,lc};
Point(6) = {lx,ly/2.0,0.0,lc};

Line(1) = {6, 3};
Line(2) = {3, 2}; // delta_gap
Line(3) = {2, 5};
Line(4) = {5, 6};
Line(5) = {3, 4};
Line(6) = {4, 1};
Line(7) = {1, 2};
Line Loop(8) = {4, 1, 2, 3};
Plane Surface(9) = {8};
Line Loop(10) = {7, -2, 5, 6};
Plane Surface(11) = {10};
