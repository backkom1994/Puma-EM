/**********************************************************************
 *
 * scatter_mesh_per_cube.h
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

#ifndef SCATTER_MESH_PER_CUBE_H
#define SCATTER_MESH_PER_CUBE_H
#include <fstream>
#include <iostream>
#include <string>
#include <blitz/array.h>
#include <map>
#include <vector>
#include <algorithm>
#include <mpi.h>

using namespace std;

#include "readWriteBlitzArrayFromFile.h"
#include "dictionary.h"


void scatter_mesh_per_cube(blitz::Array<blitz::Array<int, 1>, 1>& allCubeIntArrays,
                           blitz::Array<blitz::Array<double, 1>, 1>& allCubeDoubleArrays,
                           const string simuDir,
                           const blitz::Array<int, 1>& local_ChunksNumbers,
                           const blitz::Array<int, 1>& local_chunkNumber_N_cubesNumbers,
                           const blitz::Array<int, 1>& local_chunkNumber_to_cubesNumbers,
                           const blitz::Array<int, 1>& local_cubeNumber_to_chunkNumbers);

#endif
