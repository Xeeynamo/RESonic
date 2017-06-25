using System;

namespace GFXTool
{
    public class CryptoLib
    {
        public static uint MakeMagicCode(string extension, uint version)
        {
            char[] ext = extension.ToCharArray();
            return (uint)((uint)ext[0] ^ 0xFF) | (((uint)ext[1] ^ (uint)ext[0]) << 8) | (((uint)ext[2] ^ (uint)ext[1]) << 16) | (((version | (version << 4)) ^ (uint)ext[2]) << 24);
        }
        public static uint CheckMagicCode(System.IO.FileStream f, string extension, int maxversion)
        {
            int magiccode = f.ReadByte() | (f.ReadByte() << 8) | (f.ReadByte() << 16) | (f.ReadByte() << 24);
            for (uint i = 1; i <= maxversion; i++)
            {
                if (magiccode == MakeMagicCode(extension, i))
                {
                    return i;
                }
            }
            return 0;
        }
    }
}
