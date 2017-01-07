/**********************************************************************
 *
 * cube_crown.geo
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

lc = 0.1;
lx = 0.1;
w = 0.02; // width of crown
Point(1) = {-lx/2.0,-lx/2.0,0.0,lc};
Point(2) = {lx/2.0,-lx/2.0,0.0,lc};
Point(3) = {lx/2.0,lx/2.0,0.0,lc};
Point(4) = {-lx/2.0,lx/2.0,0.0,lc};
Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};
Line Loop(5) = {2,3,4,1};


Point(5) = {-(lx+w)/2.0,-(lx+w)/2.0,0.0,lc};
Point(6) = {(lx+w)/2.0,-(lx+w)/2.0,0.0,lc};
Point(7) = {(lx+w)/2.0,(lx+w)/2.0,0.0,lc};
Point(8) = {-(lx+w)/2.0,(lx+w)/2.0,0.0,lc};

Line(6) = {5, 6};
Line(7) = {6, 7};
Line(8) = {7, 8};
Line(9) = {8, 5};
Extrude {0, 0, lx/2.0} {
  Line{3, 4, 1, 2};
}
Extrude {0, 0, -lx/2.0} {
  Line{1, 2, 3, 4};
}
Line Loop(42) = {14, 18, 22, 10};
Plane Surface(43) = {42};
Line Loop(44) = {26, 30, 34, 38};
Plane Surface(45) = {44};
Line Loop(46) = {6, 7, 8, 9};
Plane Surface(47) = {46, 5};
