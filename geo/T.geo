/**********************************************************************
 *
 * T.geo
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
lx = 0.2;
ly = 0.1;
lz = 0.1;
Point(1) = {-lx/2,-ly/2,0,lc};
Point(2) = {lx/2,-ly/2,0,lc};
Point(3) = {lx/2,ly/2,0,lc};
Point(4) = {-lx/2,ly/2,0,lc};
Point(5) = {0,-ly/2,0,lc};
Point(6) = {0,ly/2,0,lc};
Point(7) = {0,ly/2,lz,lc};
Point(8) = {0,-ly/2,lz,lc};
Line(1) = {4,6};
Line(2) = {4,1};
Line(3) = {1,5};
Line(4) = {5,6};
Line(5) = {6,3};
Line(6) = {3,2};
Line(7) = {2,5};
Line(8) = {5,8};
Line(9) = {8,7};
Line(10) = {7,6};
Line Loop(11) = {9,10,-4,8};
Plane Surface(12) = {11};
Line Loop(13) = {1,-4,-3,-2};
Plane Surface(14) = {13};
Line Loop(15) = {5,6,7,4};
Plane Surface(16) = {15};
