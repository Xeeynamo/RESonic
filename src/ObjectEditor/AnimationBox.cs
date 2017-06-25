using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ObjectEditor
{
    public partial class AnimationBox : UserControl
    {
        Entity m_entity;
        Bitmap m_sprite = null;
        AnimationEngine m_animation = new AnimationEngine();
        ushort m_animid;

        public AnimationBox()
        {
            InitializeComponent();
            SelectedAnimationId = 0xFFFF;
            Pause();
        }
        public Entity Entity
        {
            get
            {
                return m_entity;
            }
            set
            {
                m_entity = value;
                if (m_entity != null)
                {
                    m_animation.Animation = m_entity.Animation;
                }
            }
        }
        public ushort SelectedAnimationId
        {
            get
            {
                return m_animid;
            }
            set
            {
                if (m_entity == null)
                {
                    m_animid = 0xFFFF;
                    return;
                }
                m_animid = value;
                m_animation.AnimationIndex = m_animid;
            }
        }
        public AnimationEntry AnimationEntry
        {
            get
            {
                return m_animation.AnimationEntry;
            }
        }
        public Bitmap Sprite
        {
            get
            {
                return m_sprite;
            }
            set
            {
                m_sprite = value;
            }
        }

        public void Play()
        {
            m_animation.Play();
        }
        public void Pause()
        {
            m_animation.Pause();
        }


        private void AnimationBox_Paint(object sender, PaintEventArgs e)
        {
            if (m_sprite == null)
                return;
            m_animation.Do();
            m_animation.Draw(e.Graphics, Sprite, this.Width / 2, this.Height / 2);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

    }

    public class AnimationEngine
    {
        Animation m_animation;
        AnimationEntry m_entry;
        List<AnimationChild> m_child = new List<AnimationChild>();
        List<AnimationEngine> m_anichild = new List<AnimationEngine>();
        int m_frame;
        int m_index;
        bool m_pause;

        int m_frameIndex;

        public AnimationEngine()
        {
            FrameIndex = -1;
            Animation = null;
        }
        public Animation Animation
        {
            get
            {
                return m_animation;
            }
            set
            {
                m_animation = value;
            }
        }
        public int AnimationIndex
        {
            get
            {
                if (m_index == -1)
                    return -1;
                else
                    return Animation.AnimationEntriesID[m_index];
            }
            set
            {
                if (Animation == null)
                    return;
                List<ushort> listId = Animation.AnimationEntriesID;
                for (int i = 0; i < listId.Count; i++)
                {
                    if (listId[i] == value)
                    {
                        FrameIndex = i;
                        return;
                    }
                }
                m_child = null;
                m_anichild = null;
                m_index = -1;
            }
        }
        public AnimationEntry AnimationEntry
        {
            get
            {
                return m_entry;
            }
        }
        public int FrameIndex
        {
            get
            {
                return m_frameIndex;
            }
            set
            {
                m_frame = 0;
                Play();
                m_frameIndex = value;
                if (FrameIndex != -1)
                {
                    m_entry = Animation.AnimationEntries[FrameIndex];
                    m_child = m_entry.ChildsList;
                    m_anichild.Clear();
                    for (int i = 0; i < m_child.Count; i++)
                    {
                        m_anichild.Add(new AnimationEngine());
                        m_anichild[i].Animation = Animation;
                        m_anichild[i].FrameIndex = m_child[i].Id;
                    }
                }
                else
                {
                    m_entry = null;
                    m_child = null;
                }
            }
        }
        public void Play()
        {
            m_index = 0;
            m_pause = false;
            for (int i = 0; i < m_anichild.Count; i++)
            {
                m_anichild[i].Play();
            }
        }
        public void Pause()
        {
            m_pause = true;
            for (int i = 0; i < m_anichild.Count; i++)
            {
                m_anichild[i].Play();
            }
        }

        public void Do()
        {
            if (Animation == null)
                return;
            if (m_pause == false)
            {
                m_index++;
                if (m_index >= m_entry.Speed)
                {
                    m_frame++;
                    m_index = 0;
                    if (m_frame >= m_entry.FramesCount)
                    {
                        m_frame = m_entry.LoopFrame;
                    }
                }
            }
            for (int i = 0; i < m_anichild.Count; i++)
            {
                m_anichild[i].Do();
            }
        }
        public void Draw(Graphics g, Bitmap sprite, int x, int y)
        {
            for (int i = 0; i < m_anichild.Count; i++)
            {
                if (m_entry.ChildsList[i].Priority == false)
                {
                    Point p = m_entry.ChildsList[i].Position;
                    Draw(g, sprite, p.X, p.Y);
                }
            }
            if (m_entry != null)
            {
                if (m_frame < m_entry.FramesCount)
                {
                    int index = m_entry.FramesList[m_frame];
                    if (index < Animation.AnimationFrames.Count)
                    {
                        AnimationFrame frame = Animation.AnimationFrames[index];
                        Rectangle dst = new Rectangle(x - frame.Center.X, y - frame.Center.Y, frame.Size.Width, frame.Size.Height);
                        Rectangle src = new Rectangle(frame.Position, frame.Size);
                        g.DrawImage(sprite, dst, src, GraphicsUnit.Pixel);
                    }
                }
            }
            for (int i = 0; i < m_anichild.Count; i++)
            {
                if (m_entry.ChildsList[i].Priority == true)
                {
                    Point p = m_entry.ChildsList[i].Position;
                    Draw(g, sprite, p.X, p.Y);
                }
            }
        }
    }
}
