using ControllerCompanion.Structs;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion.Views
{
    public partial class ADCSetup : UserControl
    {
        

        private int channel;
        private ChannelConfig channelConfig;
        public ADCSetup(int channel)
        {
            InitializeComponent();
            this.channel = channel;
            channelConfig = Config.settings.model[Config.settings.activeModel].channel_settings[channel];
            numMin.DataBindings.Add("Value", channelConfig, "chMin");
            numMid.DataBindings.Add("Value", channelConfig, "chMid");
            numMax.DataBindings.Add("Value", channelConfig, "chMax");
            tbMin.DataBindings.Add("Value", channelConfig, "chMin");
            tbMid.DataBindings.Add("Value", channelConfig, "chMid");
            tbMax.DataBindings.Add("Value", channelConfig, "chMax");
        }
        private void tbMin_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.chMin = (ushort)tbMin.Value;
        }

        private void tbMid_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.chMid = (ushort)tbMid.Value;
        }

        private void tbMax_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.chMax = (ushort)tbMax.Value;
        }

        private void numMin_KeyUp(object sender, KeyEventArgs e)
        {
            channelConfig.chMin = (ushort)numMin.Value;
        }

        private void numMid_KeyUp(object sender, KeyEventArgs e)
        {
            channelConfig.chMid = (ushort)numMid.Value;
        }

        private void numMax_KeyUp(object sender, KeyEventArgs e)
        {
            channelConfig.chMax = (ushort)numMax.Value;
        }
    }
}
