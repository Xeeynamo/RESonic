namespace GFXTool
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importPNGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importGFXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importFromRaw4bppGenesisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.importPaletteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importSonic16x16ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportPNGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportGFXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exportPaletteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileToolToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadMappingMDONLYToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panelControl = new System.Windows.Forms.Panel();
            this.label8 = new System.Windows.Forms.Label();
            this.cbColorMode = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.cbGfxType = new System.Windows.Forms.ComboBox();
            this.cbInternalPalette = new System.Windows.Forms.CheckBox();
            this.cbCompressed = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comboMode = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.nTextureCount = new System.Windows.Forms.NumericUpDown();
            this.nResolution = new System.Windows.Forms.NumericUpDown();
            this.nDestination = new System.Windows.Forms.NumericUpDown();
            this.nHeight = new System.Windows.Forms.NumericUpDown();
            this.nWidth = new System.Windows.Forms.NumericUpDown();
            this.panelPicture = new System.Windows.Forms.Panel();
            this.scrollTexture = new System.Windows.Forms.VScrollBar();
            this.groupPalette = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.nColorsCount = new System.Windows.Forms.NumericUpDown();
            this.bExportPalette = new System.Windows.Forms.Button();
            this.bImportPalette = new System.Windows.Forms.Button();
            this.panelPalette = new System.Windows.Forms.Panel();
            this.panelMoveColor = new System.Windows.Forms.Panel();
            this.importRSDKGIFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.panelControl.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nTextureCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nResolution)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDestination)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nWidth)).BeginInit();
            this.groupPalette.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nColorsCount)).BeginInit();
            this.panelPalette.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.importToolStripMenuItem,
            this.exportToolStripMenuItem,
            this.tileToolToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(642, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.importPNGToolStripMenuItem,
            this.importGFXToolStripMenuItem,
            this.importFromRaw4bppGenesisToolStripMenuItem,
            this.importRSDKGIFToolStripMenuItem,
            this.toolStripSeparator1,
            this.importPaletteToolStripMenuItem,
            this.importSonic16x16ToolStripMenuItem});
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.importToolStripMenuItem.Text = "Import";
            // 
            // importPNGToolStripMenuItem
            // 
            this.importPNGToolStripMenuItem.Name = "importPNGToolStripMenuItem";
            this.importPNGToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importPNGToolStripMenuItem.Text = "Import Image";
            this.importPNGToolStripMenuItem.Click += new System.EventHandler(this.importImageToolStripMenuItem_Click);
            // 
            // importGFXToolStripMenuItem
            // 
            this.importGFXToolStripMenuItem.Name = "importGFXToolStripMenuItem";
            this.importGFXToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importGFXToolStripMenuItem.Text = "Import GFX";
            this.importGFXToolStripMenuItem.Click += new System.EventHandler(this.importGFXToolStripMenuItem_Click);
            // 
            // importFromRaw4bppGenesisToolStripMenuItem
            // 
            this.importFromRaw4bppGenesisToolStripMenuItem.Name = "importFromRaw4bppGenesisToolStripMenuItem";
            this.importFromRaw4bppGenesisToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importFromRaw4bppGenesisToolStripMenuItem.Text = "Import RAW 4BPP Genesis";
            this.importFromRaw4bppGenesisToolStripMenuItem.Click += new System.EventHandler(this.importFromRaw4bppGenesisToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(209, 6);
            // 
            // importPaletteToolStripMenuItem
            // 
            this.importPaletteToolStripMenuItem.Name = "importPaletteToolStripMenuItem";
            this.importPaletteToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importPaletteToolStripMenuItem.Text = "Import Palette";
            this.importPaletteToolStripMenuItem.Click += new System.EventHandler(this.importPaletteToolStripMenuItem_Click);
            // 
            // importSonic16x16ToolStripMenuItem
            // 
            this.importSonic16x16ToolStripMenuItem.Name = "importSonic16x16ToolStripMenuItem";
            this.importSonic16x16ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importSonic16x16ToolStripMenuItem.Text = "Import Sonic 16x16 (PNG)";
            this.importSonic16x16ToolStripMenuItem.Visible = false;
            this.importSonic16x16ToolStripMenuItem.Click += new System.EventHandler(this.importSonic16x16ToolStripMenuItem_Click);
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exportPNGToolStripMenuItem,
            this.exportGFXToolStripMenuItem,
            this.toolStripSeparator2,
            this.exportPaletteToolStripMenuItem});
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.exportToolStripMenuItem.Text = "Export";
            // 
            // exportPNGToolStripMenuItem
            // 
            this.exportPNGToolStripMenuItem.Name = "exportPNGToolStripMenuItem";
            this.exportPNGToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.exportPNGToolStripMenuItem.Text = "Export Image";
            this.exportPNGToolStripMenuItem.Click += new System.EventHandler(this.exportImageToolStripMenuItem_Click);
            // 
            // exportGFXToolStripMenuItem
            // 
            this.exportGFXToolStripMenuItem.Name = "exportGFXToolStripMenuItem";
            this.exportGFXToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.exportGFXToolStripMenuItem.Text = "Export GFX";
            this.exportGFXToolStripMenuItem.Click += new System.EventHandler(this.exportGFXToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(143, 6);
            // 
            // exportPaletteToolStripMenuItem
            // 
            this.exportPaletteToolStripMenuItem.Name = "exportPaletteToolStripMenuItem";
            this.exportPaletteToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.exportPaletteToolStripMenuItem.Text = "Export Palette";
            this.exportPaletteToolStripMenuItem.Click += new System.EventHandler(this.exportPaletteToolStripMenuItem_Click);
            // 
            // tileToolToolStripMenuItem
            // 
            this.tileToolToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cToolStripMenuItem,
            this.loadMappingMDONLYToolStripMenuItem});
            this.tileToolToolStripMenuItem.Name = "tileToolToolStripMenuItem";
            this.tileToolToolStripMenuItem.Size = new System.Drawing.Size(62, 20);
            this.tileToolToolStripMenuItem.Text = "Tile tool";
            // 
            // cToolStripMenuItem
            // 
            this.cToolStripMenuItem.Name = "cToolStripMenuItem";
            this.cToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.cToolStripMenuItem.Text = "Check duplicates";
            this.cToolStripMenuItem.Click += new System.EventHandler(this.cToolStripMenuItem_Click);
            // 
            // loadMappingMDONLYToolStripMenuItem
            // 
            this.loadMappingMDONLYToolStripMenuItem.Name = "loadMappingMDONLYToolStripMenuItem";
            this.loadMappingMDONLYToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.loadMappingMDONLYToolStripMenuItem.Text = "Load mapping";
            this.loadMappingMDONLYToolStripMenuItem.Click += new System.EventHandler(this.loadMappingToolStripMenuItem_Click);
            // 
            // panelControl
            // 
            this.panelControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.panelControl.Controls.Add(this.label8);
            this.panelControl.Controls.Add(this.cbColorMode);
            this.panelControl.Controls.Add(this.label7);
            this.panelControl.Controls.Add(this.cbGfxType);
            this.panelControl.Controls.Add(this.cbInternalPalette);
            this.panelControl.Controls.Add(this.cbCompressed);
            this.panelControl.Controls.Add(this.label6);
            this.panelControl.Controls.Add(this.comboMode);
            this.panelControl.Controls.Add(this.label5);
            this.panelControl.Controls.Add(this.label4);
            this.panelControl.Controls.Add(this.label3);
            this.panelControl.Controls.Add(this.label2);
            this.panelControl.Controls.Add(this.label1);
            this.panelControl.Controls.Add(this.nTextureCount);
            this.panelControl.Controls.Add(this.nResolution);
            this.panelControl.Controls.Add(this.nDestination);
            this.panelControl.Controls.Add(this.nHeight);
            this.panelControl.Controls.Add(this.nWidth);
            this.panelControl.Location = new System.Drawing.Point(0, 27);
            this.panelControl.Name = "panelControl";
            this.panelControl.Size = new System.Drawing.Size(139, 256);
            this.panelControl.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 217);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(85, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "Mode and depth";
            // 
            // cbColorMode
            // 
            this.cbColorMode.FormattingEnabled = true;
            this.cbColorMode.Items.AddRange(new object[] {
            "RGB565",
            "BGR565",
            "XRGB1555",
            "XBGR1555",
            "ARGB1555",
            "RGB888",
            "BGR888",
            "XRGB8888",
            "ARGB8888"});
            this.cbColorMode.Location = new System.Drawing.Point(14, 233);
            this.cbColorMode.Name = "cbColorMode";
            this.cbColorMode.Size = new System.Drawing.Size(121, 21);
            this.cbColorMode.TabIndex = 16;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 178);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(105, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "Type of GFX/Palette";
            // 
            // cbGfxType
            // 
            this.cbGfxType.FormattingEnabled = true;
            this.cbGfxType.Items.AddRange(new object[] {
            "Shared resource",
            "Level resource",
            "Object static",
            "Object dynamic"});
            this.cbGfxType.Location = new System.Drawing.Point(14, 194);
            this.cbGfxType.Name = "cbGfxType";
            this.cbGfxType.Size = new System.Drawing.Size(121, 21);
            this.cbGfxType.TabIndex = 14;
            // 
            // cbInternalPalette
            // 
            this.cbInternalPalette.AutoSize = true;
            this.cbInternalPalette.Location = new System.Drawing.Point(6, 159);
            this.cbInternalPalette.Name = "cbInternalPalette";
            this.cbInternalPalette.Size = new System.Drawing.Size(96, 17);
            this.cbInternalPalette.TabIndex = 13;
            this.cbInternalPalette.Text = "Internal palette";
            this.cbInternalPalette.UseVisualStyleBackColor = true;
            // 
            // cbCompressed
            // 
            this.cbCompressed.AutoSize = true;
            this.cbCompressed.Location = new System.Drawing.Point(6, 136);
            this.cbCompressed.Name = "cbCompressed";
            this.cbCompressed.Size = new System.Drawing.Size(84, 17);
            this.cbCompressed.TabIndex = 12;
            this.cbCompressed.Text = "Compressed";
            this.cbCompressed.TextAlign = System.Drawing.ContentAlignment.TopLeft;
            this.cbCompressed.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 112);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(34, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Mode";
            // 
            // comboMode
            // 
            this.comboMode.FormattingEnabled = true;
            this.comboMode.Items.AddRange(new object[] {
            "Undefined (reserved)",
            "1-bit (1 color)",
            "4-bit (16 colors)",
            "8-bit (256 colors)",
            "16-bit (R5G6B5)",
            "24-bit (RGB8)",
            "32-bit (ARGB8)"});
            this.comboMode.Location = new System.Drawing.Point(37, 109);
            this.comboMode.Name = "comboMode";
            this.comboMode.Size = new System.Drawing.Size(101, 21);
            this.comboMode.TabIndex = 10;
            this.comboMode.SelectedIndexChanged += new System.EventHandler(this.comboMode_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 89);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(73, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Texture count";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 68);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Resolution";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 47);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Destination";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Height";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Width";
            // 
            // nTextureCount
            // 
            this.nTextureCount.Location = new System.Drawing.Point(79, 87);
            this.nTextureCount.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.nTextureCount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nTextureCount.Name = "nTextureCount";
            this.nTextureCount.Size = new System.Drawing.Size(59, 20);
            this.nTextureCount.TabIndex = 4;
            this.nTextureCount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nTextureCount.ValueChanged += new System.EventHandler(this.nTextureCount_ValueChanged);
            // 
            // nResolution
            // 
            this.nResolution.Location = new System.Drawing.Point(79, 66);
            this.nResolution.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.nResolution.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nResolution.Name = "nResolution";
            this.nResolution.Size = new System.Drawing.Size(59, 20);
            this.nResolution.TabIndex = 3;
            this.nResolution.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nResolution.ValueChanged += new System.EventHandler(this.nResolution_ValueChanged);
            // 
            // nDestination
            // 
            this.nDestination.Location = new System.Drawing.Point(79, 45);
            this.nDestination.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.nDestination.Name = "nDestination";
            this.nDestination.Size = new System.Drawing.Size(59, 20);
            this.nDestination.TabIndex = 2;
            this.nDestination.ValueChanged += new System.EventHandler(this.nDestination_ValueChanged);
            // 
            // nHeight
            // 
            this.nHeight.Enabled = false;
            this.nHeight.Location = new System.Drawing.Point(79, 24);
            this.nHeight.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.nHeight.Name = "nHeight";
            this.nHeight.Size = new System.Drawing.Size(59, 20);
            this.nHeight.TabIndex = 1;
            // 
            // nWidth
            // 
            this.nWidth.Enabled = false;
            this.nWidth.Location = new System.Drawing.Point(79, 3);
            this.nWidth.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.nWidth.Name = "nWidth";
            this.nWidth.Size = new System.Drawing.Size(59, 20);
            this.nWidth.TabIndex = 0;
            // 
            // panelPicture
            // 
            this.panelPicture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelPicture.Location = new System.Drawing.Point(141, 27);
            this.panelPicture.Name = "panelPicture";
            this.panelPicture.Size = new System.Drawing.Size(256, 256);
            this.panelPicture.TabIndex = 2;
            this.panelPicture.Paint += new System.Windows.Forms.PaintEventHandler(this.panelPicture_Paint);
            // 
            // scrollTexture
            // 
            this.scrollTexture.LargeChange = 1;
            this.scrollTexture.Location = new System.Drawing.Point(400, 27);
            this.scrollTexture.Maximum = 1;
            this.scrollTexture.Minimum = 1;
            this.scrollTexture.Name = "scrollTexture";
            this.scrollTexture.Size = new System.Drawing.Size(17, 256);
            this.scrollTexture.TabIndex = 3;
            this.scrollTexture.Value = 1;
            this.scrollTexture.Scroll += new System.Windows.Forms.ScrollEventHandler(this.scrollTexture_Scroll);
            // 
            // groupPalette
            // 
            this.groupPalette.Controls.Add(this.label9);
            this.groupPalette.Controls.Add(this.nColorsCount);
            this.groupPalette.Controls.Add(this.bExportPalette);
            this.groupPalette.Controls.Add(this.bImportPalette);
            this.groupPalette.Controls.Add(this.panelPalette);
            this.groupPalette.Location = new System.Drawing.Point(420, 27);
            this.groupPalette.Name = "groupPalette";
            this.groupPalette.Size = new System.Drawing.Size(220, 256);
            this.groupPalette.TabIndex = 4;
            this.groupPalette.TabStop = false;
            this.groupPalette.Text = "Palette";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(126, 232);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(40, 13);
            this.label9.TabIndex = 4;
            this.label9.Text = "Palette";
            // 
            // nColorsCount
            // 
            this.nColorsCount.Location = new System.Drawing.Point(167, 230);
            this.nColorsCount.Maximum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.nColorsCount.Name = "nColorsCount";
            this.nColorsCount.Size = new System.Drawing.Size(47, 20);
            this.nColorsCount.TabIndex = 3;
            this.nColorsCount.ValueChanged += new System.EventHandler(this.nColorsCount_ValueChanged);
            // 
            // bExportPalette
            // 
            this.bExportPalette.Location = new System.Drawing.Point(62, 227);
            this.bExportPalette.Name = "bExportPalette";
            this.bExportPalette.Size = new System.Drawing.Size(50, 23);
            this.bExportPalette.TabIndex = 2;
            this.bExportPalette.Text = "Export";
            this.bExportPalette.UseVisualStyleBackColor = true;
            this.bExportPalette.Click += new System.EventHandler(this.bExportPalette_Click);
            // 
            // bImportPalette
            // 
            this.bImportPalette.Location = new System.Drawing.Point(6, 227);
            this.bImportPalette.Name = "bImportPalette";
            this.bImportPalette.Size = new System.Drawing.Size(50, 23);
            this.bImportPalette.TabIndex = 1;
            this.bImportPalette.Text = "Import";
            this.bImportPalette.UseVisualStyleBackColor = true;
            this.bImportPalette.Click += new System.EventHandler(this.bImportPalette_Click);
            // 
            // panelPalette
            // 
            this.panelPalette.Controls.Add(this.panelMoveColor);
            this.panelPalette.Location = new System.Drawing.Point(6, 17);
            this.panelPalette.Name = "panelPalette";
            this.panelPalette.Size = new System.Drawing.Size(208, 208);
            this.panelPalette.TabIndex = 0;
            this.panelPalette.Paint += new System.Windows.Forms.PaintEventHandler(this.panelPalette_Paint);
            this.panelPalette.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panelPalette_MouseDown);
            this.panelPalette.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panelPalette_MouseMove);
            this.panelPalette.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panelPalette_MouseUp);
            // 
            // panelMoveColor
            // 
            this.panelMoveColor.Location = new System.Drawing.Point(32, 32);
            this.panelMoveColor.Name = "panelMoveColor";
            this.panelMoveColor.Size = new System.Drawing.Size(16, 16);
            this.panelMoveColor.TabIndex = 0;
            this.panelMoveColor.Visible = false;
            // 
            // importRSDKGIFToolStripMenuItem
            // 
            this.importRSDKGIFToolStripMenuItem.Name = "importRSDKGIFToolStripMenuItem";
            this.importRSDKGIFToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.importRSDKGIFToolStripMenuItem.Text = "Import RSDK GIF";
            this.importRSDKGIFToolStripMenuItem.Click += new System.EventHandler(this.importRSDKGIFToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 284);
            this.Controls.Add(this.groupPalette);
            this.Controls.Add(this.scrollTexture);
            this.Controls.Add(this.panelPicture);
            this.Controls.Add(this.panelControl);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "GFX Tool";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panelControl.ResumeLayout(false);
            this.panelControl.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nTextureCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nResolution)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDestination)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nWidth)).EndInit();
            this.groupPalette.ResumeLayout(false);
            this.groupPalette.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nColorsCount)).EndInit();
            this.panelPalette.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel panelControl;
        private System.Windows.Forms.NumericUpDown nTextureCount;
        private System.Windows.Forms.NumericUpDown nResolution;
        private System.Windows.Forms.NumericUpDown nDestination;
        private System.Windows.Forms.NumericUpDown nHeight;
        private System.Windows.Forms.NumericUpDown nWidth;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboMode;
        private System.Windows.Forms.CheckBox cbInternalPalette;
        private System.Windows.Forms.CheckBox cbCompressed;
        private System.Windows.Forms.Panel panelPicture;
        private System.Windows.Forms.VScrollBar scrollTexture;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importPNGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importGFXToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportPNGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportGFXToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupPalette;
        private System.Windows.Forms.Panel panelPalette;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem importPaletteToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem exportPaletteToolStripMenuItem;
        private System.Windows.Forms.Button bExportPalette;
        private System.Windows.Forms.Button bImportPalette;
        private System.Windows.Forms.ToolStripMenuItem importSonic16x16ToolStripMenuItem;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cbGfxType;
        private System.Windows.Forms.Panel panelMoveColor;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox cbColorMode;
        private System.Windows.Forms.NumericUpDown nColorsCount;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ToolStripMenuItem tileToolToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importFromRaw4bppGenesisToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadMappingMDONLYToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importRSDKGIFToolStripMenuItem;

    }
}

