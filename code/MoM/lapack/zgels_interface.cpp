/**********************************************************************
 *
 * zgels_interface.cpp
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
#include <blitz/array.h>

/*%+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*% interface to the actual (fortran) ZBESH routine
%*/

using namespace std;

extern "C" {
  //SUBROUTINE ZGELS( TRANS, M, N, NRHS, A, LDA, B, LDB, WORK, LWORK, INFO )
  void zgels_(char *, int *, int *, int *, std::complex<double> *, int *, std::complex<double> *, int *, std::complex<double> *, int *, int *);
}

void zgels(char & trans, int & m, int & n, int & nrhs, blitz::Array<std::complex<double>, 2> & A, int & lda, blitz::Array<std::complex<double>, 2> & B, int & ldb, blitz::Array<std::complex<double>, 1> & work, int & lwork, int & info) {
  zgels_(&trans, &m, &n, &nrhs, A.data(), &lda, B.data(), &ldb, work.data(), &lwork, &info);
}

void zgels2(char & trans, int & m, int & n, int & nrhs, blitz::Array<std::complex<double>, 1> & A, int & lda, blitz::Array<std::complex<double>, 1> & B, int & ldb, blitz::Array<std::complex<double>, 1> & work, int & lwork, int & info) {
  zgels_(&trans, &m, &n, &nrhs, A.data(), &lda, B.data(), &ldb, work.data(), &lwork, &info);
}
