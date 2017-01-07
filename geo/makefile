#######################################################################
##
## makefile
##
## Copyright (C) 2016 Idesbald Van den Bosch
##
## This file is part of Puma-EM.
## 
## Puma-EM is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## Puma-EM is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Puma-EM.  If not, see <http://www.gnu.org/licenses/>.
##
## Suggestions/bugs : <vandenbosch.idesbald@gmail.com>
##
#######################################################################


OBJECTS_msh = parallelipiped.msh cube.msh strip.msh strip2.msh sphere.msh cubi.msh EMCC_ogive.msh EMCC_double-ogive.msh EMCC_cone-sphere.msh EMCC_cone-gap-sphere.msh EMCC_wedge-cylinder_plate.msh EMCC_plate-cylinder_plate.msh EMCC_wedge-plate-cylinder_plate.msh 

meshes: $(OBJECTS_msh)
	ls -al $(OBJECTS_msh)

parallelipiped.msh: parallelipiped.geo
	gmsh -2 parallelipiped.geo
cube.msh: cube.geo
	gmsh -2 cube.geo
strip.msh: strip.geo
	gmsh -2 strip.geo
strip2.msh: strip2.geo
	gmsh -2 strip2.geo
sphere.msh: sphere.geo
	gmsh -2 sphere.geo
cubi.msh: cubi.geo
	gmsh -2 cubi.geo
EMCC_ogive.msh: EMCC_ogive.geo
	gmsh -2 EMCC_ogive.geo
EMCC_double-ogive.msh: EMCC_double-ogive.geo
	gmsh -2 EMCC_double-ogive.geo
EMCC_cone-sphere.msh: EMCC_cone-sphere.geo
	gmsh -2 EMCC_cone-sphere.geo
EMCC_cone-gap-sphere.msh: EMCC_cone-gap-sphere.geo
	gmsh -2 EMCC_cone-gap-sphere.geo
EMCC_wedge-cylinder_plate.msh: EMCC_wedge-cylinder_plate.geo
	gmsh -2 EMCC_wedge-cylinder_plate.geo
EMCC_plate-cylinder_plate.msh: EMCC_plate-cylinder_plate.geo
	gmsh -2 EMCC_plate-cylinder_plate.geo
EMCC_wedge-plate-cylinder_plate.msh: EMCC_wedge-plate-cylinder_plate.geo
	gmsh -2 EMCC_wedge-plate-cylinder_plate.geo
clean: 
	rm -f *.msh* *~ *.cubes* *.pos* *.unv* *.txt*
