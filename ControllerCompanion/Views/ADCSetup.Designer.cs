namespace ControllerCompanion.Views
{
    partial class ADCSetup
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
            tableLayoutPanel1 = new TableLayoutPanel();
            label4 = new Label();
            numMax = new NumericUpDown();
            numMid = new NumericUpDown();
            label2 = new Label();
            tbMax = new TrackBar();
            tbMid = new TrackBar();
            tbMin = new TrackBar();
            numMin = new NumericUpDown();
            label1 = new Label();
            label3 = new Label();
            lblCurrentValue = new Label();
            tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numMax).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numMid).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbMax).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbMid).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbMin).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numMin).BeginInit();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 4;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 140F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 100F));
            tableLayoutPanel1.Controls.Add(label4, 0, 0);
            tableLayoutPanel1.Controls.Add(numMax, 3, 3);
            tableLayoutPanel1.Controls.Add(numMid, 3, 2);
            tableLayoutPanel1.Controls.Add(label2, 0, 2);
            tableLayoutPanel1.Controls.Add(tbMax, 1, 3);
            tableLayoutPanel1.Controls.Add(tbMid, 1, 2);
            tableLayoutPanel1.Controls.Add(tbMin, 1, 1);
            tableLayoutPanel1.Controls.Add(numMin, 3, 1);
            tableLayoutPanel1.Controls.Add(label1, 0, 1);
            tableLayoutPanel1.Controls.Add(label3, 0, 3);
            tableLayoutPanel1.Controls.Add(lblCurrentValue, 1, 0);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 4;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 100F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 20F));
            tableLayoutPanel1.Size = new Size(753, 331);
            tableLayoutPanel1.TabIndex = 2;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Dock = DockStyle.Fill;
            label4.Location = new Point(3, 0);
            label4.Name = "label4";
            label4.Size = new Size(134, 100);
            label4.TabIndex = 14;
            label4.Text = "Channel current value";
            label4.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // numMax
            // 
            numMax.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numMax.Location = new Point(655, 257);
            numMax.Maximum = new decimal(new int[] { 1023, 0, 0, 0 });
            numMax.Name = "numMax";
            numMax.Size = new Size(95, 23);
            numMax.TabIndex = 13;
            numMax.KeyUp += numMax_KeyUp;
            // 
            // numMid
            // 
            numMid.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numMid.Location = new Point(655, 180);
            numMid.Maximum = new decimal(new int[] { 1023, 0, 0, 0 });
            numMid.Name = "numMid";
            numMid.Size = new Size(95, 23);
            numMid.TabIndex = 12;
            numMid.KeyUp += numMid_KeyUp;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Dock = DockStyle.Fill;
            label2.Location = new Point(3, 177);
            label2.Name = "label2";
            label2.Size = new Size(134, 77);
            label2.TabIndex = 10;
            label2.Text = "Channel middle";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // tbMax
            // 
            tbMax.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            tableLayoutPanel1.SetColumnSpan(tbMax, 2);
            tbMax.Location = new Point(143, 257);
            tbMax.Maximum = 1023;
            tbMax.Name = "tbMax";
            tbMax.Size = new Size(506, 71);
            tbMax.TabIndex = 7;
            tbMax.TickStyle = TickStyle.Both;
            tbMax.ValueChanged += tbMax_ValueChanged;
            // 
            // tbMid
            // 
            tbMid.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            tableLayoutPanel1.SetColumnSpan(tbMid, 2);
            tbMid.Location = new Point(143, 180);
            tbMid.Maximum = 1023;
            tbMid.Name = "tbMid";
            tbMid.Size = new Size(506, 71);
            tbMid.TabIndex = 6;
            tbMid.TickStyle = TickStyle.Both;
            tbMid.ValueChanged += tbMid_ValueChanged;
            // 
            // tbMin
            // 
            tbMin.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            tableLayoutPanel1.SetColumnSpan(tbMin, 2);
            tbMin.Location = new Point(143, 103);
            tbMin.Maximum = 1023;
            tbMin.Name = "tbMin";
            tbMin.Size = new Size(506, 71);
            tbMin.TabIndex = 2;
            tbMin.TickStyle = TickStyle.Both;
            tbMin.ValueChanged += tbMin_ValueChanged;
            // 
            // numMin
            // 
            numMin.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numMin.Location = new Point(655, 103);
            numMin.Maximum = new decimal(new int[] { 1023, 0, 0, 0 });
            numMin.Name = "numMin";
            numMin.Size = new Size(95, 23);
            numMin.TabIndex = 5;
            numMin.KeyUp += numMin_KeyUp;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Dock = DockStyle.Fill;
            label1.Location = new Point(3, 100);
            label1.Name = "label1";
            label1.Size = new Size(134, 77);
            label1.TabIndex = 9;
            label1.Text = "Channel minimum";
            label1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Dock = DockStyle.Fill;
            label3.Location = new Point(3, 254);
            label3.Name = "label3";
            label3.Size = new Size(134, 77);
            label3.TabIndex = 11;
            label3.Text = "Channel maximum";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblCurrentValue
            // 
            lblCurrentValue.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(lblCurrentValue, 2);
            lblCurrentValue.Dock = DockStyle.Fill;
            lblCurrentValue.Font = new Font("Segoe UI", 18F, FontStyle.Regular, GraphicsUnit.Point);
            lblCurrentValue.Location = new Point(143, 0);
            lblCurrentValue.Name = "lblCurrentValue";
            lblCurrentValue.Size = new Size(506, 100);
            lblCurrentValue.TabIndex = 15;
            lblCurrentValue.Text = "0000";
            lblCurrentValue.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // ADCSetup
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(tableLayoutPanel1);
            Name = "ADCSetup";
            Size = new Size(753, 331);
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numMax).EndInit();
            ((System.ComponentModel.ISupportInitialize)numMid).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbMax).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbMid).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbMin).EndInit();
            ((System.ComponentModel.ISupportInitialize)numMin).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private Label label2;
        private TrackBar tbMax;
        private TrackBar tbMid;
        private TrackBar tbMin;
        private NumericUpDown numMin;
        private Label label1;
        private NumericUpDown numMax;
        private NumericUpDown numMid;
        private Label label3;
        private Label label4;
        private Label lblCurrentValue;
    }
}
