#######################################################################
##
## setup_GMSH.py
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

import sys, os, argparse
from PyGmsh import executeGmsh, write_geo, isGeoFileThere

if __name__=='__main__':
    parser = argparse.ArgumentParser(description='...')
    parser.add_argument('--inputdir')
    parser.add_argument('--simudir')
    cmdline = parser.parse_args()
    simuDirName = cmdline.simudir
    inputDirName = cmdline.inputdir
    simuParams = 'simulation_parameters'

    if 'geo' not in os.listdir(simuDirName):
        os.mkdir(os.path.join(simuDirName, 'geo'))
    geoDirName = os.path.join(simuDirName, 'geo')

    sys.path.append(os.path.abspath(inputDirName))
    exec('from ' + simuParams + ' import *')
    # JPA : si l'utilisateur n'a pas donne de chemin vers la geometrie, on cherche dans le repertoire de donnees
    if params_simu.pathToTarget == "":
        params_simu.pathToTarget = inputDirName;

    filename = 'GMSHcommand.sh'
    if params_simu.meshToMake:
        os.system("cp " + os.path.join(params_simu.pathToTarget, params_simu.targetName + '.geo') + ' ' + geoDirName)
        write_geo(geoDirName, params_simu.targetName, 'lc', c/params_simu.f * params_simu.lc_factor)
        write_geo(geoDirName, params_simu.targetName, 'lx', params_simu.lx)
        write_geo(geoDirName, params_simu.targetName, 'ly', params_simu.ly)
        write_geo(geoDirName, params_simu.targetName, 'lz', params_simu.lz)
        isGeoFileThere(geoDirName, params_simu.targetName)
        f = open(filename, 'w')
        GMSH_command = 'rm -f ' + os.path.join(geoDirName, params_simu.targetName) + '.msh* \n'
        GMSH_command += 'gmsh -2 -algo del2d -rand 1e-06 ' + os.path.join(geoDirName, params_simu.targetName) + '.geo' + ' -string "General.ExpertMode=1;"\n'
        f.write(GMSH_command)
        f.write("exit 0" + "\n")
    else:
        f = open(filename, 'w')
        f.write("exit 0" + "\n")
        os.system("cp " + os.path.join(params_simu.pathToTarget, params_simu.targetName + params_simu.meshFileTermination) + ' ' + geoDirName)
    f.close()
    os.system("chmod u+x " + filename)
        

