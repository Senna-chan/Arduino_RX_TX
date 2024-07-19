namespace ControllerCompanion.Views
{
    partial class SwitchSettings
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
            label5 = new Label();
            cobOutputIO = new ComboBox();
            lblOutputInput = new Label();
            btnDetectOutputEnableIO = new Button();
            label4 = new Label();
            cobLimitSide = new ComboBox();
            label3 = new Label();
            label2 = new Label();
            label1 = new Label();
            btnDetectRateInput2 = new Button();
            cobRateInput1 = new ComboBox();
            cobRateInput2 = new ComboBox();
            lblRateInput1 = new Label();
            lblRateInput2 = new Label();
            btnDetectRateInput1 = new Button();
            numOutputMin = new NumericUpDown();
            numOutputMid = new NumericUpDown();
            numOutputMax = new NumericUpDown();
            lbOutputsToEnabled = new ListBox();
            cobChannelToRateLimit = new ComboBox();
            tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numOutputMin).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numOutputMid).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numOutputMax).BeginInit();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 7;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3351593F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3351612F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3351612F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3315048F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3315048F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 13.3315048F));
            tableLayoutPanel1.Controls.Add(label5, 5, 7);
            tableLayoutPanel1.Controls.Add(cobOutputIO, 2, 2);
            tableLayoutPanel1.Controls.Add(lblOutputInput, 1, 2);
            tableLayoutPanel1.Controls.Add(btnDetectOutputEnableIO, 0, 2);
            tableLayoutPanel1.Controls.Add(label4, 0, 1);
            tableLayoutPanel1.Controls.Add(cobLimitSide, 6, 6);
            tableLayoutPanel1.Controls.Add(label3, 5, 6);
            tableLayoutPanel1.Controls.Add(label2, 5, 4);
            tableLayoutPanel1.Controls.Add(label1, 4, 1);
            tableLayoutPanel1.Controls.Add(btnDetectRateInput2, 4, 3);
            tableLayoutPanel1.Controls.Add(cobRateInput1, 6, 2);
            tableLayoutPanel1.Controls.Add(cobRateInput2, 6, 3);
            tableLayoutPanel1.Controls.Add(lblRateInput1, 5, 2);
            tableLayoutPanel1.Controls.Add(lblRateInput2, 5, 3);
            tableLayoutPanel1.Controls.Add(btnDetectRateInput1, 4, 2);
            tableLayoutPanel1.Controls.Add(numOutputMin, 4, 5);
            tableLayoutPanel1.Controls.Add(numOutputMid, 5, 5);
            tableLayoutPanel1.Controls.Add(numOutputMax, 6, 5);
            tableLayoutPanel1.Controls.Add(lbOutputsToEnabled, 1, 3);
            tableLayoutPanel1.Controls.Add(cobChannelToRateLimit, 6, 7);
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
            tableLayoutPanel1.Size = new Size(1106, 442);
            tableLayoutPanel1.TabIndex = 1;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Dock = DockStyle.Fill;
            label5.Location = new Point(812, 270);
            label5.Name = "label5";
            label5.Size = new Size(141, 40);
            label5.TabIndex = 39;
            label5.Text = "Channel to limit";
            label5.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // cobOutputIO
            // 
            cobOutputIO.Dock = DockStyle.Fill;
            cobOutputIO.FormattingEnabled = true;
            cobOutputIO.Location = new Point(297, 73);
            cobOutputIO.Name = "cobOutputIO";
            cobOutputIO.Size = new Size(141, 23);
            cobOutputIO.TabIndex = 34;
            // 
            // lblOutputInput
            // 
            lblOutputInput.AutoSize = true;
            lblOutputInput.Dock = DockStyle.Fill;
            lblOutputInput.Location = new Point(150, 70);
            lblOutputInput.Name = "lblOutputInput";
            lblOutputInput.Size = new Size(141, 40);
            lblOutputInput.TabIndex = 35;
            lblOutputInput.Text = "NONE";
            lblOutputInput.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // btnDetectOutputEnableIO
            // 
            btnDetectOutputEnableIO.Dock = DockStyle.Fill;
            btnDetectOutputEnableIO.Location = new Point(3, 73);
            btnDetectOutputEnableIO.Name = "btnDetectOutputEnableIO";
            btnDetectOutputEnableIO.Size = new Size(141, 34);
            btnDetectOutputEnableIO.TabIndex = 36;
            btnDetectOutputEnableIO.Text = "Enable Input";
            btnDetectOutputEnableIO.UseVisualStyleBackColor = true;
            btnDetectOutputEnableIO.Click += btnDetectOutputEnableIO_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(label4, 3);
            label4.Dock = DockStyle.Fill;
            label4.Location = new Point(3, 30);
            label4.Name = "label4";
            label4.Size = new Size(435, 40);
            label4.TabIndex = 33;
            label4.Text = "OutputEnable Config";
            label4.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // cobLimitSide
            // 
            cobLimitSide.Dock = DockStyle.Fill;
            cobLimitSide.FormattingEnabled = true;
            cobLimitSide.Location = new Point(959, 233);
            cobLimitSide.Name = "cobLimitSide";
            cobLimitSide.Size = new Size(144, 23);
            cobLimitSide.TabIndex = 32;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Dock = DockStyle.Fill;
            label3.Location = new Point(812, 230);
            label3.Name = "label3";
            label3.Size = new Size(141, 40);
            label3.TabIndex = 31;
            label3.Text = "LimitSide";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Dock = DockStyle.Fill;
            label2.Location = new Point(812, 150);
            label2.Name = "label2";
            label2.Size = new Size(141, 40);
            label2.TabIndex = 30;
            label2.Text = "OutputLimits";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            label1.AutoSize = true;
            tableLayoutPanel1.SetColumnSpan(label1, 3);
            label1.Dock = DockStyle.Fill;
            label1.Location = new Point(665, 30);
            label1.Name = "label1";
            label1.Size = new Size(438, 40);
            label1.TabIndex = 25;
            label1.Text = "Ratelimit Config";
            label1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // btnDetectRateInput2
            // 
            btnDetectRateInput2.Dock = DockStyle.Fill;
            btnDetectRateInput2.Location = new Point(665, 113);
            btnDetectRateInput2.Name = "btnDetectRateInput2";
            btnDetectRateInput2.Size = new Size(141, 34);
            btnDetectRateInput2.TabIndex = 24;
            btnDetectRateInput2.Text = "Rate Input 2";
            btnDetectRateInput2.UseVisualStyleBackColor = true;
            btnDetectRateInput2.Click += btnDetectRateInput2_Click;
            // 
            // cobRateInput1
            // 
            cobRateInput1.Dock = DockStyle.Fill;
            cobRateInput1.FormattingEnabled = true;
            cobRateInput1.Location = new Point(959, 73);
            cobRateInput1.Name = "cobRateInput1";
            cobRateInput1.Size = new Size(144, 23);
            cobRateInput1.TabIndex = 1;
            // 
            // cobRateInput2
            // 
            cobRateInput2.Dock = DockStyle.Fill;
            cobRateInput2.FormattingEnabled = true;
            cobRateInput2.Location = new Point(959, 113);
            cobRateInput2.Name = "cobRateInput2";
            cobRateInput2.Size = new Size(144, 23);
            cobRateInput2.TabIndex = 2;
            // 
            // lblRateInput1
            // 
            lblRateInput1.AutoSize = true;
            lblRateInput1.Dock = DockStyle.Fill;
            lblRateInput1.Location = new Point(812, 70);
            lblRateInput1.Name = "lblRateInput1";
            lblRateInput1.Size = new Size(141, 40);
            lblRateInput1.TabIndex = 3;
            lblRateInput1.Text = "NONE";
            lblRateInput1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblRateInput2
            // 
            lblRateInput2.AutoSize = true;
            lblRateInput2.Dock = DockStyle.Fill;
            lblRateInput2.Location = new Point(812, 110);
            lblRateInput2.Name = "lblRateInput2";
            lblRateInput2.Size = new Size(141, 40);
            lblRateInput2.TabIndex = 4;
            lblRateInput2.Text = "NONE";
            lblRateInput2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // btnDetectRateInput1
            // 
            btnDetectRateInput1.Dock = DockStyle.Fill;
            btnDetectRateInput1.Location = new Point(665, 73);
            btnDetectRateInput1.Name = "btnDetectRateInput1";
            btnDetectRateInput1.Size = new Size(141, 34);
            btnDetectRateInput1.TabIndex = 23;
            btnDetectRateInput1.Text = "Rate Input 1";
            btnDetectRateInput1.UseVisualStyleBackColor = true;
            btnDetectRateInput1.Click += btnDetectRateInput1_Click;
            // 
            // numOutputMin
            // 
            numOutputMin.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numOutputMin.Location = new Point(665, 193);
            numOutputMin.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            numOutputMin.Name = "numOutputMin";
            numOutputMin.Size = new Size(141, 23);
            numOutputMin.TabIndex = 27;
            numOutputMin.Value = new decimal(new int[] { 30, 0, 0, 0 });
            // 
            // numOutputMid
            // 
            numOutputMid.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numOutputMid.Location = new Point(812, 193);
            numOutputMid.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            numOutputMid.Name = "numOutputMid";
            numOutputMid.Size = new Size(141, 23);
            numOutputMid.TabIndex = 28;
            numOutputMid.Value = new decimal(new int[] { 60, 0, 0, 0 });
            // 
            // numOutputMax
            // 
            numOutputMax.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            numOutputMax.Location = new Point(959, 193);
            numOutputMax.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            numOutputMax.Name = "numOutputMax";
            numOutputMax.Size = new Size(144, 23);
            numOutputMax.TabIndex = 29;
            numOutputMax.Value = new decimal(new int[] { 100, 0, 0, 0 });
            // 
            // lbOutputsToEnabled
            // 
            tableLayoutPanel1.SetColumnSpan(lbOutputsToEnabled, 2);
            lbOutputsToEnabled.Dock = DockStyle.Fill;
            lbOutputsToEnabled.FormattingEnabled = true;
            lbOutputsToEnabled.ItemHeight = 15;
            lbOutputsToEnabled.Location = new Point(150, 113);
            lbOutputsToEnabled.Name = "lbOutputsToEnabled";
            tableLayoutPanel1.SetRowSpan(lbOutputsToEnabled, 6);
            lbOutputsToEnabled.SelectionMode = SelectionMode.MultiSimple;
            lbOutputsToEnabled.Size = new Size(288, 234);
            lbOutputsToEnabled.TabIndex = 37;
            // 
            // cobChannelToRateLimit
            // 
            cobChannelToRateLimit.Dock = DockStyle.Fill;
            cobChannelToRateLimit.FormattingEnabled = true;
            cobChannelToRateLimit.Location = new Point(959, 273);
            cobChannelToRateLimit.Name = "cobChannelToRateLimit";
            cobChannelToRateLimit.Size = new Size(144, 23);
            cobChannelToRateLimit.TabIndex = 40;
            // 
            // SwitchSettings
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(tableLayoutPanel1);
            Name = "SwitchSettings";
            Size = new Size(1106, 442);
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numOutputMin).EndInit();
            ((System.ComponentModel.ISupportInitialize)numOutputMid).EndInit();
            ((System.ComponentModel.ISupportInitialize)numOutputMax).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private Label label1;
        private Button btnDetectRateInput2;
        private ComboBox cobRateInput1;
        private ComboBox cobRateInput2;
        private Label lblRateInput1;
        private Label lblRateInput2;
        private Button btnDetectRateInput1;
        private ComboBox cobOutputIO;
        private Label lblOutputInput;
        private Button btnDetectOutputEnableIO;
        private Label label4;
        private ComboBox cobLimitSide;
        private Label label3;
        private Label label2;
        private NumericUpDown numOutputMin;
        private NumericUpDown numOutputMid;
        private NumericUpDown numOutputMax;
        private ListBox lbOutputsToEnabled;
        private Label label5;
        private ComboBox cobChannelToRateLimit;
    }
}
