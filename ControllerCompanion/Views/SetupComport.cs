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
                Config.SelectedSerialPort = new SerialPort(lbxComPorts.SelectedItem.ToString());
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }
    }
}
