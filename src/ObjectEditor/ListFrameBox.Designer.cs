namespace ObjectEditor
{
    partial class ListFrameBox
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

        #region Codice generato da Progettazione componenti

        /// <summary> 
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare 
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.listBox = new System.Windows.Forms.ListBox();
            this.bAdd = new System.Windows.Forms.Button();
            this.bInsert = new System.Windows.Forms.Button();
            this.bRemove = new System.Windows.Forms.Button();
            this.radioPlay = new System.Windows.Forms.RadioButton();
            this.radioPause = new System.Windows.Forms.RadioButton();
            this.bLoop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBox
            // 
            this.listBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.listBox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listBox.FormattingEnabled = true;
            this.listBox.ItemHeight = 32;
            this.listBox.Location = new System.Drawing.Point(0, 0);
            this.listBox.Name = "listBox";
            this.listBox.ScrollAlwaysVisible = true;
            this.listBox.Size = new System.Drawing.Size(86, 164);
            this.listBox.TabIndex = 0;
            this.listBox.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.listBox_DrawItem);
            this.listBox.MeasureItem += new System.Windows.Forms.MeasureItemEventHandler(this.listBox_MeasureItem);
            this.listBox.SelectedIndexChanged += new System.EventHandler(this.listBox_SelectedIndexChanged);
            // 
            // bAdd
            // 
            this.bAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAdd.Location = new System.Drawing.Point(86, 0);
            this.bAdd.Name = "bAdd";
            this.bAdd.Size = new System.Drawing.Size(56, 23);
            this.bAdd.TabIndex = 1;
            this.bAdd.Text = "Add";
            this.bAdd.UseVisualStyleBackColor = true;
            this.bAdd.Click += new System.EventHandler(this.bAdd_Click);
            // 
            // bInsert
            // 
            this.bInsert.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bInsert.Location = new System.Drawing.Point(86, 22);
            this.bInsert.Name = "bInsert";
            this.bInsert.Size = new System.Drawing.Size(56, 23);
            this.bInsert.TabIndex = 2;
            this.bInsert.Text = "Insert";
            this.bInsert.UseVisualStyleBackColor = true;
            this.bInsert.Click += new System.EventHandler(this.bInsert_Click);
            // 
            // bRemove
            // 
            this.bRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemove.Location = new System.Drawing.Point(86, 44);
            this.bRemove.Name = "bRemove";
            this.bRemove.Size = new System.Drawing.Size(56, 23);
            this.bRemove.TabIndex = 3;
            this.bRemove.Text = "Remove";
            this.bRemove.UseVisualStyleBackColor = true;
            this.bRemove.Click += new System.EventHandler(this.bRemove_Click);
            // 
            // radioPlay
            // 
            this.radioPlay.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.radioPlay.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioPlay.Location = new System.Drawing.Point(86, 102);
            this.radioPlay.Name = "radioPlay";
            this.radioPlay.Size = new System.Drawing.Size(56, 23);
            this.radioPlay.TabIndex = 4;
            this.radioPlay.TabStop = true;
            this.radioPlay.Text = "Play";
            this.radioPlay.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.radioPlay.UseVisualStyleBackColor = true;
            this.radioPlay.CheckedChanged += new System.EventHandler(this.radioPlay_CheckedChanged);
            // 
            // radioPause
            // 
            this.radioPause.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.radioPause.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioPause.Location = new System.Drawing.Point(86, 125);
            this.radioPause.Name = "radioPause";
            this.radioPause.Size = new System.Drawing.Size(56, 23);
            this.radioPause.TabIndex = 5;
            this.radioPause.TabStop = true;
            this.radioPause.Text = "Pause";
            this.radioPause.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.radioPause.UseVisualStyleBackColor = true;
            this.radioPause.CheckedChanged += new System.EventHandler(this.radioPause_CheckedChanged);
            // 
            // bLoop
            // 
            this.bLoop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bLoop.Location = new System.Drawing.Point(86, 73);
            this.bLoop.Name = "bLoop";
            this.bLoop.Size = new System.Drawing.Size(56, 23);
            this.bLoop.TabIndex = 6;
            this.bLoop.Text = "Loop";
            this.bLoop.UseVisualStyleBackColor = true;
            this.bLoop.Click += new System.EventHandler(this.bLoop_Click);
            // 
            // ListFrameBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.bLoop);
            this.Controls.Add(this.radioPause);
            this.Controls.Add(this.radioPlay);
            this.Controls.Add(this.bRemove);
            this.Controls.Add(this.bInsert);
            this.Controls.Add(this.bAdd);
            this.Controls.Add(this.listBox);
            this.Name = "ListFrameBox";
            this.Size = new System.Drawing.Size(142, 166);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.Button bAdd;
        private System.Windows.Forms.Button bInsert;
        private System.Windows.Forms.Button bRemove;
        private System.Windows.Forms.RadioButton radioPlay;
        private System.Windows.Forms.RadioButton radioPause;
        private System.Windows.Forms.Button bLoop;
    }
}
