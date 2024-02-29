using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion.Views
{
    public partial class RCData : UserControl
    {
        private Dictionary<int, Label> rcChannels = new Dictionary<int, Label>();
        private Thread dataThread;
        private bool getData = false;
        public RCData()
        {
            InitializeComponent();
            dataThread = new Thread(dataGetter);
            int rcch = 1;
            int col = 1;
            for (int i = 0; i < 2; i++)
            {
                int row = 0;
                for (int j = 0; j < 12; j++)
                {
                    Label text = new Label();
                    text.Dock = DockStyle.Fill;
                    text.Text = $"CH{rcch}: ";
                    tableLayoutPanel1.Controls.Add(text, col, row);

                    Label rc = new Label();
                    rc.Dock = DockStyle.Fill;
                    rc.Text = "0000";
                    tableLayoutPanel1.Controls.Add(rc, col + 1, row);
                    rcChannels.Add(rcch - 1, rc);
                    rcch++;
                    row++;
                }
                col = 4;
            }
        }

        private void dataGetter()
        {
            Thread.CurrentThread.Name = "RCDataGetter";
            UInt16[] rcData = new UInt16[24];
            while (true)
            {
                if (getData)
                {
                    TX_Communicator.requestAndReadRC(rcData);
                    if (this.InvokeRequired)
                    {
                        this.BeginInvoke(new Action(() =>
                        {
                            for (int i = 0; i < 24; i++)
                            {
                                rcChannels[i].Text = rcData[i].ToString();
                            }
                        }));
                    }
                }
                Thread.Sleep(250);
            }
        }

        public void startDataGetter()
        {
            getData = true;
            if (dataThread.ThreadState == ThreadState.Unstarted)
            {
                dataThread.Start();
            }
        }

        public void stopDataGetter()
        {
            getData = false;
        }
    }
}
