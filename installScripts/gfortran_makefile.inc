#######################################################################
##
## gfortran_makefile.inc
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
CFLAGS:= -c -O2 -fPIC -ffast-math
#CFLAGS:= -c -O2 -fPIC -ffast-math -ftree-vectorize -msse2
#CFLAGS:= -c -g -DBZ_DEBUG -fPIC
F77:= gfortran
G2C:= gfortran
F_FLAGS:= -c -O3 -funroll-loops -fPIC -pthread

#INCLUDE_PATH= -I/path/to/include
#LIB_SEARCH_PATH= -L/path/to/lib

# Do we use the lapack library furnished with the code?
# It is usually slower than vendor-supplied lapack, but
# it always works (i.e. no compilation or linking problems).
USE_VENDOR_LAPACK = 0
ifeq ($(USE_VENDOR_LAPACK), 1)
  # indicate the location and name of vendor-supplied LAPACK
  LIBLAPACK_PATH = /usr/lib/lapack/
  LIBLAPACK = lapack
else
  # default LAPACK from Puma-EM
  LIBLAPACK_PATH = ./lapack/
  LIBLAPACK = LOCAL_LAPACK
endif

