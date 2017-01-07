#######################################################################
##
## FMM_Znear.py
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

from mpi4py import MPI
import os, sys, commands
from scipy import array
from Z_MoM import Z_MoM_triangles_arraysFromCube
from ReadWriteBlitzArray import writeBlitzArrayToDisk
from meshClass import CubeClass
import copy

def Z_nearPerCube(path, cube, CFIE, cubeNumber, w, eps_r, mu_r, ELEM_TYPE, Z_TMP_ELEM_TYPE, TDS_APPROX, Z_s, MOM_FULL_PRECISION):
    """this function computes the part of the MoM Z matrix corresponding to
    the cube 'cubeNumber' as the observer cube and all its neighbors cubes,
    including itself, as the source cubes."""
    # call of the C++ routine for computing the interaction matrix
    Z_CFIE_near_local = Z_MoM_triangles_arraysFromCube(cube, CFIE, w, eps_r, mu_r, TDS_APPROX, Z_s, MOM_FULL_PRECISION)
    # we create a 1-D array out of Z_CFIE_near_local
    Z_CFIE_nearPerCube = array(Z_CFIE_near_local.astype(ELEM_TYPE).flat)
    writeBlitzArrayToDisk(Z_CFIE_near_local.astype(Z_TMP_ELEM_TYPE), os.path.join(path, str(cubeNumber)))
    return Z_CFIE_nearPerCube

def chunk_of_Z_nearCRS_Computation(CFIE, cubesNumbers, w, eps_r, mu_r, ELEM_TYPE, Z_TMP_ELEM_TYPE, TDS_APPROX, Z_s, MOM_FULL_PRECISION, pathToSaveTo):
    """this function computes a chunk of the near non-diagonal part of the MoM matrix,
    but saves all the atomic elements on the disk. These elements will later on be used 
    by chunk_of_Z_nearCRS_Assembling and MgPrecondition"""
    pathToReadCubeFrom = pathToSaveTo
    list_cubes = compute_list_cubes(cubesNumbers, pathToReadCubeFrom)
    for cubeNumber, cube in list_cubes.items():
        Z_CFIE_near_tmp = Z_nearPerCube(pathToSaveTo, cube, CFIE, cubeNumber, w, eps_r, mu_r, ELEM_TYPE, Z_TMP_ELEM_TYPE, TDS_APPROX, Z_s, MOM_FULL_PRECISION)

def Z_nearCRS_Computation(my_id, processNumber_to_ChunksNumbers, chunkNumber_to_cubesNumbers, CFIE, MAX_BLOCK_SIZE, w, eps_r, mu_r, ELEM_TYPE, Z_TMP_ELEM_TYPE, TDS_APPROX, Z_s, MOM_FULL_PRECISION, pathToSaveTo):
    """this function computes Z_CFIE_near by slices and stores them on the disk."""
    index, percentage = 0, 0
    for chunkNumber in processNumber_to_ChunksNumbers[my_id]:
        if my_id==0:
            newPercentage = int(index * 100.0/len(processNumber_to_ChunksNumbers[my_id]))
            if (newPercentage - percentage)>=5:
                print "Process", my_id, ": computing Z_CFIE_near chunk.", newPercentage, "% completed"
                sys.stdout.flush()
                percentage = newPercentage
        pathToSaveToChunk = os.path.join(pathToSaveTo, "chunk" + str(chunkNumber))
        cubesNumbers = chunkNumber_to_cubesNumbers[chunkNumber]
        chunk_of_Z_nearCRS_Computation(CFIE, cubesNumbers, w, eps_r, mu_r, ELEM_TYPE, Z_TMP_ELEM_TYPE, TDS_APPROX, Z_s, MOM_FULL_PRECISION, pathToSaveToChunk)
        index += 1

def compute_list_cubes(cubesNumbers, pathToReadFrom):
    """returns a list of cubes"""
    list_cubes = {}
    for i in range(len(cubesNumbers)):
        cubeNumber = cubesNumbers[i]
        pathToReadCubeFrom = pathToReadFrom
        cube = CubeClass()
        cube.setIntArraysFromFile(pathToReadCubeFrom, cubeNumber)
        list_cubes[cubeNumber] = copy.copy(cube)
    return list_cubes
