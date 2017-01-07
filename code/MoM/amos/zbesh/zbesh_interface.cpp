/**********************************************************************
 *
 * zbesh_interface.cpp
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

#include <iostream>
#include <complex>
//#include <blitz/array.h>

/*%+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*% interface to the actual (fortran) ZBESH routine
%*/

using namespace std;

extern "C" {
  //SUBROUTINE ZBESH(ZR, ZI, FNU, KODE, M, N, CYR, CYI, NZ, IERR)
  void zbesh_(double *, double *, double *, int *, int *, int *, double *, double *, int *, int *);
}

void zbesh(std::complex<double>& z_cmplx, double & fnu, int & kode, int & M, int & N, std::complex<double>& h, int & nz, int & ierr) {

  double zr = real(z_cmplx), zi = imag(z_cmplx), cyr, cyi;
  zbesh_(&zr, &zi, &fnu, &kode, &M, &N, &cyr, &cyi, &nz, &ierr);
  if (ierr>0) {
    if ((zr>0.0) || (zi>0.0)) cout << "Error in computation of zbesh. Error code: " << ierr << endl;
  }
  h = std::complex<double>(cyr, cyi);
}
