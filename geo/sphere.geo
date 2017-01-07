/**********************************************************************
 *
 * sphere.geo
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

lc = 0.05;
lx = 0.051;
x_center = 0;
y_center = 0;
z_center = 0;

Point(1) = {x_center, y_center, z_center, lc};
Point(2) = {x_center - lx, y_center, z_center, lc};

Point(3) = {x_center,y_center-lx,z_center,lc};
Point(4) = {x_center-lx*Sqrt(2)/2,y_center-lx*Sqrt(2)/2,z_center,lc};
Point(5) = {x_center+lx*Sqrt(2)/2,y_center-lx * Sqrt(2)/2,z_center,lc};
Point(6) = {x_center+lx,y_center,z_center,lc};

// the basis circles
Circle(1) = {2,1,4};
Circle(2) = {4,1,3};


Circle(3) = {3,1,5};
Circle(4) = {5,1,6};
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{1};
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
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{23};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{2};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{29};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{33};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{37};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{41};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{45};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{49};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{53};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{3};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{61};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{65};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{69};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{73};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{77};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{81};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{85};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{4};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{93};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{96};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{99};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{102};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{105};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{108};
}
Extrude {{1,0,0}, {0,0,0}, Pi/4} {
  Line{111};
}
