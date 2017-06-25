namespace ObjectEditor
{
    partial class fMain
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
            ObjectEditor.AnimationFrame animationFrame1 = new ObjectEditor.AnimationFrame();
            ObjectEditor.Hitbox hitbox1 = new ObjectEditor.Hitbox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabOverview = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textEntityName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.nEntityID = new System.Windows.Forms.NumericUpDown();
            this.comboEntityType = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textFileName = new System.Windows.Forms.TextBox();
            this.textWorkingPath = new System.Windows.Forms.TextBox();
            this.bSave = new System.Windows.Forms.Button();
            this.bOpen = new System.Windows.Forms.Button();
            this.tabHitbox = new System.Windows.Forms.TabPage();
            this.comboFrameBoxHitbox = new ObjectEditor.ComboFrameBox();
            this.comboFrameBoxHitboxFrame = new ObjectEditor.ComboFrameBox();
            this.panelHitbox = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.nHitboxHeight = new System.Windows.Forms.NumericUpDown();
            this.nHitboxWidth = new System.Windows.Forms.NumericUpDown();
            this.nHitboxSourceY = new System.Windows.Forms.NumericUpDown();
            this.nHitboxSourceX = new System.Windows.Forms.NumericUpDown();
            this.tabFrames = new System.Windows.Forms.TabPage();
            this.cbFrameShowHitbox = new System.Windows.Forms.CheckBox();
            this.bFrameCenter = new System.Windows.Forms.Button();
            this.cbZoom = new System.Windows.Forms.CheckBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.nFrameHitbox = new System.Windows.Forms.NumericUpDown();
            this.nFrameCenterY = new System.Windows.Forms.NumericUpDown();
            this.nFrameCenterX = new System.Windows.Forms.NumericUpDown();
            this.nFrameHeight = new System.Windows.Forms.NumericUpDown();
            this.nFrameWidth = new System.Windows.Forms.NumericUpDown();
            this.nFrameSourceY = new System.Windows.Forms.NumericUpDown();
            this.nFrameSourceX = new System.Windows.Forms.NumericUpDown();
            this.comboFrameBox1 = new ObjectEditor.ComboFrameBox();
            this.frameBox1 = new ObjectEditor.FrameBox();
            this.tabAnimation = new System.Windows.Forms.TabPage();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.listFrameBox1 = new ObjectEditor.ListFrameBox();
            this.comboFrameBox2 = new ObjectEditor.ComboFrameBox();
            this.label20 = new System.Windows.Forms.Label();
            this.nAnimationSpeed = new System.Windows.Forms.NumericUpDown();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.animList1 = new ObjectEditor.AnimList();
            this.animationBox = new ObjectEditor.AnimationBox();
            this.tabControl1.SuspendLayout();
            this.tabOverview.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nEntityID)).BeginInit();
            this.tabHitbox.SuspendLayout();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxSourceY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxSourceX)).BeginInit();
            this.tabFrames.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameHitbox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCenterY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCenterX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameSourceY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameSourceX)).BeginInit();
            this.tabAnimation.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nAnimationSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabOverview);
            this.tabControl1.Controls.Add(this.tabHitbox);
            this.tabControl1.Controls.Add(this.tabFrames);
            this.tabControl1.Controls.Add(this.tabAnimation);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(645, 286);
            this.tabControl1.TabIndex = 0;
            // 
            // tabOverview
            // 
            this.tabOverview.Controls.Add(this.groupBox1);
            this.tabOverview.Controls.Add(this.label5);
            this.tabOverview.Controls.Add(this.label4);
            this.tabOverview.Controls.Add(this.textFileName);
            this.tabOverview.Controls.Add(this.textWorkingPath);
            this.tabOverview.Controls.Add(this.bSave);
            this.tabOverview.Controls.Add(this.bOpen);
            this.tabOverview.Location = new System.Drawing.Point(4, 22);
            this.tabOverview.Name = "tabOverview";
            this.tabOverview.Padding = new System.Windows.Forms.Padding(3);
            this.tabOverview.Size = new System.Drawing.Size(637, 260);
            this.tabOverview.TabIndex = 0;
            this.tabOverview.Text = "Overview";
            this.tabOverview.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textEntityName);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.nEntityID);
            this.groupBox1.Controls.Add(this.comboEntityType);
            this.groupBox1.Location = new System.Drawing.Point(8, 87);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(173, 100);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Entity properties";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 72);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Type";
            // 
            // textEntityName
            // 
            this.textEntityName.BackColor = System.Drawing.Color.Black;
            this.textEntityName.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textEntityName.ForeColor = System.Drawing.Color.White;
            this.textEntityName.Location = new System.Drawing.Point(44, 17);
            this.textEntityName.MaxLength = 16;
            this.textEntityName.Name = "textEntityName";
            this.textEntityName.Size = new System.Drawing.Size(121, 20);
            this.textEntityName.TabIndex = 8;
            this.textEntityName.Text = "<null>";
            this.textEntityName.TextChanged += new System.EventHandler(this.textEntityName_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "ID";
            // 
            // nEntityID
            // 
            this.nEntityID.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nEntityID.Hexadecimal = true;
            this.nEntityID.Location = new System.Drawing.Point(44, 43);
            this.nEntityID.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.nEntityID.Name = "nEntityID";
            this.nEntityID.Size = new System.Drawing.Size(121, 20);
            this.nEntityID.TabIndex = 9;
            this.nEntityID.ValueChanged += new System.EventHandler(this.nEntityID_ValueChanged);
            // 
            // comboEntityType
            // 
            this.comboEntityType.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboEntityType.FormattingEnabled = true;
            this.comboEntityType.Items.AddRange(new object[] {
            "Undefined",
            "Player",
            "Shared field",
            "Level field",
            "Enemy",
            "Boss",
            "Event"});
            this.comboEntityType.Location = new System.Drawing.Point(44, 69);
            this.comboEntityType.Name = "comboEntityType";
            this.comboEntityType.Size = new System.Drawing.Size(121, 22);
            this.comboEntityType.TabIndex = 10;
            this.comboEntityType.SelectedIndexChanged += new System.EventHandler(this.comboEntityType_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(5, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(52, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "File name";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(5, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Working path";
            // 
            // textFileName
            // 
            this.textFileName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textFileName.Enabled = false;
            this.textFileName.Location = new System.Drawing.Point(101, 61);
            this.textFileName.Name = "textFileName";
            this.textFileName.Size = new System.Drawing.Size(337, 20);
            this.textFileName.TabIndex = 10;
            // 
            // textWorkingPath
            // 
            this.textWorkingPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textWorkingPath.Enabled = false;
            this.textWorkingPath.Font = new System.Drawing.Font("Courier New", 8F);
            this.textWorkingPath.Location = new System.Drawing.Point(101, 35);
            this.textWorkingPath.Name = "textWorkingPath";
            this.textWorkingPath.Size = new System.Drawing.Size(337, 20);
            this.textWorkingPath.TabIndex = 9;
            // 
            // bSave
            // 
            this.bSave.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bSave.Location = new System.Drawing.Point(89, 6);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(75, 23);
            this.bSave.TabIndex = 1;
            this.bSave.Text = "Save";
            this.bSave.UseVisualStyleBackColor = true;
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // bOpen
            // 
            this.bOpen.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bOpen.Location = new System.Drawing.Point(8, 6);
            this.bOpen.Name = "bOpen";
            this.bOpen.Size = new System.Drawing.Size(75, 23);
            this.bOpen.TabIndex = 0;
            this.bOpen.Text = "Open";
            this.bOpen.UseVisualStyleBackColor = true;
            this.bOpen.Click += new System.EventHandler(this.bOpen_Click);
            // 
            // tabHitbox
            // 
            this.tabHitbox.Controls.Add(this.comboFrameBoxHitbox);
            this.tabHitbox.Controls.Add(this.comboFrameBoxHitboxFrame);
            this.tabHitbox.Controls.Add(this.panelHitbox);
            this.tabHitbox.Controls.Add(this.panel3);
            this.tabHitbox.Location = new System.Drawing.Point(4, 22);
            this.tabHitbox.Name = "tabHitbox";
            this.tabHitbox.Padding = new System.Windows.Forms.Padding(3);
            this.tabHitbox.Size = new System.Drawing.Size(637, 260);
            this.tabHitbox.TabIndex = 1;
            this.tabHitbox.Text = "Hitbox";
            this.tabHitbox.UseVisualStyleBackColor = true;
            // 
            // comboFrameBoxHitbox
            // 
            this.comboFrameBoxHitbox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboFrameBoxHitbox.Entity = null;
            this.comboFrameBoxHitbox.IsHitbox = true;
            this.comboFrameBoxHitbox.Location = new System.Drawing.Point(262, 3);
            this.comboFrameBoxHitbox.Name = "comboFrameBoxHitbox";
            this.comboFrameBoxHitbox.SelectedIndex = -1;
            this.comboFrameBoxHitbox.ShowEdits = true;
            this.comboFrameBoxHitbox.Size = new System.Drawing.Size(375, 38);
            this.comboFrameBoxHitbox.Sprite = null;
            this.comboFrameBoxHitbox.TabIndex = 6;
            this.comboFrameBoxHitbox.SelectedIndexChanged += new ObjectEditor.ComboFrameBox.delegate_SelectedIndexChanged(this.comboFrameBoxHitbox_SelectedIndexChanged_1);
            // 
            // comboFrameBoxHitboxFrame
            // 
            this.comboFrameBoxHitboxFrame.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboFrameBoxHitboxFrame.Entity = null;
            this.comboFrameBoxHitboxFrame.IsHitbox = false;
            this.comboFrameBoxHitboxFrame.Location = new System.Drawing.Point(259, 167);
            this.comboFrameBoxHitboxFrame.Name = "comboFrameBoxHitboxFrame";
            this.comboFrameBoxHitboxFrame.SelectedIndex = -1;
            this.comboFrameBoxHitboxFrame.ShowEdits = false;
            this.comboFrameBoxHitboxFrame.Size = new System.Drawing.Size(378, 38);
            this.comboFrameBoxHitboxFrame.Sprite = null;
            this.comboFrameBoxHitboxFrame.TabIndex = 5;
            this.comboFrameBoxHitboxFrame.SelectedIndexChanged += new ObjectEditor.ComboFrameBox.delegate_SelectedIndexChanged(this.comboFrameBoxHitbox_SelectedIndexChanged);
            // 
            // panelHitbox
            // 
            this.panelHitbox.BackColor = System.Drawing.Color.Fuchsia;
            this.panelHitbox.Location = new System.Drawing.Point(0, 0);
            this.panelHitbox.Name = "panelHitbox";
            this.panelHitbox.Size = new System.Drawing.Size(256, 256);
            this.panelHitbox.TabIndex = 3;
            this.panelHitbox.Paint += new System.Windows.Forms.PaintEventHandler(this.panelHitbox_Paint);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.label16);
            this.panel3.Controls.Add(this.label17);
            this.panel3.Controls.Add(this.label18);
            this.panel3.Controls.Add(this.label19);
            this.panel3.Controls.Add(this.nHitboxHeight);
            this.panel3.Controls.Add(this.nHitboxWidth);
            this.panel3.Controls.Add(this.nHitboxSourceY);
            this.panel3.Controls.Add(this.nHitboxSourceX);
            this.panel3.Location = new System.Drawing.Point(262, 53);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(139, 108);
            this.panel3.TabIndex = 2;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(3, 57);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(32, 13);
            this.label16.TabIndex = 10;
            this.label16.Text = "Right";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(3, 83);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(40, 13);
            this.label17.TabIndex = 10;
            this.label17.Text = "Bottom";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(3, 31);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(26, 13);
            this.label18.TabIndex = 9;
            this.label18.Text = "Top";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(3, 5);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(25, 13);
            this.label19.TabIndex = 8;
            this.label19.Text = "Left";
            // 
            // nHitboxHeight
            // 
            this.nHitboxHeight.Location = new System.Drawing.Point(73, 81);
            this.nHitboxHeight.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.nHitboxHeight.Name = "nHitboxHeight";
            this.nHitboxHeight.Size = new System.Drawing.Size(59, 20);
            this.nHitboxHeight.TabIndex = 3;
            this.nHitboxHeight.Tag = "4";
            this.nHitboxHeight.ValueChanged += new System.EventHandler(this.nHitbox_ValueChanged);
            // 
            // nHitboxWidth
            // 
            this.nHitboxWidth.Location = new System.Drawing.Point(73, 55);
            this.nHitboxWidth.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.nHitboxWidth.Name = "nHitboxWidth";
            this.nHitboxWidth.Size = new System.Drawing.Size(59, 20);
            this.nHitboxWidth.TabIndex = 2;
            this.nHitboxWidth.Tag = "3";
            this.nHitboxWidth.ValueChanged += new System.EventHandler(this.nHitbox_ValueChanged);
            // 
            // nHitboxSourceY
            // 
            this.nHitboxSourceY.Location = new System.Drawing.Point(73, 29);
            this.nHitboxSourceY.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.nHitboxSourceY.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.nHitboxSourceY.Name = "nHitboxSourceY";
            this.nHitboxSourceY.Size = new System.Drawing.Size(59, 20);
            this.nHitboxSourceY.TabIndex = 1;
            this.nHitboxSourceY.Tag = "2";
            this.nHitboxSourceY.ValueChanged += new System.EventHandler(this.nHitbox_ValueChanged);
            // 
            // nHitboxSourceX
            // 
            this.nHitboxSourceX.Location = new System.Drawing.Point(73, 3);
            this.nHitboxSourceX.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.nHitboxSourceX.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.nHitboxSourceX.Name = "nHitboxSourceX";
            this.nHitboxSourceX.Size = new System.Drawing.Size(59, 20);
            this.nHitboxSourceX.TabIndex = 0;
            this.nHitboxSourceX.Tag = "1";
            this.nHitboxSourceX.ValueChanged += new System.EventHandler(this.nHitbox_ValueChanged);
            // 
            // tabFrames
            // 
            this.tabFrames.Controls.Add(this.cbFrameShowHitbox);
            this.tabFrames.Controls.Add(this.bFrameCenter);
            this.tabFrames.Controls.Add(this.cbZoom);
            this.tabFrames.Controls.Add(this.panel2);
            this.tabFrames.Controls.Add(this.comboFrameBox1);
            this.tabFrames.Controls.Add(this.frameBox1);
            this.tabFrames.Location = new System.Drawing.Point(4, 22);
            this.tabFrames.Name = "tabFrames";
            this.tabFrames.Padding = new System.Windows.Forms.Padding(3);
            this.tabFrames.Size = new System.Drawing.Size(637, 260);
            this.tabFrames.TabIndex = 2;
            this.tabFrames.Text = "Frames";
            this.tabFrames.UseVisualStyleBackColor = true;
            // 
            // cbFrameShowHitbox
            // 
            this.cbFrameShowHitbox.AutoSize = true;
            this.cbFrameShowHitbox.Location = new System.Drawing.Point(322, 235);
            this.cbFrameShowHitbox.Name = "cbFrameShowHitbox";
            this.cbFrameShowHitbox.Size = new System.Drawing.Size(84, 17);
            this.cbFrameShowHitbox.TabIndex = 6;
            this.cbFrameShowHitbox.Text = "Show hitbox";
            this.cbFrameShowHitbox.UseVisualStyleBackColor = true;
            this.cbFrameShowHitbox.CheckedChanged += new System.EventHandler(this.cbFrameShowHitbox_CheckedChanged);
            // 
            // bFrameCenter
            // 
            this.bFrameCenter.Location = new System.Drawing.Point(407, 151);
            this.bFrameCenter.Name = "bFrameCenter";
            this.bFrameCenter.Size = new System.Drawing.Size(82, 46);
            this.bFrameCenter.TabIndex = 5;
            this.bFrameCenter.Text = "Auto center";
            this.bFrameCenter.UseVisualStyleBackColor = true;
            this.bFrameCenter.Click += new System.EventHandler(this.bFrameCenter_Click);
            // 
            // cbZoom
            // 
            this.cbZoom.AutoSize = true;
            this.cbZoom.Location = new System.Drawing.Point(262, 235);
            this.cbZoom.Name = "cbZoom";
            this.cbZoom.Size = new System.Drawing.Size(53, 17);
            this.cbZoom.TabIndex = 3;
            this.cbZoom.Text = "Zoom";
            this.cbZoom.UseVisualStyleBackColor = true;
            this.cbZoom.CheckedChanged += new System.EventHandler(this.cbZoom_CheckedChanged);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.label12);
            this.panel2.Controls.Add(this.label11);
            this.panel2.Controls.Add(this.label10);
            this.panel2.Controls.Add(this.label9);
            this.panel2.Controls.Add(this.label8);
            this.panel2.Controls.Add(this.label7);
            this.panel2.Controls.Add(this.label6);
            this.panel2.Controls.Add(this.nFrameHitbox);
            this.panel2.Controls.Add(this.nFrameCenterY);
            this.panel2.Controls.Add(this.nFrameCenterX);
            this.panel2.Controls.Add(this.nFrameHeight);
            this.panel2.Controls.Add(this.nFrameWidth);
            this.panel2.Controls.Add(this.nFrameSourceY);
            this.panel2.Controls.Add(this.nFrameSourceX);
            this.panel2.Location = new System.Drawing.Point(262, 44);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(139, 185);
            this.panel2.TabIndex = 1;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(3, 161);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(37, 13);
            this.label12.TabIndex = 13;
            this.label12.Text = "Hitbox";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(3, 135);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(48, 13);
            this.label11.TabIndex = 12;
            this.label11.Text = "Center Y";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(3, 109);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(48, 13);
            this.label10.TabIndex = 11;
            this.label10.Text = "Center X";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(3, 57);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(35, 13);
            this.label9.TabIndex = 10;
            this.label9.Text = "Width";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(3, 83);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(38, 13);
            this.label8.TabIndex = 10;
            this.label8.Text = "Height";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(3, 31);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(51, 13);
            this.label7.TabIndex = 9;
            this.label7.Text = "Source Y";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 5);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(51, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Source X";
            // 
            // nFrameHitbox
            // 
            this.nFrameHitbox.Location = new System.Drawing.Point(73, 159);
            this.nFrameHitbox.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nFrameHitbox.Name = "nFrameHitbox";
            this.nFrameHitbox.Size = new System.Drawing.Size(59, 20);
            this.nFrameHitbox.TabIndex = 6;
            this.nFrameHitbox.Tag = "7";
            this.nFrameHitbox.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameCenterY
            // 
            this.nFrameCenterY.Location = new System.Drawing.Point(73, 133);
            this.nFrameCenterY.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.nFrameCenterY.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.nFrameCenterY.Name = "nFrameCenterY";
            this.nFrameCenterY.Size = new System.Drawing.Size(59, 20);
            this.nFrameCenterY.TabIndex = 5;
            this.nFrameCenterY.Tag = "6";
            this.nFrameCenterY.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameCenterX
            // 
            this.nFrameCenterX.Location = new System.Drawing.Point(73, 107);
            this.nFrameCenterX.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.nFrameCenterX.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.nFrameCenterX.Name = "nFrameCenterX";
            this.nFrameCenterX.Size = new System.Drawing.Size(59, 20);
            this.nFrameCenterX.TabIndex = 4;
            this.nFrameCenterX.Tag = "5";
            this.nFrameCenterX.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameHeight
            // 
            this.nFrameHeight.Location = new System.Drawing.Point(73, 81);
            this.nFrameHeight.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.nFrameHeight.Name = "nFrameHeight";
            this.nFrameHeight.Size = new System.Drawing.Size(59, 20);
            this.nFrameHeight.TabIndex = 3;
            this.nFrameHeight.Tag = "4";
            this.nFrameHeight.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameWidth
            // 
            this.nFrameWidth.Location = new System.Drawing.Point(73, 55);
            this.nFrameWidth.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.nFrameWidth.Name = "nFrameWidth";
            this.nFrameWidth.Size = new System.Drawing.Size(59, 20);
            this.nFrameWidth.TabIndex = 2;
            this.nFrameWidth.Tag = "3";
            this.nFrameWidth.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameSourceY
            // 
            this.nFrameSourceY.Location = new System.Drawing.Point(73, 29);
            this.nFrameSourceY.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.nFrameSourceY.Name = "nFrameSourceY";
            this.nFrameSourceY.Size = new System.Drawing.Size(59, 20);
            this.nFrameSourceY.TabIndex = 1;
            this.nFrameSourceY.Tag = "2";
            this.nFrameSourceY.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // nFrameSourceX
            // 
            this.nFrameSourceX.Location = new System.Drawing.Point(73, 3);
            this.nFrameSourceX.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.nFrameSourceX.Name = "nFrameSourceX";
            this.nFrameSourceX.Size = new System.Drawing.Size(59, 20);
            this.nFrameSourceX.TabIndex = 0;
            this.nFrameSourceX.Tag = "1";
            this.nFrameSourceX.ValueChanged += new System.EventHandler(this.Frame_ValuesChanged);
            // 
            // comboFrameBox1
            // 
            this.comboFrameBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboFrameBox1.Entity = null;
            this.comboFrameBox1.IsHitbox = false;
            this.comboFrameBox1.Location = new System.Drawing.Point(262, 0);
            this.comboFrameBox1.Name = "comboFrameBox1";
            this.comboFrameBox1.SelectedIndex = -1;
            this.comboFrameBox1.ShowEdits = true;
            this.comboFrameBox1.Size = new System.Drawing.Size(375, 38);
            this.comboFrameBox1.Sprite = null;
            this.comboFrameBox1.TabIndex = 4;
            this.comboFrameBox1.SelectedIndexChanged += new ObjectEditor.ComboFrameBox.delegate_SelectedIndexChanged(this.comboFrameBox1_SelectedIndexChanged);
            // 
            // frameBox1
            // 
            this.frameBox1.BackColor = System.Drawing.Color.Fuchsia;
            this.frameBox1.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            animationFrame1.Center = new System.Drawing.Point(0, 0);
            animationFrame1.Hitbox = 0;
            animationFrame1.Position = new System.Drawing.Point(0, 0);
            animationFrame1.Size = new System.Drawing.Size(0, 0);
            this.frameBox1.Frame = animationFrame1;
            hitbox1.Box = new System.Drawing.Rectangle(0, 0, 0, 0);
            hitbox1.X1 = 0;
            hitbox1.X2 = 0;
            hitbox1.Y1 = 0;
            hitbox1.Y2 = 0;
            this.frameBox1.Hitbox = hitbox1;
            this.frameBox1.Location = new System.Drawing.Point(0, 0);
            this.frameBox1.MaximumSize = new System.Drawing.Size(256, 256);
            this.frameBox1.MinimumSize = new System.Drawing.Size(256, 256);
            this.frameBox1.Name = "frameBox1";
            this.frameBox1.ShowHitbox = false;
            this.frameBox1.Size = new System.Drawing.Size(256, 256);
            this.frameBox1.SpriteSheet = null;
            this.frameBox1.TabIndex = 2;
            this.frameBox1.Zoom = true;
            this.frameBox1.OnFrameboxChanging += new ObjectEditor.FrameBox.delegate_OnFrameboxChanging(this.frameBox1_OnFrameboxChanging);
            this.frameBox1.OnFrameboxChanged += new ObjectEditor.FrameBox.delegate_OnFrameboxChanged(this.frameBox1_OnFrameboxChanged);
            // 
            // tabAnimation
            // 
            this.tabAnimation.Controls.Add(this.tabControl2);
            this.tabAnimation.Controls.Add(this.animList1);
            this.tabAnimation.Controls.Add(this.animationBox);
            this.tabAnimation.Location = new System.Drawing.Point(4, 22);
            this.tabAnimation.Name = "tabAnimation";
            this.tabAnimation.Padding = new System.Windows.Forms.Padding(3);
            this.tabAnimation.Size = new System.Drawing.Size(637, 260);
            this.tabAnimation.TabIndex = 3;
            this.tabAnimation.Text = "Animation";
            this.tabAnimation.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPage1);
            this.tabControl2.Controls.Add(this.tabPage2);
            this.tabControl2.Location = new System.Drawing.Point(488, 0);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(151, 260);
            this.tabControl2.TabIndex = 26;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.listFrameBox1);
            this.tabPage1.Controls.Add(this.comboFrameBox2);
            this.tabPage1.Controls.Add(this.label20);
            this.tabPage1.Controls.Add(this.nAnimationSpeed);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(143, 234);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Animation";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // listFrameBox1
            // 
            this.listFrameBox1.Animation = null;
            this.listFrameBox1.AnimationIndex = -1;
            this.listFrameBox1.Location = new System.Drawing.Point(1, 1);
            this.listFrameBox1.Name = "listFrameBox1";
            this.listFrameBox1.Size = new System.Drawing.Size(142, 166);
            this.listFrameBox1.Sprite = null;
            this.listFrameBox1.TabIndex = 28;
            this.listFrameBox1.OnPlay += new ObjectEditor.ListFrameBox.delegate_OnPlay(this.listFrameBox1_OnPlay);
            this.listFrameBox1.OnPause += new ObjectEditor.ListFrameBox.delegate_OnPause(this.listFrameBox1_OnPause);
            this.listFrameBox1.OnSelectedFrame += new ObjectEditor.ListFrameBox.delegate_OnSelectedFrame(this.listFrameBox1_OnSelectedFrame);
            // 
            // comboFrameBox2
            // 
            this.comboFrameBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboFrameBox2.Entity = null;
            this.comboFrameBox2.IsHitbox = false;
            this.comboFrameBox2.Location = new System.Drawing.Point(0, 173);
            this.comboFrameBox2.Name = "comboFrameBox2";
            this.comboFrameBox2.SelectedIndex = -1;
            this.comboFrameBox2.ShowEdits = false;
            this.comboFrameBox2.Size = new System.Drawing.Size(142, 38);
            this.comboFrameBox2.Sprite = null;
            this.comboFrameBox2.TabIndex = 27;
            this.comboFrameBox2.SelectedIndexChanged += new ObjectEditor.ComboFrameBox.delegate_SelectedIndexChanged(this.comboFrameBox2_SelectedIndexChanged);
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(3, 215);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(38, 13);
            this.label20.TabIndex = 24;
            this.label20.Text = "Speed";
            // 
            // nAnimationSpeed
            // 
            this.nAnimationSpeed.Location = new System.Drawing.Point(49, 213);
            this.nAnimationSpeed.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nAnimationSpeed.Name = "nAnimationSpeed";
            this.nAnimationSpeed.Size = new System.Drawing.Size(59, 20);
            this.nAnimationSpeed.TabIndex = 23;
            this.nAnimationSpeed.ValueChanged += new System.EventHandler(this.nAnimationSpeed_ValueChanged);
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(143, 234);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Childs";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // animList1
            // 
            this.animList1.Location = new System.Drawing.Point(0, 0);
            this.animList1.MinimumSize = new System.Drawing.Size(0, 152);
            this.animList1.Name = "animList1";
            this.animList1.ObjectName = "";
            this.animList1.SelectedAnimation = -1;
            this.animList1.SelectedCategory = -1;
            this.animList1.Size = new System.Drawing.Size(220, 247);
            this.animList1.TabIndex = 20;
            this.animList1.OnSelectedAnimation += new ObjectEditor.AnimList.OnSelectedAnimationDelegate(this.animList1_OnSelectedAnimation);
            // 
            // animationBox
            // 
            this.animationBox.BackColor = System.Drawing.Color.Magenta;
            this.animationBox.Entity = null;
            this.animationBox.Location = new System.Drawing.Point(226, 1);
            this.animationBox.Name = "animationBox";
            this.animationBox.SelectedAnimationId = ((ushort)(65535));
            this.animationBox.Size = new System.Drawing.Size(256, 256);
            this.animationBox.Sprite = null;
            this.animationBox.TabIndex = 0;
            // 
            // fMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(645, 286);
            this.Controls.Add(this.tabControl1);
            this.DoubleBuffered = true;
            this.Name = "fMain";
            this.Text = "Object Editor";
            this.tabControl1.ResumeLayout(false);
            this.tabOverview.ResumeLayout(false);
            this.tabOverview.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nEntityID)).EndInit();
            this.tabHitbox.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxSourceY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nHitboxSourceX)).EndInit();
            this.tabFrames.ResumeLayout(false);
            this.tabFrames.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameHitbox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCenterY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameCenterX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameSourceY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nFrameSourceX)).EndInit();
            this.tabAnimation.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nAnimationSpeed)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabOverview;
        private System.Windows.Forms.Button bSave;
        private System.Windows.Forms.Button bOpen;
        private System.Windows.Forms.TabPage tabHitbox;
        private System.Windows.Forms.TabPage tabFrames;
        private System.Windows.Forms.TabPage tabAnimation;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textEntityName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown nEntityID;
        private System.Windows.Forms.ComboBox comboEntityType;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textFileName;
        private System.Windows.Forms.TextBox textWorkingPath;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown nFrameHitbox;
        private System.Windows.Forms.NumericUpDown nFrameCenterY;
        private System.Windows.Forms.NumericUpDown nFrameCenterX;
        private System.Windows.Forms.NumericUpDown nFrameHeight;
        private System.Windows.Forms.NumericUpDown nFrameWidth;
        private System.Windows.Forms.NumericUpDown nFrameSourceY;
        private System.Windows.Forms.NumericUpDown nFrameSourceX;
        private System.Windows.Forms.Panel panelHitbox;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.NumericUpDown nHitboxHeight;
        private System.Windows.Forms.NumericUpDown nHitboxWidth;
        private System.Windows.Forms.NumericUpDown nHitboxSourceY;
        private System.Windows.Forms.NumericUpDown nHitboxSourceX;
        private FrameBox frameBox1;
        private System.Windows.Forms.CheckBox cbZoom;
        private ComboFrameBox comboFrameBox1;
        private System.Windows.Forms.Button bFrameCenter;
        private ComboFrameBox comboFrameBoxHitboxFrame;
        private ComboFrameBox comboFrameBoxHitbox;
        private System.Windows.Forms.CheckBox cbFrameShowHitbox;
        private AnimationBox animationBox;
        private AnimList animList1;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.NumericUpDown nAnimationSpeed;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPage1;
        private ComboFrameBox comboFrameBox2;
        private System.Windows.Forms.TabPage tabPage2;
        private ListFrameBox listFrameBox1;
    }
}

