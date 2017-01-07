#######################################################################
##
## installBlitz++.py
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

import os

import os

def installBlitz():
    URL = "http://ftp.debian.org/debian/pool/main/b/blitz++/"
    TARGET = "blitz++_0.9.orig"
    os.system("wget " + URL + TARGET + ".tar.gz")
    os.system("tar xvzf " + TARGET + ".tar.gz")
    os.chdir("blitz++-0.9.orig")
    os.system("./configure")
    os.system("make lib")
    os.system("make install")

if __name__=="__main__":
    installBlitz()



