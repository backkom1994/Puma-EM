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

PROGR_DIR_PATH =  $(PWD)/code

all:
	make install_open-mpi;
install_open-mpi:
	make libs;
	killall python; killall mpi_mlfma; rm -rf tmp*;
	./run.sh;
	killall python; killall mpi_mlfma; rm -rf tmp*;
install_lam-mpi:
	make libs;
	killall python; killall mpi_mlfma; rm -rf tmp*;
	./run.sh;
	killall python; killall mpi_mlfma; rm -rf tmp*;
package:
	make clean;
	python $(PROGR_DIR_PATH)/makePackage.py;
libs: 
	cd $(PROGR_DIR_PATH)/MoM; make libs; make communicateZnearBlocks; make mpi_mlfma; make mesh_functions_seb; make mesh_cubes; make distribute_Z_cubes; make RWGs_renumbering; make compute_Z_near; make compute_SAI_precond;
communicateZnearBlocks:
	cd $(PROGR_DIR_PATH)/MoM; make communicateZnearBlocks;
mpi_mlfma:
	cd $(PROGR_DIR_PATH)/MoM; make mpi_mlfma;
distribute_Z_cubes:
	cd $(PROGR_DIR_PATH)/MoM; make distribute_Z_cubes;
RWGs_renumbering:
	cd $(PROGR_DIR_PATH)/MoM; make RWGs_renumbering;
compute_Z_near:
	cd $(PROGR_DIR_PATH)/MoM; make compute_Z_near;
compute_SAI_precond:
	cd $(PROGR_DIR_PATH)/MoM; make compute_SAI_precond;
mesh_functions_seb:
	cd $(PROGR_DIR_PATH)/MoM; make mesh_functions_seb;
mesh_cubes:
	cd $(PROGR_DIR_PATH)/MoM; make mesh_cubes;
documentation:
	cd doc; make documentation;
clean: 
	rm -rf *~ *.pyc *.txt *.out *.tar *.gz *.tgz MPIcommand.sh GMSHcommand.sh __pycache__;
	cd run_in_out; rm -rf *~ *.pyc;
	cd $(PROGR_DIR_PATH); make clean; 
	cd geo; make clean;
	cd installScripts; make clean;
	cd doc; make clean;
	rm -rf Puma-EM;
	rm -rf tmp*;
	rm -rf result* simuDir*;
