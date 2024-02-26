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
            bindings.Add(numMin.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig, "min"));
            bindings.Add(numMid.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig, "mid"));
            bindings.Add(numMax.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig, "max"));
            bindings.Add(tbMin.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig,  "min"));
            bindings.Add(tbMid.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig,  "mid"));
            bindings.Add(tbMax.DataBindings.Add("Value", Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig,  "max"));
        }

        public void updateBindings()
        {
            foreach (Binding binding in bindings)
            {
                binding.ReadValue();
            }
        }

        private void tbMin_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.min = (ushort)tbMin.Value;
        }

        private void tbMid_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.mid = (ushort)tbMid.Value;
        }

        private void tbMax_ValueChanged(object sender, EventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.max = (ushort)tbMax.Value;
        }

        private void numMin_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.min = (ushort)numMin.Value;
        }

        private void numMid_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.mid = (ushort)numMid.Value;
        }

        private void numMax_KeyUp(object sender, KeyEventArgs e)
        {
            Config.settings.model[Config.settings.activeModel].channel_settings[channel].adcConfig.max = (ushort)numMax.Value;
        }
    }
}
