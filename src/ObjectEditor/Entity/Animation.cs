using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using XeLib;

namespace ObjectEditor
{
    public class AnimationFrame
    {
        byte width;
        byte height;
        sbyte centerx;
        sbyte centery;
        byte sourcex;
        byte sourcey;
        byte section;
        byte hitbox;

        public void Load(FileStreamEx f)
        {
            sourcex = f.Read8();
            sourcey = f.Read8();
            width = f.Read8();
            height = f.Read8();
            centerx = f.ReadSByte();
            centery = f.ReadSByte();
            section = f.Read8();
            hitbox = f.Read8();
        }
        public void Save(FileStreamEx f)
        {
            f.Write8(sourcex);
            f.Write8(sourcey);
            f.Write8(width);
            f.Write8(height);
            f.Write8(centerx);
            f.Write8(centery);
            f.Write8(section);
            f.Write8(hitbox);
        }

        public Point Position
        {
            get
            {
                return new Point((int)sourcex, (int)sourcey | ((int)section << 8));
            }
            set
            {
                if (value.X < 0)
                {
                    sourcex = 0;
                }
                else
                {
                    sourcex = (byte)value.X;
                }
                if (value.Y < 0)
                {
                    sourcey = 0;
                }
                else
                {
                    sourcey = (byte)(value.Y & 0xFF);
                    section = (byte)((value.Y >> 8) & 0xFF);
                }
            }
        }
        public Size Size
        {
            get
            {
                return new Size((int)width, (int)height);
            }
            set
            {
                if (value.Width < 0)
                {
                    width = 0;
                }
                else
                {
                    width = (byte)value.Width;
                }
                if (value.Height < 0)
                {
                    height = 0;
                }
                else
                {
                    height = (byte)value.Height;
                }
            }
        }
        public Point Center
        {
            get
            {
                return new Point((int)centerx, (int)centery);
            }
            set
            {
                centerx = (sbyte)value.X;
                centery = (sbyte)value.Y;
            }
        }
        public int Hitbox
        {
            get
            {
                return hitbox;
            }
            set
            {
                hitbox = (byte)value;
            }
        }
    }
    public class AnimationChild
    {
        ushort id;
        short x;
        short y;
        byte param;

        public void Load(FileStreamEx f)
        {
            x = f.ReadShort();
            y = f.ReadShort();
        }
        public void Save(FileStreamEx f)
        {
            f.Write16(x);
            f.Write16(y);
        }

        public int Id
        {
            get
            {
                return id;
            }
            set
            {
                id = (ushort)value;
            }
        }
        public Point Position
        {
            get
            {
                return new Point(x, y);
            }
            set
            {
                x = (short)value.X;
                y = (short)value.Y;
            }
        }
        public bool Priority
        {
            get
            {
                return (param & 1) == 0;
            }
            set
            {
                param |= 1;
            }
        }
    }
    public class AnimationEntry
    {
        byte count;
        byte childs;
        byte speed;
        byte loop;
        List<ushort> m_frame = new List<ushort>();
        List<AnimationChild> m_child = new List<AnimationChild>();

        public void Load(FileStreamEx f)
        {
            count = f.Read8();
            childs = f.Read8();
            speed = f.Read8();
            loop = f.Read8();
        }
        public void Save(FileStreamEx f)
        {
            f.Write8((byte)FramesCount);
            f.Write8((byte)ChildsCount);
            f.Write8(speed);
            f.Write8(loop);
        }
        public void LoadFrameList(FileStreamEx f)
        {
            m_frame.Clear();
            m_child.Clear();

            for (int i = 0; i < count; i++)
            {
                m_frame.Add(f.ReadUShort());
            }
            for (int i = 0; i < childs; i++)
            {
                m_child.Add(new AnimationChild());
                m_child[i].Load(f);
            }

        }
        public void SaveFrameList(FileStreamEx f)
        {
            for (int i = 0; i < FramesCount; i++)
            {
                f.Write16(m_frame[i]);
            }
            for (int i = 0; i < ChildsCount; i++)
            {
                m_child[i].Save(f);
            }
        }

        public int FramesCount
        {
            get
            {
                return m_frame.Count;
            }
        }
        public int ChildsCount
        {
            get
            {
                return m_child.Count;
            }
        }
        public int Speed
        {
            get
            {
                return (int)speed;
            }
            set
            {
                speed = (byte)value;
            }
        }
        public int LoopFrame
        {
            get
            {
                return (int)loop;
            }
            set
            {
                loop = (byte)value;
            }
        }
        public List<ushort> FramesList
        {
            get
            {
                return m_frame;
            }
        }
        public List<AnimationChild> ChildsList
        {
            get
            {
                return m_child;
            }
        }
    }
    public class Animation
    {
        ushort m_animcount;
        ushort m_framecount;

        List<AnimationFrame> m_animationframes = new List<AnimationFrame>();
        List<AnimationEntry> m_animationentries = new List<AnimationEntry>();
        List<ushort> m_animationid = new List<ushort>();

        public void Load(FileStreamEx f)
        {
            m_animcount = f.ReadUShort();
            m_framecount = f.ReadUShort();

            m_animationframes.Clear();
            m_animationentries.Clear();
            m_animationid.Clear();
            for (int i = 0; i < m_framecount; i++)
            {
                AnimationFrame frame = new AnimationFrame();
                frame.Load(f);
                m_animationframes.Add(frame);
            }
            for (int i = 0; i < m_animcount; i++)
            {
                m_animationid.Add(f.ReadUShort());
            }
            for (int i = 0; i < m_animcount; i++)
            {
                AnimationEntry entry = new AnimationEntry();
                entry.Load(f);
                m_animationentries.Add(entry);
            }
            for (int i = 0; i < m_animcount; i++)
            {
                m_animationentries[i].LoadFrameList(f);
            }
        }
        public void Save(FileStreamEx f)
        {
            f.Write16((ushort)m_animationentries.Count);
            f.Write16((ushort)m_animationframes.Count);

            for (int i = 0; i < FrameCount; i++)
            {
                m_animationframes[i].Save(f);
            }
            for (int i = 0; i < AnimationCount; i++)
            {
                f.Write16(m_animationid[i]);
            }
            for (int i = 0; i < AnimationCount; i++)
            {
                m_animationentries[i].Save(f);
            }
            for (int i = 0; i < AnimationCount; i++)
            {
                m_animationentries[i].SaveFrameList(f);
            }
        }

        public List<AnimationFrame> AnimationFrames
        {
            get
            {
                return m_animationframes;
            }
        }
        public List<AnimationEntry> AnimationEntries
        {
            get
            {
                return m_animationentries;
            }
        }
        public List<ushort> AnimationEntriesID
        {
            get
            {
                return m_animationid;
            }
        }
        public int FrameCount
        {
            get
            {
                return m_animationframes.Count;
            }
        }
        public int AnimationCount
        {
            get
            {
                return m_animationentries.Count;
            }
        }
        
        public int GetAnimationIndex(ushort animationId)
        {
            for (int i = 0; i < AnimationCount; i++)
            {
                if (AnimationEntriesID[i] == animationId)
                    return i;
            }
            return -1;
        }
        public void AddAnimation(ushort animationId)
        {
            AnimationEntry e = new AnimationEntry();
            AnimationEntries.Add(e);
            AnimationEntriesID.Add(animationId);
        }
        public void RemoveEmptyAnimations()
        {
            for (int i = 0; i < AnimationCount; i++)
            {
                if (AnimationEntries[i].FramesCount == 0 && AnimationEntries[i].ChildsCount == 0)
                {
                    AnimationEntries.RemoveAt(i);
                    AnimationEntriesID.RemoveAt(i);
                    i--;
                }
            }
        }
    }
}
