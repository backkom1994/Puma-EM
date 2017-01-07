/**********************************************************************
 *
 * mesh_functions_seb.cpp
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

using namespace std;

#include "GetMemUsage.h"
#include "mesh.h"

int main(int argc, char *argv[]) {
  
  int V, T;
  const int my_id = 0;
  
  string simuDir = ".";
  if ( argc > 2 ) {
     if( string(argv[1]) == "--simudir" ) simuDir = argv[2];
  }
  // general variables
  const string SIMU_DIR = simuDir;
  const string TMP = SIMU_DIR + "/tmp" + intToString(my_id);
  const string MESH_DATA_PATH = TMP + "/mesh/";

  cout << "mesh_functions_seb.cpp: reading in " << MESH_DATA_PATH << endl;

  readIntFromASCIIFile(MESH_DATA_PATH + "T.txt", T);
  readIntFromASCIIFile(MESH_DATA_PATH + "V.txt", V);

  blitz::Array<int, 2> triangle_vertexes(T, 3);
  readIntBlitzArray2DFromBinaryFile(MESH_DATA_PATH + "triangle_vertexes.txt", triangle_vertexes);
  
  const int E = 3 * T; // there are 3 edges per triangles
  blitz::Array<int, 2> col_sorted_e_v(E, 2);
  for (int i=0 ; i<T ; i++) {
    for (int j=0 ; j<3 ; j++) {
      int n_orig = j;
      int n_end = (j<2) ? j+1 : 0;
      int r_orig = triangle_vertexes(i, n_orig);
      int r_end = triangle_vertexes(i, n_end);
      int index = i*3 + j;
      col_sorted_e_v(index, 0) = std::min(r_orig, r_end);
      col_sorted_e_v(index, 1) = std::max(r_orig, r_end);
    }
  }
  
  // we now sort the decimal_e_v
  // we need an argsort type function, given by the Dictionary class (see mesh.h)
  std::vector< pair< pair<int, int>, int> > decimal_e_v_ToIndexes;
  decimal_e_v_ToIndexes.reserve(E);
  for (int j=0 ; j<E ; j++) {
    decimal_e_v_ToIndexes.push_back(pair< pair<int, int>, int> (pair<int, int>(col_sorted_e_v(j, 0), col_sorted_e_v(j, 1)), j));
  }

  sort(decimal_e_v_ToIndexes.begin(), decimal_e_v_ToIndexes.end());

  blitz::Array<int, 1> ind_sorted_e_v(E);
  for (int j=0 ; j<E ; j++) {
    ind_sorted_e_v(j) = decimal_e_v_ToIndexes[j].second;
  }
  
  std::vector<int> indexesEqualPrecedingTmp;
  for (int j=1 ; j<E ; j++) {
    if (decimal_e_v_ToIndexes[j].first == decimal_e_v_ToIndexes[j-1].first) indexesEqualPrecedingTmp.push_back(j);
  }
  decimal_e_v_ToIndexes.clear();
  std::vector< pair< pair<int, int>, int> > (decimal_e_v_ToIndexes).swap(decimal_e_v_ToIndexes);

  const int N_indexesEqualPreceding = indexesEqualPrecedingTmp.size();
  blitz::Array<int, 1> indexesEqualPreceding(N_indexesEqualPreceding);
  for (int j=0 ; j<N_indexesEqualPreceding ; j++) indexesEqualPreceding(j) = indexesEqualPrecedingTmp[j];
  indexesEqualPrecedingTmp.clear();
  std::vector<int> (indexesEqualPrecedingTmp).swap(indexesEqualPrecedingTmp);

  std::string SaveDir = MESH_DATA_PATH;
  // compute_indexesEqualEdges
  std::cout << "compute_indexesEqualEdges" << std::endl;
  std::flush(std::cout);
  std::vector<std::vector<int> > indexesEqualEdges;
  compute_indexesEqualEdges(indexesEqualEdges, indexesEqualPreceding, ind_sorted_e_v);
  ind_sorted_e_v.free();
  indexesEqualPreceding.free();

  std::cout << "edgeNumber_vertexes" << std::endl;
  std::flush(std::cout);
  blitz::Array<int,2> edgeNumber_vertexes;
  compute_edgeNumber_vertexes(edgeNumber_vertexes, indexesEqualEdges, col_sorted_e_v);
  col_sorted_e_v.free();
  const int N_edges = edgeNumber_vertexes.extent(0);

  std::cout << "edgeNumber_triangles" << std::endl;
  std::flush(std::cout);
  blitz::Array<int, 2> edgeNumber_triangles;
  compute_edgeNumber_triangles(edgeNumber_triangles, indexesEqualEdges);
  indexesEqualEdges.clear(); // not needed anymore
  std::vector<std::vector<int> > (indexesEqualEdges).swap(indexesEqualEdges);

  // compute_triangle_adjacentTriangles
  std::cout << "compute_triangle_adjacentTriangles" << std::endl;
  std::flush(std::cout);
  std::vector<std::vector<int> > triangle_adjacentTriangles;
  compute_triangle_adjacentTriangles(triangle_adjacentTriangles, edgeNumber_triangles, T);

  // reordering vertexes of the triangles
  std::cout << "reorder_triangle_vertexes" << std::endl;
  std::flush(std::cout);
  blitz::Array<int, 1> triangles_surfaces(T);
  for (int j=0 ; j<T ; j++) triangles_surfaces(j) = -1;
  blitz::Array<double, 2> vertexes_coord(V, 3);
  readDoubleBlitzArray2DFromBinaryFile(MESH_DATA_PATH + "vertexes_coord.txt", vertexes_coord);
  reorder_triangle_vertexes(triangle_vertexes, triangles_surfaces, vertexes_coord, triangle_adjacentTriangles);
  triangle_adjacentTriangles.clear();
  std::vector<std::vector<int> > (triangle_adjacentTriangles).swap(triangle_adjacentTriangles);

  // finding the open and closed surfaces
  std::cout << "is_surface_closed" << std::endl;
  std::flush(std::cout);
  blitz::Array<int, 1> is_closed_surface;
  blitz::Array<std::vector<int>, 2> connected_surfaces, potential_closed_surfaces;
  is_surface_closed(is_closed_surface, connected_surfaces, potential_closed_surfaces, triangles_surfaces, edgeNumber_triangles);

  // RWGNumber_signedTriangles_computation
  std::cout << "RWGNumber_signedTriangles_computation" << std::endl;
  std::flush(std::cout);
  blitz::Array<int, 2> RWGNumber_signedTriangles, RWGNumber_edgeVertexes;
  RWGNumber_signedTriangles_computation(RWGNumber_signedTriangles, RWGNumber_edgeVertexes, edgeNumber_triangles, edgeNumber_vertexes, triangles_surfaces, is_closed_surface, triangle_vertexes, vertexes_coord);
  edgeNumber_triangles.free();
  edgeNumber_vertexes.free();

  const int N_RWG = RWGNumber_edgeVertexes.extent(0);
  double mean_RWG_length = 0.0;
  for (int i=0; i<N_RWG; i++) {
    double RWG_length = 0.0;
    const int node0 = RWGNumber_edgeVertexes(i, 0), node1 = RWGNumber_edgeVertexes(i, 1);
    for (int j=0; j<3; j++) RWG_length += (vertexes_coord(node0, j)-vertexes_coord(node1, j)) * (vertexes_coord(node0, j)-vertexes_coord(node1, j));
    mean_RWG_length += sqrt(RWG_length);
  }
  mean_RWG_length = mean_RWG_length/N_RWG;
  vertexes_coord.free();

  // computation of opposite vertexes of RWGs in triangles
  std::cout << "RWGNumber_oppVertexes_computation" << std::endl;
  std::flush(std::cout);
  blitz::Array<int, 2> RWGNumber_oppVertexes;
  RWGNumber_oppVertexes_computation(RWGNumber_oppVertexes, RWGNumber_signedTriangles, RWGNumber_edgeVertexes, triangle_vertexes);

  // writing to files
  writeIntToASCIIFile(MESH_DATA_PATH + "N_edges.txt", N_edges);
  writeIntToASCIIFile(MESH_DATA_PATH + "N_RWG.txt", N_RWG);
  writeDoubleToASCIIFile(MESH_DATA_PATH + "average_RWG_length.txt", mean_RWG_length);
  writeIntBlitzArray2DToBinaryFile(MESH_DATA_PATH + "triangle_vertexes.txt", triangle_vertexes);
  writeIntBlitzArray2DToBinaryFile(MESH_DATA_PATH + "RWGNumber_signedTriangles.txt", RWGNumber_signedTriangles);
  writeIntBlitzArray2DToBinaryFile(MESH_DATA_PATH + "RWGNumber_edgeVertexes.txt", RWGNumber_edgeVertexes);
  writeIntBlitzArray2DToBinaryFile(MESH_DATA_PATH + "RWGNumber_oppVertexes.txt", RWGNumber_oppVertexes);
  writeIntBlitzArray1DToASCIIFile(MESH_DATA_PATH + "is_closed_surface.txt", is_closed_surface);
  writeIntBlitzArray1DToASCIIFile(MESH_DATA_PATH + "triangles_surfaces.txt", triangles_surfaces);

  // Get peak memory usage of each rank
  long memusage_local = MemoryUsageGetPeak();
  std::cout << "MEMINFO " << argv[0] << " mem=" << memusage_local/(1024*1024) << " MB" << std::endl;
  flush(std::cout);
  return 0;
}
