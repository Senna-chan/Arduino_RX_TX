using ControllerCompanion.Structs;
using ControllerCompanion.Enums;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace ControllerCompanion.Views
{
    public partial class ChannelSetup : UserControl
    {
        int channel;
        ChannelConfig channelConfig;



        public ChannelSetup(int channel)
        {
            InitializeComponent();
            this.channel = channel;
            channelConfig = Config.settings.model[Config.settings.activeModel].channel_settings[channel];
            cobOutputType.DataSource = new BindingSource(ChannelOutputTypes.GetItemsForChannel(channel), null);
            cobOutputType.DisplayMember = "Value";
            cobOutputType.ValueMember = "Key";
            cobOutputType.SelectedValueChanged += CobOutputType_SelectedValueChanged;
            cobInput1.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobInput1.DisplayMember = "Value";
            cobInput1.ValueMember = "Key";
            cobInput1.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobInput2.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobInput2.DisplayMember = "Value";
            cobInput2.ValueMember = "Key";
            cobInput2.SelectedValueChanged += CobInput_SelectedValueChanged;
        }

        private void CobInput_SelectedValueChanged(object? sender, EventArgs e)
        {
            if (sender == cobInput1)
            {

            }
            else if (sender == cobInput2)
            {

            }
        }

        private void CobOutputType_SelectedValueChanged(object? sender, EventArgs e)
        {
            Console.WriteLine("OutputChanged");
            channelConfig.outputMode = (byte)cobOutputType.SelectedValue;
        }
    }
}
