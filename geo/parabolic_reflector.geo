/**********************************************************************
 *
 * parabolic_reflector.geo
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

lc = 0.025; // characteristic length
D = 1.0; // max diameter of paraboloid
d = 0.2; // depth of paraboloid
f = D^2/(16.0 * d); // the focal point

Function Parabola
  y[0] = -D/2.0;
  For i In {1:N-1}
    y[i] = y[i-1] + D/(N-1.0);
  EndFor
  For i In {0:N-1}
    z[i] = y[i]^2/(4.0 * f);
    PointNumber[i] = newp;
    Point(PointNumber[i]) = {0.0, y[i], z[i], lc};
  EndFor
Return

N = 11;
Call Parabola;

CatmullRom(1) = {1,2,3,4};
CatmullRom(2) = {4,5,6,7,8};
CatmullRom(3) = {8,9,10,11};
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{1};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{4};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{8};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{3};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{16};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{20};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{24};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{12};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{2};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{36};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{40};
}
Extrude {{0,0,1}, {0,0,0}, Pi/4} {
  Line{44};
}
