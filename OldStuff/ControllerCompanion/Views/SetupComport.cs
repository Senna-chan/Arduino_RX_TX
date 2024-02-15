using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion.Views
{
    public partial class SetupComport : Form
    {
        private string selectedComPort = "";

        public SetupComport()
        {
            InitializeComponent();
            var comports = SerialPort.GetPortNames();
            lbxComPorts.Items.AddRange(comports);
        }

        private void btnOpenComPort_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            if (lbxComPorts.SelectedItem != null)
            {
                selectedComPort = lbxComPorts.SelectedItem.ToString();
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        public string GetSelectedPort()
        {
            return selectedComPort;
        }
    }
}
