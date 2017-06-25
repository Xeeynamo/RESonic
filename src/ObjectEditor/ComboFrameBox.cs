using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ObjectEditor
{
    public partial class ComboFrameBox : UserControl
    {
        Entity m_entity;
        Bitmap m_sprite;
        bool m_isHitbox;
        bool m_edits;

        public ComboFrameBox()
        {
            InitializeComponent();
            comboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_isHitbox = false;
            ShowEdits = true;
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
                bAdd.Enabled = bRemove.Enabled = value != null;

                comboBox.Items.Clear();
                if (m_entity != null)
                {
                    if (IsHitbox)
                    {
                        for (int i = 0; i < m_entity.Physic.HitboxCount; i++)
                        {
                            comboBox.Items.Add(m_entity.Physic.Hitbox[i]);
                        }
                    }
                    else
                    {
                        for (int i = 0; i < m_entity.Animation.FrameCount; i++)
                        {
                            comboBox.Items.Add(m_entity.Animation.AnimationFrames[i]);
                        }
                    }
                }
            }
        }
        public AnimationFrame Frame
        {
            get
            {
                return GetAnimationFrame(comboBox.SelectedIndex);
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
        public bool IsHitbox
        {
            get
            {
                return m_isHitbox;
            }
            set
            {
                m_isHitbox = value;
            }
        }
        public int SelectedIndex
        {
            get
            {
                return comboBox.SelectedIndex;
            }
            set
            {
                comboBox.SelectedIndex = value;
            }
        }
        public bool ShowEdits
        {
            get
            {
                return m_edits;
            }
            set
            {
                m_edits = value;
                if (value)
                {
                    bAdd.Visible = true;
                    bRemove.Visible = true;
                    comboBox.Size = new Size(this.Size.Width - 46, this.Size.Height);
                }
                else
                {
                    bAdd.Visible = false;
                    bRemove.Visible = false;
                    comboBox.Size = this.Size;
                }
            }
        }

        private AnimationFrame GetAnimationFrame(int index)
        {
            if (index == -1)
                return new AnimationFrame();
            else
                return m_entity.Animation.AnimationFrames[index];
        }
        private Hitbox GetHitboxFrame(int index)
        {
            if (index == -1)
                return new Hitbox();
            else
                return m_entity.Physic.Hitbox[index];
        }

        private void bAdd_Click(object sender, EventArgs e)
        {
            if (IsHitbox == true)
            {
                if (comboBox.SelectedIndex != -1)
                {
                    m_entity.Physic.Hitbox.Insert(comboBox.SelectedIndex + 1, new Hitbox());
                    comboBox.Items.Insert(comboBox.SelectedIndex + 1, new Hitbox());
                }
                else
                {
                    m_entity.Physic.Hitbox.Add(new Hitbox());
                    comboBox.Items.Add(new Hitbox());
                }
            }
            else
            {
                if (comboBox.SelectedIndex != -1)
                {
                    m_entity.Animation.AnimationFrames.Insert(comboBox.SelectedIndex + 1, new AnimationFrame());
                    comboBox.Items.Insert(comboBox.SelectedIndex + 1, new AnimationFrame());
                }
                else
                {
                    m_entity.Animation.AnimationFrames.Add(new AnimationFrame());
                    comboBox.Items.Add(new AnimationFrame());
                }
            }
        }
        private void bRemove_Click(object sender, EventArgs e)
        {
            if (IsHitbox == true)
            {
                m_entity.Physic.Hitbox.RemoveAt(comboBox.SelectedIndex);
                comboBox.Items.RemoveAt(comboBox.SelectedIndex);
            }
            else
            {
                m_entity.Animation.AnimationFrames.RemoveAt(comboBox.SelectedIndex);
                comboBox.Items.RemoveAt(comboBox.SelectedIndex);
            }
        }

        public delegate void delegate_SelectedIndexChanged(object sender, AnimationFrame e, int index);
        [Category("Action")]
        [Description("Fires when a frame was selected from the list")]
        public event delegate_SelectedIndexChanged SelectedIndexChanged;

        private void comboBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            Graphics g = e.Graphics;
            e.DrawBackground();
            if (e.Index >= 0)
            {
                AnimationFrame animFrame = null;
                Hitbox hitboxFrame;
                string strPart1 = IsHitbox ? "Hitbox " : "Frame ";
                string strFrame;
                if (IsHitbox == true)
                {
                    hitboxFrame = GetHitboxFrame(e.Index);
                    strFrame = strPart1 + e.Index.ToString() + "\n" + String.Format("Pos {0},{1} Size {2},{3}",
                    hitboxFrame.X1, hitboxFrame.Y1, hitboxFrame.X2, hitboxFrame.Y2);
                }
                else
                {
                    animFrame = GetAnimationFrame(e.Index);
                    strFrame = strPart1 + e.Index.ToString() + "\n" + String.Format("{0},{1} {2},{3} {4},{5} {6}",
                    animFrame.Position.X, animFrame.Position.Y, animFrame.Size.Width, animFrame.Size.Height,
                    animFrame.Center.X, animFrame.Center.Y, animFrame.Hitbox);
                }
                if (m_sprite == null || IsHitbox == true)
                {
                    g.DrawString(strFrame, e.Font, new SolidBrush(ForeColor), e.Bounds);
                }
                else
                {
                    g.DrawImage(m_sprite, new RectangleF(e.Bounds.X, e.Bounds.Y, e.Bounds.Height, e.Bounds.Height),
                        new Rectangle(animFrame.Position, animFrame.Size), GraphicsUnit.Pixel);
                    g.DrawString(strFrame, e.Font, new SolidBrush(ForeColor),
                        new RectangleF(e.Bounds.X + 32, e.Bounds.Y, e.Bounds.Width, e.Bounds.Height));
                }
            }
            e.DrawFocusRectangle();
        }

        private void comboBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            if (Sprite != null)
            {
                e.ItemHeight = 32;
            }
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox.SelectedIndex != -1)
            {
                bRemove.Enabled = true;
                if (SelectedIndexChanged != null)
                {
                    SelectedIndexChanged(this, GetAnimationFrame(comboBox.SelectedIndex), comboBox.SelectedIndex);
                }
            }
            else
            {
                bRemove.Enabled = false;
            }
        }
    }
}
