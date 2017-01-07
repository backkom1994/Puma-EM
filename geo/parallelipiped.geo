/**********************************************************************
 *
 * parallelipiped.geo
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
lx = 0.075;
ly = 0.01;
lz = 0.01;
Point(1) = {-lx/2.0,-ly/2.0,-lz/2.0,lc};
Point(2) = {lx/2.0,-ly/2.0,-lz/2.0,lc};
Point(3) = {lx/2.0,ly/2.0,-lz/2.0,lc};
Point(4) = {-lx/2.0,ly/2.0,-lz/2.0,lc};
Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};
Line Loop(5) = {2,3,4,1};
Plane Surface(6) = {5};
Extrude Surface {6, {0.0,0.0,lz}};
