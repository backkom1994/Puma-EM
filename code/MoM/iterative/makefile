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

include ../../../makefile.inc

ZSOURCESF = ZGMRESREVCOM.f zaxpy.f zrotg.f zdotc.f dcabs1.f ztrsv.f xerbla.f zgemv.f zscal.f dznrm2.f ZSTOPTEST2.f zcopy.f lsame.f 

OBJECTS_lib = iterative.o

iterative: $(ZOURCESF)
	#f2py2.4 $(ZSOURCESF) -m zgmresrevcom -h zgmresrevcom.pyf --overwrite-signature
	f2py2.4 -c zgmresrevcom.pyf $(ZSOURCESF)


libITERATIVE: $(OBJECTS_lib)
	ar -r libITERATIVE.a $(OBJECTS_lib)
iterative.o: iterative.cpp
	$(MPICC) $(INCLUDE_PATH) $(CFLAGS) iterative.cpp

clean: 
	rm -f *.o libITERATIVE.a *~
