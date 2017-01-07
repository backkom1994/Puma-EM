/**********************************************************************
 *
 * cone.geo
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

lc = 0.2;
lx = 1.0;
lz = 1.0;
Point(1) = {0,0,0,lc};
Point(2) = {-lx/2,0,0,lc};
Point(3) = {0,0,lz,lc};

Line(1) = {2,3};
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{1};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{2};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{5};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{8};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{11};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{14};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{17};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{20};
}
Line Loop(26) = {9,12,15,18,21,24,3,6};
Plane Surface(27) = {26};
