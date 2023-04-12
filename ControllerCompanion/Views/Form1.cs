using ControllerCompanion.Structs;
using System.IO.Ports;
using System.Windows.Forms;

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
            diagBox.Filter = "JSON files (*.json)|*.json|HEX Files (*.hex)|*.hex";
            var diagResult = diagBox.ShowDialog(this);
            if (diagResult == DialogResult.OK)
            {
                var fileName = diagBox.FileName;
                Config.settings = Settings.loadFromFile(fileName);
            }
        }

        private void saveToFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var diagBox = new SaveFileDialog();
            diagBox.Filter = "JSON files (*.json)|*.json|HEX Files (*.hex)|*.hex";
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
                tslblComPort.Text = Config.SelectedSerialPort.PortName;
                writeToTXToolStripMenuItem.Visible = true;
                readFromTXToolStripMenuItem.Visible = true;
                disconnectFromTXToolStripMenuItem.Visible = true;
                connectToTXToolStripMenuItem.Visible = false;
            }
        }

        private void readFromTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Settings.readFromRemote(Config.SelectedSerialPort);
        }

        private void writeToTXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Settings.writeToRemote(Config.SelectedSerialPort, Config.settings);
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void disconnectFromTXToolStripMenuItem_Click(object sender, EventArgs e)
        {

            writeToTXToolStripMenuItem.Visible = false;
            readFromTXToolStripMenuItem.Visible = false;
            disconnectFromTXToolStripMenuItem.Visible = false;
            connectToTXToolStripMenuItem.Visible = true;
            Config.SelectedSerialPort.Close();
        }
    }
}