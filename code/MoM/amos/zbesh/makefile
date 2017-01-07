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

include ../../../../makefile.inc

OBJECTS_lib = d1mach.o zbesh_interface.o zbinu.o zbunk.o zmlt.o zseri.o zuchk.o zuni2.o zunk2.o dgamln.o xerror.o zacon.o zbesh.o zbknu.o zdiv.o zlog.o zrati.o zshch.o zunhj.o zunik.o zuoik.o i1mach.o zabs.o zairy.o zbesj.o zbuni.o zexp.o zmlri.o zs1s2.o zsqrt.o zuni1.o zunk1.o zwrsk.o zacai.o zasyi.o zkscl.o 

main: libAMOS


libAMOS: $(OBJECTS_lib)
	ar -r libAMOS.a $(OBJECTS_lib)

%.o : %.cpp
	$(CC) $(INCLUDE_PATH) $(CFLAGS) $< -o $@

%.o : %.f
	$(F77) $(F_FLAGS) $< -o $@

clean: 
	rm -f *.o libAMOS.a *~ main
