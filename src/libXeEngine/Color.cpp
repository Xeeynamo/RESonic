#include "Color.h"
#include <math.h>

XeEngine::ColorARGB::ColorARGB(XeColorF r, XeColorF g, XeColorF b, XeColorF a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
XeEngine::ColorARGB::ColorARGB(XeColorChannel r, XeColorChannel g, XeColorChannel b, XeColorChannel a)
{
	this->r = ColorIntToColorFloat(r);
	this->g = ColorIntToColorFloat(g);
	this->b = ColorIntToColorFloat(b);
	this->a = ColorIntToColorFloat(a);
}
XeEngine::ColorARGB::ColorARGB(XeColor32 color)
{
	Convert((XeColor32)color);
}
XeEngine::ColorARGB::ColorARGB(XeColor16 color)
{
	Convert((XeColor16)color);
}

XeEngine::ColorARGB& XeEngine::ColorARGB::operator = (const ColorARGB& o)
{
	if (this != &o)
	{
		this->r = o.r;
		this->g = o.g;
		this->b = o.b;
		this->a = o.a;
	}
	return *this;
}
XeEngine::ColorARGB& XeEngine::ColorARGB::operator * (const XeColorF& o)
{
	this->r *= o;
	this->g *= o;
	this->b *= o;
	this->a *= o;
	return *this;
}
XeEngine::ColorARGB& XeEngine::ColorARGB::operator * (const ColorARGB& o)
{
	if (this != &o)
	{
		this->r *= o.r;
		this->g *= o.g;
		this->b *= o.b;
		this->a *= o.a;
	}
	return *this;
}
bool XeEngine::ColorARGB::operator == (const ColorARGB& o)
{
	if (this != &o)
	{
		if (fabs(this->r - o.r) < 0.0000152 &&
			fabs(this->g - o.g) < 0.0000152 &&
			fabs(this->b - o.b) < 0.0000152 &&
			fabs(this->a - o.a) < 0.0000152)
			return true;
		else return false;
	}
	else return true;
}
bool XeEngine::ColorARGB::operator != (const ColorARGB& o)
{
	return (*this == o) == false;
}
XeEngine::ColorARGB XeEngine::ColorARGB::operator = (const XeColor32& o)
{
	Convert((XeColor32)o);
	return *this;
}
XeEngine::ColorARGB XeEngine::ColorARGB::operator = (const XeColor16& o)
{
	Convert((XeColor16)o);
	return *this;
}


XeEngine::XeColor32 XeEngine::ColorARGB::ToColor32() const
{
	return (ColorFloatToColorInt(b) <<  0) |
		(ColorFloatToColorInt(g) <<  8) |
		(ColorFloatToColorInt(r) << 16) |
		(ColorFloatToColorInt(a) << 24);
}
XeEngine::XeColor16 XeEngine::ColorARGB::ToColor16() const
{
	return (((ColorFloatToColorInt(b) >> 3)&0x1F) << 0) |
		(((ColorFloatToColorInt(g) >> 3)&0x1F) << 5) |
		(((ColorFloatToColorInt(r) >> 3)&0x1F) << 10);
}
void XeEngine::ColorARGB::Convert(XeColor32 o)
{
	this->b = ColorIntToColorFloat((o>>0)&0xFF);
	this->g = ColorIntToColorFloat((o>>8)&0xFF);
	this->r = ColorIntToColorFloat((o>>16)&0xFF);
	this->a = ColorIntToColorFloat((o>>24)&0xFF);
}
void XeEngine::ColorARGB::Convert(XeColor16 o)
{
	XeColorChannel tmp;

	tmp = ((o>>0)&0x1F);
	this->b = ColorIntToColorFloat( (tmp<<3) | (tmp>>1) );
	tmp = ((o>>5)&0x1F);
	this->b = ColorIntToColorFloat( (tmp<<3) | (tmp>>1) );
	tmp = ((o>>10)&0x1F);
	this->b = ColorIntToColorFloat( (tmp<<3) | (tmp>>1) );
	this->a = 1.0f;
}
XeEngine::XeColorF XeEngine::ColorARGB::ColorIntToColorFloat(XeColorChannel color)
{
	return float(color) / 255.0f;
}
XeEngine::XeColorChannel XeEngine::ColorARGB::ColorFloatToColorInt(XeColorF color)
{
	return (XeColorChannel)(color * 255.0f);
}

XeEngine::ColorHSV::ColorHSV(XeColorF h, XeColorF s, XeColorF v)
{
	this->h = h;
	this->s = s;
	this->v = v;
}
XeEngine::ColorHSV& XeEngine::ColorHSV::operator = (const ColorHSV& o)
{
	if (this != &o)
	{
		this->h = o.h;
		this->s = o.s;
		this->v = o.v;
	}
	return *this;
}
bool XeEngine::ColorHSV::operator == (const ColorHSV& o)
{
	if (this != &o)
	{
		if (fabs(this->h - o.h) < 0.0000152 &&
			fabs(this->s - o.s) < 0.0000152 &&
			fabs(this->v - o.v) < 0.0000152)
			return true;
		else return false;
	}
	else return true;
}
bool XeEngine::ColorHSV::operator != (const ColorHSV& o)
{
	return (*this == o) == false;
}

XeEngine::Color::Color(const XeEngine::ColorARGB& o) : XeEngine::ColorARGB(o)
{
}
XeEngine::Color::Color(ColorHSV& o)
{
	*((ColorARGB*)this) = XeEngine::Color::Convert(o);
}
XeEngine::Color XeEngine::Color::operator = (const ColorARGB& o)
{
	return *((ColorARGB*)this) = o;
}
XeEngine::Color XeEngine::Color::operator = (const ColorHSV& o)
{
	return *this = Convert(ColorHSV(o));
}

XeEngine::ColorHSV XeEngine::Color::ToHSV()
{
	return Convert(*this);
}

XeEngine::ColorARGB XeEngine::Color::Convert(const ColorHSV& in)
{
	float hh, p, q, t, ff;
	long i;
	ColorARGB out;

	if(in.s <= 0.0) // < is bogus, just shuts up warnings
	{
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
	hh = in.h;
	while(hh >= 360.0f) hh -= 360.0f;
	hh /= 60.0f;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0f - in.s);
	q = in.v * (1.0f - (in.s * ff));
	t = in.v * (1.0f - (in.s * (1.0f - ff)));

	switch(i)
	{
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;
	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}
XeEngine::ColorHSV XeEngine::Color::Convert(const ColorARGB& in)
{
	ColorHSV out;
	float min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min  < in.b ? min  : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max  > in.b ? max  : in.b;

	out.v = max;                                // v
	delta = max - min;
	if( max > 0.0 )
	{
		out.s = (delta / max);                  // s
	}
	else
	{
		// r = g = b = 0                        // s = 0, v is undefined
		out.s = 0.0;
		//out.h = NAN;                            // its now undefined
		out.h = 0.0;                            // its now undefined
		return out;
	}
	if( in.r >= max )                           // > is bogus, just keeps compilor happy
		out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
	else if( in.g >= max )
		out.h = 2.0f + ( in.b - in.r ) / delta;  // between cyan & yellow
	else
		out.h = 4.0f + ( in.r - in.g ) / delta;  // between magenta & cyan

	out.h *= 60.0f;                              // degrees

	if( out.h < 0.0f )
		out.h += 360.0f;

	return out;
}
