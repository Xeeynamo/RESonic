namespace XeLib
{
    public class FileStreamEx : System.IO.FileStream
    {
        public FileStreamEx(string filename, System.IO.FileMode mode, System.IO.FileAccess access)
            : base(filename, mode, access)
        {

        }

        public byte Read8()
        {
            return (byte)ReadByte();
        }
        public int Read16()
        {
            return ReadByte() | (ReadByte() << 8);
        }
        public int Read24()
        {
            return ReadByte() | (ReadByte() << 8) | (ReadByte() << 16);
        }
        public int Read32()
        {
            return ReadByte() | (ReadByte() << 8) | (ReadByte() << 16) | (ReadByte() << 24);
        }
        public char ReadChar()
        {
            return (char)ReadByte();
        }
        public sbyte ReadSByte()
        {
            return (sbyte)ReadByte();
        }
        public short ReadShort()
        {
            return (short)Read16();
        }
        public ushort ReadUShort()
        {
            return (ushort)Read16();
        }
        public int ReadInt()
        {
            return (int)Read32();
        }
        public uint ReadUInt()
        {
            return (uint)Read32();
        }
        public string ReadString(int length)
        {
            char[] str = new char[length + 1];
            str[length] = (char)0;
            for (int i = 0; i < length; i++)
            {
                str[i] = ReadChar();
            }
            return new string(str, 0, length);
        }

        public void Write8(byte n)
        {
            WriteByte(n);
        }
        public void Write8(sbyte n)
        {
            WriteByte((byte)n);
        }
        public void Write8(char n)
        {
            WriteByte((byte)n);
        }
        public void Write16(ushort n)
        {
            WriteByte((byte)(n & 0xFF));
            WriteByte((byte)((n >> 8) & 0xFF));
        }
        public void Write16(short n)
        {
            Write16((ushort)n);
        }
        public void Write24(int n)
        {
            WriteByte((byte)(n & 0xFF));
            WriteByte((byte)((n >> 8) & 0xFF));
            WriteByte((byte)((n >> 16) & 0xFF));
        }
        public void Write32(uint n)
        {
            WriteByte((byte)(n & 0xFF));
            WriteByte((byte)((n >> 8) & 0xFF));
            WriteByte((byte)((n >> 16) & 0xFF));
            WriteByte((byte)((n >> 24) & 0xFF));
        }
        public void Write32(int n)
        {
            Write32((uint)n);
        }
        public void WriteString(string str)
        {
            char[] cstr = str.ToCharArray();
            for (int i = 0; i < str.Length; i++)
            {
                Write8(cstr[i]);
            }
        }
        public void WriteString(string str, int length)
        {
            char[] cstr = str.ToCharArray();
            for (int i = 0; i < str.Length; i++)
            {
                Write8(cstr[i]);
            }
            for (int i = str.Length; i < 0x10; i++)
            {
                Write8(0);
            }
        }
    }
}
