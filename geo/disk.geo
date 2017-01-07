/**********************************************************************
 *
 * disk.geo
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
lc = 0.02398339664;
lx = 0.151;
lz = 0.051;

// and now the geometry
Point(1) = {0, 0, 0, lc};
Point(2) = {-lx, 0, 0, lc};
Point(3) = {0, -lx, 0, lc};
Point(4) = {lx, 0, 0, lc};
Point(5) = {0, lx, 0, lc};
Circle(1) = {2,1,3};
Circle(2) = {3,1,4};
Circle(3) = {4,1,5};
Circle(4) = {5,1,2};


Line(5) = {1, 4};
Line(6) = {1, 3};
Line(7) = {1, 2};
Line(8) = {1, 5};
Line Loop(9) = {5, -2, -6};
Plane Surface(10) = {9};
Line Loop(11) = {6, -1, -7};
Plane Surface(12) = {11};
Line Loop(13) = {7, -4, -8};
Plane Surface(14) = {13};
Line Loop(15) = {8, -3, -5};
Plane Surface(16) = {15};
