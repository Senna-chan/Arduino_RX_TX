using ControllerCompanion.Structs;
using System.IO.Ports;
using System.Text;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ControllerCompanion.Views
{
    public partial class Form1 : Form
    {
        Dictionary<int, ADCSetup> adcSetups = new Dictionary<int, ADCSetup>();
        Dictionary<int, ChannelSetup> channelSetups = new Dictionary<int, ChannelSetup>();

        public Form1()
        {
            InitializeComponent();
            for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
            {
                if (i < 10)
                {
                    ADCSetup adcSetup = new ADCSetup(i);
                    adcSetup.Dock = DockStyle.Fill;
                    adcSetup.Name = "adcCH" + (i).ToString();
                    adcSetups.Add(i, adcSetup);
                    TabPage myTabPage = new TabPage("ADC channel " + (i + 1).ToString());
                    myTabPage.Controls.Add(adcSetup);
                    tcADCChannels.TabPages.Add(myTabPage);
                }
                ChannelSetup chSetup = new ChannelSetup(i);
                chSetup.Dock = DockStyle.Fill;
                chSetup.Name = "RCCH" + (i).ToString();
                channelSetups.Add(i, chSetup);
                TabPage rcTab = new TabPage("RC channel " + (i + 1).ToString());
                rcTab.Controls.Add(chSetup);
                tcRCChannels.TabPages.Add(rcTab);
            }
        }

        private void applySettings()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(() =>
                {
                    //for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                    //{
                    //    if (i < 10)
                    //    {
                    //        channelSetups[i].SetChannelValues(settings.model[settings.activeModel].channel_settings[i]);
                    //    }
                    //}
                }));
            }
        }

        private void loadFromFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var diagBox = new OpenFileDialog();
            diagBox.Filter = "JSON files (*.json)|*.json|HEX Files (*.hex)|*.hex|BIN Files (*.bin)|*.bin";
            var diagResult = diagBox.ShowDialog(this);
            if (diagResult == DialogResult.OK)
            {
                var fileName = diagBox.FileName;
                Config.settings = Settings.loadFromFile(fileName);
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    channelSetups[i].getChannelConfig().UpdateValues(Config.settings.model[0].channel_settings[i]);
                }
            }
        }

        private void saveToFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var diagBox = new SaveFileDialog();
            diagBox.Filter = "JSON files (*.json)|*.json|HEX Files (*.hex)|*.hex|BIN Files (*.bin)|*.bin";
            var diagResult = diagBox.ShowDialog(this);
            if (diagResult == DialogResult.OK)
            {
                var fileName = diagBox.FileName;
                Settings.saveToFile(fileName, Config.settings);
            }
        }

        private void connectToTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var setupSerial = new SetupComport();
            var result = setupSerial.ShowDialog(this);
            if (result == DialogResult.OK)
            {
                try
                {
                    Config.SelectedSerialPort = new SerialPort(setupSerial.GetSelectedPort(), 115200, Parity.None, 8, StopBits.One)
                    {
                        DtrEnable = true,
                    };
                    Config.SelectedSerialPort.Open();
                    tslblComPort.Text = Config.SelectedSerialPort.PortName;
                    reconnectToTXToolStripMenuItem.Visible = true;
                    writeToTXToolStripMenuItem.Visible = true;
                    readFromTXToolStripMenuItem.Visible = true;
                    disconnectFromTXToolStripMenuItem.Visible = true;
                    connectToTXToolStripMenuItem.Visible = false;
                }
                catch
                {
                    MessageBox.Show($"Failed to connect to {Config.SelectedSerialPort.PortName}");
                    Config.SelectedSerialPort = new SerialPort();
                }
            }
        }

        private void readFromTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Settings.saveToFile("comp_config.bin", Config.settings);
            TX_Communicator.requestSettings(ref Config.settings);
            Settings.saveToFile("tx_config.bin", Config.settings);

            //for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
            //{
            //    if (i < 10)
            //    {
            //        adcSetups[i].updateBindings();
            //    }
            //    tcRCChannels.TabPages[i].Update();
            //}
        }

        private void writeToTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TX_Communicator.transmitSettings(Config.settings);
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void disconnectFromTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            reconnectToTXToolStripMenuItem.Visible = false;
            writeToTXToolStripMenuItem.Visible = false;
            readFromTXToolStripMenuItem.Visible = false;
            disconnectFromTXToolStripMenuItem.Visible = false;
            connectToTXToolStripMenuItem.Visible = true;
            Config.SelectedSerialPort.Close();
        }

        private void reconnectToTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Config.SelectedSerialPort.Close();
            Config.SelectedSerialPort.Open();
        }

        private void tcOptions_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Config.SelectedSerialPort == null || !Config.SelectedSerialPort.IsOpen)
            {
                return;
            }
            auxData1.stopDataGetter();
            adcData1.stopDataGetter();
            rcData1.stopDataGetter();
            ChannelSetup.tempStopDataGetter();
            if (tcOptions.SelectedTab.Name == "tpADCData")
            {
                adcData1.startDataGetter();
            }
            if (tcOptions.SelectedTab.Name == "tpRCData")
            {
                rcData1.startDataGetter();
            }
            if (tcOptions.SelectedTab.Name == "tpAuxData")
            {
                auxData1.startDataGetter();
            }
        }

        private void realtimeChannelDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (realtimeChannelDataToolStripMenuItem.Checked)
            {
                ChannelSetup.startDataGetter();
            }
            else
            {
                ChannelSetup.stopDataGetter();
            }
        }

        private void tcRCChannels_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = (int)tcRCChannels.SelectedIndex;
            channelSetups[index].getThisRCValue();
        }
    }
}