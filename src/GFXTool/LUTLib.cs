using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.IO;

namespace GFXTool
{
    class LUTLib
    {
        public enum LUTFormat
        {
            Unknow = 0,
            // 8 bit per color
            RGB332 = 8,
            BGR233 = 9,
            ARGB2222 = 10,
            BGRA2222 = 11,
            // 16 bit per color
            RGB565 = 16,
            BGR565 = 17,
            XRGB1555 = 18,
            XBGR1555 = 19,
            ARGB1555 = 20,
            BGRA5551 = 21,
            ARGB4444 = 22,
            BGRA4444 = 23,
            // 24 bit per color
            RGB888 = 24,
            BGR888 = 25,
            // 32 bit per color
            XRGB8888 = 32,
            BGRX8888 = 33,
            ARGB8888 = 34,
            BGRA8888 = 35,
        }
        struct GFXHeader
        {
            public int count;
            public int dest;
            public int format;
            public int flags;

            public void Load(FileStream f)
            {
                count = f.ReadByte();
                dest = f.ReadByte();
                format = f.ReadByte();
                flags = f.ReadByte();
            }
            public void Save(FileStream f)
            {
                f.WriteByte((byte)count);
                f.WriteByte((byte)dest);
                f.WriteByte((byte)format);
                f.WriteByte((byte)flags);
            }
        }

        ColorPalette palette;
        ColorPalette newpal;
        GFXHeader header;
        public Color[] color = new Color[0x100 * 0x10];
        byte[] data;

        public void OpenLUT(string filename)
        {
            FileStream f = new FileStream(filename, FileMode.Open, FileAccess.Read);
            header.Load(f);
            data = new byte[f.Length - 4];
            f.Read(data, 0, data.Length);
            f.Close();
            UnpackLUT(data, Format);
        }
        public void Save(string filename)
        {
            FileStream f = new FileStream(filename, FileMode.Create, FileAccess.Write);
            Format = Format;
            header.Save(f);
            f.Write(data, 0, data.Length);
            f.Close();
        }

        public ColorPalette Palette
        {
            get
            {
                return newpal;
            }
            set
            {
                palette = value;
                newpal = value;
                ColorArray = value.Entries;
            }
        }
        public Color[] ColorArray
        {
            set
            {
                int size = Math.Min(value.Length, color.Length);
                if (size > 0x10) header.flags = 1;
                for (int i = 0; i < size; i++)
                {
                    color[i] = value[i];
                }
                header.count = size / ColorDepth;
                if (header.count <= 0) header.count = 1;
                Format = LUTFormat.ARGB8888;
            }
        }
        public int Count
        {
            get
            {
                return header.count == 0 ? 256 : header.count;
            }
        }
        public int ColorDepth
        {
            get
            {
                return newpal.Entries.Length > 16 ? 256 : 16;
            }
        }
        public ColorPalette ClutIndex(int index)
        {
            index *= ColorDepth;
            for (int i = 0; i < newpal.Entries.Length; i++)
            {
                newpal.Entries[i] = color[index + i];
            }
            return newpal;
        }
        byte[] UnpackLUT(byte[] data, LUTFormat format)
        {
            byte[] pdata = new byte[0x1000 * 4];
            switch (format)
            {
                case LUTFormat.RGB565:
                    break;
                case LUTFormat.BGR565:
                    break;
                case LUTFormat.XRGB1555:
                    break;
                case LUTFormat.XBGR1555:
                    for (int i = 0; i < data.Length / 2; i++)
                    {
                        short color = (short)(data[i * 2 + 0] | (data[i * 2 + 1] << 8));
                        pdata[i * 4 + 0] = 255;
                        pdata[i * 4 + 1] = (byte)((color & 0x1F) << 3);
                        pdata[i * 4 + 2] = (byte)((color & 0x3E0) >> 2);
                        pdata[i * 4 + 3] = (byte)((color & 0x7C00) >> 7);
                    }
                    break;
                case LUTFormat.ARGB1555:
                    break;
                case LUTFormat.BGRA5551:
                    break;
                case LUTFormat.RGB888:
                    break;
                case LUTFormat.BGR888:
                    break;

                case LUTFormat.XRGB8888:
                    for (int i = 0; i < data.Length / 4; i++)
                    {
                        pdata[i * 4 + 0] = 255;
                        pdata[i * 4 + 1] = data[i * 4 + 1];
                        pdata[i * 4 + 2] = data[i * 4 + 2];
                        pdata[i * 4 + 3] = data[i * 4 + 3];
                    }
                    break;
                case LUTFormat.BGRX8888:
                    break;
                case LUTFormat.ARGB8888:
                    for (int i = 0; i < data.Length / 4; i++)
                    {
                        pdata[i * 4 + 0] = data[i * 4 + 3];
                        pdata[i * 4 + 1] = data[i * 4 + 2];
                        pdata[i * 4 + 2] = data[i * 4 + 1];
                        pdata[i * 4 + 3] = data[i * 4 + 0];
                    }
                    break;
                case LUTFormat.BGRA8888:
                    for (int i = 0; i < data.Length / 4; i++)
                    {
                        pdata[i * 4 + 0] = data[i * 4 + 3];
                        pdata[i * 4 + 1] = data[i * 4 + 2];
                        pdata[i * 4 + 2] = data[i * 4 + 1];
                        pdata[i * 4 + 3] = data[i * 4 + 0];
                    }
                    break;
            }
            for (int i = 0; i < pdata.Length / 4; i++)
            {
                color[i] = Color.FromArgb(pdata[i * 4 + 0], pdata[i * 4 + 1], pdata[i * 4 + 2], pdata[i * 4 + 3]);
            }
            ClutIndex(0);
            return pdata;
        }
        public LUTFormat Format
        {
            get
            {
                return (LUTFormat)header.format;
            }
            set
            {
                int colors = header.count * ((header.flags&1) == 1 ? 256 : 16);
                switch (value)
                {
                    case LUTFormat.RGB565:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 0) | ((color[i].G >> 2) << 5) | ((color[i].B >> 3) << 11));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;
                    case LUTFormat.BGR565:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 11) | ((color[i].G >> 2) << 5) | ((color[i].B >> 3) << 0));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;
                    case LUTFormat.XRGB1555:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 0) | ((color[i].G >> 3) << 5) | ((color[i].B >> 3) << 10));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;
                    case LUTFormat.XBGR1555:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 0) | ((color[i].G >> 3) << 5) | ((color[i].B >> 3) << 10));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;
                    case LUTFormat.ARGB1555:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 0) | ((color[i].G >> 3) << 5) | ((color[i].B >> 3) << 10) | (color[i].A >= 0x80 ? 0x8000 : 0x0000));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;
                    case LUTFormat.BGRA5551:
                        data = new byte[colors * 2];
                        for (int i = 0; i < colors; i++)
                        {
                            ushort c = (ushort)(((color[i].B >> 3) << 10) | ((color[i].G >> 3) << 5) | ((color[i].B >> 3) << 0) | (color[i].A >= 0x80 ? 0x8000 : 0x0000));
                            data[i * 2 + 0] = (byte)(c & 0xFF);
                            data[i * 2 + 1] = (byte)(c >> 8);
                        }
                        break;

                    case LUTFormat.RGB888:
                        data = new byte[colors * 3];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 3 + 0] = color[i].B;
                            data[i * 3 + 1] = color[i].G;
                            data[i * 3 + 2] = color[i].R;
                        }
                        break;
                    case LUTFormat.BGR888:
                        data = new byte[colors * 3];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 3 + 0] = color[i].R;
                            data[i * 3 + 1] = color[i].G;
                            data[i * 3 + 2] = color[i].B;
                        }
                        break;

                    case LUTFormat.XRGB8888:
                        data = new byte[colors * 4];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 4 + 0] = 255;
                            data[i * 4 + 1] = color[i].G;
                            data[i * 4 + 2] = color[i].R;
                            data[i * 4 + 3] = color[i].A;
                        }
                        break;
                    case LUTFormat.BGRX8888:
                        data = new byte[colors * 4];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 4 + 0] = 255;
                            data[i * 4 + 1] = color[i].R;
                            data[i * 4 + 2] = color[i].G;
                            data[i * 4 + 3] = color[i].B;
                        }
                        break;
                    case LUTFormat.ARGB8888:
                        data = new byte[colors * 4];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 4 + 0] = color[i].B;
                            data[i * 4 + 1] = color[i].G;
                            data[i * 4 + 2] = color[i].R;
                            data[i * 4 + 3] = color[i].A;
                        }
                        break;
                    case LUTFormat.BGRA8888:
                        data = new byte[colors * 4];
                        for (int i = 0; i < colors; i++)
                        {
                            data[i * 4 + 0] = color[i].A;
                            data[i * 4 + 1] = color[i].R;
                            data[i * 4 + 2] = color[i].G;
                            data[i * 4 + 3] = color[i].B;
                        }
                        break;
                    default:
                        return;
                }
                header.format = (byte)value;
                UnpackLUT(data, Format);
            }
        }
    }
}
