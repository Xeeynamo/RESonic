namespace ObjectEditor
{
    partial class FrameBox
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
            this.SuspendLayout();
            // 
            // FrameBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MaximumSize = new System.Drawing.Size(256, 256);
            this.MinimumSize = new System.Drawing.Size(256, 256);
            this.Name = "FrameBox";
            this.Size = new System.Drawing.Size(256, 256);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.FrameBox_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FrameBox_MouseDown);
            this.MouseEnter += new System.EventHandler(this.FrameBox_MouseEnter);
            this.MouseLeave += new System.EventHandler(this.FrameBox_MouseLeave);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FrameBox_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FrameBox_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion
    }
}
