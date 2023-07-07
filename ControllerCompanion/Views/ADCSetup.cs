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

        private List<Binding> bindings = new List<Binding>();

        public ADCSetup(int channel)
        {
            InitializeComponent();
            this.channel = channel;
            channelConfig = Config.settings.model[Config.settings.activeModel].channel_settings[channel];
            bindings.Add(numMin.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMin"));
            bindings.Add(numMid.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMid"));
            bindings.Add(numMax.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMax"));
            bindings.Add(tbMin.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMin"));
            bindings.Add(tbMid.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMid"));
            bindings.Add(tbMax.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel], "chMax"));
        }

        public void updateBindings()
        {
            foreach(Binding binding in bindings)
            {
                binding.ReadValue();
            }
        }

        private void tbMin_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMin = (ushort)tbMin.Value;
        }

        private void tbMid_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMid = (ushort)tbMid.Value;
        }

        private void tbMax_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMax = (ushort)tbMax.Value;
        }

        private void numMin_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMin = (ushort)numMin.Value;
        }

        private void numMid_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMid = (ushort)numMid.Value;
        }

        private void numMax_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].chMax = (ushort)numMax.Value;
        }
    }
}
