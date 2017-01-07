/**********************************************************************
 *
 * triangle_int_FS.cpp
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

using namespace std;

const std::complex<double> I (0.0, 1.0);
const double RSMALL = 1.0e-6; // A. Francavilla (2013)

#include "GK_triangle.h"
#include "GL.h"
#include "triangle_int.h"
#include "dictionary.h"

/****************************************************************************/
/********************************* Triangle *********************************/
/****************************************************************************/

Triangle::Triangle(const double r0[],
                   const double r1[],
                   const double r2[],
                   const int tr_number)
{
  number = tr_number;
  for (int i=0 ; i<3 ; ++i) {
    r_nodes[0][i] = r0[i];
    r_nodes[1][i] = r1[i];
    r_nodes[2][i] = r2[i];
  }
  // gravity center
  double r2_r1[3], r3_r1[3], r3_r2[3], r_grav_r1[3], r_grav_r2[3], r_grav_r3[3];
  for (int i=0 ; i<3 ; ++i) {
    r_grav[i] = (r_nodes[0][i] + r_nodes[1][i] + r_nodes[2][i])/3.0;
    r2_r1[i] = r_nodes[1][i] - r_nodes[0][i];
    r3_r2[i] = r_nodes[2][i] - r_nodes[1][i];
    r3_r1[i] = r_nodes[2][i] - r_nodes[0][i];
  }

  // T.n_hat and T.A construction
  // n_hat is the result of a cross-product
  cross3D(n_hat, r2_r1, r3_r1);
  // n_hat[0] = r2_r1[1] * r3_r1[2] - r2_r1[2] * r3_r1[1];
  // n_hat[1] = r2_r1[2] * r3_r1[0] - r2_r1[0] * r3_r1[2];
  // n_hat[2] = r2_r1[0] * r3_r1[1] - r2_r1[1] * r3_r1[0];
 
  A = sqrt(n_hat[0]*n_hat[0] + n_hat[1]*n_hat[1] + n_hat[2]*n_hat[2])/2.0;
  for (int i=0 ; i<3 ; ++i) n_hat[i] *= 1.0/(2.0*A);

  // T.s_i_hat construction
  double r2_r1_norm = sqrt(r2_r1[0]*r2_r1[0] + r2_r1[1]*r2_r1[1] + r2_r1[2]*r2_r1[2]);
  double r3_r2_norm = sqrt(r3_r2[0]*r3_r2[0] + r3_r2[1]*r3_r2[1] + r3_r2[2]*r3_r2[2]);
  double r3_r1_norm = sqrt(r3_r1[0]*r3_r1[0] + r3_r1[1]*r3_r1[1] + r3_r1[2]*r3_r1[2]);
  for (int i=0 ; i<3 ; ++i) {
    s_i_hat[0][i] = r2_r1[i]/r2_r1_norm;
    s_i_hat[1][i] = r3_r2[i]/r3_r2_norm;
    s_i_hat[2][i] = -1.0*r3_r1[i]/r3_r1_norm;
  }
  // T.m_i_hat construction
  cross3D(m_i_hat[0], s_i_hat[0], n_hat);
  cross3D(m_i_hat[1], s_i_hat[1], n_hat);
  cross3D(m_i_hat[2], s_i_hat[2], n_hat);
  // R_max computation. R_max is the greatest |r_grav - ri|, i=0..2  
  for (int i=0 ; i<3 ; ++i) {
    r_grav_r1[i] = r_grav[i] - r_nodes[0][i];
    r_grav_r2[i] = r_grav[i] - r_nodes[1][i];
    r_grav_r3[i] = r_grav[i] - r_nodes[2][i];
  }
  double R1 = r_grav_r1[0] * r_grav_r1[0] + r_grav_r1[1] * r_grav_r1[1] + r_grav_r1[2] * r_grav_r1[2];
  double R2 = r_grav_r2[0] * r_grav_r2[0] + r_grav_r2[1] * r_grav_r2[1] + r_grav_r2[2] * r_grav_r2[2];
  double R3 = r_grav_r3[0] * r_grav_r3[0] + r_grav_r3[1] * r_grav_r3[1] + r_grav_r3[2] * r_grav_r3[2];
  R_max = ( R1 > R2 ) ? R1 : R2;
  R_max = ( R_max > R3) ? sqrt(R_max) : sqrt(R3);
}

void Triangle::copyTriangle (const Triangle& triangleToCopy) // copy member function
{
  number = triangleToCopy.number;
  for (int i=0 ; i<3 ; i++) {
    for (int j=0 ; j<3 ; j++) {
      r_nodes[i][j] = triangleToCopy.r_nodes[i][j];
      m_i_hat[i][j] = triangleToCopy.m_i_hat[i][j];
      s_i_hat[i][j] = triangleToCopy.s_i_hat[i][j];
    }
    n_hat[i] = triangleToCopy.n_hat[i];
    r_grav[i] = triangleToCopy.r_grav[i];
  }
  A = triangleToCopy.A;
  R_max = triangleToCopy.R_max;
  RWGIndexes.resize(triangleToCopy.RWGIndexes.size());
  RWGIndexes = triangleToCopy.RWGIndexes;
  signInRWG.resize(triangleToCopy.signInRWG.size());
  signInRWG = triangleToCopy.signInRWG;
  indexesInRWGs.resize(triangleToCopy.indexesInRWGs.size());
  indexesInRWGs = triangleToCopy.indexesInRWGs;
}

Triangle::Triangle(const Triangle& triangleToCopy) // copy constructor
{
  copyTriangle(triangleToCopy);
}

Triangle& Triangle::operator=(const Triangle& triangleToCopy) { // copy assignment
  copyTriangle(triangleToCopy);
  return *this;
}

Triangle::~Triangle() {
  RWGIndexes.clear();
  indexesInRWGs.clear();
  signInRWG.clear();
}

//! this function is useful in the MoM
void constructVectorTriangles(std::vector<Triangle>& triangles,
                              const std::vector<RWG>& vectorRWGs,
                              const std::vector<Dictionary<int, int> >& TriangleToRWG)
{
  int index = 0;
  for (unsigned int i=0 ; i<TriangleToRWG.size() ; i++) {
    const int tr_number = TriangleToRWG[i].getKey();
    const int RWG_index = TriangleToRWG[i].getVal();
    int indexInRWG = (tr_number == vectorRWGs[RWG_index].triangleNumbers[0]) ? 0 : 1;
    double sign = static_cast<double>(vectorRWGs[RWG_index].triangleSigns[indexInRWG]);
    if (triangles.size()==0) { // initialisation of the vector of triangles
      if (indexInRWG==0) triangles.push_back(Triangle(vectorRWGs[RWG_index].vertexesCoord_0,
                                                      vectorRWGs[RWG_index].vertexesCoord_1,
                                                      vectorRWGs[RWG_index].vertexesCoord_2,
                                                      tr_number));
      else triangles.push_back(Triangle(vectorRWGs[RWG_index].vertexesCoord_2,
                                        vectorRWGs[RWG_index].vertexesCoord_1,
                                        vectorRWGs[RWG_index].vertexesCoord_3,
                                        tr_number));
    }
    else if (tr_number!=triangles[index].number) { // we create a new triangle
      index++;
      if (indexInRWG==0) triangles.push_back(Triangle(vectorRWGs[RWG_index].vertexesCoord_0,
                                                      vectorRWGs[RWG_index].vertexesCoord_1,
                                                      vectorRWGs[RWG_index].vertexesCoord_2,
                                                      tr_number));
      else triangles.push_back(Triangle(vectorRWGs[RWG_index].vertexesCoord_2,
                                        vectorRWGs[RWG_index].vertexesCoord_1,
                                        vectorRWGs[RWG_index].vertexesCoord_3,
                                        tr_number));
    }
    // we have to actualise RWGIndexes, signInRWG and indexesInRWGs
    triangles[index].RWGIndexes.push_back(RWG_index);
    triangles[index].signInRWG.push_back(sign);
    triangles[index].indexesInRWGs.push_back(indexInRWG);
  }
  std::vector<Triangle>(triangles).swap(triangles);
}

/****************************************************************************/
/****************************** RWG_function ********************************/
/****************************************************************************/

//! Half_RWG_function class
RWG::RWG(const int RWG_number,
         const int triangle_numbers[], // dim 2
         const int triangle_signs[],
         const double r0[], // dim 3
         const double r1[],
         const double r2[],
         const double r3[])
{
  number = RWG_number;
  for (int i=0 ; i<2 ; ++i) {
    triangleNumbers[i] = triangle_numbers[i];
    triangleSigns[i] = triangle_signs[i];
  }
  for (int j=0 ; j<3 ; ++j) {
    vertexesCoord_0[j] = r0[j];
    vertexesCoord_1[j] = r1[j];
    vertexesCoord_2[j] = r2[j];
    vertexesCoord_3[j] = r3[j];
  }
  double r1_r2[3];
  for (int j=0 ; j<3 ; ++j) r1_r2[j] = vertexesCoord_1[j] - vertexesCoord_2[j];
  length = std::sqrt(r1_r2[0]*r1_r2[0] + r1_r2[1]*r1_r2[1] + r1_r2[2]*r1_r2[2]);
}

void RWG::copyRWG(const RWG& RWGToCopy)
{
  number = RWGToCopy.number;
  for (int i=0 ; i<2 ; ++i) {
    triangleNumbers[i] = RWGToCopy.triangleNumbers[i];
    triangleSigns[i] = RWGToCopy.triangleSigns[i];
  }
  for (int j=0 ; j<3 ; ++j) {
    vertexesCoord_0[j] = RWGToCopy.vertexesCoord_0[j];
    vertexesCoord_1[j] = RWGToCopy.vertexesCoord_1[j];
    vertexesCoord_2[j] = RWGToCopy.vertexesCoord_2[j];
    vertexesCoord_3[j] = RWGToCopy.vertexesCoord_3[j];
  }
  length = RWGToCopy.length;
}

RWG::RWG(const RWG& RWGToCopy) // copy constructor
{
  copyRWG(RWGToCopy);
}

RWG& RWG::operator=(const RWG& RWGToCopy) { // copy assignment
  copyRWG(RWGToCopy);
  return *this;
}

/****************************************************************************/
/***************** various integration functions ****************************/
/****************************************************************************/

void IT_fm_fn (double & IT_r_square,
               double IT_r[], // dim 3
               const Triangle & T)
{
  IT_r_square = 0.0;
  for (int i=0 ; i<3 ; ++i) {
    IT_r[i] = T.A * (T.r_nodes[0][i] + T.r_nodes[1][i] + T.r_nodes[2][i])/3.0;
    IT_r_square += T.r_nodes[0][i] * T.r_nodes[0][i] + T.r_nodes[1][i] * T.r_nodes[1][i] + T.r_nodes[2][i] * T.r_nodes[2][i] + T.r_nodes[0][i] * T.r_nodes[1][i] + T.r_nodes[0][i] * T.r_nodes[2][i] + T.r_nodes[1][i] * T.r_nodes[2][i];
  }
  IT_r_square *= T.A/6.0;
}

void IT_singularities (double & IT_1_R,
                       double & IT_R,
                       double IT_1_R_rprime_r[], // dim 3
                       double IT_R_rprime_r[], // dim 3
                       double IT_grad_1_R[], // dim 3
                       const double r[],
                       const Triangle & T)
/**
 * notations are taken from: Pasi Yla-Oijala and Matti Taskinen, "Calculation of CFIE Impedance Matrix
 * Elements With RWG and n x RWG Functions", IEEE Transactions on Antennas and Propagation, Vol. 51, 
 * No. 8, August 2003, pp. 1837--1846. 
 */
{
  const double w0 = ((r[0]-T.r_nodes[0][0]) * T.n_hat[0] + (r[1]-T.r_nodes[0][1]) * T.n_hat[1] + (r[2]-T.r_nodes[0][2]) * T.n_hat[2]); 
  const double abs_w0 = abs(w0), sign_w0 = (abs_w0<RSMALL) ? 0.0 : w0/abs_w0;
  const double third(1.0/3.0);
  double I_L_minus_1__i, I_L_plus_1__i, I_L_plus_3__i, beta_i, K_1_minus_1__i, K_1_plus_1__i;
  
  // double K_2_minus_1__i[3], K_2_plus_1__i[3], K_3_minus_1__i[3], K_3_plus_1__i[3];

  IT_1_R = 0.0;
  IT_R = 0.0;
  for (int i=0 ; i<3 ; ++i) {
    IT_1_R_rprime_r[i] = 0.0;
    IT_R_rprime_r[i] = 0.0;
    IT_grad_1_R[i] = 0.0;
  }

  for (int i=0 ; i<3 ; ++i) {
    const double * r_plus__i, * r_minus__i, * m_i_hat, * s_i_hat;
    r_plus__i = T.r_nodes[(i+1)%3]; // (i+1)%3 : 1 if i=0, 2 if i=1, 0 if i=3
    r_minus__i = T.r_nodes[i];
    m_i_hat = T.m_i_hat[i];
    s_i_hat = T.s_i_hat[i];
    // s_plus__i, s_minus__i computation
    const double r_plus__i_r[3] = {r_plus__i[0]-r[0], r_plus__i[1]-r[1], r_plus__i[2]-r[2]}; 
    const double r_minus__i_r[3] = {r_minus__i[0]-r[0], r_minus__i[1]-r[1], r_minus__i[2]-r[2]};
    const double s_plus__i = r_plus__i_r[0]*s_i_hat[0] + r_plus__i_r[1]*s_i_hat[1] + r_plus__i_r[2]*s_i_hat[2]; 
    const double s_minus__i = r_minus__i_r[0]*s_i_hat[0] + r_minus__i_r[1]*s_i_hat[1] + r_minus__i_r[2]*s_i_hat[2];
    
    // t_i_0 : distance from r (projected on plane of triangle) to edge
    double t_i_0 = r_plus__i_r[0]*m_i_hat[0] + r_plus__i_r[1]*m_i_hat[1] + r_plus__i_r[2]*m_i_hat[2];

    // R_plus__i, R_minus__i, R_i_0 computation
    const double R_plus__i = sqrt(r_plus__i_r[0]*r_plus__i_r[0] + r_plus__i_r[1]*r_plus__i_r[1] + r_plus__i_r[2]*r_plus__i_r[2]);
    const double R_minus__i = sqrt(r_minus__i_r[0]*r_minus__i_r[0] + r_minus__i_r[1]*r_minus__i_r[1] + r_minus__i_r[2]*r_minus__i_r[2]);
    const double R_i_0_square = t_i_0*t_i_0 + w0*w0;

    // different cases according to the position vector
    if (abs_w0>RSMALL) {
      if (abs(t_i_0) > RSMALL) beta_i = atan(t_i_0*s_plus__i/(R_i_0_square + abs_w0*R_plus__i)) - atan(t_i_0*s_minus__i/(R_i_0_square + abs_w0*R_minus__i));
      else t_i_0 = beta_i = 0.0;
      I_L_minus_1__i = log((R_plus__i+s_plus__i)/(R_minus__i+s_minus__i));
      I_L_plus_1__i = 0.5 * (s_plus__i*R_plus__i - s_minus__i*R_minus__i + R_i_0_square*I_L_minus_1__i);
    }
    else {
      beta_i = 0.0;
      if (abs(t_i_0) > RSMALL) {
        I_L_minus_1__i = log((R_plus__i+s_plus__i)/(R_minus__i+s_minus__i));
        I_L_plus_1__i = 0.5 * (s_plus__i*R_plus__i - s_minus__i*R_minus__i + R_i_0_square*I_L_minus_1__i);
      }
      else {
        t_i_0 = 0.0;
        // the following line is derived with the help of HOSPITAL rule for the non-singular part
        I_L_minus_1__i = (s_minus__i*s_plus__i <= 0.0) ? 1.0e+90 : s_plus__i/abs(s_plus__i) * log(s_plus__i/s_minus__i);
        I_L_plus_1__i = 0.5 * (s_plus__i*R_plus__i - s_minus__i*R_minus__i);        
      }
    }

    I_L_plus_3__i = 0.25 * (s_plus__i*R_plus__i*R_plus__i*R_plus__i - s_minus__i*R_minus__i*R_minus__i*R_minus__i + 3.0 * R_i_0_square * I_L_plus_1__i);

    K_1_minus_1__i = t_i_0*I_L_minus_1__i - abs_w0 * beta_i;
    K_1_plus_1__i = third * (w0*w0 * K_1_minus_1__i + t_i_0*I_L_plus_1__i);

//    K_2_minus_1__i = m_i_hat * I_L_plus_1__i - T.n_hat * (w0 * K_1_minus_1__i); 
//    K_2_plus_1__i = 1.0/3.0 * m_i_hat * I_L_plus_3__i - T.n_hat * (w0 * K_1_plus_1__i);
//    K_3_minus_1__i = (-sign_w0 * beta_i) * T.n_hat - I_L_minus_1__i * m_i_hat;
//    K_3_plus_1__i = -K_2_minus_1__i; //(h * K_1_minus_1__i) * T.n_hat - I_L_plus_1__i * m_i_hat;

    IT_1_R += K_1_minus_1__i;
    IT_R += K_1_plus_1__i;
    const double h_K_minus(w0 * K_1_minus_1__i), h_K_plus(w0 * K_1_plus_1__i), sign_beta(-sign_w0 * beta_i);
    IT_1_R_rprime_r[0] += m_i_hat[0] * I_L_plus_1__i - T.n_hat[0] * h_K_minus;
    IT_1_R_rprime_r[1] += m_i_hat[1] * I_L_plus_1__i - T.n_hat[1] * h_K_minus;
    IT_1_R_rprime_r[2] += m_i_hat[2] * I_L_plus_1__i - T.n_hat[2] * h_K_minus;
    IT_R_rprime_r[0] += (third * I_L_plus_3__i) * m_i_hat[0] - T.n_hat[0] * h_K_plus; //K_2_plus_1__i[0];
    IT_R_rprime_r[1] += (third * I_L_plus_3__i) * m_i_hat[1] - T.n_hat[1] * h_K_plus; //K_2_plus_1__i[1];
    IT_R_rprime_r[2] += (third * I_L_plus_3__i) * m_i_hat[2] - T.n_hat[2] * h_K_plus; //K_2_plus_1__i[2];
    IT_grad_1_R[0] += sign_beta * T.n_hat[0] - I_L_minus_1__i * m_i_hat[0]; //K_3_minus_1__i[0];
    IT_grad_1_R[1] += sign_beta * T.n_hat[1] - I_L_minus_1__i * m_i_hat[1]; //K_3_minus_1__i[1];
    IT_grad_1_R[2] += sign_beta * T.n_hat[2] - I_L_minus_1__i * m_i_hat[2]; //K_3_minus_1__i[2];
  }
}

void ITs_free (std::complex<double>& ITs_G,
               std::complex<double> ITs_G_rprime_r[], // dim 3
               std::complex<double> ITs_grad_G[], // dim 3
               const double r[], // dim 3
               const Triangle & Ts,
               const std::complex<double> & k,
               const int N_points,
               const double * xi,
               const double * eta,
               const double * weights,
               const double sum_weights,
               const int EXTRACT_1_R,
               const int EXTRACT_R)
{
  const double RSMALL_SQUARE = RSMALL*RSMALL;
  double R, R_square, IT_1_R, IT_R;
  std::complex<double> G_j, minus_I_k(-I*k), minus_I_k_R, exp_minus_I_k_R;
  double rprime_r[3], IT_1_R_rprime_r[3], IT_R_rprime_r[3], IT_grad_1_R[3]; // IT_grad_R[3];
  const double r0_r2[3] = {Ts.r_nodes[0][0]-Ts.r_nodes[2][0], Ts.r_nodes[0][1]-Ts.r_nodes[2][1], Ts.r_nodes[0][2]-Ts.r_nodes[2][2]};
  const double r1_r2[3] = {Ts.r_nodes[1][0]-Ts.r_nodes[2][0], Ts.r_nodes[1][1]-Ts.r_nodes[2][1], Ts.r_nodes[1][2]-Ts.r_nodes[2][2]};
  const double r2_r[3] = {Ts.r_nodes[2][0]-r[0], Ts.r_nodes[2][1]-r[1], Ts.r_nodes[2][2]-r[2]};

  const double norm_factor = Ts.A/sum_weights;

  ITs_G = 0.0; // complex<double>
  for (int i=0; i<3; i++) {
    ITs_G_rprime_r[i] = 0.0; // Vector<complex<double>, 3>
    ITs_grad_G[i] = 0.0; // Vector<complex<double>, 3>
  }
  if ((EXTRACT_1_R==0) && (EXTRACT_R==0)) { // no singularity extraction
    for (int j=0 ; j<N_points ; j++) {
      rprime_r[0] = r0_r2[0] * xi[j] + r1_r2[0] * eta[j] + r2_r[0];
      rprime_r[1] = r0_r2[1] * xi[j] + r1_r2[1] * eta[j] + r2_r[1];
      rprime_r[2] = r0_r2[2] * xi[j] + r1_r2[2] * eta[j] + r2_r[2];
      R_square = rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2];
      R = sqrt(R_square);
      minus_I_k_R = minus_I_k*R;
//      G_j = exp(minus_I_k_R) * (weights[j]/R);
//      G_j = (exp(minus_I_k_R.real()) * (weights[j]/R)) * std::complex<double>(cos(minus_I_k_R.imag()), sin(minus_I_k_R.imag())); // exp(a + ib) = exp(a) * (cos(b) + i*sin(b))
      double c, s, e;
      e = (minus_I_k_R.real() == 0.0) ? 1.0 * (weights[j]/R) : exp(minus_I_k_R.real()) * (weights[j]/R);
      sincos(minus_I_k_R.imag(), &s, &c);
      G_j = e * std::complex<double>(c, s);
      ITs_G += G_j;
      ITs_G_rprime_r[0] += G_j * rprime_r[0];
      ITs_G_rprime_r[1] += G_j * rprime_r[1];
      ITs_G_rprime_r[2] += G_j * rprime_r[2];
      const std::complex<double> temp(G_j * (1.0-minus_I_k_R)/(R_square));
      ITs_grad_G[0] += temp * rprime_r[0];
      ITs_grad_G[1] += temp * rprime_r[1];
      ITs_grad_G[2] += temp * rprime_r[2];
    }
    ITs_G *= norm_factor;
    for (int i=0; i<3; i++) {
      ITs_G_rprime_r[i] *= norm_factor;
      ITs_grad_G[i] *= norm_factor;
    }
  }
 
  else if ((EXTRACT_1_R==1) && (EXTRACT_R==0)) { // 1/R singularity extraction
    for (int j=0 ; j<N_points ; j++) {
      rprime_r[0] = r0_r2[0] * xi[j] + r1_r2[0] * eta[j] + r2_r[0];
      rprime_r[1] = r0_r2[1] * xi[j] + r1_r2[1] * eta[j] + r2_r[1];
      rprime_r[2] = r0_r2[2] * xi[j] + r1_r2[2] * eta[j] + r2_r[2];
      R_square = rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2];
      if (R_square>RSMALL_SQUARE) {
        R = sqrt(R_square);
        minus_I_k_R = minus_I_k*R;
//        exp_minus_I_k_R = exp(minus_I_k_R);
//        exp_minus_I_k_R = exp(minus_I_k_R.real()) * std::complex<double>(cos(minus_I_k_R.imag()), sin(minus_I_k_R.imag()));
        double c, s, e;
        e = (minus_I_k_R.real() == 0.0) ? 1.0 : exp(minus_I_k_R.real());
        sincos(minus_I_k_R.imag(), &s, &c);
        exp_minus_I_k_R = e * std::complex<double>(c, s);
        G_j = (exp_minus_I_k_R - 1.0) * (weights[j]/R);
        const std::complex<double> temp((exp_minus_I_k_R*(1.0-minus_I_k_R) - 1.0) * (weights[j]/(R*R_square)) );
        ITs_grad_G[0] += temp * rprime_r[0];
        ITs_grad_G[1] += temp * rprime_r[1];
        ITs_grad_G[2] += temp * rprime_r[2];
      }
      else {
        G_j = minus_I_k * weights[j];
      }
      ITs_G += G_j;
      ITs_G_rprime_r[0] += G_j * rprime_r[0];
      ITs_G_rprime_r[1] += G_j * rprime_r[1];
      ITs_G_rprime_r[2] += G_j * rprime_r[2];
    }
    IT_singularities (IT_1_R, IT_R, IT_1_R_rprime_r, IT_R_rprime_r, IT_grad_1_R, r, Ts);
    ITs_G = ITs_G * norm_factor + IT_1_R;
    for (int i=0; i<3; i++) {
      ITs_G_rprime_r[i] = ITs_G_rprime_r[i] * norm_factor + IT_1_R_rprime_r[i];
      ITs_grad_G[i] = ITs_grad_G[i] * norm_factor + IT_grad_1_R[i];
    }
  }

  else if ((EXTRACT_1_R==1) && (EXTRACT_R==1)) { // 1/R and R singularity extraction
    const std::complex<double> k_square = k*k;
    for (int j=0 ; j<N_points ; j++) {
      rprime_r[0] = r0_r2[0] * xi[j] + r1_r2[0] * eta[j] + r2_r[0];
      rprime_r[1] = r0_r2[1] * xi[j] + r1_r2[1] * eta[j] + r2_r[1];
      rprime_r[2] = r0_r2[2] * xi[j] + r1_r2[2] * eta[j] + r2_r[2];
      R_square = rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2];
      if (R_square>RSMALL_SQUARE) {
        R = sqrt(R_square);
        minus_I_k_R = minus_I_k*R;
//        exp_minus_I_k_R = exp(minus_I_k_R);
//        exp_minus_I_k_R = exp(minus_I_k_R.real()) * std::complex<double>(cos(minus_I_k_R.imag()), sin(minus_I_k_R.imag()));
        double c, s, e;
        e = (minus_I_k_R.real() == 0.0) ? 1.0 : exp(minus_I_k_R.real());
        sincos(minus_I_k_R.imag(), &s, &c);
        exp_minus_I_k_R = e * std::complex<double>(c, s);
        G_j = ( (exp_minus_I_k_R - 1.0)/R + k_square * (R*0.5) ) * weights[j];
        const std::complex<double> temp( (exp_minus_I_k_R*(1.0-minus_I_k_R) - 1.0 - k_square * (0.5*R_square)) * (weights[j]/(R*R_square)) );
        ITs_grad_G[0] += temp * rprime_r[0];
        ITs_grad_G[1] += temp * rprime_r[1];
        ITs_grad_G[2] += temp * rprime_r[2];
      }
      else {
        G_j = minus_I_k * weights[j];
      }
      ITs_G += G_j;
      ITs_G_rprime_r[0] += G_j * rprime_r[0];
      ITs_G_rprime_r[1] += G_j * rprime_r[1];
      ITs_G_rprime_r[2] += G_j * rprime_r[2];
    }
    IT_singularities (IT_1_R, IT_R, IT_1_R_rprime_r, IT_R_rprime_r, IT_grad_1_R, r, Ts);
    const std::complex<double> k_square_2(k_square*0.5);
    ITs_G = ITs_G * norm_factor + IT_1_R - k_square_2 * IT_R;
    for (int i=0; i<3; i++) {
      ITs_G_rprime_r[i] = ITs_G_rprime_r[i] * norm_factor + IT_1_R_rprime_r[i] - k_square_2 * IT_R_rprime_r[i];
      // IT_grad_R = -IT_1_R_rprime_r
      ITs_grad_G[i] = ITs_grad_G[i] * norm_factor + IT_grad_1_R[i] + k_square_2 * IT_1_R_rprime_r[i];
    }
  }
}

void ITo_ITs_free (std::complex<double>& ITo_ITs_G,
                   std::complex<double> ITo_r_ITs_G[], // 3D
                   std::complex<double> ITo_ITs_G_rprime[], // 3D
                   std::complex<double>& ITo_r_dot_ITs_G_rprime,
                   std::complex<double>& ITo_n_hat_X_r_dot_ITs_G_rprime,
                   std::complex<double> ITo_ITs_grad_G[], // 3D
                   std::complex<double> ITo_r_X_ITs_grad_G[], // 3D
                   std::complex<double> & ITo_n_hat_X_r_dot_r_X_ITs_grad_G,
                   std::complex<double> ITo_n_hat_X_r_X_ITs_grad_G[], // 3D
                   const Triangle & To,
                   const Triangle & Ts,
                   const std::complex<double> k,
                   const int N_points_o,
                   const int N_points_s,
                   const int EXTRACT_1_R,
                   const int EXTRACT_R)
{
  int j;
  double sum_weigths, sum_weights_source, norm_factor;
  std::complex<double> ITs_G_j;
  double r[3], n_hat_X_r[3];
  std::complex<double> r_ITs_G_j[3], ITs_G_rprime_r_j[3], ITs_G_rprime_j[3], ITs_grad_G_j[3], r_X_ITs_grad_G_j[3], n_hat_X_r_X_ITs_grad_G_j[3];

  const double *xi, *eta, *weigths;
  IT_points (xi, eta, weigths, sum_weigths, N_points_o);

  const double *xi_source, *eta_source, *weights_source;
  IT_points (xi_source, eta_source, weights_source, sum_weights_source, N_points_s);

  ITo_ITs_G = 0.0; // complex<double>
  ITo_r_dot_ITs_G_rprime = 0.0; // complex<double>
  ITo_n_hat_X_r_dot_ITs_G_rprime = 0.0; // complex<double>
  ITo_n_hat_X_r_dot_r_X_ITs_grad_G = 0.0; // complex<double>
  for (int i=0 ; i<3 ; ++i) {
    ITo_r_ITs_G[i] = 0.0; // Vector<complex<double>, 3>
    ITo_ITs_G_rprime[i] = 0.0; // Vector<complex<double>, 3>
    ITo_ITs_grad_G[i] = 0.0; // Vector<complex<double>, 3>
    ITo_r_X_ITs_grad_G[i] = 0.0; // Vector<complex<double>, 3>
    ITo_n_hat_X_r_X_ITs_grad_G[i] = 0.0; // Vector<complex<double>, 3>
  }
  for (j=0 ; j<N_points_o ; j++) {
    r[0] = To.r_nodes[0][0]*xi[j] + To.r_nodes[1][0]*eta[j] + To.r_nodes[2][0]*(1-xi[j]-eta[j]);
    r[1] = To.r_nodes[0][1]*xi[j] + To.r_nodes[1][1]*eta[j] + To.r_nodes[2][1]*(1-xi[j]-eta[j]);
    r[2] = To.r_nodes[0][2]*xi[j] + To.r_nodes[1][2]*eta[j] + To.r_nodes[2][2]*(1-xi[j]-eta[j]);
    cross3D(n_hat_X_r, To.n_hat, r);
    ITs_free (ITs_G_j, ITs_G_rprime_r_j, ITs_grad_G_j, r, Ts, k, N_points_s, xi_source, eta_source, weights_source, sum_weights_source, EXTRACT_1_R, EXTRACT_R);

    ITs_G_j *= weigths[j];
    r_ITs_G_j[0] = ITs_G_j * r[0];
    r_ITs_G_j[1] = ITs_G_j * r[1];
    r_ITs_G_j[2] = ITs_G_j * r[2];
    ITs_G_rprime_j[0] = ITs_G_rprime_r_j[0] * weigths[j] + r_ITs_G_j[0];
    ITs_G_rprime_j[1] = ITs_G_rprime_r_j[1] * weigths[j] + r_ITs_G_j[1];
    ITs_G_rprime_j[2] = ITs_G_rprime_r_j[2] * weigths[j] + r_ITs_G_j[2];
    ITs_grad_G_j[0] *= weigths[j];
    ITs_grad_G_j[1] *= weigths[j];
    ITs_grad_G_j[2] *= weigths[j];
    r_X_ITs_grad_G_j[0] = r[1] * ITs_grad_G_j[2] - r[2] * ITs_grad_G_j[1];
    r_X_ITs_grad_G_j[1] = r[2] * ITs_grad_G_j[0] - r[0] * ITs_grad_G_j[2];
    r_X_ITs_grad_G_j[2] = r[0] * ITs_grad_G_j[1] - r[1] * ITs_grad_G_j[0];
    n_hat_X_r_X_ITs_grad_G_j[0] = n_hat_X_r[1] * ITs_grad_G_j[2] - n_hat_X_r[2] * ITs_grad_G_j[1];
    n_hat_X_r_X_ITs_grad_G_j[1] = n_hat_X_r[2] * ITs_grad_G_j[0] - n_hat_X_r[0] * ITs_grad_G_j[2];
    n_hat_X_r_X_ITs_grad_G_j[2] = n_hat_X_r[0] * ITs_grad_G_j[1] - n_hat_X_r[1] * ITs_grad_G_j[0];

    ITo_ITs_G += ITs_G_j;
    ITo_r_ITs_G[0] += r_ITs_G_j[0];
    ITo_r_ITs_G[1] += r_ITs_G_j[1];
    ITo_r_ITs_G[2] += r_ITs_G_j[2];
    ITo_ITs_G_rprime[0] += ITs_G_rprime_j[0];
    ITo_ITs_G_rprime[1] += ITs_G_rprime_j[1];
    ITo_ITs_G_rprime[2] += ITs_G_rprime_j[2];
    ITo_r_dot_ITs_G_rprime += (r[0] * ITs_G_rprime_j[0] + r[1] * ITs_G_rprime_j[1] + r[2] * ITs_G_rprime_j[2]);
    ITo_n_hat_X_r_dot_ITs_G_rprime += (n_hat_X_r[0] * ITs_G_rprime_j[0] + n_hat_X_r[1] * ITs_G_rprime_j[1] + n_hat_X_r[2] * ITs_G_rprime_j[2]);
    ITo_ITs_grad_G[0] += ITs_grad_G_j[0];
    ITo_ITs_grad_G[1] += ITs_grad_G_j[1];
    ITo_ITs_grad_G[2] += ITs_grad_G_j[2];
    ITo_r_X_ITs_grad_G[0] +=  r_X_ITs_grad_G_j[0];
    ITo_r_X_ITs_grad_G[1] +=  r_X_ITs_grad_G_j[1];
    ITo_r_X_ITs_grad_G[2] +=  r_X_ITs_grad_G_j[2];
    ITo_n_hat_X_r_dot_r_X_ITs_grad_G += (n_hat_X_r[0] * r_X_ITs_grad_G_j[0] + n_hat_X_r[1] * r_X_ITs_grad_G_j[1] + n_hat_X_r[2] * r_X_ITs_grad_G_j[2]);
    ITo_n_hat_X_r_X_ITs_grad_G[0] += n_hat_X_r_X_ITs_grad_G_j[0];
    ITo_n_hat_X_r_X_ITs_grad_G[1] += n_hat_X_r_X_ITs_grad_G_j[1];
    ITo_n_hat_X_r_X_ITs_grad_G[2] += n_hat_X_r_X_ITs_grad_G_j[2];
  }
  norm_factor = To.A/(4.0*M_PI*sum_weigths);
  ITo_ITs_G *= norm_factor;
  ITo_r_dot_ITs_G_rprime *= norm_factor;
  ITo_n_hat_X_r_dot_ITs_G_rprime *= norm_factor;
  ITo_n_hat_X_r_dot_r_X_ITs_grad_G *= norm_factor;
  for (int i=0 ; i<3 ; ++i) {
    ITo_r_ITs_G[i] *= norm_factor;
    ITo_ITs_G_rprime[i] *= norm_factor;
    ITo_ITs_grad_G[i] *= norm_factor;
    ITo_r_X_ITs_grad_G[i] *= norm_factor;
    ITo_n_hat_X_r_X_ITs_grad_G[i] *= norm_factor;
  }
}

void IDTo_ITs_free (std::complex<double> & IDTo_l_hat_dot_r_ITs_G,
                    complex<double> IDTo_l_hat_ITs_G[], // 3D
                    const Triangle & To,
                    const Triangle & Ts,
                    const std::complex<double> k,
                    const int N_points_o,
                    const int N_points_s,
                    const int EXTRACT_1_R,
                    const int EXTRACT_R)
{
  const double *XGL, *WGL;
  Gauss_Legendre (XGL, WGL, N_points_o);

  double norm_factor, norm_r_hlgth, sum_weights_source;
  double r[3], r_center[3], r_hlgth[3]; // n_hat_X_r[3], m_hat[3]
  const double * l_hat, * r_plus__i, * r_minus__i;

  const double *xi_source, *eta_source, *weights_source;
  IT_points (xi_source, eta_source, weights_source, sum_weights_source, N_points_s);

  std::complex<double> ITs_G_j, I_k;
  std::complex<double> ITs_G_rprime_r_j[3], ITs_grad_G_j[3], I_r_k[3];

  IDTo_l_hat_dot_r_ITs_G = 0.0; // complex<double>
  for (int i=0 ; i<3 ; i++) IDTo_l_hat_ITs_G[i] = 0.0; // Vector<complex<double>, 3>
  for (int i=0 ; i<3 ; i++) { // we turn on the contour of T_obs
    r_plus__i = To.r_nodes[(i+1)%3]; // (i+1)%3 : 1 if i=0, 2 if i=1, 0 if i=3
    r_minus__i = To.r_nodes[i];
    l_hat = To.s_i_hat[i];

    // This is a Gauss-Kronrod rule, applied to each edge
    r_hlgth[0] = 0.5*(r_plus__i[0]-r_minus__i[0]);
    r_hlgth[1] = 0.5*(r_plus__i[1]-r_minus__i[1]);
    r_hlgth[2] = 0.5*(r_plus__i[2]-r_minus__i[2]);
    norm_r_hlgth = sqrt(dot3D(r_hlgth, r_hlgth));
    r_center[0] = 0.5*(r_plus__i[0]+r_minus__i[0]);
    r_center[1] = 0.5*(r_plus__i[1]+r_minus__i[1]);
    r_center[2] = 0.5*(r_plus__i[2]+r_minus__i[2]);
    I_k = 0.0;
    I_r_k[0] = 0.0;
    I_r_k[1] = 0.0;
    I_r_k[2] = 0.0;
    for (int j=0 ; j<N_points_o ; j++) {
      r[0] = r_center[0] + r_hlgth[0] * XGL[j];
      r[1] = r_center[1] + r_hlgth[1] * XGL[j];
      r[2] = r_center[2] + r_hlgth[2] * XGL[j];
      ITs_free (ITs_G_j, ITs_G_rprime_r_j, ITs_grad_G_j, r, Ts, k, N_points_s, xi_source, eta_source, weights_source, sum_weights_source, EXTRACT_1_R, EXTRACT_R);
      const std::complex<double> temp(ITs_G_j * WGL[j]);
      I_k += temp;
      I_r_k[0] += temp * r[0];
      I_r_k[1] += temp * r[1];
      I_r_k[2] += temp * r[2];
    } // end of the Gauss-Kronrod rule applied to edge (i)
    const std::complex<double> temp(I_k * norm_r_hlgth);
    IDTo_l_hat_ITs_G[0] += temp * l_hat[0];
    IDTo_l_hat_ITs_G[1] += temp * l_hat[1];
    IDTo_l_hat_ITs_G[2] += temp * l_hat[2];
    IDTo_l_hat_dot_r_ITs_G += (l_hat[0] * I_r_k[0] + l_hat[1] * I_r_k[1] + l_hat[2] * I_r_k[2]) * norm_r_hlgth;
  } // contour integration finished
  norm_factor = 1.0/(4.0*M_PI);
  IDTo_l_hat_dot_r_ITs_G *= norm_factor;
  for (int i=0 ; i<3 ; i++) IDTo_l_hat_ITs_G[i] *= norm_factor;
}

/* special functions for the excitation vectors calculations */
void V_EH_ITo_free (std::complex<double>& ITo_G,
                    std::complex<double> ITo_G_rprime_r[],
                    std::complex<double> ITo_grad_G[],
                    std::complex<double> ITo_n_hat_X_r_X_grad_G[],
                    double r[],
                    const Triangle & To,
                    const std::complex<double> k,
                    const int N_points,
                    const int EXTRACT_1_R,
                    const int EXTRACT_R)
{
  double sum_weigths, norm_factor, R, IT_1_R, IT_R;
  std::complex<double> G_j, I_k_R, exp_minus_I_k_R, k_square;
  double rprime[3], rprime_r[3], IT_1_R_rprime_r[3], IT_R_rprime_r[3], IT_grad_1_R[3], n_hat_X_rprime[3]; // IT_grad_R[3]
  std::complex<double> ITo_grad_G_j[3];

  const double *xi, *eta, *weigths;
  IT_points (xi, eta, weigths, sum_weigths, N_points);
  norm_factor = To.A/sum_weigths;

  ITo_G = 0.0; // complex<double>
  for (int i=0 ; i<3 ; ++i) {
    ITo_G_rprime_r[i] = 0.0; // Vector<complex<double>, 3>
    ITo_grad_G[i] = 0.0; // Vector<complex<double>, 3>
    ITo_n_hat_X_r_X_grad_G[i] = 0.0; // Vector<complex<double>, 3>
  }
  if ((EXTRACT_1_R==0) && (EXTRACT_R==0)) { // no singularity extraction
    for (int j=0 ; j<N_points ; ++j) {
      rprime[0] = To.r_nodes[0][0]*xi[j] + To.r_nodes[1][0]*eta[j] + To.r_nodes[2][0]*(1-xi[j]-eta[j]);
      rprime[1] = To.r_nodes[0][1]*xi[j] + To.r_nodes[1][1]*eta[j] + To.r_nodes[2][1]*(1-xi[j]-eta[j]);
      rprime[2] = To.r_nodes[0][2]*xi[j] + To.r_nodes[1][2]*eta[j] + To.r_nodes[2][2]*(1-xi[j]-eta[j]);
      rprime_r[0] = rprime[0]-r[0];
      rprime_r[1] = rprime[1]-r[1];
      rprime_r[2] = rprime[2]-r[2];
      R = sqrt(rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2]);
      I_k_R = I*k*R;
      exp_minus_I_k_R = exp(-I_k_R);
      G_j = exp_minus_I_k_R/R * weigths[j];
      ITo_G += G_j;
      ITo_G_rprime_r[0] += G_j * rprime_r[0];
      ITo_G_rprime_r[1] += G_j * rprime_r[1];
      ITo_G_rprime_r[2] += G_j * rprime_r[2];
      const std::complex<double> temp(G_j * (1.0+I_k_R)/(R*R));
      ITo_grad_G[0] += temp * rprime_r[0];
      ITo_grad_G[1] += temp * rprime_r[1];
      ITo_grad_G[2] += temp * rprime_r[2];
      n_hat_X_rprime[0] = To.n_hat[1]*rprime[2]-To.n_hat[2]*rprime[1];
      n_hat_X_rprime[1] = To.n_hat[2]*rprime[0]-To.n_hat[0]*rprime[2];
      n_hat_X_rprime[2] = To.n_hat[0]*rprime[1]-To.n_hat[1]*rprime[0];
      ITo_n_hat_X_r_X_grad_G[0] += n_hat_X_rprime[1] * ITo_grad_G_j[2] - n_hat_X_rprime[2] * ITo_grad_G_j[1];
      ITo_n_hat_X_r_X_grad_G[1] += n_hat_X_rprime[2] * ITo_grad_G_j[0] - n_hat_X_rprime[0] * ITo_grad_G_j[2];
      ITo_n_hat_X_r_X_grad_G[2] += n_hat_X_rprime[0] * ITo_grad_G_j[1] - n_hat_X_rprime[1] * ITo_grad_G_j[0];
    }
    ITo_G *= norm_factor;
    for (int i=0 ; i<3 ; ++i) {
      ITo_G_rprime_r[i] *= norm_factor; // Vector<complex<double>, 3>
      ITo_grad_G[i] *= norm_factor; // Vector<complex<double>, 3>
      ITo_n_hat_X_r_X_grad_G[i] *= norm_factor; // Vector<complex<double>, 3>
    }
  }
 
  else if ((EXTRACT_1_R==1) && (EXTRACT_R==0)) { // 1/R singularity extraction
    for (int j=0 ; j<N_points ; ++j) {
      rprime[0] = To.r_nodes[0][0]*xi[j] + To.r_nodes[1][0]*eta[j] + To.r_nodes[2][0]*(1-xi[j]-eta[j]);
      rprime[1] = To.r_nodes[0][1]*xi[j] + To.r_nodes[1][1]*eta[j] + To.r_nodes[2][1]*(1-xi[j]-eta[j]);
      rprime[2] = To.r_nodes[0][2]*xi[j] + To.r_nodes[1][2]*eta[j] + To.r_nodes[2][2]*(1-xi[j]-eta[j]);
      rprime_r[0] = rprime[0]-r[0];
      rprime_r[1] = rprime[1]-r[1];
      rprime_r[2] = rprime[2]-r[2];
      R = sqrt(rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2]);
      if (R>RSMALL) {
        I_k_R = I*k*R;
        exp_minus_I_k_R = exp(-I_k_R);
        G_j = (exp_minus_I_k_R - 1.0)/R * weigths[j];
        const std::complex<double> temp( -(-exp_minus_I_k_R*(1.0+I_k_R) + 1.0)/(R*R*R) * weigths[j] );
        ITo_grad_G[0] += temp * rprime_r[0];
        ITo_grad_G[1] += temp * rprime_r[1];
        ITo_grad_G[2] += temp * rprime_r[2];
      }
      else {
        G_j = -I * k * weigths[j];
      }
      ITo_G += G_j;
      ITo_G_rprime_r[0] += G_j * rprime_r[0];
      ITo_G_rprime_r[1] += G_j * rprime_r[1];
      ITo_G_rprime_r[2] += G_j * rprime_r[2];
      n_hat_X_rprime[0] = To.n_hat[1]*rprime[2]-To.n_hat[2]*rprime[1];
      n_hat_X_rprime[1] = To.n_hat[2]*rprime[0]-To.n_hat[0]*rprime[2];
      n_hat_X_rprime[2] = To.n_hat[0]*rprime[1]-To.n_hat[1]*rprime[0];
      ITo_n_hat_X_r_X_grad_G[0] += n_hat_X_rprime[1] * ITo_grad_G_j[2] - n_hat_X_rprime[2] * ITo_grad_G_j[1];
      ITo_n_hat_X_r_X_grad_G[1] += n_hat_X_rprime[2] * ITo_grad_G_j[0] - n_hat_X_rprime[0] * ITo_grad_G_j[2];
      ITo_n_hat_X_r_X_grad_G[2] += n_hat_X_rprime[0] * ITo_grad_G_j[1] - n_hat_X_rprime[1] * ITo_grad_G_j[0];
    }
    IT_singularities (IT_1_R, IT_R, IT_1_R_rprime_r, IT_R_rprime_r, IT_grad_1_R, r, To);
    ITo_G = ITo_G * norm_factor + IT_1_R;
    for (int i=0 ; i<3 ; ++i) {
      ITo_G_rprime_r[i] = ITo_G_rprime_r[i] * norm_factor + IT_1_R_rprime_r[i];
      ITo_grad_G[i] = ITo_grad_G[i] * norm_factor + IT_grad_1_R[i];
      ITo_n_hat_X_r_X_grad_G[i] = ITo_n_hat_X_r_X_grad_G[i] * norm_factor;
    }
  }

  else if ((EXTRACT_1_R==1) && (EXTRACT_R==1)) { // 1/R and R singularity extraction
    k_square = k*k;
    for (int j=0 ; j<N_points ; ++j) {
      rprime[0] = To.r_nodes[0][0]*xi[j] + To.r_nodes[1][0]*eta[j] + To.r_nodes[2][0]*(1-xi[j]-eta[j]);
      rprime[1] = To.r_nodes[0][1]*xi[j] + To.r_nodes[1][1]*eta[j] + To.r_nodes[2][1]*(1-xi[j]-eta[j]);
      rprime[2] = To.r_nodes[0][2]*xi[j] + To.r_nodes[1][2]*eta[j] + To.r_nodes[2][2]*(1-xi[j]-eta[j]);
      rprime_r[0] = rprime[0]-r[0];
      rprime_r[1] = rprime[1]-r[1];
      rprime_r[2] = rprime[2]-r[2];
      R = sqrt(rprime_r[0]*rprime_r[0] + rprime_r[1]*rprime_r[1] + rprime_r[2]*rprime_r[2]);
      if (R>RSMALL) {
        I_k_R = I*k*R;
        exp_minus_I_k_R = exp(-I_k_R);
        G_j = ( (exp_minus_I_k_R - 1.0)/R + k_square/2.0 * R ) * weigths[j];
        const std::complex<double> temp( -(-exp_minus_I_k_R*(1.0+I_k_R) + 1.0 + k_square/2.0 * R*R)/(R*R*R) * weigths[j] );
        ITo_grad_G[0] += temp * rprime_r[0];
        ITo_grad_G[1] += temp * rprime_r[1];
        ITo_grad_G[2] += temp * rprime_r[2];
      }
      else {
        G_j = -I * k * weigths[j];
      }
      ITo_G += G_j;
      ITo_G_rprime_r[0] += G_j * rprime_r[0];
      ITo_G_rprime_r[1] += G_j * rprime_r[1];
      ITo_G_rprime_r[2] += G_j * rprime_r[2];
      n_hat_X_rprime[0] = To.n_hat[1]*rprime[2]-To.n_hat[2]*rprime[1];
      n_hat_X_rprime[1] = To.n_hat[2]*rprime[0]-To.n_hat[0]*rprime[2];
      n_hat_X_rprime[2] = To.n_hat[0]*rprime[1]-To.n_hat[1]*rprime[0];
      ITo_n_hat_X_r_X_grad_G[0] += n_hat_X_rprime[1] * ITo_grad_G_j[2] - n_hat_X_rprime[2] * ITo_grad_G_j[1];
      ITo_n_hat_X_r_X_grad_G[1] += n_hat_X_rprime[2] * ITo_grad_G_j[0] - n_hat_X_rprime[0] * ITo_grad_G_j[2];
      ITo_n_hat_X_r_X_grad_G[2] += n_hat_X_rprime[0] * ITo_grad_G_j[1] - n_hat_X_rprime[1] * ITo_grad_G_j[0];
    }
    IT_singularities (IT_1_R, IT_R, IT_1_R_rprime_r, IT_R_rprime_r, IT_grad_1_R, r, To);
    ITo_G = ITo_G * norm_factor + IT_1_R - k_square * (IT_R*0.5);
    for (int i=0 ; i<3 ; ++i) {
      ITo_G_rprime_r[i] = ITo_G_rprime_r[i] * norm_factor + IT_1_R_rprime_r[i] - k_square * (0.5 * IT_R_rprime_r[i]);
      // IT_grad_R = -IT_1_R_rprime_r
      ITo_grad_G[i] = ITo_grad_G[i] * norm_factor + IT_grad_1_R[i] + k_square * (0.5 * IT_1_R_rprime_r[i]);
      //ITo_n_hat_X_r_X_grad_G[i] = ITo_n_hat_X_r_X_grad_G[i] * norm_factor;
    }
  }
}

