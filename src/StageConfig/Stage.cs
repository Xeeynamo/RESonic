using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace StageConfig
{
    class Stage
    {
        public class Act
        {
            public string gfx;
            public string clut;
            public string cli;
            public string hbx;
            public string map;
            public string blk;
            public string rng;
            public string obp;
            public string def;
            public string dtl;
            public string tpl;
            public string crd;
            public string bgm;

            public string GetString(int index)
            {
                switch (index)
                {
                    case 0x00: return gfx;
                    case 0x01: return clut;
                    case 0x02: return cli;
                    case 0x03: return hbx;
                    case 0x04: return map;
                    case 0x05: return blk;
                    case 0x06: return rng;
                    case 0x07: return obp;
                    case 0x08: return def;
                    case 0x09: return dtl;
                    case 0x0A: return tpl;
                    case 0x0B: return crd;
                    case 0x0C: return bgm;
                    default: return "";
                }
            }
            public string SetString(int index, string str)
            {
                switch (index)
                {
                    case 0x00: return gfx = str;
                    case 0x01: return clut = str;
                    case 0x02: return cli = str;
                    case 0x03: return hbx = str;
                    case 0x04: return map = str;
                    case 0x05: return blk = str;
                    case 0x06: return rng = str;
                    case 0x07: return obp = str;
                    case 0x08: return def = str;
                    case 0x09: return dtl = str;
                    case 0x0A: return tpl = str;
                    case 0x0B: return crd = str;
                    case 0x0C: return bgm = str;
                    default: return "";
                }
            }
        }
        public struct StringRepositioning
        {
            public int pos;
            public string str;
        }

        byte stagenamelength;
        byte resolutions;
        byte actcount;
        byte hidetilecard;

        string stagename;
        List<Act> actList;

        public Stage()
        {
            resolutions = 1;
            hidetilecard = 0;
            StageName = "";
            actList = new List<Act>();
            AddAct();
        }
        public void AddAct()
        {
            actList.Add(EmptyAct);
            actcount++;
        }
        public void RemoveAct(int index)
        {
            actList.RemoveAt(index);
            actcount--;
        }
        public Act SelectAct(int index)
        {
            if (index >= actList.Count)
                return EmptyAct;
            if (index < 0)
                return EmptyAct;
            return actList[index];
        }
        public string StageName
        {
            get
            {
                return stagename;
            }
            set
            {
                stagename = value;
                stagenamelength = (byte)(value.Length + 1);
            }
        }
        public int ActCount
        {
            get
            {
                return actList.Count;
            }
        }
        public void Resolution(int res, bool bit)
        {
            if (res > 8)
                res = 8;
            if (bit == true)
                resolutions |= (byte)(1 << res);
            else
                resolutions &= (byte)(~(1 << res));
        }
        public bool Resolution(int res)
        {
            return (resolutions & (1 << res)) != 0;
        }
        public string Load(string filename)
        {
            string err = null;
            try
            {
                FileStream f = new FileStream(filename, FileMode.Open, FileAccess.Read);
                if (Read(f) == false)
                    err = "Read(FileStream)";
                f.Close();
            }
            catch (System.Exception ex)
            {
                return ex.Message;
            }
            return err;
        }
        public string Save(string filename)
        {
            string err = null;
            try
            {
                FileStream f = new FileStream(filename, FileMode.Create, FileAccess.Write);
                if (Write(f) == false)
                    err = "Write(FileStream)";
                f.Close();
            }
            catch (System.Exception ex)
            {
                return ex.Message;
            }
            return err;
        }


        bool Read(FileStream f)
        {
            const int structSize = 13;

            stagenamelength = (byte)f.ReadByte();
            resolutions = (byte)f.ReadByte();
            actcount = (byte)f.ReadByte();
            hidetilecard = (byte)f.ReadByte();

            byte[] strbyte = new byte[stagenamelength];
            f.Read(strbyte, 0, stagenamelength);
            StageName = ByteToString(strbyte);

            int stagePointers = (f.ReadByte() << 0) | (f.ReadByte() << 8) | (f.ReadByte() << 16) | (f.ReadByte() << 24);
            actList.RemoveRange(0, actList.Count);

            char[] strchar = new char[0x80];
            for (int i = 0; i < actcount; i++)
            {
                Act act = new Act();
                for (int j = 0; j < structSize; j++)
                {
                    f.Position = stagePointers + (i * structSize + j) * 2;
                    short pointer = (short)((f.ReadByte() << 0) | (f.ReadByte() << 8));
                    f.Position = pointer;

                    int index = -1;
                    do 
                    {
                        index++;
                        strchar[index] = (char)f.ReadByte();
                    } while (strchar[index] != 0);
                    act.SetString(j, new String(strchar, 0, index));
                }
                actList.Add(act);
            }

            return true;
        }
        bool Write(FileStream f)
        {
            byte[] strbyte = StringToByte(stagename);

            f.WriteByte(stagenamelength);
            f.WriteByte(resolutions);
            f.WriteByte(actcount);
            f.WriteByte(hidetilecard);
            f.Write(strbyte, 0, strbyte.Length);
            int repos = (int)(f.Position + 4);
            List<StringRepositioning> strRe = new List<StringRepositioning>();
            for (int i = 0; i < actList.Count; i++)
            {
                Act act = actList[i];
                for (int j = 0; j <= 0x0C; j++)
                {
                    AddString(strRe, act.GetString(j), ref repos);
                }
            }
            f.WriteByte((byte)(repos >> 0 & 0xFF));
            f.WriteByte((byte)(repos >> 8 & 0xFF));
            f.WriteByte((byte)(repos >> 16 & 0xFF));
            f.WriteByte((byte)(repos >> 24 & 0xFF));

            for(int i=0; i<strRe.Count; i++)
            {
                strbyte = StringToByte(strRe[i].str);
                f.Write(strbyte, 0, strbyte.Length);
            }
            for (int i = 0; i < actList.Count; i++)
            {
                Act act = actList[i];
                for (int j = 0; j <= 0x0C; j++)
                {
                    ushort k = IndexString(strRe, act.GetString(j));
                    f.WriteByte((byte)((k >> 0) & 0xFF));
                    f.WriteByte((byte)((k >> 8) & 0xFF));
                }
            }

            return true;
        }
        byte[] StringToByte(string str)
        {
            char[] strchar = str.ToCharArray();
            byte[] strbyte = new byte[strchar.Length + 1];
            for (int i = strchar.Length - 1; i >= 0; i--)
            {
                strbyte[i] = (byte)strchar[i];
            }
            strbyte[strchar.Length] = 0;
            return strbyte;
        }
        string ByteToString(byte[] strbyte)
        {
            char[] strchar = new char[strbyte.Length];
            for (int i = 0; i < strbyte.Length; i++)
            {
                strchar[i] = (char)strbyte[i];
            }
            return new String(strchar);
        }
        void AddString(List<StringRepositioning> strRe, string str, ref int pos)
        {
            if (str == null || str == "") return;
            for (int i = strRe.Count - 1; i >= 0; i--)
            {
                if (strRe[i].str == str)
                    return;
            }
            StringRepositioning strrepos;
            strrepos.str = str;
            strrepos.pos = pos;
            strRe.Add(strrepos);
            pos += str.Length + 1;
        }
        ushort IndexString(List<StringRepositioning> strRe, string str)
        {
            if (str == null || str == "") return 0xFFFF;
            for (int i = strRe.Count - 1; i >= 0; i--)
            {
                if (strRe[i].str == str)
                    return (ushort)(strRe[i].pos);
            }
            return 0xFFFF;
        }

        Act EmptyAct
        {
            get
            {
                Act act = new Act();
                act.gfx = act.clut = act.cli = act.hbx = act.map = act.blk = act.rng = act.obp = act.def = act.dtl = act.tpl = act.crd = act.bgm = "";
                return act;
            }
        }

    }
    
}
