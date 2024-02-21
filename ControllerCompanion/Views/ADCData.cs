using System;
using System.Collections;
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
    public partial class ADCData : UserControl
    {
        private Dictionary<int, Label> adcChannels = new Dictionary<int, Label>();
        private Thread dataThread;
        private bool getData = false;
        public ADCData()
        {
            InitializeComponent();
            dataThread = new Thread(dataGetter);
            int adcch = 0;
            int col = 1;
            for (int i = 0; i < 2; i++)
            {
                int row = 0;
                for (int j = 0; j < 6; j++)
                {
                    Label text = new Label();
                    text.Dock = DockStyle.Fill;
                    text.Text = $"ADC {adcch}: ";
                    tableLayoutPanel2.Controls.Add(text, col, row);

                    Label adc = new Label();
                    adc.Dock = DockStyle.Fill;
                    adc.Text = "0000";
                    tableLayoutPanel2.Controls.Add(adc, col + 1, row);
                    adcChannels.Add(adcch, adc);
                    adcch++;
                    row++;
                }
                col = 4;
            }
        }

        private void dataGetter()
        {
            Thread.CurrentThread.Name = "ADCDataGetter";
            UInt16[] adcData = new UInt16[24];
            UInt32 ioData = 0;
            while (true)
            {
                if (getData)
                {
                    DataGetter.requestAndReadRAW(adcData, ioData);
                    if (this.InvokeRequired)
                    {
                        this.BeginInvoke(new Action(() =>
                        {
                            for (int i = 0; i < 12; i++)
                            {
                                adcChannels[i].Text = adcData[i].ToString();
                            }
                            lblIOData.Text = Convert.ToString(ioData, 2);
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
