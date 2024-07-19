
namespace ControllerCompanion.Views
{
    partial class SetupComport
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            lbxComPorts = new ListBox();
            btnOpenComPort = new Button();
            SuspendLayout();
            // 
            // lbxComPorts
            // 
            lbxComPorts.FormattingEnabled = true;
            lbxComPorts.ItemHeight = 15;
            lbxComPorts.Location = new Point(15, 15);
            lbxComPorts.Margin = new Padding(4, 3, 4, 3);
            lbxComPorts.Name = "lbxComPorts";
            lbxComPorts.Size = new Size(367, 139);
            lbxComPorts.TabIndex = 0;
            lbxComPorts.KeyUp += lbxComPorts_KeyUp;
            // 
            // btnOpenComPort
            // 
            btnOpenComPort.Dock = DockStyle.Bottom;
            btnOpenComPort.Font = new Font("Microsoft Sans Serif", 10F, FontStyle.Regular, GraphicsUnit.Point);
            btnOpenComPort.Location = new Point(0, 187);
            btnOpenComPort.Margin = new Padding(4, 3, 4, 3);
            btnOpenComPort.Name = "btnOpenComPort";
            btnOpenComPort.Size = new Size(397, 44);
            btnOpenComPort.TabIndex = 1;
            btnOpenComPort.Text = "Open COM Port";
            btnOpenComPort.UseVisualStyleBackColor = true;
            btnOpenComPort.Click += btnOpenComPort_Click;
            // 
            // SetupComport
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(397, 231);
            Controls.Add(btnOpenComPort);
            Controls.Add(lbxComPorts);
            Margin = new Padding(4, 3, 4, 3);
            Name = "SetupComport";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.ListBox lbxComPorts;
        private System.Windows.Forms.Button btnOpenComPort;
    }
}

