#######################################################################
##
## makefile.inc
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

CC:= g++
MPICC:= mpiCC
# safe flags
#CFLAGS:= -c -O2 -fPIC -pthread -march=native -mfpmath=both
# potentially faster flags
CFLAGS:= -c -O2 -fPIC -pthread -march=native -mfpmath=both -ffast-math
# debug flags
#CFLAGS:= -c -g -DBZ_DEBUG -Wall -fPIC
F77:= gfortran
G2C:= gfortran
F_FLAGS:= -c -O2 -fPIC -pthread -march=native -mfpmath=both -ffast-math

# we can use vendor-supplied lapack. If empty, puma-em lapack is used
#LIBLAPACK:= -L/usr/lib/ -llapack

#INCLUDE_PATH= -I/path/to/include
#LIB_SEARCH_PATH= -L/path/to/lib
