#pragma once

#include "linmath.h"

LINMATH_H_FUNC void mat4x4_transpose(mat4x4 M)
{
	int i;
	for (i = 1; i < 4; ++i) {
		float tmp = M[i][0];
		M[i][0] = M[0][i];
		M[0][i] = tmp;

	}
	for (i = 2; i < 4; ++i) {
		float tmp = M[i][0];
		M[i][0] = M[0][i];
		M[0][i] = tmp;
	}
	float tmp = M[3][0];
	M[3][0] = M[0][3];
	M[0][3] = tmp;
}

LINMATH_H_FUNC void mat4x4_scale_uniform(mat4x4 model, float scale) {
	model[0][0] *= scale;
	model[1][1] *= scale;
	model[2][2] *= scale;
}

LINMATH_H_FUNC void mat4x4_polar_append(mat4x4 model, float rotateZ, float rotateX, float rotateY) {
	mat4x4_rotate_Z(model, model, rotateZ);
	mat4x4_rotate_X(model, model, rotateX);
	mat4x4_rotate_Y(model, model, rotateY);
}

LINMATH_H_FUNC void mat4x4_translate_append(mat4x4 model, float x, float y, float z) {
	model[3][0] += x;
	model[3][1] += y;
	model[3][2] += z;
}

LINMATH_H_FUNC void mat4x4_clear(mat4x4 model) {
	for (int i = 0; i < 4 * 4; ++i) {
		model[i / 4][i % 4] = 0.0;
	}
}

LINMATH_H_FUNC void vec2_clear(vec2 v) {
	for (int i = 0; i < 2; ++i) {
		v[i] = 0.0;
	}
}

LINMATH_H_FUNC void vec3_clear(vec3 v) {
	for (int i = 0; i < 3; ++i) {
		v[i] = 0.0;
	}
}

LINMATH_H_FUNC void vec4_clear(vec4 v) {
	for (int i = 0; i < 4; ++i) {
		v[i] = 0.0;
	}
}


