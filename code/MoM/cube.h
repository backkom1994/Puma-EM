/**********************************************************************
 *
 * cube.h
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

#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <blitz/array.h>
#include <vector>
#include <algorithm>  // Include STL algorithms for sorting lists and vectors

using namespace std;

#include "EMConstants.h"
#include "GK_triangle.h"
#include "dictionary.h"

class Cube {
    //! the absolute number of the current cube
    int number;
    //! the current index of the current cube in the list of all cubes at a given level
    int index;
    //! index before sorting
    int oldIndex;
    //! the absolute number of the father
    int fatherNumber;
    //! index of the father 
    int fatherIndex;
  public:
    //! the process number of the current cube
    int procNumber;
    //! the process number of the father of the current cube
    int fatherProcNumber;
    //! the indexes of the children of the current cube
    std::vector<int> sonsIndexes;
    //! the processes number of the children of the current cube
    std::vector<int> sonsProcNumbers;
    //! the indexes of the neighbors of the current cube
    std::vector<int> neighborsIndexes;
    //! \brief the indexes of the cubes that will participate to the alpha translation to the current cube
    //! and that are located on the same process as that of the current cube
    std::vector<int> localAlphaTransParticipantsIndexes;
    //! \brief the indexes of the cubes that will participate to the alpha translation to the current cube
    //! and that are located on another process as that of the current cube
    std::vector<int> nonLocalAlphaTransParticipantsIndexes;
    //! the absolute coordinates of the center of the current cube 
    float rCenter[3];
    //! \brief the absolute cartesian coordinates of the center of the current cube
    //! calculated with respect to the location of the Father of all Cubes and the side length of the current cube  
    float absoluteCartesianCoord[3];
    //! the numbers of the RWGs pertaining to the current cube
    std::vector<int> RWG_numbers;
    std::vector<int> RWG_numbers_CFIE_OK;
    std::vector<int> Triangle_numberOfRWGs;
    std::vector<int> TriangleToRWGindex;
    std::vector<float> TriangleToRWGweight; 
    std::vector<float> TriangleToRWG_ropp;
    blitz::Array<float, 2> triangle_GaussCoord;
    blitz::Array<float, 2> triangle_nHat;
    // constructors
    Cube(void){};
    //! the base constructor
    /*!
      \param level the number of the level
      \param sideLength the length of the cube side
      \param big_cube_lower_coord the lower coordinate of the father of all cubes
      \param r_c the coordinates of cube center
      \return the constructed cube
    */
    Cube(const int level,
         const double sideLength,
         const double big_cube_lower_coord[3],
         const double r_c[3]);
    //! allows a cube to be overwritten by the provided cube
    /*!
      \param cubeToCopy the cube to copy
    */
    void copyCube (const Cube& cubeToCopy);
    Cube(const Cube&); // copy constructor
    Cube& operator=(const Cube&); // copy assignment operator
    //! the constructor from a children cube
    /*!
      \param sonCube the children cube
      \param level the number of the level
      \param big_cube_lower_coord the lower coordinate of the father of all cubes
      \param sideLength the length of the cube side
      \return the constructed cube
    */
    Cube(const Cube& sonCube,
         const int level,
         const double big_cube_lower_coord[3],
         const double sideLength);
    //! the destructor
    ~Cube();

    // specific functions
    void addSon(const Cube&);
    //! returns the sonsIndexes vector
    void setIndex(const int i) {index = i;}
    int getIndex(void) const {return index;}
    void setOldIndex(const int i) {oldIndex = i;}
    int getOldIndex(void) const {return oldIndex;}
    int getNumber(void) const {return number;}
    int getProcNumber(void) const {return procNumber;}
    int getFatherNumber(void) const {return fatherNumber;}
    void setFatherNumber(const int n) {fatherNumber = n;}
    int getFatherIndex(void) const {return fatherIndex;}
    void setFatherIndex(const int i) {fatherIndex = i;}

    //! \brief computes the points locations and values for the arguments for the complex exponentials 
    //! that will be used in computing the radiation function of the leaf cube 
    /*!
      \param target_mesh the mesh of the target, C++ object
      \param N_Gauss int, the number of points per triangles
      \return void
    */
    void computeGaussLocatedArguments(const blitz::Array<int, 1>& local_RWG_numbers,
                                      const blitz::Array<int, 1>& local_RWG_Numbers_CFIE_OK,
                                      const blitz::Array<int, 2>& local_RWGNumbers_signedTriangles,
                                      const blitz::Array<float, 2>& local_RWGNumbers_trianglesCoord,
                                      const int startIndex_in_localArrays,
                                      const int NRWG,
                                      const int N_Gauss);
    // overloaded operators
    bool operator== (const Cube &) const;
    bool operator< (const Cube &) const;
};

#endif
