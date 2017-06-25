#pragma once

struct vec2 {
	float x, y;

	vec2(){}
	vec2(const float ixy){
		x = y = ixy;
	}
	vec2(const float ix, const float iy){
		x = ix;
		y = iy;
	}
	operator float *() const { return (float *) &x; }

	void operator += (const float s);
	void operator += (const vec2 &v);
	void operator -= (const float s);
	void operator -= (const vec2 &v);
	void operator *= (const float s);
	void operator *= (const vec2 &v);
	void operator /= (const float s);
	void operator /= (const vec2 &v);
};

vec2 operator + (const vec2 &u, const vec2 &v);
vec2 operator + (const vec2 &v, const float s);
vec2 operator + (const float s, const vec2 &v);

vec2 operator - (const vec2 &u, const vec2 &v);
vec2 operator - (const vec2 &v, const float s);
vec2 operator - (const float s, const vec2 &v);

vec2 operator - (const vec2 &v);

vec2 operator * (const vec2 &u, const vec2 &v);
vec2 operator * (const float s, const vec2 &v);
vec2 operator * (const vec2 &v, const float s);

vec2 operator / (const vec2 &u, const vec2 &v);
vec2 operator / (const vec2 &v, const float s);
vec2 operator / (const float s, const vec2 &v);

bool operator == (const vec2 &u, const vec2 &v);

/* --------------------------------------------------------------------------------- */

struct vec3 {
	float x, y, z;

	vec3(){}
	vec3(const float ixyz){
		x = y = z = ixyz;
	}
	vec3(const float ix, const float iy, const float iz){
		x = ix;
		y = iy;
		z = iz;
	}
	vec3(const vec2 iv, const float iz){
		x = iv.x;
		y = iv.y;
		z = iz;
	}
	vec3(const float ix, const vec2 iv){
		x = ix;
		y = iv.x;
		z = iv.y;
	}
	operator float *() const { return (float *) &x; }

	vec2 xy() const { return vec2(x, y); }
	vec2 yz() const { return vec2(y, z); }
	vec2 xz() const { return vec2(x, z); }

	void operator += (const float s);
	void operator += (const vec3 &v);
	void operator -= (const float s);
	void operator -= (const vec3 &v);
	void operator *= (const float s);
	void operator *= (const vec3 &v);
	void operator /= (const float s);
	void operator /= (const vec3 &v);
};

vec3 operator + (const vec3 &u, const vec3 &v);
vec3 operator + (const vec3 &v, const float s);
vec3 operator + (const float s, const vec3 &v);

vec3 operator - (const vec3 &u, const vec3 &v);
vec3 operator - (const vec3 &v, const float s);
vec3 operator - (const float s, const vec3 &v);

vec3 operator - (const vec3 &v);

vec3 operator * (const vec3 &u, const vec3 &v);
vec3 operator * (const float s, const vec3 &v);
vec3 operator * (const vec3 &v, const float s);

vec3 operator / (const vec3 &u, const vec3 &v);
vec3 operator / (const vec3 &v, const float s);
vec3 operator / (const float s, const vec3 &v);

bool operator == (const vec3 &u, const vec3 &v);

/* --------------------------------------------------------------------------------- */

struct vec4 {
	float x, y, z, w;

	vec4(){}
	vec4(const float ixyzw){
		x = y = z = w = ixyzw;
	}
	vec4(const float ix, const float iy, const float iz, const float iw){
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}
	vec4(const vec2 iv, const float iz, const float iw){
		x = iv.x;
		y = iv.y;
		z = iz;
		w = iw;
	}
	vec4(const float ix, const vec2 iv, const float iw){
		x = ix;
		y = iv.x;
		z = iv.y;
		w = iw;
	}
	vec4(const float ix, const float iy, const vec2 iv){
		x = ix;
		y = iy;
		z = iv.x;
		w = iv.y;
	}
	vec4(const vec2 iv0, const vec2 iv1){
		x = iv0.x;
		y = iv0.y;
		z = iv1.x;
		w = iv1.y;
	}
	vec4(const vec3 iv, const float iw){
		x = iv.x;
		y = iv.y;
		z = iv.z;
		w = iw;
	}
	vec4(const float ix, const vec3 iv){
		x = ix;
		y = iv.x;
		z = iv.y;
		w = iv.z;
	}
	operator float *() const { return (float *) &x; }

	vec2 xy() const { return vec2(x, y); }
	vec2 xz() const { return vec2(x, z); }
	vec2 xw() const { return vec2(x, w); }
	vec2 yz() const { return vec2(y, z); }
	vec2 yw() const { return vec2(y, w); }
	vec2 zw() const { return vec2(z, w); }
	vec3 xyz() const { return vec3(x, y, z); }
	vec3 yzw() const { return vec3(y, z, w); }

	void operator += (const float s);
	void operator += (const vec4 &v);
	void operator -= (const float s);
	void operator -= (const vec4 &v);
	void operator *= (const float s);
	void operator *= (const vec4 &v);
	void operator /= (const float s);
	void operator /= (const vec4 &v);
};

vec4 operator + (const vec4 &u, const vec4 &v);
vec4 operator + (const vec4 &v, const float s);
vec4 operator + (const float s, const vec4 &v);

vec4 operator - (const vec4 &u, const vec4 &v);
vec4 operator - (const vec4 &v, const float s);
vec4 operator - (const float s, const vec4 &v);

vec4 operator - (const vec4 &v);

vec4 operator * (const vec4 &u, const vec4 &v);
vec4 operator * (const float s, const vec4 &v);
vec4 operator * (const vec4 &v, const float s);

vec4 operator / (const vec4 &u, const vec4 &v);
vec4 operator / (const vec4 &v, const float s);
vec4 operator / (const float s, const vec4 &v);

bool operator == (const vec4 &u, const vec4 &v);