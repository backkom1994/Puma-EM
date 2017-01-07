/**********************************************************************
 *
 * corner_reflector.geo
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

lc = 0.01;
lx = 0.1;
ly = 0.1;
lz = 0.1;
Point(1) = {0,0,0,lc};
Point(2) = {lx,0,0,lc};
Point(3) = {0,ly,0,lc};
Point(4) = {0,0,lz,lc};
Line(1) = {4,1};
Line(2) = {1,2};
Line(3) = {1,3};
Line(4) = {3,4};
Line(5) = {4,2};
Line(6) = {2,3};
Line Loop(7) = {5,-2,-1};
Plane Surface(8) = {7};
Line Loop(9) = {1,3,4};
Plane Surface(10) = {9};
Line Loop(11) = {3,-6,-2};
Plane Surface(12) = {11};
