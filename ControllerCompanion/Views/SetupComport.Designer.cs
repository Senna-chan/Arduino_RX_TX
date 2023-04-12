
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
            this.lbxComPorts = new System.Windows.Forms.ListBox();
            this.btnOpenComPort = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbxComPorts
            // 
            this.lbxComPorts.FormattingEnabled = true;
            this.lbxComPorts.Location = new System.Drawing.Point(13, 13);
            this.lbxComPorts.Name = "lbxComPorts";
            this.lbxComPorts.Size = new System.Drawing.Size(315, 121);
            this.lbxComPorts.TabIndex = 0;
            // 
            // btnOpenComPort
            // 
            this.btnOpenComPort.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btnOpenComPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.btnOpenComPort.Location = new System.Drawing.Point(0, 162);
            this.btnOpenComPort.Name = "btnOpenComPort";
            this.btnOpenComPort.Size = new System.Drawing.Size(340, 38);
            this.btnOpenComPort.TabIndex = 1;
            this.btnOpenComPort.Text = "Open COM Port";
            this.btnOpenComPort.UseVisualStyleBackColor = true;
            this.btnOpenComPort.Click += new System.EventHandler(this.btnOpenComPort_Click);
            // 
            // SetupComport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(340, 200);
            this.Controls.Add(this.btnOpenComPort);
            this.Controls.Add(this.lbxComPorts);
            this.Name = "SetupComport";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lbxComPorts;
        private System.Windows.Forms.Button btnOpenComPort;
    }
}

