using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using XeLib;

namespace ObjectEditor
{
    public class Hitbox
    {
        byte left;
        byte top;
        byte right;
        byte bottom;

        public void Load(FileStreamEx f)
        {
            left = f.Read8();
            top = f.Read8();
            right = f.Read8();
            bottom = f.Read8();
        }
        public void Save(FileStreamEx f)
        {
            f.Write8(left);
            f.Write8(top);
            f.Write8(right);
            f.Write8(bottom);
        }
        public Rectangle Box
        {
            get
            {
                return new Rectangle(left, top, right, bottom);
            }
            set
            {
                left = (byte)value.X;
                top = (byte)value.Y;
                right = (byte)value.Width;
                bottom = (byte)value.Height;
            }
        }
        public int X1
        {
            get
            {
                return left;
            }
            set
            {
                left = (byte)value;
            }
        }
        public int Y1
        {
            get
            {
                return top;
            }
            set
            {
                top = (byte)value;
            }
        }
        public int X2
        {
            get
            {
                return right;
            }
            set
            {
                right = (byte)value;
            }
        }
        public int Y2
        {
            get
            {
                return bottom;
            }
            set
            {
                bottom = (byte)value;
            }
        }
        public int Width
        {
            get
            {
                return left + right;
            }
        }
        public int Height
        {
            get
            {
                return top + bottom;
            }
        }
    }

    public class Physic
    {
        byte hitboxCount;
        byte physicCount;
        byte dummy02;
        byte dummy03;
        List<Hitbox> m_hitbox = new List<Hitbox>();

        public void Load(FileStreamEx f)
        {
            hitboxCount = f.Read8();
            physicCount = f.Read8();
            dummy02 = f.Read8();
            dummy03 = f.Read8();

            m_hitbox.Clear();
            for (int i = 0; i < hitboxCount; i++)
            {
                Hitbox hitbox = new Hitbox();
                hitbox.Load(f);
                m_hitbox.Add(hitbox);
            }
        }
        public void Save(FileStreamEx f)
        {
            f.Write8((byte)HitboxCount);
            f.Write8((byte)physicCount);
            f.Write8((byte)dummy02);
            f.Write8((byte)dummy03);

            for (int i = 0; i < HitboxCount; i++)
            {
                m_hitbox[i].Save(f);
            }
        }

        public int HitboxCount
        {
            get
            {
                return m_hitbox.Count;
            }
        }
        public List<Hitbox> Hitbox
        {
            get
            {
                return m_hitbox;
            }
        }
    }
}
