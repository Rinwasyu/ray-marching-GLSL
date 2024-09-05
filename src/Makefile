#
# Copyright 2024 Rinwasyu
# 
# This file is part of ray-marching-GLSL.
# 
# Ray-marching-GLSL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Ray-marching-GLSL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 

.PHONY: all clean

PROGNAME ?= main
CC ?= clang
CFLAGS ?= -std=c17 -W -Wall -Wextra -O3
LDFLAGS ?= -lglfw -lGL -lGLEW -lm

all: $(PROGNAME)

clean:
	rm $(PROGNAME)

$(PROGNAME): $(PROGNAME).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<