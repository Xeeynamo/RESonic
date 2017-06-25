using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace GameList
{
    public partial class Form1 : Form
    {
        FileStream f;
        public class XeList 
        {
            public ushort id;
            public string name;
        }
        List<XeList> list;

        public Form1()
        {
            InitializeComponent();
            list = new List<XeList>();
        }

        private void bFileSelect_Click(object sender, EventArgs e)
        {
            OpenFileDialog openfiledialog = new OpenFileDialog();
            openfiledialog.Filter = "XeEngine list|*.bin";
            openfiledialog.CheckFileExists = false;
            if (openfiledialog.ShowDialog() == DialogResult.OK)
            {
                f = new FileStream(openfiledialog.FileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                LoadList();
                RefreshList();
            }
        }

        void LoadList()
        {
            list.RemoveRange(0, list.Count);
            if (f.Length == 0) return;
            ushort count;
            count = (ushort)(f.ReadByte() + (f.ReadByte() << 8));

            while (count-- > 0)
            {
                XeList l = new XeList();
                byte[] name = new byte[0xE];
                l.id = (ushort)(f.ReadByte() + (f.ReadByte() << 8));
                f.Read(name, 0, name.Length);
                l.name = ByteToString(name);
                list.Add(l);
            }
        }
        void SaveList()
        {
            ushort count = (ushort)list.Count;
            f.Position = 0;
            f.WriteByte((byte)(count & 0xFF));
            f.WriteByte((byte)(count >> 8));

            for (int i = 0; i < count; i++)
            {
                f.WriteByte((byte)(list[i].id & 0xFF));
                f.WriteByte((byte)(list[i].id >> 8));
                
                byte[] bout = StringToByte(list[i].name);
                byte[] b = new byte[0x0E];
                for (int j = 0; j < Math.Min(bout.Length, b.Length); j++)
                {
                    b[j] = bout[j];
                }
                f.Write(b, 0, b.Length);
            }
        }

        void RefreshList()
        {
            listBox.Items.Clear();
            for (int i = 0; i < list.Count; i++)
            {
                listBox.Items.Add(list[i].id.ToString("X04") + " - " + list[i].name);
            }
        }
        void SortList()
        {
            list.Sort(
                delegate(XeList p1, XeList p2)
                {
                    return p1.id.CompareTo(p2.id);
                });
        }
        byte[] StringToByte(string str)
        {
            char[] strchar = str.ToCharArray();
            byte[] strbyte = new byte[strchar.Length + 1];
            for (int i = strchar.Length - 1; i >= 0; i--)
            {
                strbyte[i] = (byte)strchar[i];
            }
            strbyte[strchar.Length] = 0;
            return strbyte;
        }
        string ByteToString(byte[] strbyte)
        {
            char[] strchar = new char[strbyte.Length];
            for (int i = 0; i < strbyte.Length; i++)
            {
                strchar[i] = (char)strbyte[i];
            }
            return new String(strchar);
        }
        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            nID.Value = list[listBox.SelectedIndex].id;
            tbName.Text = list[listBox.SelectedIndex].name;
        }
        private void bAdd_Click(object sender, EventArgs e)
        {
            XeList l = new XeList();
            l.id = 0;
            l.name = "";
            for (int i = 0; i < list.Count; i++)
            {
                if (list[i].id == 0)
                    return;
            }
            list.Add(l);
            SortList();
            RefreshList();
            listBox.SelectedIndex = 0;
        }
        private void bSave_Click(object sender, EventArgs e)
        {
            SaveList();
        }

        private void tbName_TextChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedIndex < 0) return;
            list[listBox.SelectedIndex].name = tbName.Text;
        }
        private void nID_ValueChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedIndex < 0) return;
            int i = listBox.SelectedIndex;
            list[i].id = (ushort)nID.Value;
            XeList l = list[i];
            SortList();
            RefreshList();
            listBox.SelectedIndex = list.IndexOf(l);
        }
    }
}
