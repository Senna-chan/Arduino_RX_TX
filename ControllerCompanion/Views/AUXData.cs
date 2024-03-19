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
    public partial class AUXData : UserControl
    {
        private Dictionary<int, Label> auxChannels = new Dictionary<int, Label>();
        private Thread dataThread;
        private bool getData = false;
        public AUXData()
        {
            InitializeComponent();
            dataThread = new Thread(dataGetter);
            int auxch = 0;
            int col = 1;
            for (int i = 0; i < 2; i++)
            {
                int row = 0;
                for (int j = 0; j < 10; j++)
                {
                    Label text = new Label();
                    text.Dock = DockStyle.Fill;
                    text.Text = $"AUX {auxch}: ";
                    tableLayoutPanel1.Controls.Add(text, col, row);

                    Label aux = new Label();
                    aux.Dock = DockStyle.Fill;
                    aux.Text = "0000";
                    tableLayoutPanel1.Controls.Add(aux, col + 1, row);
                    auxChannels.Add(auxch, aux);
                    auxch++;
                    row++;
                }
                col = 4;
            }
        }

        private void dataGetter()
        {
            Thread.CurrentThread.Name = "AuxDataGetter";
            UInt16[] auxData = new UInt16[Config.RC_MAX_CHANNELS];
            while (true)
            {
                if (getData)
                {
                    TX_Communicator.requestAndReadAUX(auxData);
                    if (this.InvokeRequired)
                    {
                        this.BeginInvoke(new Action(() =>
                        {
                            for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                            {
                                auxChannels[i].Text = auxData[i].ToString();
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
            if(dataThread.ThreadState == ThreadState.Unstarted)
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
