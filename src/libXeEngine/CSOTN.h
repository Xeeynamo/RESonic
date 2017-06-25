#pragma once
#include "Memory.h"
#include "File.h"

namespace Loader
{
	class CSOTN
	{
		enum CSOTNAddr
		{
			CSOTNAddr_None,
			CSOTNAddr_Dra,
			CSOTNAddr_Map,
		};
		struct Header
		{
			u32 unk00;
			u32 unk04;
			u32 unk08;
			u32 unk0C;
			u32 roomDefPosition;
			u32 unk14;
			u32 unk18;
			u32 unk1C;
			u32 tilesLayout;
			u32 objectsGfx;
			u32 unk28;
			u32 unk2C;
			u32 unk30;
			u32 unk34;
			u32 unk38;
			u32 unk3C;
			u32 unk40;
			u32 unk44;
			u32 unk48;
			u32 unk4C;
			u32 unk50;
			u32 unk54;
			u32 unk58;
			u32 unk5C;
			u32 unk60;
			u32 unk64;
			u32 unk68;
			u32 unk6C;
			u32 unk70;
			u32 unk74;
			u32 unk78;
			u32 unk7C;
			u32 unk80;
			u32 unk84;
			u32 unk88;
		};
		struct MapProperties
		{
			u32 unk00;
			u32 unk04;
			u32 unk08;
			u32 unk0C;
			u32 unk10;
			u32 unk14;
			u32 unk18;
			u16 baseObjectPlacement;
			u16 unk1E;
			u32 unk20;
			u32 unk24;
			u32 unk28;
		};
		struct MapRoom
		{
			u8 roomPosStartX;
			u8 roomPosStartY;
			u8 roomPosEndX;
			u8 roomPosEndY;
			u8 layoutID;
			u8 tileGfxID;
			u8 objGfxID;
			u8 objLayoutID;
		};
		struct ObjectGFX
		{
			u16 x, y, w, h;
			u32 address;
		};
		struct ObjectPlacement
		{
			s16 x, y;
			u16 id : 10;
			u16 unk1 : 3;
			u16 unk2 : 3;
			u8 unk3;
			u8 unk4;
			u16 initState;
		};
		struct LayerProperties
		{
			u32 startX	: 6;
			u32 startY	: 6;
			u32 endX	: 6;
			u32 endY	: 6;
			u32 mapFlag : 8;
			u8 num6;
			u8 num7;
			u16 flag;

			u16 Width()
			{
				return endX - startX + 1;
			}
			u16 Height()
			{
				return endY - startY + 1;
			}
		};
		struct MapTile
		{
			u8 texture;
			u8 tile;
			u8 palette;
			u8 collision;
		};
		struct Layer
		{
			LayerProperties properties;
			MapTile* layout;
		};
	private:
		XeEngine::File file;
		Header header;
		MapProperties mapProperties;
		int mapRoomCount;
		MapRoom mapRoom[0x40];
		Layer mapRoomLayer[0x40][2];
		int objectGfxCount;
		ObjectGFX objectGfx[0x100];
		int objectCount;
		ObjectPlacement objectPlacement[0x200];

		void Convert(u32&, CSOTNAddr);
		void ReadLayer(u32 address, Layer&);
	public:
		CSOTN();
		~CSOTN();

		bool Open(XeEngine::String&);
	};
}