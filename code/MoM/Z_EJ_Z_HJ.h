/**********************************************************************
 *
 * Z_EJ_Z_HJ.h
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

#ifndef Z_EJ_Z_HJ_H
#define Z_EJ_Z_HJ_H
using namespace std;

void Z_CFIE_J_computation (blitz::Array<std::complex<double>, 2>& Z_CFIE_J,
                           blitz::Array<std::complex<double>, 2>& Z_CFIE_M,
                           const blitz::Array<std::complex<double>, 1>& CFIE,
                           const double signSurfObs,
                           const double signSurfSrc,
                           const blitz::Array<int, 1>& numbers_RWG_test,
                           const blitz::Array<int, 1>& numbers_RWG_src,
                           const blitz::Array<int, 1>& testRWGNumber_CFIE_OK,
                           const blitz::Array<int, 1>& srcRWGNumber_CURRENT_M_OK,
                           const blitz::Array<int, 2>& RWGNumber_signedTriangles,
                           const blitz::Array<int, 2>& RWGNumber_nodes,
                           const blitz::Array<double, 2>& nodesCoord,
                           const double w,
                           const std::complex<double>& eps_r,
                           const std::complex<double>& mu_r,
                           const int TDS_APPROX, // do we compute for a surface impedance?
                           const std::complex<double>& Z_s, // surface impedance
                           const int FULL_PRECISION);

void Z_EH_J_computation (blitz::Array<std::complex<double>, 2>& Z_tE_J,
                         blitz::Array<std::complex<double>, 2>& Z_nE_J,
                         blitz::Array<std::complex<double>, 2>& Z_tH_J,
                         blitz::Array<std::complex<double>, 2>& Z_nH_J,
                         const blitz::Array<double, 1>& TENETHNH,
                         const double signSurfObs,
                         const double signSurfSrc,
                         const blitz::Array<int, 1>& numbers_RWG_test,
                         const blitz::Array<int, 1>& numbers_RWG_src,
                         const blitz::Array<int, 1>& testRWGNumber_CFIE_OK,
                         const blitz::Array<int, 2>& RWGNumber_signedTriangles,
                         const blitz::Array<int, 2>& RWGNumber_nodes,
                         const blitz::Array<double, 2>& nodesCoord,
                         const double w,
                         const std::complex<double>& eps_r,
                         const std::complex<double>& mu_r,
                         const int TDS_APPROX, // do we compute for a surface impedance?
                         const std::complex<double>& Z_s, // surface impedance
                         const int FULL_PRECISION);


//void Z_EJ_Z_HJ_ML (Array<complex<double>,2>& Z_TE_J, Array<complex<double>,2>& Z_NE_J, Array<complex<double>,2>& Z_TH_J, Array<complex<double>,2>& Z_NH_J, const mesh & MESH, const KA_grid & KA_tab, const Kphi_grid & Kphi_tab, const G_HJ_grid & G_HJ_tab, const layers_constants & LC);

#endif
