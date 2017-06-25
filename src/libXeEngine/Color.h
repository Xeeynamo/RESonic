#pragma once
#include "XeBase.h"

namespace XeEngine
{
	typedef float XeColorF;
	typedef unsigned int XeColor32;
	typedef unsigned short XeColor16;
	typedef unsigned char XeColorChannel;

	//! \brief A class that manage ARGB colors in float and integer numbers
	class EXPORT ColorARGB
	{
	public:
		XeColorF a, r, g, b;

		//! \brief Initialize a XeColorARGB from channels in floating point
		ColorARGB(XeColorF r = .0f, XeColorF g = .0f, XeColorF b = .0f, XeColorF a = 1.0f);

		//! \brief Initialize a XeColorARGB from channels in integer
		ColorARGB(XeColorChannel r, XeColorChannel g, XeColorChannel b, XeColorChannel a = 255);

		//! \brief Initialize a XeColorARGB from a color in A8R8G8B8 format
		ColorARGB(XeColor32);

		//! \brief Initialize a XeColorARGB from a color in X1R5G5B5 format
		ColorARGB(XeColor16);

		//! \brief Copy a XeColorARGB to another one
		ColorARGB& operator = (const ColorARGB& o);

		//! \brief Multiply a XeColorARGB with A 
		ColorARGB& operator * (const XeColorF& o);

		//! \brief Multiply two XeColorARGB
		ColorARGB& operator * (const ColorARGB& o);

		//! \brief Compare two XeColorARGB
		bool operator == (const ColorARGB& o);

		//! \brief Compare two XeColorARGB
		bool operator != (const ColorARGB& o);

		//! \brief Transfer a color from A8R8G8B8 format to XeColorARGB
		ColorARGB operator = (const XeColor32& o);

		//! \brief Transfer a color from X1R5G5B5 format to XeColorARGB
		ColorARGB operator = (const XeColor16& o);

		//! \brief Convert a color from XeColorARGB to A8R8G8B8 format
		//! \return The color in A8R8G8B8
		XeColor32 ToColor32() const;

		//! \brief Convert a color from XeColorARGB to X1R5G5B5 format
		//! \return The color in X1R5G5B5
		XeColor16 ToColor16() const;

		//! \brief Convert a color from A8R8G8B8 format to XeColorARGB
		//! \param The color in A8R8G8B8
		void Convert(XeColor32);

		//! \brief Convert a color from X1R5G5B5 format to XeColorARGB
		//! \param The color in X1R5G5B5
		void Convert(XeColor16);

		//! \brief Convert a single color's channel from integer to float
		//! \param Color's channel in integer
		//! \return Color's channel in floating point
		static XeColorF ColorIntToColorFloat(XeColorChannel color);

		//! \brief Convert a single color's channel from float to integer
		//! \param Color's channel in floating point
		//! \return Color's channel in integer
		static XeColorChannel ColorFloatToColorInt(XeColorF color);
	};

	//! \brief A class that manage HSV colors in float numbers
	class EXPORT ColorHSV
	{
	public:
		XeColorF h, s, v;

		//! \brief Create a HSV color
		//! \param H
		//! \param Saturation
		//! \param Light
		ColorHSV(XeColorF h = .0f, XeColorF s = .0f, XeColorF v = .0f);

		//! \brief Copy a XeColorHSV to another one
		ColorHSV& operator = (const ColorHSV& o);

		//! \brief Compare two XeColorHSV
		bool operator == (const ColorHSV& o);

		//! \brief Compare two XeColorHSV
		bool operator != (const ColorHSV& o);
	};

	//! \brief A class that manage ARGB and HSV colors in float and integer numbers and perform convertions
	class EXPORT Color : public ColorARGB
	{
	private:
	protected:
	public:
		//! \brief Create a XeColor from XeColorARGB
		//! \param XeColorARGB class
		Color(const ColorARGB&);
		//! \brief Create a XeColor from XeColorHSV
		//! \param XeColorHSV class
		Color(ColorHSV&);

		//! \brief Transfer XeColorARGB to XeColor
		Color operator = (const ColorARGB&);

		//! \brief Transfer XeColorHSV to XeColor
		//! \warning This operator can influence in terms of performance
		Color operator = (const ColorHSV&);

		//! \brief Convert XeColor to XeColorHSV
		//! \return XeColorHSV class
		//! \warning This method can influence in terms of performance
		ColorHSV ToHSV();

		//! \brief Convert XeColorHSV to XeColorARGB
		//! \param XeColorHSV class
		//! \return XeColorARGB class
		//! \warning This method can influence in terms of performance
		static ColorARGB Convert(const ColorHSV&);

		//! \brief Convert XeColorARGB to XeColorHSV
		//! \param XeColorARGB class
		//! \return XeColorHSV class
		//! \warning This method can influence in terms of performance
		static ColorHSV Convert(const ColorARGB&);
	};
}
