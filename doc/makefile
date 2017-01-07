#######################################################################
##
## makefile
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

documentation:
	doxygen Doxyfile;
	latex guide; bibtex guide; latex guide; latex guide; dvipdf guide.dvi
	latex EMtheory; bibtex EMtheory; latex EMtheory; latex EMtheory; dvipdf EMtheory.dvi
guide:
	latex guide.tex; bibtex guide; latex guide; latex guide.tex; dvips guide.dvi; ps2pdf guide.ps
EMtheory:
	latex EMtheory; bibtex EMtheory; latex EMtheory; latex EMtheory; dvips EMtheory.dvi; ps2pdf EMtheory.ps
clean: 
	rm -rf *~ html latex *.aux *.bbl *.blg *.dvi *.log *.toc *.ps *.pdf;
