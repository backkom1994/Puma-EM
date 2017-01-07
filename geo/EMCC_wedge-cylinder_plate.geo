/**********************************************************************
 *
 * EMCC_wedge-cylinder_plate.geo
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

lc = 0.0155397293179;
lx = 0.141411536792;
offset = 2.0 * lx * Cos(30.0/180.0 * Pi);

Point(1) = {-offset,0,0,lc};
Point(2) = {-offset,-lx,0,lc};
Point(3) = {-offset-lx,0,0,lc};
Point(4) = {-offset,lx,0,lc};
Point(5) = {0,0,0,lc};
Circle(1) = {2,1,3};
Circle(2) = {3,1,4};
Line(3) = {5,4};
Line(4) = {5,2};
Line Loop(5) = {3,-2,-1,-4};
Plane Surface(6) = {5};
