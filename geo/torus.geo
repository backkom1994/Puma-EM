/**********************************************************************
 *
 * torus.geo
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

lc = 0.005;
R = 0.1;
r = 0.03;
Point(1) = {0,0,0,lc};
Point(2) = {R,0,0,lc};
Point(3) = {R-r,0,0,lc};
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{3};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{4};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{5};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{6};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{7};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{8};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{9};
}
Extrude {{0,1,0}, {R,0,0}, Pi/4} {
  Point{10};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{2,1,8,7,6,5,3,4};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{9,13,17,21,25,29,33,37};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{41,65,69,61,57,53,49,45};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{97,93,89,85,81,77,73,101};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{129,125,121,117,113,109,105,133};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{141,145,149,153,157,161,165,137};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{197,169,173,177,181,185,189,193};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{201,229,225,221,217,213,209,205};
}
