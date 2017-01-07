#######################################################################
##
## zbesh_interface.py
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

import os.path
from scipy import weave, special, Numeric
from Numeric import *
from weave import converters
from scipy.special import hankel2, jv

def zbesh_interface(z_cmplx, fnu):
	kode = 1
	M = 2
	N = 1
	h_scipy = hankel2(fnu, z_cmplx)
	h_cpp = zeros(1, Complex)
	nz = 0
	ierr = 0
	wrapping_code = """
	complex<double> HCPP;
	zbesh(z_cmplx, fnu, kode, M, N, HCPP, nz, ierr);
	h_cpp(0) = HCPP;"""
   	weave.inline(wrapping_code,
                ['z_cmplx', 'fnu', 'kode', 'M', 'N', 'h_cpp', 'nz', 'ierr'],
                type_converters = converters.blitz,
                include_dirs = ['.'],
                library_dirs = ['.'],
                libraries = ['g2c', 'm', 'AMOS'],
                headers = ['<iostream>','<complex>','"zbesh_interface.h"'],
                compiler = 'gcc')
	
	return h_scipy, h_cpp

if __name__=="__main__":
	z_cmplx = 9000 - 100.j
	fnu = 115.5
 	h_scipy, h_cpp = zbesh_interface(z_cmplx, fnu)
 	print h_scipy, h_cpp[0]
        
