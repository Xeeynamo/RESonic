using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;

namespace GFXTool
{
    class GFXLib
    {
        const int MaxVersionSupported = 1;

        public struct GFXSize
        {
            public short width;
            public short height;
        }
        struct GFXHeader
        {
            public byte headersize;
            public byte dstindex;
            public byte width;
            public byte height;
            public byte resolution;
            public byte texturecount;
            public byte mode;
            public byte flags;

            public void Read(FileStream f)
            {
                headersize = (byte)f.ReadByte();
                dstindex = (byte)f.ReadByte();
                width = (byte)f.ReadByte();
                height = (byte)f.ReadByte();
                resolution = (byte)f.ReadByte();
                texturecount = (byte)f.ReadByte();
                mode = (byte)f.ReadByte();
                flags = (byte)f.ReadByte();
            }
            public void Write(FileStream f)
            {
                f.WriteByte(headersize);
                f.WriteByte(dstindex);
                f.WriteByte(width);
                f.WriteByte(height);
                f.WriteByte(resolution);
                f.WriteByte(texturecount);
                f.WriteByte(mode);
                f.WriteByte(flags);
            }
        }
        GFXHeader head;

        public GFXLib()
        {

        }
        ~GFXLib()
        {

        }

        public void Identity()
        {
            head.headersize = 8;
            head.dstindex = 0;
            head.width = 0;
            head.height = 0;
            head.resolution = 1;
            head.texturecount = 1;
            head.mode = 0;
            head.flags = 0;
        }
        public bool Open(string filename, ref Bitmap bmp)
        {
            try
            {
                FileStream f = new FileStream(filename, FileMode.Open, FileAccess.Read);
                //version = CryptoLib.CheckMagicCode(f, "GFX", MaxVersionSupported);
                //if (version == 0) return false;
                head.Read(f);

                bmp = new Bitmap(Size.width * Resolution, Size.height * Resolution * TextureCount, PixelMode);
                if (bmp.Palette.Entries.Length == 0x100)
                {
                    ColorPalette pal = bmp.Palette;
                    for (int i = 0; i < 0x10; i++)
                    {
                        for (int j = 0; j < 0x10; j++)
                        {
                            int r=0, g=0, b=0;
                            switch (i)
                            {
                                case 0:
                                    r = 16;
                                    g = 16;
                                    b = 16;
                                    break;
                                case 1:
                                    r = 16;
                                    break;
                                case 2:
                                    g = 16;
                                    break;
                                case 3:
                                    b = 16;
                                    break;
                                case 4:
                                    r = 16;
                                    g = 16;
                                    break;
                                case 5:
                                    r = 16;
                                    b = 16;
                                    break;
                                case 6:
                                    g = 16;
                                    b = 16;
                                    break;
                                case 7:
                                    r = 8;
                                    g = 8;
                                    b = 8;
                                    break;
                                case 8:
                                    r = 8;
                                    break;
                                case 9:
                                    g = 8;
                                    break;
                                case 10:
                                    b = 8;
                                    break;
                                case 11:
                                    r = 8;
                                    g = 8;
                                    break;
                                case 12:
                                    r = 8;
                                    b = 8;
                                    break;
                                case 13:
                                    g = 8;
                                    b = 8;
                                    break;
                                case 14:
                                    r = 7;
                                    g = 3;
                                    break;
                                case 15:
                                    r = 3;
                                    b = 7;
                                    break;
                            }
                            r = (r * j) % 0x100;
                            if (r == 0) r++;
                            g = (g * j) % 0x100;
                            if (g == 0) g++;
                            b = (b * j) % 0x100;
                            if (b == 0) b++;
                            pal.Entries[j + i * 0x10] = Color.FromArgb(r, g, b);
                        }
                    }
                    bmp.Palette = pal;
                }

                Rectangle lockRect = new Rectangle(0, 0, bmp.Width, bmp.Height);
                BitmapData bmpdata = bmp.LockBits(lockRect, ImageLockMode.WriteOnly, bmp.PixelFormat);
                int size = bmpdata.Width * bmpdata.Height;
                byte[] data;
                switch (Mode)
                {
                    case 1: size /= 8; break;
                    case 2: size /= 2; break;
                    case 3: size *= 1; break;
                    case 4: size *= 2; break;
                    case 5: size *= 3; break;
                    case 6: size *= 4; break;
                }
                data = new byte[size];
                f.Read(data, 0, size);
                if (Mode == 2)
                {
                    for (int i = 0; i < size; i++)
                    {
                        data[i] = (byte)(((data[i] & 15) << 4) | ((data[i] >> 4) & 0xF));
                    }
                }
                System.Runtime.InteropServices.Marshal.Copy(data, 0, bmpdata.Scan0, size);
                bmp.UnlockBits(bmpdata);
                /*if (FlagInternalPalette)
                {
                    int paletteCount = 0;
                    switch (Mode)
                    {
                        case 1:
                            paletteCount = 2;
                            break;
                        case 2:
                            paletteCount = 16;
                            break;
                        case 3:
                            paletteCount = 256;
                            break;
                    }
                    paletteCount = Math.Max(paletteCount, bmp.Palette.Entries.Length);
                    for (int i = 0; i < paletteCount; i++)
                    {
                        f.WriteByte(bmp.Palette.Entries[i].R);
                        f.WriteByte(bmp.Palette.Entries[i].G);
                        f.WriteByte(bmp.Palette.Entries[i].B);
                        f.WriteByte(bmp.Palette.Entries[i].A);
                    }
                }*/
                f.Close();
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }
        public bool Save(string filename, ref Bitmap bmp)
        {
            FileStream f = new FileStream(filename, FileMode.Create, FileAccess.Write);
            /*uint magiccode = CryptoLib.MakeMagicCode("GFX", MaxVersionSupported);
            f.WriteByte((byte)((magiccode >> 0) & 0xFF));
            f.WriteByte((byte)((magiccode >> 8) & 0xFF));
            f.WriteByte((byte)((magiccode >> 16) & 0xFF));
            f.WriteByte((byte)((magiccode >> 24) & 0xFF));*/
            head.Write(f);

            //bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);
            Rectangle lockRect = new Rectangle(0, 0, bmp.Width & ~3, bmp.Height & ~3);
            BitmapData bmpdata = bmp.LockBits(lockRect, ImageLockMode.ReadOnly, bmp.PixelFormat);
            int size = bmpdata.Stride * bmpdata.Height;
            byte[] data = new byte[size];
            System.Runtime.InteropServices.Marshal.Copy(bmpdata.Scan0, data, 0, size);
            if (Mode == 2)
            {
                for (int i = 0; i < size; i++)
                {
                    data[i] = (byte)(((data[i] & 15) << 4) | ((data[i] >> 4) & 0xF)); 
                }
            }
            f.Write(data, 0, size);
            bmp.UnlockBits(bmpdata);
            //bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);
            if (FlagInternalPalette)
            {
                int paletteCount = 0;
                switch (Mode)
                {
                    case 1:
                        paletteCount = 2;
                        break;
                    case 2:
                        paletteCount = 16;
                        break;
                    case 3:
                        paletteCount = 256;
                        break;
                }
                paletteCount = Math.Max(paletteCount, bmp.Palette.Entries.Length);
                for (int i = 0; i < paletteCount; i++)
                {
                    f.WriteByte(bmp.Palette.Entries[i].R);
                    f.WriteByte(bmp.Palette.Entries[i].G);
                    f.WriteByte(bmp.Palette.Entries[i].B);
                    f.WriteByte(bmp.Palette.Entries[i].A);
                }
            }
            f.Close();
            return true;
        }
        public void Create(short width, short height, PixelFormat pixelformat, byte[] data, ref Bitmap bmp)
        {
            GFXSize gfxSize;
            gfxSize.width = width;
            gfxSize.height = height;

            head.headersize = 8;
            Size = gfxSize;
            head.flags = 0;
            DestinationIndex = 0;
            Resolution = 1;
            PixelMode = pixelformat;

            bmp = new Bitmap(Size.width * Resolution, Size.height * Resolution, PixelMode);

            Rectangle lockRect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            BitmapData bmpdata = bmp.LockBits(lockRect, ImageLockMode.WriteOnly, bmp.PixelFormat);
            int size = bmpdata.Width * bmpdata.Height;
            switch (Mode)
            {
                case 1: size /= 8; break;
                case 2: size /= 2; break;
                case 3: size *= 1; break;
                case 4: size *= 2; break;
                case 5: size *= 3; break;
                case 6: size *= 4; break;
            }
            System.Runtime.InteropServices.Marshal.Copy(data, 0, bmpdata.Scan0, size);
            bmp.UnlockBits(bmpdata);
        }

        public void SetSize(short width, short height)
        {
            head.width = (byte)(width / 8);
            head.height = (byte)(height / 8);
        }
        public void SetSize(int width, int height)
        {
            head.width = (byte)(width / 4);
            head.height = (byte)(height / 4);
        }
        public GFXSize Size
        {
            get
            {
                GFXSize size;
                size.width = (short)(head.width * 4);
                size.height = (short)(head.height * 4);
                if (head.width == 0) size.width = 256;
                if (head.height == 0) size.height = 256;
                size.height *= TextureCount;
                return size;
            }
            set
            {
                head.width = (byte)(value.width / 4);
                head.height = (byte)(value.height / 4);
                TextureCount = (byte)(value.height / 256);
            }
        }
        public byte DestinationIndex
        {
            get { return head.dstindex; }
            set { head.dstindex = value; }
        }
        public byte Resolution
        {
            get { return head.resolution; }
            set { head.resolution = value; }
        }
        public byte TextureCount
        {
            get { return head.texturecount; }
            set { head.texturecount = value; }
        }
        public byte Mode
        {
            get { return head.mode; }
            set { head.mode = value; }
        }
        public bool FlagCompressed
        {
            get { return (head.flags & 1) != 0; }
            set { head.flags = (byte)((head.flags & (~1)) | (value ? 1 : 0)); }
        }
        public bool FlagInternalPalette
        {
            get { return (head.flags & 2) != 0; }
            set { head.flags = (byte)((head.flags & (~2)) | (value ? 2 : 0)); }
        }
        public PixelFormat PixelMode
        {
            get
            {
                switch (Mode)
                {
                    case 1: return PixelFormat.Format1bppIndexed;
                    case 2: return PixelFormat.Format4bppIndexed;
                    case 3: return PixelFormat.Format8bppIndexed;
                    case 4: return PixelFormat.Format16bppRgb565;
                    case 5: return PixelFormat.Format24bppRgb;
                    case 6: return PixelFormat.Format32bppArgb;
                    default: return PixelFormat.Undefined;
                }
            }
            set
            {
                switch (value)
                {
                    case PixelFormat.Format1bppIndexed:
                        Mode = 1;
                        break;
                    case PixelFormat.Format4bppIndexed:
                        Mode = 2;
                        break;
                    case PixelFormat.Format8bppIndexed:
                        Mode = 3;
                        break;
                    case PixelFormat.Format16bppRgb565:
                        Mode = 4;
                        break;
                    case PixelFormat.Format24bppRgb:
                        Mode = 5;
                        break;
                    case PixelFormat.Format32bppArgb:
                        Mode = 6;
                        break;
                    default:
                        Mode = 0;
                        break;
                }
            }
        }
    }
}
