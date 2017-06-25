using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ObjectEditor
{
    [DefaultEvent("OnFrameboxChanging")]
    public partial class FrameBox : UserControl
    {
        bool m_focus = false;
        int m_viewY = 0;
        int m_mouseX = 0;
        int m_mouseY = 0;
        bool m_mouseDown = false;
        bool m_zoom = false;
        bool m_showHitbox = false;
        Pen m_penMouse;
        Pen m_penSelection;
        Pen m_penCenter;
        AnimationFrame m_frame = new AnimationFrame();
        Hitbox m_hitbox;
        Bitmap m_sprite;
        Bitmap m_buffer = new Bitmap(256, 256);
        Point m_pSelection1 = new Point();
        Point m_pSelection2 = new Point();

        public FrameBox()
        {
            InitializeComponent();
            this.MouseWheel += new MouseEventHandler(FrameBox_MouseWheel);
            m_penMouse = new Pen(Color.FromArgb(0x80, 0xFF, 0xFF, 0xFF));
            m_penSelection = new Pen(Color.FromArgb(0xC0, 0xFF, 0xFF, 0xFF));
            m_penCenter = new Pen(Color.FromArgb(0xC0, 0xFF, 0x00, 0xFF));
            Hitbox = null;
        }

        public AnimationFrame Frame
        {
            get
            {
                return m_frame;
            }
            set
            {
                m_frame = value;
                Invalidate();
            }
        }
        public Hitbox Hitbox
        {
            get
            {
                return m_hitbox;
            }
            set
            {
                if (value == null)
                    m_hitbox = new Hitbox();
                else
                    m_hitbox = value;
                Invalidate();
            }
        }
        public Bitmap SpriteSheet
        {
            get
            {
                return m_sprite;
            }
            set
            {
                m_sprite = value;
                m_viewY = 0;
                Invalidate();
            }
        }
        public bool Zoom
        {
            get
            {
                return m_zoom;
            }
            set
            {
                m_zoom = value;
                Invalidate();
            }
        }
        public bool ShowHitbox
        {
            get
            {
                return m_showHitbox;
            }
            set
            {
                m_showHitbox = value;
                Invalidate();
            }
        }
        private bool FrameMouseDown
        {
            get
            {
                return m_mouseDown;
            }
            set
            {
                if (m_mouseDown == true && value == false)
                {
                    EditAndFire();
                }
                m_mouseDown = value;
            }
        }

        private void EditAndFire()
        {
            EditFrame(m_frame, m_pSelection1, m_pSelection2, m_viewY);
            if (this.OnFrameboxChanged != null)
            {
                OnFrameboxChanged(this, m_frame);
            }
        }
        private void SetFocus(bool focus)
        {
            if (focus == m_focus)
            {
                return;
            }

            if (focus == true)
            {
                Focus();
            }
            else
            {

            }
            FrameMouseDown = false;
            m_focus = focus;
            Invalidate();
        }

        void CorrectPoint(ref Point p)
        {
            if (p.X < 0) p.X = 0;
            if (p.X > 256) p.X = 256;
            if (p.Y < 0) p.Y = 0;
            if (p.Y > 256) p.Y = 256;
        }
        void EditFrame(AnimationFrame frame, Point p1, Point p2, int section)
        {
            CorrectPoint(ref p1);
            CorrectPoint(ref p2);
            frame.Position = new Point(Math.Min(p1.X, p2.X), Math.Min(p1.Y, p2.Y) + section);
            frame.Size = new Size(Math.Max(p1.X, p2.X) - frame.Position.X, Math.Max(p1.Y, p2.Y) - frame.Position.Y);
            frame.Center = new Point(frame.Size.Width / 2, frame.Size.Height / 2);
        }

        private void FrameBox_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            Graphics g = Graphics.FromImage(m_buffer);
            if (m_sprite != null)
            {
                if (m_focus == true)
                {
                    g.Clear(Color.Magenta);
                    Rectangle dstRect2 = new Rectangle(0, 0, m_sprite.Width, Math.Min(m_sprite.Height - m_viewY, 256));
                    Rectangle srcRect2 = new Rectangle(0, m_viewY, m_sprite.Width, Math.Min(m_sprite.Height - m_viewY, 256));
                    g.DrawImage(m_sprite, dstRect2, srcRect2, GraphicsUnit.Pixel);

                    g.DrawLine(m_penMouse, new Point(m_mouseX, 0), new Point(m_mouseX, 256));
                    g.DrawLine(m_penMouse, new Point(0, m_mouseY), new Point(256, m_mouseY));

                    if (FrameMouseDown == true)
                    {
                        g.DrawRectangle(m_penSelection, new Rectangle(
                            Math.Min(m_pSelection1.X, m_pSelection2.X), Math.Min(m_pSelection1.Y, m_pSelection2.Y),
                            Math.Max(m_pSelection1.X, m_pSelection2.X) - Math.Min(m_pSelection1.X, m_pSelection2.X),
                            Math.Max(m_pSelection1.Y, m_pSelection2.Y) - Math.Min(m_pSelection1.Y, m_pSelection2.Y)));
                    }

                    int quadrant = 3;
                    
                    if (m_mouseX >= 128)
                        quadrant -= 1;
                    if (m_mouseY >= 128)
                        quadrant -= 2;

                    string strMouseCoordinates = m_mouseX.ToString("D3") + ", " + m_mouseY.ToString("D3");
                    RectangleF rectf = new RectangleF(0.0f, 0.0f, Font.SizeInPoints * 8, Font.Height);
                    if ((quadrant & 1) != 0)
                    {
                        rectf.X = 256.0f - rectf.Width;
                    }
                    if ((quadrant & 2) != 0)
                    {
                        rectf.Y = 256.0f - rectf.Height;
                    }
                    g.FillRectangle(new SolidBrush(Color.FromArgb(0xE0, Color.Yellow)), rectf);
                    g.DrawString(strMouseCoordinates, this.Font, new SolidBrush(ForeColor), rectf);
                }
                else
                {
                    g.Clear(Color.Aqua);
                    g.DrawLine(m_penCenter, 0, 128, 256, 128);
                    g.DrawLine(m_penCenter, 128, 0, 128, 256);

                    Rectangle dstRect2 = new Rectangle(m_buffer.Width / 2 - Frame.Center.X, m_buffer.Height / 2 - Frame.Center.Y, Frame.Size.Width, Frame.Size.Height);
                    Rectangle srcRect2 = new Rectangle(Frame.Position, Frame.Size);
                    g.DrawRectangle(new Pen(new SolidBrush(Color.FromArgb(0x40, Color.Black))),
                        new Rectangle(dstRect2.X - 1, dstRect2.Y - 1, dstRect2.Width + 1, dstRect2.Height + 1));
                    g.DrawImage(m_sprite, dstRect2, srcRect2, GraphicsUnit.Pixel);
                    if (ShowHitbox == true)
                    {
                        g.FillRectangle(new SolidBrush(Color.FromArgb(0x80, Color.Aquamarine)),
                            new Rectangle(m_buffer.Width / 2 - m_hitbox.X1,
                                m_buffer.Height / 2 - m_hitbox.Y1,
                                m_hitbox.Width, m_hitbox.Height));
                    }
                }
            }
            Rectangle dstRect = new Rectangle(0, 0, m_buffer.Width, m_buffer.Height);
            Rectangle srcRect = new Rectangle(0, 0, m_buffer.Width, m_buffer.Height);
            if (m_zoom == true)
            {
                if (m_focus == true)
                {
                    e.Graphics.DrawImage(m_buffer, dstRect, srcRect, GraphicsUnit.Pixel);

                    const int zoomSize = 96;
                    dstRect = new Rectangle(m_mouseX - zoomSize, m_mouseY - zoomSize, zoomSize * 2, zoomSize * 2);
                    srcRect = new Rectangle(m_mouseX - zoomSize / 2, m_mouseY - zoomSize / 2, zoomSize, zoomSize);

                    e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(0x80, Color.Black)), new Rectangle(0, 0, m_buffer.Width, m_buffer.Height));
                }
                else
                {
                    g.DrawRectangle(new Pen(new SolidBrush(Color.FromArgb(0x80, Color.Black))),
                        new Rectangle(0, 0, 256, 256));
                    dstRect = new Rectangle(0, 0, 256, 256);
                    srcRect = new Rectangle(64, 64, 128, 128);
                }
            }
            e.Graphics.DrawImage(m_buffer, dstRect, srcRect, GraphicsUnit.Pixel);
        }

        private void FrameBox_MouseWheel(object sender, MouseEventArgs e)
        {
            if (m_sprite == null)
            {
                return;
            }
            int ChangedValue = (e.Delta / SystemInformation.MouseWheelScrollDelta);
            m_viewY -= (ChangedValue * 256);
            if (m_viewY >= m_sprite.Height)
            {
                m_viewY -= 256;
            }
            if (m_viewY < 0)
            {
                m_viewY = 0;
            }
            Invalidate();
        }
        private void FrameBox_MouseLeave(object sender, EventArgs e)
        {
            SetFocus(false);
        }
        private void FrameBox_MouseEnter(object sender, EventArgs e)
        {
            SetFocus(true);
        }
        private void FrameBox_MouseDown(object sender, MouseEventArgs e)
        {
            FrameMouseDown = true;
            m_pSelection1.X = e.X;
            m_pSelection1.Y = e.Y;
            m_pSelection2.X = e.X;
            m_pSelection2.Y = e.Y;
            EditAndFire();
        }
        private void FrameBox_MouseUp(object sender, MouseEventArgs e)
        {
            Point p = new Point(e.X, e.Y);
            if (p.X < 0) p.X = 0;
            if (p.X > 256) p.X = 256;
            if (p.Y < 0) p.Y = 0;
            if (p.Y > 256) p.Y = 256;

            m_pSelection2.X = e.X;
            m_pSelection2.Y = e.Y;
            FrameMouseDown = false;
        }
        private void FrameBox_MouseMove(object sender, MouseEventArgs e)
        {
            Point p = new Point(e.X, e.Y);
            if (p.X < 0) p.X = 0;
            if (p.X > 256) p.X = 256;
            if (p.Y < 0) p.Y = 0;
            if (p.Y > 256) p.Y = 256;

            m_mouseX = p.X;
            m_mouseY = p.Y;
            if (FrameMouseDown == true)
            {
                m_pSelection2.X = e.X;
                m_pSelection2.Y = e.Y;
                EditFrame(m_frame, m_pSelection1, m_pSelection2, m_viewY);
                if (this.OnFrameboxChanged != null)
                {
                    OnFrameboxChanging(this, m_frame);
                }
            }
            Invalidate();
        }

        public delegate void delegate_OnFrameboxChanging(object sender, AnimationFrame e);
        [Category("Action")]
        [Description("Fires during a frame selection")]
        public event delegate_OnFrameboxChanging OnFrameboxChanging;
        public delegate void delegate_OnFrameboxChanged(object sender, AnimationFrame e);
        [Category("Action")]
        [Description("Fires when the frame selection is finished")]
        public event delegate_OnFrameboxChanged OnFrameboxChanged;
    }
}
