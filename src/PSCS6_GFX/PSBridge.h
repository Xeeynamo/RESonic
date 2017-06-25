#pragma once
#include "GFX.h"

extern FormatRecord * gFormatRecord;
static VPoint GetFormatImageSize(void)
{
	VPoint returnPoint = {0, 0};
	if (gFormatRecord->HostSupports32BitCoordinates && gFormatRecord->PluginUsing32BitCoordinates)
	{
		returnPoint.v = gFormatRecord->imageSize32.v;
		returnPoint.h = gFormatRecord->imageSize32.h;
	}
	else
	{
		returnPoint.v = gFormatRecord->imageSize.v;
		returnPoint.h = gFormatRecord->imageSize.h;
	}
	return returnPoint;
}
static void SetFormatImageSize(VPoint inPoint)
{
	if (gFormatRecord->HostSupports32BitCoordinates && 
		gFormatRecord->PluginUsing32BitCoordinates)
	{
		gFormatRecord->imageSize32.v = inPoint.v;
		gFormatRecord->imageSize32.h = inPoint.h;
	}
	else
	{
		gFormatRecord->imageSize.v = static_cast<int16>(inPoint.v);
		gFormatRecord->imageSize.h = static_cast<int16>(inPoint.h);
	}
}
static void SetFormatTheRect(VRect inRect)
{
	if (gFormatRecord->HostSupports32BitCoordinates && 
		gFormatRecord->PluginUsing32BitCoordinates)
	{
		gFormatRecord->theRect32.top = inRect.top;
		gFormatRecord->theRect32.left = inRect.left;
		gFormatRecord->theRect32.bottom = inRect.bottom;
		gFormatRecord->theRect32.right = inRect.right;
	}
	else
	{
		gFormatRecord->theRect.top = static_cast<int16>(inRect.top);
		gFormatRecord->theRect.left = static_cast<int16>(inRect.left);
		gFormatRecord->theRect.bottom = static_cast<int16>(inRect.bottom);
		gFormatRecord->theRect.right = static_cast<int16>(inRect.right);
	}
}
static int16 GetFormatImageDepth()
{
	return gFormatRecord->depth;
}
static void SetFormatImageDepth(int16 depth)
{
	gFormatRecord->depth = depth;
}
static int16 GetFormatImagePlanes()
{
	return gFormatRecord->planes;
}
static void SetFormatImagePlanes(int16 planes)
{
	gFormatRecord->depth = planes;
}