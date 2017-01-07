/**********************************************************************
 *
 * GetMemUsage.h
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

#ifndef GETMEMUSAGE_H
#define GETMEMUSAGE_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
    
// written by Maxime Martinasso, november 2011

static long parseLine(char* line)
{
    long i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    i = atol(line);
    return i;
}
    

long MemoryUsageGetPeak()
{ 
    FILE* file = fopen("/proc/self/status", "r");
    long result = 0;
    char line[128];
    
    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmHWM:", 5) == 0) 
        {
           result = parseLine(line);
           break;
        }
    }
    fclose(file);
    return result*1024;
}

#endif
