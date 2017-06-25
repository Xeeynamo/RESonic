using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace GFXTool
{
    public partial class Form1 : Form
    {
        int textureIndex;
        GFXLib gfx;
        LUTLib lut;
        Bitmap bmp;
        Bitmap bmpOriginal;

        Bitmap BitmapImage
        {
            get { return bmp; }
            set
            {
                bmpOriginal = value;
                bmp = (Bitmap)bmpOriginal.Clone();
                panelPicture.BackgroundImage = bmp;

                gfx.Resolution = 1;
                gfx.TextureCount = 1;
                LoadControlsValue();

                if (bmp.Palette.Entries.Length != 0)
                {
                    lut.Palette = bmp.Palette;
                    bmp.Palette = lut.Palette;
                }
            }
        }
        void LoadControlsValue()
        {
            nDestination.Value = gfx.DestinationIndex;
            nResolution.Value = gfx.Resolution;
            nTextureCount.Value = gfx.TextureCount;
            switch (bmpOriginal.PixelFormat)
            {
                case PixelFormat.Format1bppIndexed:
                    comboMode.SelectedIndex = 1;
                    break;
                case PixelFormat.Format4bppIndexed:
                    comboMode.SelectedIndex = 2;
                    break;
                case PixelFormat.Format8bppIndexed:
                    comboMode.SelectedIndex = 3;
                    break;
                case PixelFormat.Format16bppRgb565:
                    comboMode.SelectedIndex = 4;
                    break;
                case PixelFormat.Format24bppRgb:
                    comboMode.SelectedIndex = 5;
                    break;
                case PixelFormat.Format32bppArgb:
                    comboMode.SelectedIndex = 6;
                    break;
                case PixelFormat.Format32bppRgb:
                    comboMode.SelectedIndex = 6;
                    break;
                default:
                    comboMode.SelectedIndex = 0;
                    break;
            }
            Control_LoadImageSize((int)bmp.Width, (int)bmp.Height);
        }
        void Control_LoadImageSize(int width, int height)
        {
            gfx.SetSize(width / gfx.Resolution, (height / gfx.Resolution) / gfx.TextureCount);
            // Controlla la larghezza
            if (((gfx.Size.width & 3) != 0) ||
                gfx.Size.width * gfx.Resolution != width)
            {
                nWidth.BackColor = Color.Red;
            }
            else nWidth.BackColor = Color.DarkGreen;
            // Controlla l'altezza
            if (((gfx.Size.height & 3) != 0) ||
                gfx.Size.height * gfx.Resolution * gfx.TextureCount != height)
            {
                nHeight.BackColor = Color.Red;
            }
            else nHeight.BackColor = Color.DarkGreen;

            nWidth.Value = gfx.Size.width;
            nHeight.Value = gfx.Size.height;
        }
        void ConvertBPPImage(Bitmap bmpOriginal, ref Bitmap bmpOutput, GFXLib gfx)
        {
            PixelFormat format = gfx.PixelMode;
            Rectangle lockRect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            bmpOutput = bmpOriginal.Clone(lockRect, format);
        }

        public Form1()
        {
            InitializeComponent();
            textureIndex = 0;
            gfx = new GFXLib();
            lut = new LUTLib();
        }


        private void importImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Recommend files|*.png;*.bmp;*.gif|All files|*.*";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                gfx.Identity();
                BitmapImage = new Bitmap(openFileDialog.FileName);
            }
        }
        private void importGFXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "GFX XeEngine texture|*.GFX";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                gfx.Open(openFileDialog.FileName, ref bmpOriginal);
                BitmapImage = bmpOriginal;
            }
        }
        private void exportImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Image file|*.png;*.bmp;*.gif|PNG file|*.png|Bitmap file|*.bmp|Bitmap file|*.gif";
            saveFileDialog.AddExtension = true;
            saveFileDialog.DefaultExt = "bmp";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                ImageFormat format;
                switch (Path.GetExtension(saveFileDialog.FileName).ToLower())
                {
                    case ".png":
                        format = ImageFormat.Png;
                        break;
                    case ".bmp":
                        format = ImageFormat.Bmp;
                        break;
                    case ".gif":
                        format = ImageFormat.Gif;
                        break;
                    default:
                        format = ImageFormat.Bmp;
                        break;
                }
                BitmapImage.Save(saveFileDialog.FileName, format);
            }
        }
        private void exportGFXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "GFX XeEngine texture|*.GFX";
            saveFileDialog.AddExtension = true;
            saveFileDialog.DefaultExt = "GFX";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                gfx.Save(saveFileDialog.FileName, ref bmp);
            }
        }
        private void importPaletteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "GFX XeEngine texture|*.GFX";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                gfx.Open(openFileDialog.FileName, ref bmpOriginal);
                BitmapImage = bmpOriginal;
            }
        }
        private void exportPaletteToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        private void importSonic16x16ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Multiselect = true;
            openFileDialog.Filter = "Sonic 1/2/3K/CD tiles|*.png";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                double minsize;
                int size;
                Array.Sort(openFileDialog.FileNames);
                minsize = Math.Sqrt((double)openFileDialog.FileNames.Length);
                if (minsize > (double)((int)minsize))
                    minsize = (double)((int)minsize + 1);
                size = (int)minsize;
                if ((size&3)!=0)
                    minsize += (4 - (minsize % 4));
                Bitmap bmp = new Bitmap(size*16, size*16, PixelFormat.Format8bppIndexed);
                Graphics g = Graphics.FromImage(bmp);
                for (int i = 0; i < openFileDialog.FileNames.Length; i++)
                {
                    g.DrawImage(new Bitmap(openFileDialog.FileNames[i]), (i % size) * 16, (i / size) * 16);
                }
                ColorPalette palette = bmp.Palette;
                Bitmap bmppalette = new Bitmap(openFileDialog.FileNames[0]);
                for (int i = 0; i < bmppalette.Palette.Entries.Length; i++)
                {
                    palette.Entries[0] = bmppalette.Palette.Entries[i];
                }
                bmp.Palette = palette;
                BitmapImage = bmp;
            }
        }

        private void scrollTexture_Scroll(object sender, ScrollEventArgs e)
        {
            textureIndex = scrollTexture.Value - 1;
            panelPicture.Invalidate();
        }
        private void nDestination_ValueChanged(object sender, EventArgs e)
        {
            gfx.DestinationIndex = (byte)nDestination.Value;
        }
        private void nResolution_ValueChanged(object sender, EventArgs e)
        {
            gfx.Resolution = (byte)nResolution.Value;
            Control_LoadImageSize(bmp.Width, bmp.Height);
            panelPicture.Invalidate();
        }
        private void nTextureCount_ValueChanged(object sender, EventArgs e)
        {
            scrollTexture.Maximum = (int)nTextureCount.Value;
            gfx.TextureCount = (byte)nTextureCount.Value;
            Control_LoadImageSize(bmp.Width, bmp.Height);
            panelPicture.Invalidate();
        }
        private void comboMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (bmp == null) return;
            gfx.Mode = (byte)comboMode.SelectedIndex;
            ConvertBPPImage(bmpOriginal, ref bmp, gfx);
            panelPicture.Invalidate();
        }

        private void panelPicture_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillRectangle(new SolidBrush(panelPicture.BackColor), 0, 0, panelPicture.Size.Width, panelPicture.Size.Height);
            if (bmp == null) return;
            int h = bmp.Height / gfx.TextureCount;

            Rectangle dstRect = new Rectangle(0, 0, bmp.Width / gfx.Resolution, h / gfx.Resolution);
            Rectangle srcRect = new Rectangle(0, h * textureIndex, bmp.Width, h);
            e.Graphics.DrawImage(bmp, dstRect, srcRect, GraphicsUnit.Pixel);
            panelPalette.Invalidate();
        }
        private void panelPalette_Paint(object sender, PaintEventArgs e)
        {
            if (bmp == null) return;
            int palettecount = bmp.Palette.Entries.Length;
            int elementsperline = palettecount > 16 ? 16 : 4;
            int size = Math.Min(panelPalette.Width, panelPalette.Height) / elementsperline;
            for (int i = 0, k = 0; i < elementsperline; i++)
            {
                for (int j = 0; j < elementsperline && k < palettecount; j++, k++)
                {
                    e.Graphics.FillRectangle(new SolidBrush(bmp.Palette.Entries[k]), j * size, i * size, size - 1, size - 1);
                }
            }
        }

        private void bImportPalette_Click(object sender, EventArgs e)
        {
            if (gfx.PixelMode == PixelFormat.Format1bppIndexed ||
                gfx.PixelMode == PixelFormat.Format4bppIndexed ||
                gfx.PixelMode == PixelFormat.Format8bppIndexed)
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "All CLUT supported|*.lut;*.act;*.bin|Xeeynamo's engine CLUT file|*.lut|Photoshop CLUT|*.act|Sonic the Hedgehog Megadrive Palette|*.bin";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    int type = (cbGfxType.SelectedIndex == -1 ? 0 : cbGfxType.SelectedIndex) & 3;
                    ColorPalette pal = bmp.Palette;
                    int colorsCount = bmp.Palette.Entries.Length;
                    string ext = Path.GetExtension(openFileDialog.FileName);
                    FileStream f;
                    Color[] colorArray;
                    switch (ext.ToUpper())
                    {
                        case ".ACT":
                            f = new FileStream(openFileDialog.FileName, FileMode.Open, FileAccess.Read);
                            colorsCount = Math.Min((int)(f.Length / 3), colorsCount);
                            for (int i = 0; i < colorsCount; i++)
                            {
                                byte R = (byte)f.ReadByte();
                                byte G = (byte)f.ReadByte();
                                byte B = (byte)f.ReadByte();
                                pal.Entries[i] = Color.FromArgb(255, R, G, B);
                            }
                            lut.Palette = pal;
                            f.Close();
                            break;
                        case ".BIN":
                            f = new FileStream(openFileDialog.FileName, FileMode.Open, FileAccess.Read);
                            colorArray = new Color[f.Length / 2];
                            for (int i = 0; i < colorArray.Length; i++)
                            {
                                byte color1 = (byte)f.ReadByte();
                                byte color2 = (byte)f.ReadByte();
                                byte R = (byte)((color2 & 0xF) << 4);
                                byte G = (byte)(color2 &0xF0);
                                byte B = (byte)((color1 & 0xF) << 4);
                                colorArray[i] = Color.FromArgb(255, R, G, B);
                            }
                            lut.Palette = pal;
                            lut.ColorArray = colorArray;
                            pal = lut.ClutIndex(0);
                            f.Close();
                            break;
                        case ".LUT":
                            lut.OpenLUT(openFileDialog.FileName);
                            pal = lut.Palette;
                            break;
                    }
                    nColorsCount.Maximum = lut.Count - 1;
                    nColorsCount.Value = 0;
                    bmp.Palette = pal;
                    panelPicture.Invalidate();
                }
            }
            else
            {
                MessageBox.Show("Palette works only on 1/4/8 bpp modes", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void bExportPalette_Click(object sender, EventArgs e)
        {
            if (gfx.PixelMode == PixelFormat.Format1bppIndexed ||
                gfx.PixelMode == PixelFormat.Format4bppIndexed ||
                gfx.PixelMode == PixelFormat.Format8bppIndexed)
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "Color LookUp-Table file|*.lut";
                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    lut.Save(saveFileDialog.FileName);
                }
            }
            else
            {
                MessageBox.Show("Palette works only on 1/4/8 bpp modes", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        bool mouseDragMode = false;
        int mouseDragFrom = 0;
        private void panelPalette_MouseDown(object sender, MouseEventArgs e)
        {
            int elementsperline = bmp.Palette.Entries.Length > 16 ? 16 : 4;
            int size = Math.Min(panelPalette.Width, panelPalette.Height) / elementsperline;
            int index = (e.X / size) + ((e.Y / size) * elementsperline);
            if (e.Button == MouseButtons.Right)
            {
                ColorDialog colorDialog = new ColorDialog();
                for (int i = 0; i < 0x10; i++)
                {
                    colorDialog.CustomColors[i] = bmp.Palette.Entries[i].ToArgb();
                    colorDialog.Color = bmp.Palette.Entries[index];
                }
                if (colorDialog.ShowDialog() == DialogResult.OK)
                {
                    lut.color[(int)(lut.ColorDepth * nColorsCount.Value + index)] = colorDialog.Color;
                    bmp.Palette = lut.ClutIndex((int)nColorsCount.Value);
                    panelPicture.Invalidate();
                }
                return;
            }

            if (gfx.PixelMode == PixelFormat.Format1bppIndexed ||
                gfx.PixelMode == PixelFormat.Format4bppIndexed ||
                gfx.PixelMode == PixelFormat.Format8bppIndexed)
            {
                mouseDragFrom = index;
                if (mouseDragFrom >= bmp.Palette.Entries.Length) return;
                mouseDragMode = true;
                panelMoveColor.Size = new Size(size, size);
                panelMoveColor.Visible = true;
                panelMoveColor.BackColor = bmp.Palette.Entries[mouseDragFrom];
            }
            panelMoveColor.Location = new Point(e.X - panelMoveColor.Size.Width / 2, e.Y - panelMoveColor.Size.Height / 2);
        }
        private void panelPalette_MouseMove(object sender, MouseEventArgs e)
        {
            if (mouseDragMode == true)
            {
                panelMoveColor.Location = new Point(e.X - panelMoveColor.Size.Width / 2, e.Y - panelMoveColor.Size.Height / 2);
            }
        }
        private void panelPalette_MouseUp(object sender, MouseEventArgs e)
        {
            if (mouseDragMode == false) return;
            int elementsperline = bmp.Palette.Entries.Length > 16 ? 16 : 4;
            int size = Math.Min(panelPalette.Width, panelPalette.Height) / elementsperline;
            int mouseDragTo = (e.X / size) + ((e.Y / size) * elementsperline);
            mouseDragMode = false;
            panelMoveColor.Visible = false;
            if (mouseDragTo >= bmp.Palette.Entries.Length) return;
            if (mouseDragFrom == mouseDragTo) return;

            /*ColorPalette pal = bmp.Palette;
            Color tmp = pal.Entries[mouseDragTo];
            pal.Entries[mouseDragTo] = pal.Entries[mouseDragFrom];
            pal.Entries[mouseDragFrom] = tmp;
            bmp.Palette = pal;*/

            Color tmp = lut.color[(int)nColorsCount.Value * elementsperline + mouseDragTo];
            lut.color[(int)nColorsCount.Value * elementsperline + mouseDragTo] = lut.color[(int)nColorsCount.Value * elementsperline + mouseDragFrom];
            lut.color[(int)nColorsCount.Value * elementsperline + mouseDragFrom] = tmp;
            bmp.Palette = lut.ClutIndex((int)nColorsCount.Value);

            BitmapData bmpdata = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, bmp.PixelFormat);
            byte[] data = new byte[bmpdata.Stride * bmp.Height];
            int datasize = data.Length;
            System.Runtime.InteropServices.Marshal.Copy(bmpdata.Scan0, data, 0, datasize);

            if (bmp.PixelFormat == PixelFormat.Format4bppIndexed)
            {
                for (int i = 0; i < datasize; i++)
                {
                    if ((data[i] & 0xF) == (byte)mouseDragFrom)
                        data[i] = (byte)(mouseDragTo | (data[i] & 0xF0));
                    else if ((data[i] & 0xF) == (byte)mouseDragTo)
                        data[i] = (byte)(mouseDragFrom | (data[i] & 0xF0));

                    if ((data[i] >> 4) == (byte)mouseDragFrom)
                        data[i] = (byte)((mouseDragTo<<4) | (data[i] & 0xF));
                    else if ((data[i] >> 4) == (byte)mouseDragTo)
                        data[i] = (byte)((mouseDragFrom << 4) | (data[i] & 0xF));
                }
            }
            else
            {
                for (int i = 0; i < datasize; i++)
                {
                    if (data[i] == (byte)mouseDragFrom)
                        data[i] = (byte)mouseDragTo;
                    else if (data[i] == (byte)mouseDragTo)
                        data[i] = (byte)mouseDragFrom;
                }
            }
            System.Runtime.InteropServices.Marshal.Copy(data, 0, bmpdata.Scan0, datasize);
            bmp.UnlockBits(bmpdata);
            panelPicture.Invalidate();
            return;
        }

        private void nColorsCount_ValueChanged(object sender, EventArgs e)
        {
            bmp.Palette = lut.ClutIndex((int)nColorsCount.Value);
            panelPicture.Invalidate();
        }

        private void cToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (BitmapImage == null) return;
            int emptycount = 0;
            List<int> indexes = new List<int>();
            Bitmap workbmp = (Bitmap)BitmapImage.Clone();

            int w = BitmapImage.Width / 16;
            int h = BitmapImage.Height / 16;

            for (int j = 0; j < h-1; j++)
            {
                for (int i = 0; i < w; i++)
                {
                    bool cont = false;
                    for (int ix = indexes.Count - 1; ix >= 0; ix--)
                    {
                        if (indexes[ix] == i+j*w)
                        {
                            cont = true;
                            ix = 0;
                        }
                    }
                    if (cont == true)
                        continue;

                    BitmapData data = BitmapImage.LockBits(new Rectangle(i * 16, j * 16, 16, 16), ImageLockMode.ReadOnly, BitmapImage.PixelFormat);
                    int length = data.Stride * data.Height / 0x10;
                    byte[] a = new byte[length];
                    byte[] b = new byte[length];
                    System.Runtime.InteropServices.Marshal.Copy(data.Scan0, a, 0, length);

                    for (int sj = j; sj < h; sj++)
                    {
                        for (int si = i + 1; si < w; si++)
                        {
                            BitmapData workdata = workbmp.LockBits(new Rectangle(si * 16, sj * 16, 16, 16), ImageLockMode.ReadOnly, BitmapImage.PixelFormat);
                            System.Runtime.InteropServices.Marshal.Copy(workdata.Scan0, b, 0, length);

                            bool empty = true;
                            bool equal = true;
                            for (int k = 0; k < length; k++)
                            {
                                if (a[k] != 0)
                                {
                                    empty = false;
                                }
                                if (a[k] != b[k])
                                {
                                    equal = false;
                                    k = length;
                                }
                            }
                            if (empty == false)
                            {
                                if (equal == true)
                                {
                                    int index = i + j * w;
                                    bool dup = false;
                                    for (int ix = indexes.Count - 1; ix >= 0; ix--)
                                    {
                                        if (indexes[ix] == index)
                                        {
                                            dup = true;
                                            ix = 0;
                                        }
                                    }
                                    if (dup == false)
                                        indexes.Add(index);
                                }
                            }
                            else
                                emptycount++;
                            workbmp.UnlockBits(workdata);
                        }
                    }

                    BitmapImage.UnlockBits(data);
                }
            }

            MessageBox.Show("Found " + indexes.Count.ToString() + " duplicate tiles!\n" +
                "Found also " + emptycount.ToString() + " empty tiles!\n");

            string str = "";
            for (int i = 0; i < indexes.Count; i++)
            {
                int tmp;
                tmp = (indexes[i] % w) * 16;
                str += "X " + tmp.ToString();
                tmp = (indexes[i] / w) * 16;
                str += "Y " + tmp.ToString();
                if ((i % 4) == 0)
                    str += "\n";
                else
                    str += "\t";
            }
            MessageBox.Show(str);
        }
        private void importFromRaw4bppGenesisToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Binary files|*.bin;*.dec|All files|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                FileStream f = new FileStream(openFileDialog.FileName, FileMode.Open, FileAccess.Read);
                byte[] data = new byte[f.Length];
                f.Read(data, 0, data.Length);
                gfx.Create(8, (short)(data.Length / 4), PixelFormat.Format4bppIndexed, data, ref bmpOriginal);
                BitmapImage = bmpOriginal;
            }
        }
        private void loadMappingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Mapping files|*.dec|All files|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                /*talloc.Tile = (data & 0x3FF);
                talloc.mirror = (data & 0x0800) ? 1 : 0;
                talloc.flip = (data & 0x1000) ? 1 : 0;
                talloc.path1 = (data >> 13);
                talloc.path2 = (data >> 13);
                talloc.unknow = 0;*/

                FileStream f = new FileStream(openFileDialog.FileName, FileMode.Open, FileAccess.Read);
                ushort map = (ushort)((f.ReadByte() << 8) | f.ReadByte());

                //new Bitmap()
                //BitmapImage = new Bitmap(openFileDialog.FileName);
                /*byte[] data = new byte[f.Length];
                f.Read(data, 0, data.Length);
                gfx.Create(8, (short)(data.Length / 4), PixelFormat.Format4bppIndexed, data, ref bmpOriginal);
                BitmapImage = bmpOriginal;*/
            }
        }

        unsafe private void importRSDKGIFToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "RSDK gif|*.gif|All files|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Bitmap inbmp = new Bitmap(openFileDialog.FileName);
                int tilesPerLine = (int)Math.Sqrt((double)(inbmp.Size.Height / 16)) * 16;
                Bitmap outbmp = new Bitmap(tilesPerLine, tilesPerLine, inbmp.PixelFormat);
                outbmp.Palette = inbmp.Palette;

                BitmapData indata = inbmp.LockBits(new Rectangle(0, 0, inbmp.Width, inbmp.Height), ImageLockMode.ReadOnly, inbmp.PixelFormat);
                BitmapData outdata = outbmp.LockBits(new Rectangle(0, 0, outbmp.Width, outbmp.Height), ImageLockMode.ReadOnly, outbmp.PixelFormat);

                byte* din = (byte*)indata.Scan0;
                byte* dout = (byte*)outdata.Scan0;

                for (int j = 0; j < 1024; j++)
                {
                    for (int i = 0; i < 16; i++)
                    {
                        for (int k = 0; k < 16; k++)
                        {
                            dout[k + i * tilesPerLine + (j % 32) * 16 + (j >> 5) * 16 * tilesPerLine] = din[k + i * 16 + j * 16 * 16];
                        }
                    }
                }
                inbmp.UnlockBits(indata);
                outbmp.UnlockBits(outdata);

                BitmapImage = outbmp;
                return;
            }
        }
    }
}
