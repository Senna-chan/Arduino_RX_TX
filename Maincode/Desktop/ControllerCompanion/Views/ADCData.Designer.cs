namespace ControllerCompanion.Views
{
    partial class ADCData
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            tableLayoutPanel2 = new TableLayoutPanel();
            label13 = new Label();
            lblIOData = new Label();
            tableLayoutPanel2.SuspendLayout();
            SuspendLayout();
            // 
            // tableLayoutPanel2
            // 
            tableLayoutPanel2.ColumnCount = 7;
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 27.57847F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 8.623662F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 8.623664F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 10.3483953F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 8.623664F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 8.623664F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 27.578474F));
            tableLayoutPanel2.Controls.Add(label13, 0, 6);
            tableLayoutPanel2.Controls.Add(lblIOData, 1, 6);
            tableLayoutPanel2.Dock = DockStyle.Fill;
            tableLayoutPanel2.Location = new Point(0, 0);
            tableLayoutPanel2.Name = "tableLayoutPanel2";
            tableLayoutPanel2.RowCount = 7;
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.49275F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.492753F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.492753F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.492753F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.492753F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 14.492753F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 13.04348F));
            tableLayoutPanel2.Size = new Size(1332, 468);
            tableLayoutPanel2.TabIndex = 1;
            // 
            // label13
            // 
            label13.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            label13.AutoSize = true;
            label13.Location = new Point(3, 402);
            label13.Name = "label13";
            label13.Size = new Size(361, 66);
            label13.TabIndex = 24;
            label13.Text = "IO";
            label13.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblIOData
            // 
            lblIOData.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            lblIOData.AutoSize = true;
            tableLayoutPanel2.SetColumnSpan(lblIOData, 6);
            lblIOData.Location = new Point(370, 402);
            lblIOData.Name = "lblIOData";
            lblIOData.Size = new Size(959, 66);
            lblIOData.TabIndex = 25;
            lblIOData.Text = "IO DATA HERE";
            lblIOData.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // ADCData
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(tableLayoutPanel2);
            Name = "ADCData";
            Size = new Size(1332, 468);
            tableLayoutPanel2.ResumeLayout(false);
            tableLayoutPanel2.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel2;
        private Label label13;
        private Label lblIOData;
    }
}
