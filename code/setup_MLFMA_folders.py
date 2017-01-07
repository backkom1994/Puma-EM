#######################################################################
##
## setup_MLFMA_folders.py
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

import os, argparse
from mpi4py import MPI

if __name__=='__main__':
    my_id = MPI.COMM_WORLD.Get_rank()
    parser = argparse.ArgumentParser(description='...')
    parser.add_argument('--simudir')
    cmdline = parser.parse_args()
    simuDirName = cmdline.simudir

    if (my_id==0):
        if 'result' not in os.listdir(simuDirName):
            os.mkdir(os.path.join(simuDirName, 'result'))
    # creation of the directories
    tmpDirName = os.path.join(simuDirName, 'tmp' + str(my_id))
    os.mkdir( tmpDirName )
    os.mkdir( os.path.join(tmpDirName,'Z_tmp') )
    os.mkdir( os.path.join(tmpDirName,'Z_near') )
    os.mkdir( os.path.join(tmpDirName,'Mg_LeftFrob') )
    os.mkdir( os.path.join(tmpDirName,'mesh') )
    os.mkdir( os.path.join(tmpDirName,'octtree_data') )
    os.mkdir( os.path.join(tmpDirName,'V_CFIE') )
    os.mkdir( os.path.join(tmpDirName,'ZI') )
    os.mkdir( os.path.join(tmpDirName,'iterative_data') )
    os.mkdir( os.path.join(tmpDirName,'pickle') )
