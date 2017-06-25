#include "XeEngineLV2.h"

float xetexture_colorfilter[16];

XeTexture::XeTexture()
{
	_id = 0xFFFFFFFF;
	cachestate = 0;
	vertexwritten = 0;
	textureres = 1;
	posx = 0.0f;
	posy = 0.0f;
	posz = 0.0f;

	for(int i=0; i<5; i++)
		vertices[i] = 0.0f;
	for(int i=0; i<4; i++)
	{
		vertexblock[i].r = 1.0f;
		vertexblock[i].g = 1.0f;
		vertexblock[i].b = 1.0f;
		vertexblock[i].a = 1.0f;
	}
	Destroy();
}
XeTexture::~XeTexture()
{
	Destroy();
}

bool XeTexture::Create(XeEngine::XeImage *image)
{
	bool result;
	if (!image) return false;
	if (_id != 0xFFFFFFFF) Destroy();
	result = Create(image->GetWidth(), image->GetHeight(), image->GetTextureCount(), image->GetFormat(), image->GetData());
	SetResolution(image->GetResolution());
	return result;
}
bool XeTexture::Create(short w, short h, short depth, XeEngine::XeTexturePixelFormat f, void *data)
{
	if (!data) return false;
	Destroy();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_3D, _id);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	switch(f)
	{
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA8888:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, (int)w, (int)h, (int)depth, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB888:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, (int)w, (int)h, (int)depth, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB565:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, (int)w, (int)h, (int)depth, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA5551:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB5_A1, (int)w, (int)h, (int)depth, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA4444:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, (int)w, (int)h, (int)depth, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_AI88:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE_ALPHA, (int)w, (int)h, (int)depth, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_ALPHA, (int)w, (int)h, (int)depth, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_FLOAT:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, (int)w, (int)h, (int)depth, 0, GL_RED, GL_FLOAT, data);
		break;

	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGRA8888:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, (int)w, (int)h, (int)depth, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGR888:
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, (int)w, (int)h, (int)depth, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		break;

	default:
		Destroy();
		return false;
	}

	this->width = w;
	this->height = h;
	this->depth = depth;
	this->format = f;

	this->vfWidth = (float)w;
	this->vfHeight = (float)h;
	this->depthf = (float)depth;

	return true;
}
void XeTexture::Destroy()
{
	if (_id != 0xFFFFFFFF)
	{
		glDeleteTextures(1, &_id);
		_id = 0xFFFFFFFF;
	}
	width = height = depth = 0;
}
void XeTexture::Upload(short dstx, short dsty, short w, short h, short dstz, short d, void *data)
{
	glBindTexture(GL_TEXTURE_3D, _id);

	switch(this->format)
	{
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA8888:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB888:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB565:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA5551:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA4444:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_AI88:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_ALPHA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_FLOAT:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_RED, GL_FLOAT, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGRA8888:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGR888:
		glTexSubImage3D(GL_TEXTURE_3D, 0, (int)dstx, (int)dsty, (int)dstz,
			(int)w, (int)h, (int)d, GL_BGR, GL_UNSIGNED_BYTE, data);
		break;
	}
}
int XeTexture::GetID()
{
	return _id;
}
short XeTexture::GetWidth()
{
	return width;
}
short XeTexture::GetHeight()
{
	return height;
}
short XeTexture::GetDepth()
{
	return depth;
}
short XeTexture::GetVirtualWidth()
{
	return (short)vfWidth;
}
short XeTexture::GetVirtualHeight()
{
	return (short)vfHeight;
}

char XeTexture::GetResolution()
{
	return textureres;
}
void XeTexture::SetResolution(int resolution)
{
	if (resolution == 0) return;
	textureres = resolution;
	vfWidth = (float)(width/resolution);
	vfHeight = (float)(height/resolution);
}
void XeTexture::SetPosition(short x, short y, float z)
{
	posx = (float)x;
	posy = (float)y;
	posz = z;
}
void XeTexture::Draw(short x, short y, short width, short height, short depth, XeColorF filter[])
{
	// Se altezza e larghezza sono uguali a zero, allora esce
	if (width == 0 || height == 0) return;
	// Se la profondità della texture selezionata è maggiore di quella sorgente
	if (depth >= this->depth) return;
	XeTexture_Vertex *v = vertexblock;
	// Genera le coordinate UV
	v[0].u = (float)((float)(x) / vfWidth);
	v[0].v = (float)((float)(y) / vfHeight);
	v[1].u = (float)((float)(x+width) / vfWidth);
	v[1].v = (float)((float)(y) / vfHeight);
	v[2].u = (float)((float)(x+width) / vfWidth);
	v[2].v = (float)((float)(y+height) / vfHeight);
	v[3].u = (float)((float)(x) / vfWidth);
	v[3].v = (float)((float)(y+height) / vfHeight);

	// Crea il modello 3D per la texture da stampare
	vertices[2] = vertices[6] = width;
	vertices[5] = vertices[7] = height;
	// Crea l'array di filtri dei colori
	if (filter) // Se il filtro è specificato, allora genera i colori
	{
		for(int i=0; i<4; i++)
		{
			v[i].r = filter[i+1].r * filter[0].r;
			v[i].g = filter[i+1].g * filter[0].g;
			v[i].b = filter[i+1].b * filter[0].b;
			v[i].a = filter[i+1].a * filter[0].a;
		}
	}

#if OPENGL_TYPE == OPENGL_TYPE_ES
	glDisableVertexAttribArray(XeVertexFlag_Color);
	glEnableVertexAttribArray(XeVertexFlag_Position);
	glEnableVertexAttribArray(XeVertexFlag_Texture);
	XeScene::Bind3DTexture(_id);
	glVertexAttribPointer(XeVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(XeVertexAttrib_Texture, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
#else	
	v[0].w = v[1].w = v[2].w = v[3].w = (float(depth) + .5f) / this->depthf;
	v[0].z = v[1].z = v[2].z = v[3].z = posz;

	if (cachestate == 1)
	{
		if (vertexwritten >= int(vertexCache.Size()/sizeof(XeTexture_Vertex)/4))
		{
			cachestate = 0;
		}
		else v = ((XeTexture_Vertex*)vertexCache.GetMemoryHandle()) + vertexwritten*4;
	}
	if (cachestate == 0) XeScene::Bind3DTexture(_id);

	v[0].x = posx;
	v[0].y = posy;
	v[1].x = v[0].x + width;
	v[1].y = v[0].y;
	v[2].x = v[0].x + width;
	v[2].y = v[0].y + height;
	v[3].x = v[0].x;
	v[3].y = v[0].y + height;

	if (cachestate == 0)
	{
		glVertexPointer(3, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].x);
		glTexCoordPointer(3, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].u);
		glColorPointer(4, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].r);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	else vertexwritten++;

#endif
}
void XeTexture::Draw(short depth)
{
	Draw(0, 0, this->width, this->height, depth, NULL);
}

void XeTexture::CacheStart(int vertexCount)
{
	cachestate = 1;
	vertexwritten = 0;
	if (vertexCache.Size() / (sizeof(XeTexture_Vertex) * 4) != vertexCount)
	{
		vertexCache.Free();
		vertexCache.Alloc(vertexCount * sizeof(XeTexture_Vertex) * 4);
	}
}
void XeTexture::CacheEnd()
{
	if (cachestate == 0) return;
	XeScene::Bind3DTexture(_id);
	XeTexture_Vertex *v = (XeTexture_Vertex*)vertexCache.GetMemoryHandle();
	glVertexPointer(3, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].x);
	glTexCoordPointer(3, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].u);
	glColorPointer(4, GL_FLOAT, sizeof(XeTexture_Vertex), &v[0].r);
	glDrawArrays(GL_QUADS, 0, vertexwritten*4);

	cachestate = 0;
	vertexwritten = 0;
}