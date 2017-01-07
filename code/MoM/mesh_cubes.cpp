/**********************************************************************
 *
 * mesh_cubes.cpp
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
#include <string>
#include <blitz/array.h>
#include <vector>
#include <algorithm>
#include <math.h> 
#include <map>

using namespace std;

#include "GetMemUsage.h"
#include "readWriteBlitzArrayFromFile.h"
#include "dictionary.h"

void cube_lower_coord_computation(int & N_levels,
                                  int & max_N_cubes_1D,
                                  std::vector<double> & big_cube_center_coord,
                                  std::vector<double> & big_cube_lower_coord,
                                  const double a, 
                                  const blitz::Array<double, 2>& vertexes_coord, 
                                  const int V)
{
  // This function computes the coordinates of the 1st cube,
  // and the number of small cubes in each direction x, y, z.
  // a is the length of the side of a cube.
  double x_min, x_max, y_min, y_max, z_min, z_max;
  x_min = vertexes_coord(0, 0);
  x_max = vertexes_coord(0, 0);
  y_min = vertexes_coord(0, 1);
  y_max = vertexes_coord(0, 1);
  z_min = vertexes_coord(0, 2);
  z_max = vertexes_coord(0, 2);
  for (int i=1; i<V; i++) {
    x_min = min(vertexes_coord(i, 0), x_min);
    x_max = max(vertexes_coord(i, 0), x_max);
    y_min = min(vertexes_coord(i, 1), y_min);
    y_max = max(vertexes_coord(i, 1), y_max);
    z_min = min(vertexes_coord(i, 2), z_min);
    z_max = max(vertexes_coord(i, 2), z_max);
  }
  const double Delta_x = x_max - x_min + (sqrt(2.0)-1.0) * a;
  const double Delta_y = y_max - y_min + (sqrt(2.0)-1.0) * a;
  const double Delta_z = z_max - z_min + (sqrt(2.0)-1.0) * a;
  const double length_side_of_big_cube = max(Delta_x, max(Delta_y, Delta_z));
  N_levels = max(2, static_cast<int>(ceil(log2(length_side_of_big_cube/a))));
  big_cube_center_coord.resize(3);
  big_cube_center_coord[0] = (x_min + x_max)/2.0;
  big_cube_center_coord[1] = (y_min + y_max)/2.0;
  big_cube_center_coord[2] = (z_min + z_max)/2.0;
  max_N_cubes_1D = pow(2, N_levels);
  big_cube_lower_coord.resize(3);
  for (int i=0; i<3; i++) big_cube_lower_coord[i] = big_cube_center_coord[i] - length_side_of_big_cube/2.0;
}

void compute_RWGNumber_edgeCentroidCoord(blitz::Array<double, 2>& edgeCentroidCoord,
                                         const blitz::Array<double, 2>& vertexes_coord,
                                         const blitz::Array<int, 2>& RWGNumber_edgeVertexes,
                                         const int N_RWG)
{
  for (int i=0; i<N_RWG; i++) {
    const int index_1 = RWGNumber_edgeVertexes(i, 0), index_2 = RWGNumber_edgeVertexes(i, 1);
    for (int j=0; j<3; j++) edgeCentroidCoord(i, j) = (vertexes_coord(index_1, j) + vertexes_coord(index_2, j))/2.0;
  }
}

void cubeIndex_RWGNumbers_computation(blitz::Array<int, 1>& cubes_RWGsNumbers,
                                      blitz::Array<int, 1>& cube_N_RWGs,
                                      blitz::Array<double, 2>& cubeCentroidCoord,
                                      const double a,
                                      const int max_N_cubes_1D, 
                                      const std::vector<double> & cube_lower_coord, 
                                      const blitz::Array<double, 2>& RWGNumber_edgeCentroidCoord,
                                      const int N_RWG)
{
  // This function finds for each edge the cube to which it belongs.
  // a is the length of the side of a cube
  std::vector< Dictionary<unsigned long int, int> > CubeNumber_RWGnumber;
  CubeNumber_RWGnumber.reserve(N_RWG);
  for (int i=0; i<N_RWG; i++) {
    const unsigned long int RWGNumber_cube0 = static_cast<unsigned long int>(floor((RWGNumber_edgeCentroidCoord(i, 0) - cube_lower_coord[0])/a));
    const unsigned long int RWGNumber_cube1 = static_cast<unsigned long int>(floor((RWGNumber_edgeCentroidCoord(i, 1) - cube_lower_coord[1])/a));
    const unsigned long int RWGNumber_cube2 = static_cast<unsigned long int>(floor((RWGNumber_edgeCentroidCoord(i, 2) - cube_lower_coord[2])/a));    
    unsigned long int cubeNumber = (RWGNumber_cube0 * max_N_cubes_1D) * max_N_cubes_1D;
    cubeNumber += RWGNumber_cube1 * max_N_cubes_1D + RWGNumber_cube2;
    CubeNumber_RWGnumber.push_back(Dictionary<unsigned long int, int>(cubeNumber, i));
  }
  sort(CubeNumber_RWGnumber.begin(), CubeNumber_RWGnumber.end());
  int index = 0;
  std::vector< std::vector<int> > cubes_lists_RWGsNumbers;
  cubes_lists_RWGsNumbers.push_back(std::vector<int>());
  cubes_lists_RWGsNumbers[index].push_back(CubeNumber_RWGnumber[0].getVal());
  for (int i=1; i<N_RWG; i++) {
    if (CubeNumber_RWGnumber[i].getKey() != CubeNumber_RWGnumber[i-1].getKey())
    {
      index++;
      cubes_lists_RWGsNumbers.push_back(std::vector<int>());
    }
    cubes_lists_RWGsNumbers[index].push_back(CubeNumber_RWGnumber[i].getVal());
  }
  const int C = cubes_lists_RWGsNumbers.size();
  for (int i=0; i<C; i++) sort(cubes_lists_RWGsNumbers[i].begin(), cubes_lists_RWGsNumbers[i].end());

  cubeCentroidCoord.resize(C, 3);
  for (int i=0; i<C; i++) {
    const int RWG = cubes_lists_RWGsNumbers[i][0];
    const int RWGNumber_cube0 = static_cast<int>(floor((RWGNumber_edgeCentroidCoord(RWG, 0) - cube_lower_coord[0])/a));
    const int RWGNumber_cube1 = static_cast<int>(floor((RWGNumber_edgeCentroidCoord(RWG, 1) - cube_lower_coord[1])/a));
    const int RWGNumber_cube2 = static_cast<int>(floor((RWGNumber_edgeCentroidCoord(RWG, 2) - cube_lower_coord[2])/a));    
    cubeCentroidCoord(i, 0) = cube_lower_coord[0] + a * RWGNumber_cube0 + a/2.0;
    cubeCentroidCoord(i, 1) = cube_lower_coord[1] + a * RWGNumber_cube1 + a/2.0;
    cubeCentroidCoord(i, 2) = cube_lower_coord[2] + a * RWGNumber_cube2 + a/2.0;
  }
  
  cubes_RWGsNumbers.resize(N_RWG); 
  cube_N_RWGs.resize(C);
  index = 0;
  for (int i=0; i<C; i++) {
    cube_N_RWGs(i) = cubes_lists_RWGsNumbers[i].size();
    for (int j=0; j<cube_N_RWGs(i); j++) {
      cubes_RWGsNumbers(index) = cubes_lists_RWGsNumbers[i][j];
      index++;
    }
  }
}

void findCubeNeighbors(blitz::Array<int, 1>& cubes_neighborsIndexes,
                       blitz::Array<int, 1>& cube_N_neighbors,
                       blitz::Array<int, 2>& cubesNeighborsIndexesTmp2,
                       const int max_N_cubes_1D,
                       const blitz::Array<double, 1>& big_cube_lower_coord, 
                       const blitz::Array<double, 2>& cubes_centroids, 
                       const double a,
                       const int C)
{
  // for each cubes finds its neighbors.
  // We use a code similar to Level::searchCubesNeighborsIndexes() from octtree.cpp
  std::map<unsigned long int, int> CubeNumber_CubeIndex;
  std::map<unsigned long int, int>::iterator itr;
  blitz::Array<unsigned long int, 2> absoluteCartesianCoord(C, 3);
  for (int i=0; i<C; i++) {
    absoluteCartesianCoord(i, 0) = static_cast<unsigned long int>(floor( (cubes_centroids(i, 0) - big_cube_lower_coord(0))/a ));
    absoluteCartesianCoord(i, 1) = static_cast<unsigned long int>(floor( (cubes_centroids(i, 1) - big_cube_lower_coord(1))/a ));
    absoluteCartesianCoord(i, 2) = static_cast<unsigned long int>(floor( (cubes_centroids(i, 2) - big_cube_lower_coord(2))/a ));
    unsigned long int cubeNumber = (absoluteCartesianCoord(i, 0) * max_N_cubes_1D) * max_N_cubes_1D;
    cubeNumber += absoluteCartesianCoord(i, 1) * max_N_cubes_1D + absoluteCartesianCoord(i, 2);
    CubeNumber_CubeIndex.insert( std::pair<unsigned long int, int>(cubeNumber, i) );
  }
  cubesNeighborsIndexesTmp2.resize(C, 28);
  cubesNeighborsIndexesTmp2 = -1;
  int counter;
  for (int i=0 ; i<C ; ++i) {
    blitz::Array<unsigned long int, 1> absCartCoord(3);
    absCartCoord = absoluteCartesianCoord(i, 0), absoluteCartesianCoord(i, 1), absoluteCartesianCoord(i, 2);
    counter = 1;
    cubesNeighborsIndexesTmp2(i, 0) = i; // we first consider the cube itself
    // we find the neighbors
    for (int x=-1 ; x<2 ; ++x) {
      for (int y=-1 ; y<2 ; ++y) {
        for (int z=-1 ; z<2 ; ++z) {
          int index = -1;
          blitz::Array<double, 1> CandidateAbsCartCoord(3);
          CandidateAbsCartCoord = absCartCoord(0) + x, absCartCoord(1) + y, absCartCoord(2) + z;
          /// no component of (absoluteCartesianCoord(i) + p) -- where i=0,1,2 and p = x,y,z -- can be:
          /// (1) negative or (2) greater than MaxNumberCubes1D.
          int condition = 1;
          for (int j=0 ; j<3 ; ++j) condition *= ( (CandidateAbsCartCoord(j) >= 0) && (CandidateAbsCartCoord(j) < max_N_cubes_1D) );
          // we also do not want to consider the cube itself
          condition *= !((x==0) && (y==0) && (z==0));
          if (condition>0) {
            const unsigned long candidate_number = (CandidateAbsCartCoord(0) * max_N_cubes_1D)*max_N_cubes_1D + CandidateAbsCartCoord(1) * max_N_cubes_1D + CandidateAbsCartCoord(2);
            itr = CubeNumber_CubeIndex.find(candidate_number);
            if ( itr == CubeNumber_CubeIndex.end() ) index = -1;
            else index = (*itr).second;
          }
          if (index>-1) {cubesNeighborsIndexesTmp2(i, counter) = index; counter++;}
        } // z
      } // y
    } // x
  }
  cube_N_neighbors.resize(C);
  std::vector<int> cubes_neighborsIndexes_tmp;
  cubes_neighborsIndexes_tmp.reserve(C * 27);
  for (int i=0 ; i<C ; i++) {
    int j = 0;
    cube_N_neighbors(i) = 0;
    while (cubesNeighborsIndexesTmp2(i, j) > -1) {
      cube_N_neighbors(i) += 1;
      cubes_neighborsIndexes_tmp.push_back(cubesNeighborsIndexesTmp2(i, j));
      j++;
    }
  }
  cubes_neighborsIndexes.resize(cubes_neighborsIndexes_tmp.size());
  for (unsigned int i=0 ; i<cubes_neighborsIndexes.size() ; i++) cubes_neighborsIndexes(i) = cubes_neighborsIndexes_tmp[i];
}

int main(int argc, char *argv[]) {
  
  int V, T, N_RWG;
  double a;
  const string READING_PATH = argv[1];
  cout << "mesh_cubes.cpp: reading in " << READING_PATH << endl;
  string filename;

  readIntFromASCIIFile(READING_PATH + "T.txt", T);
  readIntFromASCIIFile(READING_PATH + "V.txt", V);
  readIntFromASCIIFile(READING_PATH + "N_RWG.txt", N_RWG);
  readDoubleFromASCIIFile(READING_PATH + "a.txt", a);
    
  blitz::Array<double, 2> vertexes_coord(V, 3);
  readDoubleBlitzArray2DFromBinaryFile(READING_PATH + "vertexes_coord.txt", vertexes_coord);

  int N_levels, max_N_cubes_1D;
  std::vector<double> big_cube_center_coord_tmp, big_cube_lower_coord_tmp;
  cube_lower_coord_computation(N_levels, max_N_cubes_1D, big_cube_center_coord_tmp, big_cube_lower_coord_tmp, a, vertexes_coord, V);

  blitz::Array<double, 1> big_cube_center_coord(3), big_cube_lower_coord(3);
  for (int i=0; i<3; i++) {
    big_cube_center_coord(i) = big_cube_center_coord_tmp[i];
    big_cube_lower_coord(i) = big_cube_lower_coord_tmp[i];
  }
    
  blitz::Array<int, 2> RWGNumber_edgeVertexes(N_RWG, 2);
  readIntBlitzArray2DFromBinaryFile(READING_PATH + "RWGNumber_edgeVertexes.txt", RWGNumber_edgeVertexes);

  blitz::Array<double, 2> RWGNumber_edgeCentroidCoord(N_RWG, 3);
  compute_RWGNumber_edgeCentroidCoord(RWGNumber_edgeCentroidCoord, vertexes_coord, RWGNumber_edgeVertexes, N_RWG);
  
  blitz::Array<int, 1> cubes_RWGsNumbers, cube_N_RWGs;
  blitz::Array<double, 2> cubes_centroids;
  cubeIndex_RWGNumbers_computation(cubes_RWGsNumbers, cube_N_RWGs, cubes_centroids, a, max_N_cubes_1D, big_cube_lower_coord_tmp, RWGNumber_edgeCentroidCoord, N_RWG);
  const int C = cube_N_RWGs.size();
  std::cout << "mesh_cubes.cpp: the number of cubes is " << C << std::endl;

  blitz::Array<int, 2> cubesNeighborsIndexesTmp2;
  blitz::Array<int, 1> cubes_neighborsIndexes, cube_N_neighbors;
  findCubeNeighbors(cubes_neighborsIndexes, cube_N_neighbors, cubesNeighborsIndexesTmp2, max_N_cubes_1D, big_cube_lower_coord, cubes_centroids, a, C);

  // writing of the arrays
  writeIntToASCIIFile(READING_PATH + "N_levels.txt", N_levels);
  writeIntToASCIIFile(READING_PATH + "C.txt", C);
  writeIntToASCIIFile(READING_PATH + "max_N_cubes_1D.txt", max_N_cubes_1D);
  writeDoubleBlitzArray1DToBinaryFile(READING_PATH + "big_cube_center_coord.txt", big_cube_center_coord);
  writeDoubleBlitzArray1DToBinaryFile(READING_PATH + "big_cube_lower_coord.txt", big_cube_lower_coord);
  writeIntBlitzArray1DToBinaryFile(READING_PATH + "cubes_RWGsNumbers.txt", cubes_RWGsNumbers);
  writeIntBlitzArray1DToBinaryFile(READING_PATH + "cube_N_RWGs.txt", cube_N_RWGs);
  writeDoubleBlitzArray2DToBinaryFile(READING_PATH + "cubes_centroids.txt", cubes_centroids);
  writeIntBlitzArray2DToBinaryFile(READING_PATH + "cubesNeighborsIndexesTmp2.txt", cubesNeighborsIndexesTmp2);
  writeIntBlitzArray1DToBinaryFile(READING_PATH + "cubes_neighborsIndexes.txt", cubes_neighborsIndexes);
  writeIntBlitzArray1DToBinaryFile(READING_PATH + "cube_N_neighbors.txt", cube_N_neighbors);
  // Get peak memory usage of each rank
  long memusage_local = MemoryUsageGetPeak();
  std::cout << "MEMINFO " << argv[0] << " mem=" << memusage_local/(1024*1024) << " MB" << std::endl;
  flush(std::cout);
  return 0;
}
