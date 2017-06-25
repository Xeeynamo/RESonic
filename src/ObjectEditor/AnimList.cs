using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Windows.Forms;

namespace ObjectEditor
{
    public partial class AnimList : UserControl
    {
        static XmlTextReader xmlTextReader;
        static List<string> listCat = new List<string>();
        static List<List<string>> listAnim = new List<List<string>>();
        static List<List<string>> listDesc = new List<List<string>>();
        static List<List<List<string>>> listSubAnim = new List<List<List<string>>>();

        static List<string> listObjectAnim = new List<string>();
        static List<string> listObjectDesc = new List<string>();
        static List<List<string>> listObjectSubAnim = new List<List<string>>();

        string objectName;
        int curCat;
        int curAnm;
        int curSub;

        public AnimList()
        {
            InitializeComponent();
            objectName = "";
            curCat = -1;
            curAnm = -1;
            curSub = -1;
        }
        public string AnimationList
        {
            set
            {
                curCat = -1;
                curAnm = -1;
                curSub = -1;
                LoadXML(value);
                listCategories.Items.Clear();
                for (int i = 0; i < listCat.Count; i++)
                {
                    listCategories.Items.Add(listCat[i]);
                }
                for (int i = listCat.Count; i < 0xF; i++)
                {
                    listCategories.Items.Add("No category here");
                }
                listCategories.Items.Add("Object");
            }
        }
        public int SelectedCategory
        {
            get
            {
                return curCat;
            }
            set
            {
                if (value == -1) return;
                if (curCat == value) return;
                listAnimations.Items.Clear();
                if (value >= listCat.Count && value != 0xF) return;
                curCat = value;
                curAnm = -1;
                if (curCat != 0xF)
                {
                    for (int i = 0; i < listAnim[curCat].Count; i++)
                    {
                        listAnimations.Items.Add(listAnim[curCat][i]);
                    }
                }
                else
                {
                    for (int i = 0; i < listObjectAnim.Count; i++)
                    {
                        listAnimations.Items.Add(listObjectAnim[i]);
                    }
                }
            }
        }
        public int SelectedAnimation
        {
            get
            {
                return curAnm;
            }
            set
            {
                if (value == -1) return;
                if (curCat == -1) return;
                if (curAnm == value) return;
                if (curCat != 0xF)
                {
                    if (curCat >= listAnim.Count) return;
                    if (value >= listAnim[curCat].Count) return;
                    curAnm = value;
                    labelDescription.Text = listDesc[curCat][curAnm];
                    comboSubanim.Items.Clear();
                    for (int i = 0; i < 0x10; i++)
                    {
                        if (i >= listSubAnim[curCat][curAnm].Count)
                        {
                            if (i != 0) comboSubanim.Items.Add("Unused");
                            else comboSubanim.Items.Add("Default");
                        }
                        else
                        {
                            comboSubanim.Items.Add(listSubAnim[curCat][curAnm][i]);
                        }
                    }
                }
                else
                {
                    curAnm = value;
                    labelDescription.Text = listObjectDesc[curAnm];
                    comboSubanim.Items.Clear();
                    for (int i = 0; i < 0x10; i++)
                    {
                        if (i >= listObjectSubAnim[curAnm].Count)
                        {
                            if (i != 0) comboSubanim.Items.Add("Unused");
                            else comboSubanim.Items.Add("Default");
                        }
                        else
                        {
                            comboSubanim.Items.Add(listObjectSubAnim[curAnm][i]);
                        }
                    }
                }
                comboSubanim.SelectedIndex = 0;
            }
        }
        public ushort AnimationIndex
        {
            get
            {
                if (curCat == -1) return 0xFFFF;
                if (curAnm == -1) return 0xFFFF;
                if (curSub == -1) return 0xFFFF;
                return (ushort)(((curCat & 0xF) << 12) | ((curSub & 0xF) << 8) | (curAnm & 0xFF));
            }
        }
        public string ObjectName
        {
            get
            {
                return objectName;
            }
            set
            {
                if (value == null || value == "") return;
                objectName = value;
                LoadObjectXML(value + ".xml");
            }
        }
        void LoadObjectXML(string filename)
        {
            listObjectAnim.Clear();
            listObjectDesc.Clear();
            try
            {
                xmlTextReader = new XmlTextReader(filename);
                xmlTextReader.Read();
                while (xmlTextReader.Read())
                {
                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                    if (xmlTextReader.Name == "animlist" && xmlTextReader.NodeType == XmlNodeType.Element)
                    {
                        while (xmlTextReader.Read())
                        {
                            if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                            if (xmlTextReader.Name == "animlist" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                            {
                                break;
                            }
                            if (xmlTextReader.Name == "category" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1 && xmlTextReader.GetAttribute(0) == "Object")
                            {
                                while (xmlTextReader.Read())
                                {
                                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                    if (xmlTextReader.Name == "category" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                    {
                                        break;
                                    }
                                    if (xmlTextReader.Name == "entry" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1)
                                    {
                                        bool descriptionFound = false;
                                        int animListIndex = listCat.Count;
                                        listObjectSubAnim.Add(new List<string>());
                                        listObjectAnim.Add(xmlTextReader.GetAttribute(0));
                                        while (xmlTextReader.Read())
                                        {
                                            if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                            if (xmlTextReader.Name == "entry" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                            {
                                                if (descriptionFound == false)
                                                {
                                                    listObjectDesc.Add("NO DESCRIPTION");
                                                }
                                                break;
                                            }
                                            // Add description
                                            if (xmlTextReader.Name == "description" && xmlTextReader.NodeType == XmlNodeType.Element)
                                            {
                                                while (xmlTextReader.Read())
                                                {
                                                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                                    if (xmlTextReader.Name == "description" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                                    {
                                                        break;
                                                    }
                                                    if (xmlTextReader.NodeType == XmlNodeType.Text)
                                                    {
                                                        listObjectDesc.Add(xmlTextReader.Value.ToString());
                                                        descriptionFound = true;
                                                    }
                                                }
                                            }
                                            // Add sub animation
                                            if (xmlTextReader.Name == "subanim" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1)
                                            {
                                                listObjectSubAnim[listObjectAnim.Count - 1].Add(xmlTextReader.GetAttribute(0));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (System.Exception)
            {
                return;
            }
        }
        void LoadXML(string filename)
        {
            for (int i = 0; i < listAnim.Count; i++)
            {
                listAnim[i].Clear();
            }
            for (int i = 0; i < listSubAnim.Count; i++)
            {
                for (int j = 0; j < listSubAnim[i].Count; j++)
                {
                    listSubAnim[i][j].Clear();
                }
                listSubAnim[i].Clear();
            }
            listCat.Clear();
            try
            {
                xmlTextReader = new XmlTextReader(filename);
                xmlTextReader.Read();
                while (xmlTextReader.Read())
                {
                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                    if (xmlTextReader.Name == "animlist" && xmlTextReader.NodeType == XmlNodeType.Element)
                    {
                        while (xmlTextReader.Read())
                        {
                            if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                            if (xmlTextReader.Name == "animlist" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                            {
                                break;
                            }
                            if (xmlTextReader.Name == "category" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1)
                            {
                                int animListIndex = listCat.Count;
                                listAnim.Add(new List<string>());
                                listDesc.Add(new List<string>());
                                listSubAnim.Add(new List<List<string>>());
                                listCat.Add(xmlTextReader.GetAttribute(0));
                                while (xmlTextReader.Read())
                                {
                                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                    if (xmlTextReader.Name == "category" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                    {
                                        break;
                                    }
                                    if (xmlTextReader.Name == "entry" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1)
                                    {
                                        bool descriptionFound = false;
                                        listAnim[animListIndex].Add(xmlTextReader.GetAttribute(0));
                                        listSubAnim[animListIndex].Add(new List<string>());
                                        while (xmlTextReader.Read())
                                        {
                                            if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                            if (xmlTextReader.Name == "entry" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                            {
                                                if (descriptionFound == false)
                                                {
                                                    listDesc[animListIndex].Add("NO DESCRIPTION");
                                                }
                                                break;
                                            }
                                            // Add description
                                            if (xmlTextReader.Name == "description" && xmlTextReader.NodeType == XmlNodeType.Element)
                                            {
                                                while (xmlTextReader.Read())
                                                {
                                                    if (xmlTextReader.NodeType == XmlNodeType.Whitespace) continue;
                                                    if (xmlTextReader.Name == "description" && xmlTextReader.NodeType == XmlNodeType.EndElement)
                                                    {
                                                        break;
                                                    }
                                                    if (xmlTextReader.NodeType == XmlNodeType.Text)
                                                    {
                                                        listDesc[animListIndex].Add(xmlTextReader.Value.ToString());
                                                        descriptionFound = true;
                                                    }
                                                }
                                            }
                                            // Add sub animation
                                            if (xmlTextReader.Name == "subanim" && xmlTextReader.NodeType == XmlNodeType.Element && xmlTextReader.AttributeCount == 1)
                                            {
                                                listSubAnim[animListIndex][listAnim[animListIndex].Count - 1].Add(xmlTextReader.GetAttribute(0));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Impossibile aprire il file " + filename + ".\n" + ex.Message,
                    "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
        }

        private void listCategories_SelectedIndexChanged(object sender, EventArgs e)
        {
            SelectedCategory = listCategories.SelectedIndex;
            textAnimID.Text = AnimationIndex.ToString("X04");
        }
        private void listAnimations_SelectedIndexChanged(object sender, EventArgs e)
        {
            SelectedAnimation = listAnimations.SelectedIndex;
            textAnimID.Text = AnimationIndex.ToString("X04");
            if (OnSelectedAnimation != null)
            {
                OnSelectedAnimation(AnimationIndex);
            }
        }
        private void comboSubanim_SelectedIndexChanged(object sender, EventArgs e)
        {
            curSub = comboSubanim.SelectedIndex;
            textAnimID.Text = AnimationIndex.ToString("X04");
            if (OnSelectedAnimation != null)
            {
                OnSelectedAnimation(AnimationIndex);
            }
        }
        private void AnimList_Resize(object sender, EventArgs e)
        {
            labelAnimations.Size = new Size(listAnimations.Size.Width, 13);
        }

        // Eventi
        public delegate void OnSelectedAnimationDelegate(ushort index);
        [Category("AnimList")]
        [Description("Return the current animation index")]
        public event OnSelectedAnimationDelegate OnSelectedAnimation;
    }
}
