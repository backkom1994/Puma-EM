/**********************************************************************
 *
 * ztrsm_interface.cpp
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
*% interface to the actual (fortran) ZTRSM routine
%*/

using namespace std;

const complex<double> I (0.0, 1.0);

extern "C" {
  //SUBROUTINE ZTRSM( SIDE, UPLO, TRANSA, DIAG, M, N, ALPHA, A, LDA, B, LDB )
  void ztrsm_(char *, char *, char *, char *, int *, int *, complex<double> *, complex<double> *, int *, complex<double> *, int *);
}

void ztrsm(char & side, char & uplo, char & transa, char & diag, int & m, int & n, complex<double> & alpha, blitz::Array<std::complex<double>, 2> & A, int & lda, blitz::Array<std::complex<double>, 2> & B, int & ldb) {
  ztrsm_(&side, &uplo, &transa, &diag, &m, &n, &alpha, A.data(), &lda, B.data(), &ldb);
}
