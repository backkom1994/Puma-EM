/**********************************************************************
 *
 * distribute_Z_cubes.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <blitz/array.h>
#include <vector>
#include <algorithm>
#include <mpi.h>

using namespace blitz;

#include "GetMemUsage.h"
#include "octtree.h"
#include "EMConstants.h"

int main(int argc, char* argv[]) {

  MPI::Init();
  int num_procs = MPI::COMM_WORLD.Get_size();
  int my_id = MPI::COMM_WORLD.Get_rank();

  string simuDir = ".";
  if ( argc > 2 ) {
     if( string(argv[1]) == "--simudir" ) simuDir = argv[2];
  }

  // general variables
  const string TMP = simuDir + "/tmp" + intToString(my_id);
  const string OCTTREE_DATA_PATH = TMP + "/octtree_data/";
  const string MESH_DATA_PATH = TMP + "/mesh/";
  writeIntToASCIIFile(OCTTREE_DATA_PATH + "CUBES_DISTRIBUTION.txt", 1);
  if (my_id==0) {
    int C;
    string filename = MESH_DATA_PATH + "C.txt";
    readIntFromASCIIFile(filename, C);
    blitz::Array<double, 2> cubes_centroids(C, 3);
    filename = MESH_DATA_PATH + "cubes_centroids.txt";
    readDoubleBlitzArray2DFromBinaryFile(filename, cubes_centroids);

    Octtree octtree(OCTTREE_DATA_PATH, cubes_centroids, my_id, num_procs);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  // we write 0 on the file
  writeIntToASCIIFile(OCTTREE_DATA_PATH + "CUBES_DISTRIBUTION.txt", 0);

  // Get peak memory usage of each rank
  float memusage_local_MB = static_cast<float>(MemoryUsageGetPeak())/(1024.0*1024.0);
  float tot_memusage_MB, max_memusage_MB;
  MPI_Reduce(&memusage_local_MB, &max_memusage_MB, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Reduce(&memusage_local_MB, &tot_memusage_MB, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (my_id==0) {
    std::cout << "MEMINFO " << argv[0] << " : max mem = " << max_memusage_MB << " MB, tot mem = " << tot_memusage_MB << " MB, avg mem = " << tot_memusage_MB/num_procs << " MB" << std::endl;
  }
  MPI::Finalize();
  return 0;
}
