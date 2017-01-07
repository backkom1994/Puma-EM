/**********************************************************************
 *
 * double_elliptic_cylinder.geo
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
factor = 0.5; // the multiplication factor for the -x side of the elliptic cylinder
ly = 0.03;
lz = 0.2;
Point(1) = {0,0,0,lc};
Point(2) = {0,ly,0,lc};
Point(3) = {lx,0,0,lc};
Point(4) = {-lx * factor,0,0,lc};
Point(5) = {0,-ly,0,lc};
Ellipse(1) = {2,1,3,3};
Ellipse(2) = {5,1,3,3};
Ellipse(3) = {5,1,4,4};
Ellipse(4) = {2,1,4,4};
Line Loop(5) = {1,-2,3,-4};
Plane Surface(6) = {5};
Extrude {0,0,lz/2.0} {
  Surface{6};
}
Extrude {0,0,-lz/2.0} {
  Surface{6};
}
