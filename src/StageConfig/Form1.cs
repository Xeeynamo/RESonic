using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace StageConfig
{
    public partial class FormStageConfig : Form
    {
        Stage stage;
        string prevfile;

        public FormStageConfig()
        {
            InitializeComponent();
            stage = new Stage();
            prevfile = null;

            nActSelected.Value = 1;
            nActCount.Value = 1;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.AddExtension = true;
            openFileDialog.DefaultExt = "stg";
            openFileDialog.Filter = "Stage files|*.stg";
            openFileDialog.FileName = prevfile == null ? stage.StageName : prevfile;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string err = stage.Load(openFileDialog.FileName);
                if (err != null)
                {
                    MessageBox.Show(err, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                SelectedAct = 0;
                textStageName.Text = stage.StageName;
                prevfile = openFileDialog.FileName;
            }
        }
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.AddExtension = true;
            saveFileDialog.DefaultExt = "STG";
            saveFileDialog.Filter = "Stage files|*.STG";
            saveFileDialog.FileName = prevfile == null ? stage.StageName : prevfile;
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string err = stage.Save(saveFileDialog.FileName);
                if (err != null)
                {
                    MessageBox.Show(err, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
        }
        int SelectedAct
        {
            get
            {
                return (int)nActSelected.Value - 1;
            }
            set
            {
                AssignStrigns(value);
            }
        }

        void AssignStrigns(int actIndex)
        {
            Stage.Act act = stage.SelectAct(actIndex);
            nActCount.Value = stage.ActCount;
            nActSelected.Maximum = stage.ActCount;
            nActSelected.Value = actIndex+1;

            textGfx.Text = act.gfx;
            textClut.Text = act.clut;
            textCli.Text = act.cli;
            textHbx.Text = act.hbx;
            textMap.Text = act.map;
            textBlk.Text = act.blk;
            textRng.Text = act.rng;
            textObp.Text = act.obp;
            textDef.Text = act.def;
            textDtl.Text = act.dtl;
            textTpl.Text = act.tpl;
            textCrd.Text = act.crd;
            textBgm.Text = act.bgm;

            cbRes1.Checked = stage.Resolution(0);
            cbRes2.Checked = stage.Resolution(1);
            cbRes3.Checked = stage.Resolution(2);
            cbRes4.Checked = stage.Resolution(3);
            cbRes5.Checked = stage.Resolution(4);
            cbRes6.Checked = stage.Resolution(5);
            cbRes7.Checked = stage.Resolution(6);
            cbRes8.Checked = stage.Resolution(7);
        }

        private void nActSelected_ValueChanged(object sender, EventArgs e)
        {
            SelectedAct = (int)(nActSelected.Value - 1);
        }
        private void nActCount_ValueChanged(object sender, EventArgs e)
        {
            nActSelected.Maximum = nActCount.Value;
        }
        private void textStageName_TextChanged(object sender, EventArgs e)
        {
            stage.StageName = textStageName.Text;
        }
        private void textOfAct_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            int tag = Convert.ToInt32(tb.Tag);
            stage.SelectAct(SelectedAct).SetString(tag, tb.Text);

            if (tag == 0)
            {
                labelGFXExample.Text = tb.Text + "@2.GFX";
            }
        }
        private void cbRes_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            stage.Resolution(Convert.ToInt32(cb.Tag)-1, cb.Checked);
        }

        private void addActToolStripMenuItem_Click(object sender, EventArgs e)
        {
            stage.AddAct();
            SelectedAct = stage.ActCount - 1;
        }
        private void removeActToolStripMenuItem_Click(object sender, EventArgs e)
        {
            stage.RemoveAct(SelectedAct);
            if (SelectedAct >= stage.ActCount)
                SelectedAct = stage.ActCount - 1;
            else SelectedAct = SelectedAct;
        }
    }
}
