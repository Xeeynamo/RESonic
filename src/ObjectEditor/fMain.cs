using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using XeLib;
using System.IO;

namespace ObjectEditor
{
    public partial class fMain : Form
    {
        AnimationFrame m_frame;
        string filename;
        Entity entity = new Entity();
        GFX gfx = new GFX();
        LUT lut = new LUT();
        Bitmap sprite;

        public fMain()
        {
            InitializeComponent();
            RefreshGUI();
            animList1.AnimationList = "AnimList.xml";
        }
        void RefreshGUI()
        {
            //////////////////////////////////////////////////////////////////////////
            // Overview
            textWorkingPath.Text = Directory.GetCurrentDirectory();
            textFileName.Text = Path.GetFileNameWithoutExtension(filename);

            textEntityName.Text = entity.Properties.Name;
            nEntityID.Value = entity.Properties.ID;
            comboEntityType.SelectedIndex = entity.Properties.Type;

            //////////////////////////////////////////////////////////////////////////
            // Frames
            comboFrameBox1.Entity = entity;
            comboFrameBox2.Entity = entity;
            comboFrameBoxHitbox.Entity = entity;
            comboFrameBoxHitboxFrame.Entity = entity;
            frameBox1.Frame = comboFrameBox1.Frame;

            cbZoom.Checked = frameBox1.Zoom;
            cbFrameShowHitbox.Checked = frameBox1.ShowHitbox;
            m_frame = frameBox1.Frame;
            animationBox.Entity = entity;

            RefreshGUI_SetFrame(comboFrameBox1.Frame);
        }
        void RefreshGUI_SetFrame(AnimationFrame frame)
        {
            nFrameSourceX.Value = frame.Position.X;
            nFrameSourceY.Value = frame.Position.Y;
            nFrameWidth.Value = frame.Size.Width;
            nFrameHeight.Value = frame.Size.Height;
            nFrameCenterX.Value = frame.Center.X;
            nFrameCenterY.Value = frame.Center.Y;
            nFrameHitbox.Value = frame.Hitbox;
        }
        void RefreshGUI_SetHitbox(Hitbox hitbox)
        {
            nHitboxSourceX.Value = hitbox.X1;
            nHitboxSourceY.Value = hitbox.Y1;
            nHitboxWidth.Value = hitbox.X2;
            nHitboxHeight.Value = hitbox.Y2;
        }
        void LaunchError(string message)
        {
            MessageBox.Show(message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void bOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "XeEngine entity definition|*.ent";
            openFileDialog.AddExtension = true;
            openFileDialog.CheckPathExists = true;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                FileStreamEx f;
                try
                {
                    f = new FileStreamEx(openFileDialog.FileName, System.IO.FileMode.Open, System.IO.FileAccess.Read);
                    FileName = openFileDialog.FileName;
                }
                catch (System.Exception ex)
                {
                    LaunchError(ex.Message);
                    return;
                }
                entity.Load(f);
                f.Close();
                RefreshGUI();
            }
        }

        private void bSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "XeEngine entity definition|*.ent";
            saveFileDialog.AddExtension = true;
            saveFileDialog.CheckPathExists = true;
            saveFileDialog.FileName = filename;
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                FileStreamEx f;
                try
                {
                    f = new FileStreamEx(saveFileDialog.FileName, System.IO.FileMode.Create, System.IO.FileAccess.Write);
                    FileName = saveFileDialog.FileName;
                }
                catch (System.Exception ex)
                {
                    LaunchError(ex.Message);
                    return;
                }
                entity.Animation.RemoveEmptyAnimations();
                entity.Save(f);
                f.Close();
            }
        }
        private string FileName
        {
            get
            {
                return filename;
            }
            set
            {
                filename = value;
                Directory.SetCurrentDirectory(Path.GetDirectoryName(filename));
                textWorkingPath.Text = Directory.GetCurrentDirectory();
                textFileName.Text = "";
            }
        }
        protected int FrameIndex
        {
            set
            {
                m_frame = entity.Animation.AnimationFrames[value];
            }
        }
        public Bitmap Sprite
        {
            get
            {
                return sprite;
            }
            set
            {
                sprite = value;
                frameBox1.SpriteSheet = value;
                comboFrameBox1.Sprite = value;
                comboFrameBox2.Sprite = value;
                comboFrameBoxHitboxFrame.Sprite = value;
                animationBox.Sprite = value;
                listFrameBox1.Sprite = value;
            }
        }

        bool LoadGFX(string filename)
        {
            try
            {
                return gfx.Open(filename, ref sprite);
            }
            catch (System.Exception ex)
            {
                LaunchError(ex.Message);
                return false;
            }
        }
        bool LoadLut(string filename)
        {
            try
            {
                lut.Palette = sprite.Palette;
                lut.OpenLUT(filename);
                sprite.Palette = lut.Palette;
                return true;
            }
            catch (System.IO.FileNotFoundException)
            {
                return false;
            }
            catch (System.Exception ex)
            {
                LaunchError(ex.Message);
                return false;
            }
        }
        int LoadEntityGraphics(string gfxFilename, string lutFilename)
        {
            int ok = 0;
            if (LoadGFX(gfxFilename) == true)
            {
                ok += 1;
                Sprite = sprite;
            }
            if (LoadLut(lutFilename) == true)
                ok += 2;
            return ok;
        }
        int LoadEntityGraphicsByEntity(string entityname)
        {
            string tmp;
            for (int i = 8; i > 0; i--)
            {
                tmp = entityname + "@" + i.ToString() + ".GFX";
                if (System.IO.File.Exists(tmp) == true)
                {
                    return LoadEntityGraphics(tmp, entityname + ".LUT");
                }
            }
            tmp = entityname + ".GFX";
            if (System.IO.File.Exists(tmp) == true)
            {
                return LoadEntityGraphics(tmp, entityname + ".LUT");
            }
            return 0;
        }

        private void textEntityName_TextChanged(object sender, EventArgs e)
        {
            entity.Properties.Name = textEntityName.Text;
            animList1.ObjectName = textEntityName.Text;
            switch (LoadEntityGraphicsByEntity(entity.Properties.Name))
            {
                case 0:
                    textEntityName.BackColor = Color.DarkRed;
                    break;
                case 1:
                    textEntityName.BackColor = Color.DarkOrange;
                    break;
                case 2:
                    textEntityName.BackColor = Color.DarkOrange;
                    break;
                case 3:
                    textEntityName.BackColor = Color.DarkGreen;
                    break;
            }
        }
        private void nEntityID_ValueChanged(object sender, EventArgs e)
        {
            entity.Properties.ID = (ushort)nEntityID.Value;
        }
        private void comboEntityType_SelectedIndexChanged(object sender, EventArgs e)
        {
            entity.Properties.Type = comboEntityType.SelectedIndex;
        }

        private void panelFrame_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(sprite, new Point(0, 0));
        }

        private void frameBox1_OnFrameboxChanging(object sender, AnimationFrame e)
        {
            RefreshGUI_SetFrame(e);
        }
        private void frameBox1_OnFrameboxChanged(object sender, AnimationFrame e)
        {
            RefreshGUI_SetFrame(e);
        }
        private void comboFrameBox1_SelectedIndexChanged(object sender, AnimationFrame e, int index)
        {
            m_frame = comboFrameBox1.Frame;
            frameBox1.Frame = m_frame;
            RefreshGUI_SetFrame(m_frame);
        }
        private void bFrameCenter_Click(object sender, EventArgs e)
        {
            m_frame.Center = new Point(m_frame.Size.Width / 2, m_frame.Size.Height / 2);
            RefreshGUI_SetFrame(m_frame);
        }

        private void cbZoom_CheckedChanged(object sender, EventArgs e)
        {
            frameBox1.Zoom = cbZoom.Checked;
            frameBox1.Invalidate();
        }
        private void cbFrameShowHitbox_CheckedChanged(object sender, EventArgs e)
        {
            frameBox1.ShowHitbox = cbFrameShowHitbox.Checked;
        }

        private void Frame_ValuesChanged(object sender, EventArgs e)
        {
            
            switch (Convert.ToInt32(((NumericUpDown)sender).Tag))
            {
                case 1:
                    m_frame.Position = new Point((int)nFrameSourceX.Value, m_frame.Position.Y);
                    break;
                case 2:
                    m_frame.Position = new Point(m_frame.Position.X, (int)nFrameSourceY.Value);
                    break;
                case 3:
                    m_frame.Size = new Size((int)nFrameWidth.Value, m_frame.Size.Height);
                    break;
                case 4:
                    m_frame.Size = new Size(m_frame.Size.Width, (int)nFrameHeight.Value);
                    break;
                case 5:
                    m_frame.Center = new Point((int)nFrameCenterX.Value, m_frame.Center.Y);
                    break;
                case 6:
                    m_frame.Center = new Point(m_frame.Center.X, (int)nFrameCenterY.Value);
                    break;
                case 7:
                    if (nFrameHitbox.Value >= entity.Physic.HitboxCount)
                    {
                        nFrameHitbox.Value = entity.Physic.HitboxCount - 1;
                    }
                    else
                    {
                        m_frame.Hitbox = (int)nFrameHitbox.Value;
                        frameBox1.Hitbox = entity.Physic.Hitbox[m_frame.Hitbox];
                    }
                    break;
            }
            frameBox1.Invalidate();
        }

        //////////////////////////////////////////////////////////////////////////
        /// HITBOX PART
        private void comboFrameBoxHitbox_SelectedIndexChanged(object sender, AnimationFrame e, int index)
        {
            panelHitbox.Invalidate();
        }
        private void comboFrameBoxHitbox_SelectedIndexChanged_1(object sender, AnimationFrame e, int index)
        {
            RefreshGUI_SetHitbox(entity.Physic.Hitbox[comboFrameBoxHitbox.SelectedIndex]);
            panelHitbox.Invalidate();
        }
        private void panelHitbox_Paint(object sender, PaintEventArgs e)
        {
            int frameIndex = comboFrameBoxHitboxFrame.SelectedIndex;
            int hitboxIndex = comboFrameBoxHitbox.SelectedIndex;
            if (frameIndex != -1 && sprite != null)
            {
                AnimationFrame frame = entity.Animation.AnimationFrames[frameIndex];
                e.Graphics.DrawImage(sprite, new Rectangle(128 - frame.Center.X, 128 - frame.Center.Y, frame.Size.Width, frame.Size.Height)
                    , new Rectangle(frame.Position, frame.Size), GraphicsUnit.Pixel);
            }
            if (hitboxIndex != -1)
            {
                Hitbox hitbox = entity.Physic.Hitbox[hitboxIndex];
                e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(0x80, Color.Aquamarine)),
                    new Rectangle(128 - hitbox.X1, 128 - hitbox.Y1, hitbox.Width, hitbox.Height));
            }
        }

        private void nHitbox_ValueChanged(object sender, EventArgs e)
        {
            if (comboFrameBoxHitbox.SelectedIndex == -1)
                return;
            Hitbox hitbox = entity.Physic.Hitbox[comboFrameBoxHitbox.SelectedIndex];
            switch (Convert.ToInt32(((NumericUpDown)sender).Tag))
            {
                case 1:
                    hitbox.X1 = (int)((NumericUpDown)sender).Value;
                    break;
                case 2:
                    hitbox.Y1 = (int)((NumericUpDown)sender).Value;
                    break;
                case 3:
                    hitbox.X2 = (int)((NumericUpDown)sender).Value;
                    break;
                case 4:
                    hitbox.Y2 = (int)((NumericUpDown)sender).Value;
                    break;
            }
            panelHitbox.Invalidate();
        }

        //////////////////////////////////////////////////////////////////////////
        // Animation
        private void animList1_OnSelectedAnimation(ushort id)
        {
            listFrameBox1.Animation = entity.Animation;
            int index = entity.Animation.GetAnimationIndex(id);
            if (index == -1)
            {
                entity.Animation.AddAnimation(id);
                index = entity.Animation.GetAnimationIndex(id);
            }
            animationBox.SelectedAnimationId = id;
            listFrameBox1.AnimationIndex = index;

            AnimationEntry entry = animationBox.AnimationEntry;
            if (entry != null)
            {
                nAnimationSpeed.Value = entry.Speed;
            }
        }
        private void listFrameBox1_OnPause(object sender)
        {
            animationBox.Pause();
        }
        private void listFrameBox1_OnPlay(object sender)
        {
            animationBox.Play();
        }
        private void listFrameBox1_OnSelectedFrame(object sender, int frame)
        {
            comboFrameBox2.SelectedIndex = frame;
        }
        private void comboFrameBox2_SelectedIndexChanged(object sender, AnimationFrame e, int index)
        {
            if (comboFrameBox2.SelectedIndex != -1)
            {
                listFrameBox1.SetFrameIndex(comboFrameBox2.SelectedIndex);
            }
        }
        private void nAnimationSpeed_ValueChanged(object sender, EventArgs e)
        {
            AnimationEntry entry = animationBox.AnimationEntry;
            if (entry != null)
            {
                entry.Speed = (int)nAnimationSpeed.Value;
            }
        }
    }
}
