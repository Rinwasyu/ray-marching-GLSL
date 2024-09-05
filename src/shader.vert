#version 460 core

/*
 * Copyright 2024 Rinwasyu
 * 
 * This file is part of ray-marching-GLSL.
 * 
 * Ray-marching-GLSL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Ray-marching-GLSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

in vec4 position;
out vec3 pos;

void main(void) {
	gl_Position = position;
	pos = position.xyz;
}