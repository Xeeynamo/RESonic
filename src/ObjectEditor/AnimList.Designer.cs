namespace ObjectEditor
{
    partial class AnimList
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
            this.labelCategories = new System.Windows.Forms.Label();
            this.listCategories = new System.Windows.Forms.ListBox();
            this.labelAnimations = new System.Windows.Forms.Label();
            this.listAnimations = new System.Windows.Forms.ListBox();
            this.comboSubanim = new System.Windows.Forms.ComboBox();
            this.labelSubAnimation = new System.Windows.Forms.Label();
            this.textAnimID = new System.Windows.Forms.TextBox();
            this.labelDescription = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // labelCategories
            // 
            this.labelCategories.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCategories.Location = new System.Drawing.Point(0, 0);
            this.labelCategories.Name = "labelCategories";
            this.labelCategories.Size = new System.Drawing.Size(105, 13);
            this.labelCategories.TabIndex = 4;
            this.labelCategories.Text = "Categories";
            this.labelCategories.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // listCategories
            // 
            this.listCategories.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.listCategories.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listCategories.FormattingEnabled = true;
            this.listCategories.Location = new System.Drawing.Point(0, 16);
            this.listCategories.Name = "listCategories";
            this.listCategories.Size = new System.Drawing.Size(105, 199);
            this.listCategories.TabIndex = 3;
            this.listCategories.SelectedIndexChanged += new System.EventHandler(this.listCategories_SelectedIndexChanged);
            // 
            // labelAnimations
            // 
            this.labelAnimations.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelAnimations.Location = new System.Drawing.Point(111, 0);
            this.labelAnimations.Name = "labelAnimations";
            this.labelAnimations.Size = new System.Drawing.Size(105, 13);
            this.labelAnimations.TabIndex = 6;
            this.labelAnimations.Text = "Animations";
            this.labelAnimations.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // listAnimations
            // 
            this.listAnimations.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listAnimations.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listAnimations.FormattingEnabled = true;
            this.listAnimations.Location = new System.Drawing.Point(111, 16);
            this.listAnimations.Name = "listAnimations";
            this.listAnimations.Size = new System.Drawing.Size(105, 199);
            this.listAnimations.TabIndex = 5;
            this.listAnimations.SelectedIndexChanged += new System.EventHandler(this.listAnimations_SelectedIndexChanged);
            // 
            // comboSubanim
            // 
            this.comboSubanim.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboSubanim.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboSubanim.FormattingEnabled = true;
            this.comboSubanim.Location = new System.Drawing.Point(57, 216);
            this.comboSubanim.Name = "comboSubanim";
            this.comboSubanim.Size = new System.Drawing.Size(126, 21);
            this.comboSubanim.TabIndex = 7;
            this.comboSubanim.SelectedIndexChanged += new System.EventHandler(this.comboSubanim_SelectedIndexChanged);
            // 
            // labelSubAnimation
            // 
            this.labelSubAnimation.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelSubAnimation.AutoSize = true;
            this.labelSubAnimation.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSubAnimation.Location = new System.Drawing.Point(3, 219);
            this.labelSubAnimation.Name = "labelSubAnimation";
            this.labelSubAnimation.Size = new System.Drawing.Size(48, 13);
            this.labelSubAnimation.TabIndex = 8;
            this.labelSubAnimation.Text = "Subanim";
            // 
            // textAnimID
            // 
            this.textAnimID.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.textAnimID.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textAnimID.Location = new System.Drawing.Point(184, 216);
            this.textAnimID.Name = "textAnimID";
            this.textAnimID.Size = new System.Drawing.Size(32, 20);
            this.textAnimID.TabIndex = 9;
            this.textAnimID.Text = "FFFF";
            // 
            // labelDescription
            // 
            this.labelDescription.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.labelDescription.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelDescription.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDescription.Location = new System.Drawing.Point(3, 241);
            this.labelDescription.Name = "labelDescription";
            this.labelDescription.Size = new System.Drawing.Size(210, 43);
            this.labelDescription.TabIndex = 10;
            // 
            // AnimList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.labelDescription);
            this.Controls.Add(this.textAnimID);
            this.Controls.Add(this.labelSubAnimation);
            this.Controls.Add(this.comboSubanim);
            this.Controls.Add(this.labelAnimations);
            this.Controls.Add(this.listAnimations);
            this.Controls.Add(this.labelCategories);
            this.Controls.Add(this.listCategories);
            this.Name = "AnimList";
            this.Size = new System.Drawing.Size(216, 287);
            this.Resize += new System.EventHandler(this.AnimList_Resize);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelCategories;
        private System.Windows.Forms.ListBox listCategories;
        private System.Windows.Forms.Label labelAnimations;
        private System.Windows.Forms.ListBox listAnimations;
        private System.Windows.Forms.ComboBox comboSubanim;
        private System.Windows.Forms.Label labelSubAnimation;
        private System.Windows.Forms.TextBox textAnimID;
        private System.Windows.Forms.Label labelDescription;

    }
}
