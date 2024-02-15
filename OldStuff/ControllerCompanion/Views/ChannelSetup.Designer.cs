namespace ControllerCompanion.Views
{
    partial class ChannelSetup
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
            numSTEPMax = new NumericUpDown();
            lblSTEPMax = new Label();
            numSTEPMin = new NumericUpDown();
            lblSTEPMin = new Label();
            numPWMFreq = new NumericUpDown();
            lblPWMFreq = new Label();
            label6 = new Label();
            chbCenteredStick = new CheckBox();
            label5 = new Label();
            label4 = new Label();
            cobOutputType = new ComboBox();
            lblOutputMode = new Label();
            label3 = new Label();
            lblChannelId = new Label();
            cobInput1 = new ComboBox();
            cobInput2 = new ComboBox();
            lblInput1 = new Label();
            lblInput2 = new Label();
            label1 = new Label();
            label2 = new Label();
            numDefaultChannelValue = new NumericUpDown();
            chbReversedChannel = new CheckBox();
            tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numSTEPMax).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numSTEPMin).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numPWMFreq).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numDefaultChannelValue).BeginInit();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 7;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20.02598F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 9.816656F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20.0259781F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25.7910328F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 6.574185F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 7.164176F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 10.6019917F));
            tableLayoutPanel1.Controls.Add(numSTEPMax, 1, 5);
            tableLayoutPanel1.Controls.Add(lblSTEPMax, 1, 5);
            tableLayoutPanel1.Controls.Add(numSTEPMin, 2, 4);
            tableLayoutPanel1.Controls.Add(lblSTEPMin, 1, 4);
            tableLayoutPanel1.Controls.Add(numPWMFreq, 2, 3);
            tableLayoutPanel1.Controls.Add(lblPWMFreq, 1, 3);
            tableLayoutPanel1.Controls.Add(label6, 4, 7);
            tableLayoutPanel1.Controls.Add(chbCenteredStick, 6, 7);
            tableLayoutPanel1.Controls.Add(label5, 4, 6);
            tableLayoutPanel1.Controls.Add(label4, 4, 5);
            tableLayoutPanel1.Controls.Add(cobOutputType, 6, 4);
            tableLayoutPanel1.Controls.Add(lblOutputMode, 5, 4);
            tableLayoutPanel1.Controls.Add(label3, 4, 4);
            tableLayoutPanel1.Controls.Add(lblChannelId, 0, 0);
            tableLayoutPanel1.Controls.Add(cobInput1, 6, 2);
            tableLayoutPanel1.Controls.Add(cobInput2, 6, 3);
            tableLayoutPanel1.Controls.Add(lblInput1, 5, 2);
            tableLayoutPanel1.Controls.Add(lblInput2, 5, 3);
            tableLayoutPanel1.Controls.Add(label1, 4, 2);
            tableLayoutPanel1.Controls.Add(label2, 4, 3);
            tableLayoutPanel1.Controls.Add(numDefaultChannelValue, 6, 5);
            tableLayoutPanel1.Controls.Add(chbReversedChannel, 6, 6);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 11;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 30F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle());
            tableLayoutPanel1.Size = new Size(1188, 466);
            tableLayoutPanel1.TabIndex = 0;
            // 
            // numSTEPMax
            // 
            numSTEPMax.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numSTEPMax.Location = new Point(356, 193);
            numSTEPMax.Maximum = new decimal(new int[] { 2000, 0, 0, 0 });
            numSTEPMax.Name = "numSTEPMax";
            numSTEPMax.Size = new Size(231, 23);
            numSTEPMax.TabIndex = 22;
            // 
            // lblSTEPMax
            // 
            lblSTEPMax.AutoSize = true;
            lblSTEPMax.Dock = DockStyle.Fill;
            lblSTEPMax.Location = new Point(240, 190);
            lblSTEPMax.Name = "lblSTEPMax";
            lblSTEPMax.Size = new Size(110, 40);
            lblSTEPMax.TabIndex = 21;
            lblSTEPMax.Text = "Max Frequency";
            lblSTEPMax.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // numSTEPMin
            // 
            numSTEPMin.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numSTEPMin.Location = new Point(356, 153);
            numSTEPMin.Maximum = new decimal(new int[] { 2000, 0, 0, 0 });
            numSTEPMin.Name = "numSTEPMin";
            numSTEPMin.Size = new Size(231, 23);
            numSTEPMin.TabIndex = 20;
            // 
            // lblSTEPMin
            // 
            lblSTEPMin.AutoSize = true;
            lblSTEPMin.Dock = DockStyle.Fill;
            lblSTEPMin.Location = new Point(240, 150);
            lblSTEPMin.Name = "lblSTEPMin";
            lblSTEPMin.Size = new Size(110, 40);
            lblSTEPMin.TabIndex = 19;
            lblSTEPMin.Text = "Min Frequency";
            lblSTEPMin.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // numPWMFreq
            // 
            numPWMFreq.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numPWMFreq.Location = new Point(356, 113);
            numPWMFreq.Maximum = new decimal(new int[] { 2000, 0, 0, 0 });
            numPWMFreq.Name = "numPWMFreq";
            numPWMFreq.Size = new Size(231, 23);
            numPWMFreq.TabIndex = 18;
            // 
            // lblPWMFreq
            // 
            lblPWMFreq.AutoSize = true;
            lblPWMFreq.Dock = DockStyle.Fill;
            lblPWMFreq.Location = new Point(240, 110);
            lblPWMFreq.Name = "lblPWMFreq";
            lblPWMFreq.Size = new Size(110, 40);
            lblPWMFreq.TabIndex = 17;
            lblPWMFreq.Text = "Frequency";
            lblPWMFreq.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            label6.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(label6, 2);
            label6.Dock = DockStyle.Fill;
            label6.Location = new Point(899, 270);
            label6.Name = "label6";
            label6.Size = new Size(157, 40);
            label6.TabIndex = 16;
            label6.Text = "Centered stick";
            label6.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // chbCenteredStick
            // 
            chbCenteredStick.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            chbCenteredStick.AutoSize = true;
            chbCenteredStick.Location = new Point(1062, 273);
            chbCenteredStick.Name = "chbCenteredStick";
            chbCenteredStick.Size = new Size(123, 34);
            chbCenteredStick.TabIndex = 15;
            chbCenteredStick.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            label5.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(label5, 2);
            label5.Dock = DockStyle.Fill;
            label5.Location = new Point(899, 230);
            label5.Name = "label5";
            label5.Size = new Size(157, 40);
            label5.TabIndex = 12;
            label5.Text = "Channel reversed";
            label5.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            label4.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(label4, 2);
            label4.Dock = DockStyle.Fill;
            label4.Location = new Point(899, 190);
            label4.Name = "label4";
            label4.Size = new Size(157, 40);
            label4.TabIndex = 10;
            label4.Text = "Default Value";
            label4.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // cobOutputType
            // 
            cobOutputType.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            cobOutputType.FormattingEnabled = true;
            cobOutputType.Location = new Point(1062, 153);
            cobOutputType.Name = "cobOutputType";
            cobOutputType.Size = new Size(123, 23);
            cobOutputType.TabIndex = 9;
            // 
            // lblOutputMode
            // 
            lblOutputMode.AutoSize = true;
            lblOutputMode.Dock = DockStyle.Fill;
            lblOutputMode.Location = new Point(977, 150);
            lblOutputMode.Name = "lblOutputMode";
            lblOutputMode.Size = new Size(79, 40);
            lblOutputMode.TabIndex = 8;
            lblOutputMode.Text = "NONE";
            lblOutputMode.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Dock = DockStyle.Fill;
            label3.Location = new Point(899, 150);
            label3.Name = "label3";
            label3.Size = new Size(72, 40);
            label3.TabIndex = 7;
            label3.Text = "OutputType";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblChannelId
            // 
            lblChannelId.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(lblChannelId, 7);
            lblChannelId.Dock = DockStyle.Top;
            lblChannelId.Location = new Point(3, 0);
            lblChannelId.Name = "lblChannelId";
            lblChannelId.Size = new Size(1182, 15);
            lblChannelId.TabIndex = 0;
            lblChannelId.Text = "Channel????";
            lblChannelId.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // cobInput1
            // 
            cobInput1.Dock = DockStyle.Fill;
            cobInput1.FormattingEnabled = true;
            cobInput1.Location = new Point(1062, 73);
            cobInput1.Name = "cobInput1";
            cobInput1.Size = new Size(123, 23);
            cobInput1.TabIndex = 1;
            // 
            // cobInput2
            // 
            cobInput2.Dock = DockStyle.Fill;
            cobInput2.FormattingEnabled = true;
            cobInput2.Location = new Point(1062, 113);
            cobInput2.Name = "cobInput2";
            cobInput2.Size = new Size(123, 23);
            cobInput2.TabIndex = 2;
            // 
            // lblInput1
            // 
            lblInput1.AutoSize = true;
            lblInput1.Dock = DockStyle.Fill;
            lblInput1.Location = new Point(977, 70);
            lblInput1.Name = "lblInput1";
            lblInput1.Size = new Size(79, 40);
            lblInput1.TabIndex = 3;
            lblInput1.Text = "NONE";
            lblInput1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblInput2
            // 
            lblInput2.AutoSize = true;
            lblInput2.Dock = DockStyle.Fill;
            lblInput2.Location = new Point(977, 110);
            lblInput2.Name = "lblInput2";
            lblInput2.Size = new Size(79, 40);
            lblInput2.TabIndex = 4;
            lblInput2.Text = "NONE";
            lblInput2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Dock = DockStyle.Fill;
            label1.Location = new Point(899, 70);
            label1.Name = "label1";
            label1.Size = new Size(72, 40);
            label1.TabIndex = 5;
            label1.Text = "Input 1";
            label1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Dock = DockStyle.Fill;
            label2.Location = new Point(899, 110);
            label2.Name = "label2";
            label2.Size = new Size(72, 40);
            label2.TabIndex = 6;
            label2.Text = "Input 2";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // numDefaultChannelValue
            // 
            numDefaultChannelValue.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numDefaultChannelValue.Location = new Point(1062, 193);
            numDefaultChannelValue.Maximum = new decimal(new int[] { 2000, 0, 0, 0 });
            numDefaultChannelValue.Name = "numDefaultChannelValue";
            numDefaultChannelValue.Size = new Size(123, 23);
            numDefaultChannelValue.TabIndex = 11;
            // 
            // chbReversedChannel
            // 
            chbReversedChannel.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            chbReversedChannel.AutoSize = true;
            chbReversedChannel.Location = new Point(1062, 233);
            chbReversedChannel.Name = "chbReversedChannel";
            chbReversedChannel.Size = new Size(123, 34);
            chbReversedChannel.TabIndex = 13;
            chbReversedChannel.UseVisualStyleBackColor = true;
            // 
            // ChannelSetup
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(tableLayoutPanel1);
            Name = "ChannelSetup";
            Size = new Size(1188, 466);
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numSTEPMax).EndInit();
            ((System.ComponentModel.ISupportInitialize)numSTEPMin).EndInit();
            ((System.ComponentModel.ISupportInitialize)numPWMFreq).EndInit();
            ((System.ComponentModel.ISupportInitialize)numDefaultChannelValue).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private Label lblChannelId;
        private Label label1;
        private Label label2;
        private Label label3;
        private ComboBox cobOutputType;
        private Label lblOutputMode;
        private ComboBox cobInput1;
        private ComboBox cobInput2;
        private Label lblInput1;
        private Label lblInput2;
        private Label label4;
        private CheckBox chbCenteredStick;
        private Label label5;
        private NumericUpDown numDefaultChannelValue;
        private CheckBox chbReversedChannel;
        private Label label6;
        private NumericUpDown numSTEPMax;
        private Label lblSTEPMax;
        private NumericUpDown numSTEPMin;
        private Label lblSTEPMin;
        private NumericUpDown numPWMFreq;
        private Label lblPWMFreq;
    }
}
