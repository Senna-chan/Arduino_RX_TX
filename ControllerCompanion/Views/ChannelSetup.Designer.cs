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
            tableLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 7;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 19.9999981F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 9.803922F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25.757576F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 6.56565666F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 7.154882F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 10.5882368F));
            tableLayoutPanel1.Controls.Add(cobOutputType, 6, 4);
            tableLayoutPanel1.Controls.Add(lblOutputMode, 5, 4);
            tableLayoutPanel1.Controls.Add(label3, 4, 4);
            tableLayoutPanel1.Controls.Add(lblChannelId, 1, 0);
            tableLayoutPanel1.Controls.Add(cobInput1, 6, 2);
            tableLayoutPanel1.Controls.Add(cobInput2, 6, 3);
            tableLayoutPanel1.Controls.Add(lblInput1, 5, 2);
            tableLayoutPanel1.Controls.Add(lblInput2, 5, 3);
            tableLayoutPanel1.Controls.Add(label1, 4, 2);
            tableLayoutPanel1.Controls.Add(label2, 4, 3);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 8;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 30F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 19.6916122F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 30F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 30F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 19.6916122F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 19.6916122F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 19.6916122F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 21.233551F));
            tableLayoutPanel1.Size = new Size(1188, 466);
            tableLayoutPanel1.TabIndex = 0;
            // 
            // cobOutputType
            // 
            cobOutputType.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            cobOutputType.FormattingEnabled = true;
            cobOutputType.Location = new Point(1062, 167);
            cobOutputType.Name = "cobOutputType";
            cobOutputType.Size = new Size(123, 23);
            cobOutputType.TabIndex = 9;
            // 
            // lblOutputMode
            // 
            lblOutputMode.AutoSize = true;
            lblOutputMode.Dock = DockStyle.Fill;
            lblOutputMode.Location = new Point(977, 164);
            lblOutputMode.Name = "lblOutputMode";
            lblOutputMode.Size = new Size(79, 74);
            lblOutputMode.TabIndex = 8;
            lblOutputMode.Text = "NONE";
            lblOutputMode.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Dock = DockStyle.Fill;
            label3.Location = new Point(899, 164);
            label3.Name = "label3";
            label3.Size = new Size(72, 74);
            label3.TabIndex = 7;
            label3.Text = "OutputType";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblChannelId
            // 
            lblChannelId.AutoSize = true;
            lblChannelId.Dock = DockStyle.Top;
            lblChannelId.Location = new Point(240, 0);
            lblChannelId.Name = "lblChannelId";
            lblChannelId.Size = new Size(110, 15);
            lblChannelId.TabIndex = 0;
            lblChannelId.Text = "Channel????";
            lblChannelId.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // cobInput1
            // 
            cobInput1.Dock = DockStyle.Fill;
            cobInput1.FormattingEnabled = true;
            cobInput1.Location = new Point(1062, 107);
            cobInput1.Name = "cobInput1";
            cobInput1.Size = new Size(123, 23);
            cobInput1.TabIndex = 1;
            // 
            // cobInput2
            // 
            cobInput2.Dock = DockStyle.Fill;
            cobInput2.FormattingEnabled = true;
            cobInput2.Location = new Point(1062, 137);
            cobInput2.Name = "cobInput2";
            cobInput2.Size = new Size(123, 23);
            cobInput2.TabIndex = 2;
            // 
            // lblInput1
            // 
            lblInput1.AutoSize = true;
            lblInput1.Dock = DockStyle.Fill;
            lblInput1.Location = new Point(977, 104);
            lblInput1.Name = "lblInput1";
            lblInput1.Size = new Size(79, 30);
            lblInput1.TabIndex = 3;
            lblInput1.Text = "NONE";
            lblInput1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // lblInput2
            // 
            lblInput2.AutoSize = true;
            lblInput2.Dock = DockStyle.Fill;
            lblInput2.Location = new Point(977, 134);
            lblInput2.Name = "lblInput2";
            lblInput2.Size = new Size(79, 30);
            lblInput2.TabIndex = 4;
            lblInput2.Text = "NONE";
            lblInput2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Dock = DockStyle.Fill;
            label1.Location = new Point(899, 104);
            label1.Name = "label1";
            label1.Size = new Size(72, 30);
            label1.TabIndex = 5;
            label1.Text = "Input 1";
            label1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Dock = DockStyle.Fill;
            label2.Location = new Point(899, 134);
            label2.Name = "label2";
            label2.Size = new Size(72, 30);
            label2.TabIndex = 6;
            label2.Text = "Input 2";
            label2.TextAlign = ContentAlignment.MiddleCenter;
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
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private Label lblChannelId;
        private ComboBox cobInput1;
        private ComboBox cobInput2;
        private Label lblInput1;
        private Label lblInput2;
        private Label label1;
        private Label label2;
        private ComboBox cobOutputType;
        private Label lblOutputMode;
        private Label label3;
    }
}
