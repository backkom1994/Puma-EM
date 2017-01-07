/**********************************************************************
 *
 * cone-sphere.geo
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

lc = 0.149896229;
lx = 2.38567257962;
R = lx;
Point(1) = {0,0,0,lc};
Point(2) = {-R,0,0,lc};
Point(3) = {0,R,0,lc};
Point(4) = {lx,0,0,lc};
Circle(1) = {3,1,2};
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{1};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{2};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{5};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{8};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{11};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{14};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{17};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{20};
}
Line(26) = {4,3};
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{26};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{27};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{30};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{33};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{36};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{39};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{42};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{45};
}
