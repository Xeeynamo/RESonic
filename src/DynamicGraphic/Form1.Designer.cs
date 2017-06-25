namespace DynamicGraphic
{
    partial class Form1
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Liberare le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gFXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importAGFXForThisAnimationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportTheCurrentPictureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.importLUTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.animationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addAnimationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeCurrentAnimationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.nPaletteIndex = new System.Windows.Forms.NumericUpDown();
            this.nDstTexture = new System.Windows.Forms.NumericUpDown();
            this.cbPattern = new System.Windows.Forms.CheckBox();
            this.tbPattern = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.nSpeed = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.nDstIndex = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.nFrameCount = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.nTilesPerLine = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.bLoadImage = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.panel1 = new DynamicGraphic.Dynamic();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nPaletteIndex)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDstTexture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nSpeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDstIndex)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nTilesPerLine)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.gFXToolStripMenuItem,
            this.animationsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(623, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.openToolStripMenuItem.Text = "Open";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(100, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // gFXToolStripMenuItem
            // 
            this.gFXToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.importAGFXForThisAnimationToolStripMenuItem,
            this.exportTheCurrentPictureToolStripMenuItem,
            this.toolStripSeparator3,
            this.importLUTToolStripMenuItem});
            this.gFXToolStripMenuItem.Name = "gFXToolStripMenuItem";
            this.gFXToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.gFXToolStripMenuItem.Text = "GFX";
            // 
            // importAGFXForThisAnimationToolStripMenuItem
            // 
            this.importAGFXForThisAnimationToolStripMenuItem.Name = "importAGFXForThisAnimationToolStripMenuItem";
            this.importAGFXForThisAnimationToolStripMenuItem.Size = new System.Drawing.Size(240, 22);
            this.importAGFXForThisAnimationToolStripMenuItem.Text = "Import a GFX for this animation";
            // 
            // exportTheCurrentPictureToolStripMenuItem
            // 
            this.exportTheCurrentPictureToolStripMenuItem.Name = "exportTheCurrentPictureToolStripMenuItem";
            this.exportTheCurrentPictureToolStripMenuItem.Size = new System.Drawing.Size(240, 22);
            this.exportTheCurrentPictureToolStripMenuItem.Text = "Export the current picture";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(237, 6);
            // 
            // importLUTToolStripMenuItem
            // 
            this.importLUTToolStripMenuItem.Name = "importLUTToolStripMenuItem";
            this.importLUTToolStripMenuItem.Size = new System.Drawing.Size(240, 22);
            this.importLUTToolStripMenuItem.Text = "Import LUT";
            this.importLUTToolStripMenuItem.Click += new System.EventHandler(this.importLUTToolStripMenuItem_Click);
            // 
            // animationsToolStripMenuItem
            // 
            this.animationsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addAnimationToolStripMenuItem,
            this.removeCurrentAnimationToolStripMenuItem});
            this.animationsToolStripMenuItem.Name = "animationsToolStripMenuItem";
            this.animationsToolStripMenuItem.Size = new System.Drawing.Size(80, 20);
            this.animationsToolStripMenuItem.Text = "Animations";
            // 
            // addAnimationToolStripMenuItem
            // 
            this.addAnimationToolStripMenuItem.Name = "addAnimationToolStripMenuItem";
            this.addAnimationToolStripMenuItem.Size = new System.Drawing.Size(215, 22);
            this.addAnimationToolStripMenuItem.Text = "Add animation";
            // 
            // removeCurrentAnimationToolStripMenuItem
            // 
            this.removeCurrentAnimationToolStripMenuItem.Name = "removeCurrentAnimationToolStripMenuItem";
            this.removeCurrentAnimationToolStripMenuItem.Size = new System.Drawing.Size(215, 22);
            this.removeCurrentAnimationToolStripMenuItem.Text = "Remove current animation";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.nPaletteIndex);
            this.groupBox1.Controls.Add(this.nDstTexture);
            this.groupBox1.Controls.Add(this.cbPattern);
            this.groupBox1.Controls.Add(this.tbPattern);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.nSpeed);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.nDstIndex);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.nFrameCount);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.nTilesPerLine);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.bLoadImage);
            this.groupBox1.Location = new System.Drawing.Point(95, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(260, 128);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Animation";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(121, 76);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(68, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Palette index";
            // 
            // nPaletteIndex
            // 
            this.nPaletteIndex.Enabled = false;
            this.nPaletteIndex.Location = new System.Drawing.Point(194, 74);
            this.nPaletteIndex.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nPaletteIndex.Name = "nPaletteIndex";
            this.nPaletteIndex.Size = new System.Drawing.Size(60, 20);
            this.nPaletteIndex.TabIndex = 13;
            this.nPaletteIndex.ValueChanged += new System.EventHandler(this.nPaletteIndex_ValueChanged);
            // 
            // nDstTexture
            // 
            this.nDstTexture.Hexadecimal = true;
            this.nDstTexture.Location = new System.Drawing.Point(182, 22);
            this.nDstTexture.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nDstTexture.Name = "nDstTexture";
            this.nDstTexture.Size = new System.Drawing.Size(37, 20);
            this.nDstTexture.TabIndex = 12;
            this.nDstTexture.ValueChanged += new System.EventHandler(this.nDstTexture_ValueChanged);
            // 
            // cbPattern
            // 
            this.cbPattern.AutoSize = true;
            this.cbPattern.Location = new System.Drawing.Point(200, 49);
            this.cbPattern.Name = "cbPattern";
            this.cbPattern.Size = new System.Drawing.Size(60, 17);
            this.cbPattern.TabIndex = 11;
            this.cbPattern.Text = "Pattern";
            this.cbPattern.UseVisualStyleBackColor = true;
            this.cbPattern.CheckedChanged += new System.EventHandler(this.cbPattern_CheckedChanged);
            // 
            // tbPattern
            // 
            this.tbPattern.Location = new System.Drawing.Point(6, 102);
            this.tbPattern.Name = "tbPattern";
            this.tbPattern.Size = new System.Drawing.Size(248, 20);
            this.tbPattern.TabIndex = 10;
            this.tbPattern.WordWrap = false;
            this.tbPattern.TextChanged += new System.EventHandler(this.tbPattern_TextChanged);
            this.tbPattern.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbPattern_KeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(121, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Speed";
            // 
            // nSpeed
            // 
            this.nSpeed.Location = new System.Drawing.Point(160, 48);
            this.nSpeed.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nSpeed.Name = "nSpeed";
            this.nSpeed.Size = new System.Drawing.Size(37, 20);
            this.nSpeed.TabIndex = 8;
            this.nSpeed.ValueChanged += new System.EventHandler(this.nSpeed_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(121, 24);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(60, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "Destination";
            // 
            // nDstIndex
            // 
            this.nDstIndex.Hexadecimal = true;
            this.nDstIndex.Location = new System.Drawing.Point(223, 22);
            this.nDstIndex.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nDstIndex.Name = "nDstIndex";
            this.nDstIndex.Size = new System.Drawing.Size(37, 20);
            this.nDstIndex.TabIndex = 6;
            this.nDstIndex.ValueChanged += new System.EventHandler(this.nDstIndex_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Frames count";
            // 
            // nFrameCount
            // 
            this.nFrameCount.Enabled = false;
            this.nFrameCount.Location = new System.Drawing.Point(78, 74);
            this.nFrameCount.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nFrameCount.Name = "nFrameCount";
            this.nFrameCount.Size = new System.Drawing.Size(37, 20);
            this.nFrameCount.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Tiles per line";
            // 
            // nTilesPerLine
            // 
            this.nTilesPerLine.Enabled = false;
            this.nTilesPerLine.Location = new System.Drawing.Point(78, 48);
            this.nTilesPerLine.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nTilesPerLine.Name = "nTilesPerLine";
            this.nTilesPerLine.Size = new System.Drawing.Size(37, 20);
            this.nTilesPerLine.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Tileset";
            // 
            // bLoadImage
            // 
            this.bLoadImage.Location = new System.Drawing.Point(78, 19);
            this.bLoadImage.Name = "bLoadImage";
            this.bLoadImage.Size = new System.Drawing.Size(37, 23);
            this.bLoadImage.TabIndex = 0;
            this.bLoadImage.Text = "..";
            this.bLoadImage.UseVisualStyleBackColor = true;
            this.bLoadImage.Click += new System.EventHandler(this.bLoadImage_Click);
            // 
            // listBox1
            // 
            this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(5, 34);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(84, 121);
            this.listBox1.TabIndex = 3;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.panel1.AnimationRunning = true;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(361, 34);
            this.panel1.Name = "panel1";
            this.panel1.SelectedAnimation = 0;
            this.panel1.Size = new System.Drawing.Size(256, 122);
            this.panel1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 160);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Dynamic graphic";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nPaletteIndex)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDstTexture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nSpeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDstIndex)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nTilesPerLine)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DynamicGraphic.Dynamic panel1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ToolStripMenuItem animationsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addAnimationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeCurrentAnimationToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button bLoadImage;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown nTilesPerLine;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown nFrameCount;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown nSpeed;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown nDstIndex;
        private System.Windows.Forms.CheckBox cbPattern;
        private System.Windows.Forms.TextBox tbPattern;
        private System.Windows.Forms.ToolStripMenuItem gFXToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importAGFXForThisAnimationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportTheCurrentPictureToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem importLUTToolStripMenuItem;
        private System.Windows.Forms.NumericUpDown nDstTexture;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown nPaletteIndex;
    }
}

