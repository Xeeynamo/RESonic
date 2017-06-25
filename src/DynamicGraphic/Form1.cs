using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using XeLib;

namespace DynamicGraphic
{
    public partial class Form1 : Form
    {
        LUT lut;
        Dynamic.Animation anim;

        public Form1()
        {
            InitializeComponent();

            anim = new Dynamic.Animation();
            //anim.source = new Bitmap("D:\\Xeeynamo\\Dropbox\\STHX\\@Final\\LEVEL\\S1GHZ\\Dynamic tiles\\_Flower large.png");
            anim.count = 4;
            anim.speed = 15;
            anim.index = 0;
            anim.framesIndex = 0;
            anim.framesCount = 1;
            anim.pattern = 0xFF;
            anim.dstIndex = 0;
            anim.dstTexture = 0;
            anim.pat[0] = 0xFF;

            panel1.AddAnimation(anim);
            panel1.SelectedAnimation = 0;
            SelectAnimation(panel1.CurrentAnimation);
        }

        private void SelectAnimation(Dynamic.Animation a)
        {
            anim = a;
            nSpeed.Value = anim.speed;
            nDstIndex.Value = anim.dstIndex;
            nDstTexture.Value = anim.dstTexture;
            nTilesPerLine.Value = anim.count;
            nFrameCount.Value = anim.framesCount + 1;
        }

        private void bLoadImage_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "GFX file|*.GFX";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                anim.LoadGFX(openFileDialog.FileName);
                SelectAnimation(panel1.CurrentAnimation);
            }
        }
        private void importLUTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (anim.bmp == null)
            {
                MessageBox.Show("Impossibile caricare la palette senza un GFX caricato precedentemente.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (anim.bmp.Palette.Entries.Length == 0)
            {
                MessageBox.Show("Il GFX selezionato non ha la modalità palette, quindi è inutile che tenti di caricare la palette, mongoloide! Scherzavo XD non te la prendere u.u", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "LUT file|*.LUT";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                lut = new LUT();
                lut.Palette = anim.bmp.Palette;
                lut.OpenLUT(openFileDialog.FileName);
                anim.bmp.Palette = lut.ClutIndex(0);
                nPaletteIndex.Enabled = true;
            }
        }
        private void nSpeed_ValueChanged(object sender, EventArgs e)
        {
            anim.speed = (byte)nSpeed.Value;
        }
        private void nDstIndex_ValueChanged(object sender, EventArgs e)
        {
            anim.dstIndex = (byte)nDstIndex.Value;
        }
        private void nDstTexture_ValueChanged(object sender, EventArgs e)
        {
            anim.dstTexture = (byte)nDstTexture.Value;
        }
        private void nPaletteIndex_ValueChanged(object sender, EventArgs e)
        {
            if (lut == null) return;
            anim.bmp.Palette = lut.ClutIndex((int)nPaletteIndex.Value);
        }
        private void cbPattern_CheckedChanged(object sender, EventArgs e)
        {
            anim.pattern = (byte)(cbPattern.Checked == true ? 0x00 : 0xFF);
        }

        private void tbPattern_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar))
            {
                if (e.KeyChar != ' ' && e.KeyChar != 0x08)
                    e.Handled = true;
            }
        }
        private void tbPattern_TextChanged(object sender, EventArgs e)
        {
            string s = "";
            string[] words = tbPattern.Text.Split(' ');
            for (int i = 0; i < words.Length; i++)
            {
                if (i != 0) s += ' ';
                if (words[i] == "")
                {
                    i = words.Length;
                    continue;
                }
                try
                {
                    anim.pat[i] = (byte)Convert.ToUInt64(words[i]);
                    if (anim.pat[i] == 0xFF)
                        anim.pat[i] = 0xFE;
                }
                catch (System.Exception)
                {
                    anim.pat[i] = 0;
                }
                s += anim.pat[i].ToString();
            }
            for (int i = words.Length; i < anim.pat.Length; i++)
                anim.pat[i] = 0xFF;
            tbPattern.Text = s;
            tbPattern.Select(s.Length, 0);
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Dynamic tiles|*.DTL|Dynamic palette|*.DCL";
            saveFileDialog.AddExtension = true;
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                panel1.SaveProject(saveFileDialog.FileName);
            }
        }
    }
}
