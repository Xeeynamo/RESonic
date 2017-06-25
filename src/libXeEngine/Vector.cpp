#include "Vector.h"

void vec2::operator += (const float s){
	x += s;
	y += s;
}

void vec2::operator += (const vec2 &v){
	x += v.x;
	y += v.y;
}

void vec2::operator -= (const float s){
	x -= s;
	y -= s;
}

void vec2::operator -= (const vec2 &v){
	x -= v.x;
	y -= v.y;
}

void vec2::operator *= (const float s){
	x *= s;
	y *= s;
}

void vec2::operator *= (const vec2 &v){
	x *= v.x;
	y *= v.y;
}

void vec2::operator /= (const float s){
	x /= s;
	y /= s;
}

void vec2::operator /= (const vec2 &v){
	x /= v.x;
	y /= v.y;
}

vec2 operator + (const vec2 &u, const vec2 &v){
	return vec2(u.x + v.x, u.y + v.y);
}

vec2 operator + (const vec2 &v, const float s){
	return vec2(v.x + s, v.y + s);
}

vec2 operator + (const float s, const vec2 &v){
	return vec2(v.x + s, v.y + s);
}

vec2 operator - (const vec2 &u, const vec2 &v){
	return vec2(u.x - v.x, u.y - v.y);
}

vec2 operator - (const vec2 &v, const float s){
	return vec2(v.x - s, v.y - s);
}

vec2 operator - (const float s, const vec2 &v){
	return vec2(s - v.x, s - v.y);
}

vec2 operator - (const vec2 &v){
	return vec2(-v.x, -v.y);
}

vec2 operator * (const vec2 &u, const vec2 &v){
	return vec2(u.x * v.x, u.y * v.y);
}

vec2 operator * (const float s, const vec2 &v){
	return vec2(v.x * s, v.y * s);
}

vec2 operator * (const vec2 &v, const float s){
	return vec2(v.x * s, v.y * s);
}

vec2 operator / (const vec2 &u, const vec2 &v){
	return vec2(u.x / v.x, u.y / v.y);
}

vec2 operator / (const vec2 &v, const float s){
	return vec2(v.x / s, v.y / s);
}

vec2 operator / (const float s, const vec2 &v){
	return vec2(s / v.x, s / v.y);
}

bool operator == (const vec2 &u, const vec2 &v){
	return (u.x == v.x && u.y == v.y);
}

/* --------------------------------------------------------------------------------- */

void vec3::operator += (const float s){
	x += s;
	y += s;
	z += s;
}

void vec3::operator += (const vec3 &v){
	x += v.x;
	y += v.y;
	z += v.z;
}

void vec3::operator -= (const float s){
	x -= s;
	y -= s;
	z -= s;
}

void vec3::operator -= (const vec3 &v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void vec3::operator *= (const float s){
	x *= s;
	y *= s;
	z *= s;
}

void vec3::operator *= (const vec3 &v){
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void vec3::operator /= (const float s){
	x /= s;
	y /= s;
	z /= s;
}

void vec3::operator /= (const vec3 &v){
	x /= v.x;
	y /= v.y;
	z /= v.z;
}

vec3 operator + (const vec3 &u, const vec3 &v){
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec3 operator + (const vec3 &v, const float s){
	return vec3(v.x + s, v.y + s, v.z + s);
}

vec3 operator + (const float s, const vec3 &v){
	return vec3(v.x + s, v.y + s, v.z + s);
}

vec3 operator - (const vec3 &u, const vec3 &v){
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

vec3 operator - (const vec3 &v, const float s){
	return vec3(v.x - s, v.y - s, v.z - s);
}

vec3 operator - (const float s, const vec3 &v){
	return vec3(s - v.x, s - v.y, s - v.z);
}

vec3 operator - (const vec3 &v){
	return vec3(-v.x, -v.y, -v.z);
}

vec3 operator * (const vec3 &u, const vec3 &v){
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vec3 operator * (const float s, const vec3 &v){
	return vec3(v.x * s, v.y * s, v.z * s);
}

vec3 operator * (const vec3 &v, const float s){
	return vec3(v.x * s, v.y * s, v.z * s);
}

vec3 operator / (const vec3 &u, const vec3 &v){
	return vec3(u.x / v.x, u.y / v.y, u.z / v.z);
}

vec3 operator / (const vec3 &v, const float s){
	return vec3(v.x / s, v.y / s, v.z / s);
}

vec3 operator / (const float s, const vec3 &v){
	return vec3(s / v.x, s / v.y, s / v.z);
}

bool operator == (const vec3 &u, const vec3 &v){
	return (u.x == v.x && u.y == v.y && u.z == v.z);
}

/* --------------------------------------------------------------------------------- */

void vec4::operator += (const float s){
	x += s;
	y += s;
	z += s;
	w += s;
}

void vec4::operator += (const vec4 &v){
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

void vec4::operator -= (const float s){
	x -= s;
	y -= s;
	z -= s;
	w -= s;
}

void vec4::operator -= (const vec4 &v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

void vec4::operator *= (const float s){
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

void vec4::operator *= (const vec4 &v){
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
}

void vec4::operator /= (const float s){
	x /= s;
	y /= s;
	z /= s;
	w /= s;
}

void vec4::operator /= (const vec4 &v){
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
}

vec4 operator + (const vec4 &u, const vec4 &v){
	return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

vec4 operator + (const vec4 &v, const float s){
	return vec4(v.x + s, v.y + s, v.z + s, v.w + s);
}

vec4 operator + (const float s, const vec4 &v){
	return vec4(v.x + s, v.y + s, v.z + s, v.w + s);
}

vec4 operator - (const vec4 &u, const vec4 &v){
	return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

vec4 operator - (const vec4 &v, const float s){
	return vec4(v.x - s, v.y - s, v.z - s, v.w - s);
}

vec4 operator - (const float s, const vec4 &v){
	return vec4(s - v.x, s - v.y, s - v.z, s - v.w);
}

vec4 operator - (const vec4 &v){
	return vec4(-v.x, -v.y, -v.z, -v.w);
}

vec4 operator * (const vec4 &u, const vec4 &v){
	return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

vec4 operator * (const float s, const vec4 &v){
	return vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

vec4 operator * (const vec4 &v, const float s){
	return vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

vec4 operator / (const vec4 &u, const vec4 &v){
	return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w);
}

vec4 operator / (const vec4 &v, const float s){
	return vec4(v.x / s, v.y / s, v.z / s, v.w / s);
}

vec4 operator / (const float s, const vec4 &v){
	return vec4(s / v.x, s / v.y, s / v.z, s / v.w);
}

bool operator == (const vec4 &u, const vec4 &v){
	return (u.x == v.x && u.y == v.y && u.z == v.z && u.w && v.w);
}