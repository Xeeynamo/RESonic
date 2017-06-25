using System;
using System.Collections.Generic;
using System.Text;
using XeLib;

namespace ObjectEditor
{
    public class EntityProperties
    {
        ushort id;
        byte type;
        byte dummy;
        string name;

        public void Load(FileStreamEx f)
        {
            id = f.ReadUShort();
            type = f.Read8();
            dummy = f.Read8();
            name = f.ReadString(0x10);
        }
        public void Save(FileStreamEx f)
        {
            f.Write16(id);
            f.Write8(type);
            f.Write8(dummy);
            f.WriteString(name, 0x10);
        }

        public ushort ID
        {
            get
            {
                return id;
            }
            set
            {
                id = value;
            }
        }
        public int Type
        {
            get
            {
                return (int)type;
            }
            set
            {
                type = (byte)value;
            }
        }
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                if (value.Length >= 0x10)
                    name = value.Substring(0, 0x10);
                else
                    name = value;
            }
        }
    }
}
