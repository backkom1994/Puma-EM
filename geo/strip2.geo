/**********************************************************************
 *
 * strip2.geo
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
lx = 0.01;
ly = 0.01;
bx = lx;
by = ly;
center = 0.11;
Point(1) = {-center-lx,ly,0.0,lc};
Point(2) = {-center+lx,ly,0.0,lc};
Point(3) = {-center+lx,-ly,0.0,lc};
Point(4) = {-center-lx,-ly,0.0,lc};
Point(5) = {center-bx,-by,0.0,lc};
Point(6) = {center+bx,-by,0.0,lc};
Point(7) = {center+bx,by,0.0,lc};
Point(8) = {center-bx,by,0.0,lc};
Line(1) = {4,3};
Line(2) = {3,2};
Line(3) = {2,1};
Line(4) = {1,4};
Line(5) = {5,6};
Line(6) = {6,7};
Line(7) = {7,8};
Line(8) = {8,5};
Line Loop(9) = {2,3,4,1};
Plane Surface(10) = {9};
Line Loop(11) = {5,6,7,8};
Plane Surface(12) = {11};
