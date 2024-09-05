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

in vec3 pos;
uniform vec3 ray_vector;
out vec4 frag_color;

float sdf_sphere(vec3 p, float radius) {
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z) - radius;
}

float sdf_sphere_dx(vec3 p, float radius) {
	return p.x/sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

float sdf_sphere_dy(vec3 p, float radius) {
	return p.y/sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

float sdf_sphere_dz(vec3 p, float radius) {
	return p.z/sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

float sdf_box(vec3 p, vec3 b) {
	vec3 q = abs(p) - b;
	vec3 r = max(q, vec3(0,0,0));
	return sqrt(r.x*r.x+r.y*2+r.z*2) + min(max(q.x, max(q.y, q.z)), 0);
}

void main(void) {
	vec3 box_pos = vec3(0, 0, -7);
	vec3 sphere_pos = vec3(0, 0, -10);
	vec3 ray = normalize(ray_vector);
	
	frag_color = vec4(0, 0, 0, 1);
	
	for (vec3 p = pos; p.z >= -10; p += vec3(pos.xy, -5)/500) {
		if (sdf_sphere(p-sphere_pos, 2) <= 0.0001) {
			vec3 n = vec3(sdf_sphere_dx(p-sphere_pos, 2), sdf_sphere_dy(p-sphere_pos, 2), sdf_sphere_dz(p-sphere_pos, 2));
			frag_color = vec4(1, 1, 1, 1) * dot(ray, normalize(n));
			break;
		}
	}
}