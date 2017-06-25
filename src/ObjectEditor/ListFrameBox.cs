using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ObjectEditor
{
    public partial class ListFrameBox : UserControl
    {
        int m_animationIndex;
        AnimationEntry entry = null;

        public ListFrameBox()
        {
            InitializeComponent();
        }
        public Animation Animation { get; set; }
        public Bitmap Sprite { get; set; }
        public int AnimationIndex
        {
            get
            {
                return m_animationIndex;
            }
            set
            {
                if (Animation == null)
                    value = -1;
                m_animationIndex = value;
                if (value == -1 || value >= Animation.AnimationCount)
                {
                    entry = null;
                    return;
                }
                entry = Animation.AnimationEntries[m_animationIndex];
                int count = entry.FramesCount;
                listBox.Items.Clear();
                for (int i = 0; i < count; i++)
                {
                    listBox.Items.Add(0);
                }
            }
        }
        public void SetFrameIndex(int index)
        {
            if (index <= Animation.FrameCount && listBox.SelectedIndex != -1)
            {
                entry.FramesList[listBox.SelectedIndex] = (ushort)index;
                listBox.Invalidate();
            }
        }

        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (OnSelectedFrame != null && listBox.SelectedIndex != -1)
            {
                OnSelectedFrame(this, entry.FramesList[listBox.SelectedIndex]);
            }
        }
        private void bAdd_Click(object sender, EventArgs e)
        {
            int index = listBox.SelectedIndex;
            if (entry == null)
                return;
            listBox.Items.Add(0);
            if (index + 1 >= entry.FramesCount || index == -1)
            {
                entry.FramesList.Add(0);
            }
            else
            {
                entry.FramesList.Insert(index + 1, 0);
            }
            /*if (entry.LoopFrame >= index)
            {
                entry.LoopFrame++;
                if (entry.LoopFrame >= entry.FramesCount)
                {
                    entry.LoopFrame = entry.FramesCount - 1;
                }
            }*/
        }
        private void bInsert_Click(object sender, EventArgs e)
        {
            int index = listBox.SelectedIndex;
            if (index == -1)
                return;
            if (entry == null)
                return;
            listBox.Items.Add(0);
            entry.FramesList.Insert(index, 0);

            /*if (entry.LoopFrame >= index)
            {
                entry.LoopFrame++;
                if (entry.LoopFrame >= entry.FramesCount)
                {
                    entry.LoopFrame = entry.FramesCount - 1;
                }
            }*/
        }
        private void bRemove_Click(object sender, EventArgs e)
        {
            int index = listBox.SelectedIndex;
            if (index == -1)
                return;
            if (listBox.Items.Count == 0)
                return;
            if (entry == null)
                return;
            listBox.Items.RemoveAt(0);
            entry.FramesList.RemoveAt(index);

            if (entry.LoopFrame >= index && entry.LoopFrame > 0)
            {
                entry.LoopFrame--;
                if (entry.LoopFrame >= entry.FramesCount)
                {
                    entry.LoopFrame = entry.FramesCount - 1;
                }
            }
        }
        private void bLoop_Click(object sender, EventArgs e)
        {
            int index = listBox.SelectedIndex;
            if (index == -1)
                return;
            entry.LoopFrame = index;
            listBox.Invalidate();
        }
        private void radioPlay_CheckedChanged(object sender, EventArgs e)
        {
            if (OnPlay != null)
                OnPlay(this);
        }
        private void radioPause_CheckedChanged(object sender, EventArgs e)
        {
            if (OnPause != null)
                OnPause(this);
        }
        private void listBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index == -1) return;
            if (Animation == null) return;
            if (Sprite == null) return;
            if (AnimationIndex == -1 || AnimationIndex >= Animation.AnimationCount)
                return;
            if (entry == null)
                return;
            e.DrawBackground();
            e.DrawFocusRectangle();

            ushort index = entry.FramesList[e.Index];
            if (index < Animation.FrameCount)
            {
                AnimationFrame frame = Animation.AnimationFrames[index];
                e.Graphics.DrawImage(Sprite, new Rectangle(e.Bounds.Left, e.Bounds.Top, e.Bounds.Height, e.Bounds.Height),
                    new Rectangle(frame.Position, frame.Size), GraphicsUnit.Pixel);
            }
            string str = index.ToString();
            if (e.Index == entry.LoopFrame)
                str += "\nloop";
            e.Graphics.DrawString(str, this.Font, new SolidBrush(this.ForeColor),
                new RectangleF(e.Bounds.Left + e.Bounds.Height, e.Bounds.Top, e.Bounds.Width - e.Bounds.Height, e.Bounds.Height));

        }
        private void listBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            e.ItemHeight = 32;
        }

        // Eventi
        public delegate void delegate_OnPlay(object sender);
        public delegate void delegate_OnPause(object sender);
        public delegate void delegate_OnSelectedFrame(object sender, int frame);

        [Category("Action")]
        [Description("Play button pressed")]
        public event delegate_OnPlay OnPlay;
        [Category("Action")]
        [Description("Pause button pressed")]
        public event delegate_OnPause OnPause;
        [Category("Action")]
        [Description("When a frame is selected")]
        public event delegate_OnSelectedFrame OnSelectedFrame;
    }
}
