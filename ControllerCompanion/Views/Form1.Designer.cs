namespace ControllerCompanion.Views
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            tcOptions = new TabControl();
            tpADCSetup = new TabPage();
            tcADCChannels = new TabControl();
            tpChannelSetup = new TabPage();
            tcRCChannels = new TabControl();
            tpADCData = new TabPage();
            adcData1 = new ADCData();
            tpRCData = new TabPage();
            rcData1 = new RCData();
            tpAuxData = new TabPage();
            auxData1 = new AUXData();
            statStip = new StatusStrip();
            toolStripStatusLabel1 = new ToolStripStatusLabel();
            tslblComPort = new ToolStripStatusLabel();
            menuMain = new MenuStrip();
            fileToolStripMenuItem = new ToolStripMenuItem();
            loadFromFileToolStripMenuItem = new ToolStripMenuItem();
            saveToFileToolStripMenuItem = new ToolStripMenuItem();
            toolStripSeparator1 = new ToolStripSeparator();
            quitToolStripMenuItem = new ToolStripMenuItem();
            modelToolStripMenuItem = new ToolStripMenuItem();
            transmitterToolStripMenuItem = new ToolStripMenuItem();
            connectToTXToolStripMenuItem = new ToolStripMenuItem();
            disconnectFromTXToolStripMenuItem = new ToolStripMenuItem();
            reconnectToTXToolStripMenuItem = new ToolStripMenuItem();
            readFromTXToolStripMenuItem = new ToolStripMenuItem();
            writeToTXToolStripMenuItem = new ToolStripMenuItem();
            miscToolStripMenuItem = new ToolStripMenuItem();
            realtimeChannelDataToolStripMenuItem = new ToolStripMenuItem();
            tableLayoutPanel1 = new TableLayoutPanel();
            tcOptions.SuspendLayout();
            tpADCSetup.SuspendLayout();
            tpChannelSetup.SuspendLayout();
            tpADCData.SuspendLayout();
            tpRCData.SuspendLayout();
            tpAuxData.SuspendLayout();
            statStip.SuspendLayout();
            menuMain.SuspendLayout();
            tableLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // tcOptions
            // 
            tcOptions.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            tcOptions.Controls.Add(tpADCSetup);
            tcOptions.Controls.Add(tpChannelSetup);
            tcOptions.Controls.Add(tpADCData);
            tcOptions.Controls.Add(tpRCData);
            tcOptions.Controls.Add(tpAuxData);
            tcOptions.Location = new Point(3, 3);
            tcOptions.Name = "tcOptions";
            tableLayoutPanel1.SetRowSpan(tcOptions, 3);
            tcOptions.SelectedIndex = 0;
            tcOptions.Size = new Size(1340, 496);
            tcOptions.TabIndex = 0;
            tcOptions.SelectedIndexChanged += tcOptions_SelectedIndexChanged;
            // 
            // tpADCSetup
            // 
            tpADCSetup.Controls.Add(tcADCChannels);
            tpADCSetup.Location = new Point(4, 24);
            tpADCSetup.Name = "tpADCSetup";
            tpADCSetup.Padding = new Padding(3);
            tpADCSetup.Size = new Size(1332, 468);
            tpADCSetup.TabIndex = 0;
            tpADCSetup.Text = "ADC Setup";
            tpADCSetup.UseVisualStyleBackColor = true;
            // 
            // tcADCChannels
            // 
            tcADCChannels.Dock = DockStyle.Fill;
            tcADCChannels.Location = new Point(3, 3);
            tcADCChannels.Name = "tcADCChannels";
            tcADCChannels.SelectedIndex = 0;
            tcADCChannels.Size = new Size(1326, 462);
            tcADCChannels.TabIndex = 0;
            // 
            // tpChannelSetup
            // 
            tpChannelSetup.Controls.Add(tcRCChannels);
            tpChannelSetup.Location = new Point(4, 24);
            tpChannelSetup.Name = "tpChannelSetup";
            tpChannelSetup.Padding = new Padding(3);
            tpChannelSetup.Size = new Size(1332, 468);
            tpChannelSetup.TabIndex = 1;
            tpChannelSetup.Text = "Channel Setup";
            tpChannelSetup.UseVisualStyleBackColor = true;
            // 
            // tcRCChannels
            // 
            tcRCChannels.Dock = DockStyle.Fill;
            tcRCChannels.Location = new Point(3, 3);
            tcRCChannels.Name = "tcRCChannels";
            tcRCChannels.SelectedIndex = 0;
            tcRCChannels.Size = new Size(1326, 462);
            tcRCChannels.TabIndex = 1;
            tcRCChannels.SelectedIndexChanged += tcRCChannels_SelectedIndexChanged;
            // 
            // tpADCData
            // 
            tpADCData.Controls.Add(adcData1);
            tpADCData.Location = new Point(4, 24);
            tpADCData.Name = "tpADCData";
            tpADCData.Padding = new Padding(3);
            tpADCData.Size = new Size(1332, 468);
            tpADCData.TabIndex = 2;
            tpADCData.Text = "ADC Data";
            tpADCData.UseVisualStyleBackColor = true;
            // 
            // adcData1
            // 
            adcData1.Dock = DockStyle.Fill;
            adcData1.Location = new Point(3, 3);
            adcData1.Name = "adcData1";
            adcData1.Size = new Size(1326, 462);
            adcData1.TabIndex = 0;
            // 
            // tpRCData
            // 
            tpRCData.Controls.Add(rcData1);
            tpRCData.Location = new Point(4, 24);
            tpRCData.Name = "tpRCData";
            tpRCData.Padding = new Padding(3);
            tpRCData.Size = new Size(1332, 468);
            tpRCData.TabIndex = 3;
            tpRCData.Text = "RC Data";
            tpRCData.UseVisualStyleBackColor = true;
            // 
            // rcData1
            // 
            rcData1.Dock = DockStyle.Fill;
            rcData1.Location = new Point(3, 3);
            rcData1.Name = "rcData1";
            rcData1.Size = new Size(1326, 462);
            rcData1.TabIndex = 0;
            // 
            // tpAuxData
            // 
            tpAuxData.Controls.Add(auxData1);
            tpAuxData.Location = new Point(4, 24);
            tpAuxData.Name = "tpAuxData";
            tpAuxData.Padding = new Padding(3);
            tpAuxData.Size = new Size(1332, 468);
            tpAuxData.TabIndex = 4;
            tpAuxData.Text = "AUX Data";
            tpAuxData.UseVisualStyleBackColor = true;
            // 
            // auxData1
            // 
            auxData1.Dock = DockStyle.Fill;
            auxData1.Location = new Point(3, 3);
            auxData1.Name = "auxData1";
            auxData1.Size = new Size(1326, 462);
            auxData1.TabIndex = 0;
            // 
            // statStip
            // 
            statStip.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel1, tslblComPort });
            statStip.Location = new Point(0, 526);
            statStip.Name = "statStip";
            statStip.Size = new Size(1346, 22);
            statStip.TabIndex = 1;
            statStip.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            toolStripStatusLabel1.Size = new Size(60, 17);
            toolStripStatusLabel1.Text = "COMPort:";
            // 
            // tslblComPort
            // 
            tslblComPort.Name = "tslblComPort";
            tslblComPort.Size = new Size(86, 17);
            tslblComPort.Text = "Not connected";
            // 
            // menuMain
            // 
            menuMain.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, modelToolStripMenuItem, transmitterToolStripMenuItem, miscToolStripMenuItem });
            menuMain.Location = new Point(0, 0);
            menuMain.Name = "menuMain";
            menuMain.Size = new Size(1346, 24);
            menuMain.TabIndex = 2;
            menuMain.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { loadFromFileToolStripMenuItem, saveToFileToolStripMenuItem, toolStripSeparator1, quitToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(37, 20);
            fileToolStripMenuItem.Text = "File";
            // 
            // loadFromFileToolStripMenuItem
            // 
            loadFromFileToolStripMenuItem.Name = "loadFromFileToolStripMenuItem";
            loadFromFileToolStripMenuItem.Size = new Size(187, 22);
            loadFromFileToolStripMenuItem.Text = "Load setting from file";
            loadFromFileToolStripMenuItem.Click += loadFromFileToolStripMenuItem_Click;
            // 
            // saveToFileToolStripMenuItem
            // 
            saveToFileToolStripMenuItem.Name = "saveToFileToolStripMenuItem";
            saveToFileToolStripMenuItem.Size = new Size(187, 22);
            saveToFileToolStripMenuItem.Text = "Save settings to file";
            saveToFileToolStripMenuItem.Click += saveToFileToolStripMenuItem_Click;
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new Size(184, 6);
            // 
            // quitToolStripMenuItem
            // 
            quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            quitToolStripMenuItem.Size = new Size(187, 22);
            quitToolStripMenuItem.Text = "Quit";
            quitToolStripMenuItem.Click += quitToolStripMenuItem_Click;
            // 
            // modelToolStripMenuItem
            // 
            modelToolStripMenuItem.Name = "modelToolStripMenuItem";
            modelToolStripMenuItem.Size = new Size(53, 20);
            modelToolStripMenuItem.Text = "Model";
            // 
            // transmitterToolStripMenuItem
            // 
            transmitterToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { connectToTXToolStripMenuItem, disconnectFromTXToolStripMenuItem, reconnectToTXToolStripMenuItem, readFromTXToolStripMenuItem, writeToTXToolStripMenuItem });
            transmitterToolStripMenuItem.Name = "transmitterToolStripMenuItem";
            transmitterToolStripMenuItem.Size = new Size(78, 20);
            transmitterToolStripMenuItem.Text = "Transmitter";
            // 
            // connectToTXToolStripMenuItem
            // 
            connectToTXToolStripMenuItem.Name = "connectToTXToolStripMenuItem";
            connectToTXToolStripMenuItem.Size = new Size(180, 22);
            connectToTXToolStripMenuItem.Text = "Connect to TX";
            connectToTXToolStripMenuItem.Click += connectToTXToolStripMenuItem_Click;
            // 
            // disconnectFromTXToolStripMenuItem
            // 
            disconnectFromTXToolStripMenuItem.Name = "disconnectFromTXToolStripMenuItem";
            disconnectFromTXToolStripMenuItem.Size = new Size(180, 22);
            disconnectFromTXToolStripMenuItem.Text = "Disconnect from TX";
            disconnectFromTXToolStripMenuItem.Visible = false;
            // 
            // reconnectToTXToolStripMenuItem
            // 
            reconnectToTXToolStripMenuItem.Name = "reconnectToTXToolStripMenuItem";
            reconnectToTXToolStripMenuItem.Size = new Size(180, 22);
            reconnectToTXToolStripMenuItem.Text = "Reconnect to TX";
            reconnectToTXToolStripMenuItem.Visible = false;
            // 
            // readFromTXToolStripMenuItem
            // 
            readFromTXToolStripMenuItem.Name = "readFromTXToolStripMenuItem";
            readFromTXToolStripMenuItem.Size = new Size(180, 22);
            readFromTXToolStripMenuItem.Text = "Read settings";
            readFromTXToolStripMenuItem.Visible = false;
            // 
            // writeToTXToolStripMenuItem
            // 
            writeToTXToolStripMenuItem.Name = "writeToTXToolStripMenuItem";
            writeToTXToolStripMenuItem.Size = new Size(180, 22);
            writeToTXToolStripMenuItem.Text = "Write settings";
            writeToTXToolStripMenuItem.Visible = false;
            // 
            // miscToolStripMenuItem
            // 
            miscToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { realtimeChannelDataToolStripMenuItem });
            miscToolStripMenuItem.Name = "miscToolStripMenuItem";
            miscToolStripMenuItem.Size = new Size(44, 20);
            miscToolStripMenuItem.Text = "Misc";
            // 
            // realtimeChannelDataToolStripMenuItem
            // 
            realtimeChannelDataToolStripMenuItem.CheckOnClick = true;
            realtimeChannelDataToolStripMenuItem.Name = "realtimeChannelDataToolStripMenuItem";
            realtimeChannelDataToolStripMenuItem.Size = new Size(191, 22);
            realtimeChannelDataToolStripMenuItem.Text = "Realtime channel data";
            realtimeChannelDataToolStripMenuItem.Click += realtimeChannelDataToolStripMenuItem_Click;
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 1;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.Controls.Add(tcOptions, 0, 0);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 24);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 3;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 2F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 2F));
            tableLayoutPanel1.Size = new Size(1346, 502);
            tableLayoutPanel1.TabIndex = 2;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1346, 548);
            Controls.Add(tableLayoutPanel1);
            Controls.Add(statStip);
            Controls.Add(menuMain);
            MainMenuStrip = menuMain;
            Name = "Form1";
            Text = "Controller Companion";
            tcOptions.ResumeLayout(false);
            tpADCSetup.ResumeLayout(false);
            tpChannelSetup.ResumeLayout(false);
            tpADCData.ResumeLayout(false);
            tpRCData.ResumeLayout(false);
            tpAuxData.ResumeLayout(false);
            statStip.ResumeLayout(false);
            statStip.PerformLayout();
            menuMain.ResumeLayout(false);
            menuMain.PerformLayout();
            tableLayoutPanel1.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TabControl tcOptions;
        private TabPage tpADCSetup;
        private TabControl tcADCChannels;
        private TabPage tpChannelSetup;
        private StatusStrip statStip;
        private MenuStrip menuMain;
        private ToolStripStatusLabel toolStripStatusLabel1;
        private ToolStripStatusLabel tslblComPort;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem loadFromFileToolStripMenuItem;
        private ToolStripMenuItem saveToFileToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem quitToolStripMenuItem;
        private TableLayoutPanel tableLayoutPanel1;
        private TabControl tcRCChannels;
        private ToolStripMenuItem modelToolStripMenuItem;
        private TabPage tpADCData;
        private TabPage tpRCData;
        private TabPage tpAuxData;
        private ADCData adcData1;
        private AUXData auxData1;
        private RCData rcData1;
        private ToolStripMenuItem transmitterToolStripMenuItem;
        private ToolStripMenuItem disconnectFromTXToolStripMenuItem;
        private ToolStripMenuItem reconnectToTXToolStripMenuItem;
        private ToolStripMenuItem readFromTXToolStripMenuItem;
        private ToolStripMenuItem writeToTXToolStripMenuItem;
        private ToolStripMenuItem miscToolStripMenuItem;
        private ToolStripMenuItem realtimeChannelDataToolStripMenuItem;
        private ToolStripMenuItem connectToTXToolStripMenuItem;
    }
}