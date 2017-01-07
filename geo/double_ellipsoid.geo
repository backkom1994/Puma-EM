/**********************************************************************
 *
 * double_ellipsoid.geo
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
lx = 0.1; // supposed to be the great axis
factor = 0.5; // the multiplication factor for the left side of the ellipsoid
ly = 0.02; // the target becomes a circular "cushion" if ly>lx
Point(1) = {0,0,0,lc};
Point(2) = {0,ly,0,lc};
Point(3) = {lx,0,0,lc};
Point(4) = {-lx * factor,0,0,lc};
Ellipse(1) = {2,1,3,3};
Ellipse(2) = {2,1,4,4};
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{1};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{3};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{6};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{9};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{12};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{15};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{18};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{21};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{2};
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
