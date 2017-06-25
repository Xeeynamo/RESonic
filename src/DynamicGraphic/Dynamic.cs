using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using XeLib;

namespace DynamicGraphic
{
    public partial class Dynamic : UserControl
    {
        public class Animation
        {
            public GFX source;   // Sorgente immagine
            public Bitmap bmp;
            public byte count;      // Quantità dei contenuti da prendere
            public byte speed;      // Velocità dell'animazione
            public byte index;
            public byte framesCount;
            public byte framesIndex;
            public byte pattern;    // Indice della lista dei pattern
            public byte dstIndex;
            public byte dstTexture;

            public byte[] pat = new byte[0x100];

            public void LoadGFX(string filename)
            {
                source.Open(filename, ref bmp);
                count = (byte)(bmp.Width / 16 / source.Resolution);
                framesCount = (byte)(bmp.Height / 16 / source.Resolution - 1);
            }
            public void Load(FileStreamEx f)
            {
                count = f.Read8();
                speed = f.Read8();
                index = f.Read8();
                framesCount = f.Read8();
                framesIndex = f.Read8();
                pattern = f.Read8();
                dstIndex = f.Read8();
                dstTexture = f.Read8();
            }
            public void Save(FileStreamEx f)
            {
                index = 0;
                framesIndex = 0;

                f.Write8(count);
                f.Write8(speed);
                f.Write8(index);
                f.Write8(framesCount);
                f.Write8(framesIndex);
                f.Write8(pattern);
                f.Write8(dstIndex);
                f.Write8(dstTexture);
            }

            public Animation()
            {
                source = new GFX();
            }
        }
        List<Animation> animList;
        Rectangle src, dst;

        int selectedanimation;
        public Animation CurrentAnimation
        {
            get { return animList[selectedanimation]; }
        }
        public int SelectedAnimation
        {
            get { return selectedanimation; }
            set
            {
                if (selectedanimation < animList.Count)
                    selectedanimation = value;
            }
        }
        public bool AnimationRunning
        {
            get { return timerAnim.Enabled; }
            set { timerAnim.Enabled = value; }
        }

        public Dynamic()
        {
            InitializeComponent();
            src = new Rectangle();
            dst = new Rectangle();
            animList = new List<Animation>();
        }
        public void LoadProject(string filename)
        {
            FileStreamEx f = new FileStreamEx(filename, System.IO.FileMode.Open, System.IO.FileAccess.Read);



            f.Close();
        }
        public void SaveProject(string filename)
        {
            FileStreamEx f = new FileStreamEx(filename, System.IO.FileMode.Create, System.IO.FileAccess.Write);

            f.Write8((byte)animList.Count);
            f.Write8((byte)animList[0].source.Resolution);
            f.Write16((ushort)(animList[0].source.BitsPerPixel* animList[0].source.Resolution * 16 * 16 / 8));
            for (int i = 0; i < animList.Count; i++)
                animList[i].Save(f);
            for (int i = 0; i < animList.Count; i++)
            {
                int j = 0;
                do
                {
                    f.Write8(animList[i].pat[j]);
                } while (animList[i].pat[j] != 0xFF);
            }
            for (int i = 0; i < animList.Count; i++)
                animList[i].source.SaveRawData(ref animList[i].bmp, f);
            f.Close();
        }

        public void AddAnimation(Animation a)
        {
            animList.Add(a);
        }
        private void timerAnim_Tick(object sender, EventArgs e)
        {
            this.Invalidate();
        }
        private void Dynamic_Paint(object sender, PaintEventArgs e)
        {
            if (selectedanimation >= animList.Count) return;
            Animation anim = animList[selectedanimation];
            if (anim.bmp == null) return;

            // Avanza di un frame se index raggiunge speed
            if (++anim.index >= anim.speed)
            {
                anim.index = 0;
                anim.framesIndex++;
                /*if (anim.framesIndex++ >= anim.framesCount)
                {
                    anim.framesIndex = 0;
                }*/
            }

            // Imposta il frame da eseguire
            int index;
            if (anim.pattern != 0xFF)
            {
                if (anim.framesIndex >= anim.pat.Length)
                    return;
                if (anim.pat[anim.framesIndex] == 0xFF)
                    anim.framesIndex = 0;
                index = anim.pat[anim.framesIndex];
            }
            else
            {
                if (anim.framesIndex > anim.framesCount)
                {
                    anim.framesIndex = 0;
                }
                index = anim.framesIndex;
            }
            if (index == 0xFF) return;

            src.X = 0;
            src.Y = index * 16 * anim.source.Resolution;
            src.Width = anim.count * 16 * anim.source.Resolution;
            src.Height = 16 * anim.source.Resolution;

            dst.X = 0;
            dst.Y = 0;
            dst.Width = src.Width;
            dst.Height = src.Height;

            e.Graphics.DrawImage(anim.bmp, dst, src, GraphicsUnit.Pixel);
        }
    }
}
