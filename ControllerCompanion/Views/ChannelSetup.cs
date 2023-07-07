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
using System.Reflection;

namespace ControllerCompanion.Views
{
    public partial class ChannelSetup : UserControl
    {
        int channel;
        ChannelConfig channelConfig;
        s_pwmConfig pwmConfig;
        s_stepperConfig stepperConfig;

        private void changeStepObjects(bool visible)
        {
            numSTEPMin.Visible = visible;
            numSTEPMax.Visible = visible;
            lblSTEPMin.Visible = visible;
            lblSTEPMax.Visible = visible;
        }
        private void changePWMObjects(bool visible)
        {
            numPWMFreq.Visible = visible;
            lblPWMFreq.Visible = visible;
        }

        public ChannelSetup(int channel)
        {
            InitializeComponent();
            changeStepObjects(false);
            changePWMObjects(false);
            this.channel = channel;
            channelConfig = Config.settings.model[Config.settings.activeModel].channel_settings[channel];
            stepperConfig = channelConfig.stepperConfig;
            pwmConfig = channelConfig.pwmConfig;
            cobOutputType.DataSource = new BindingSource(ChannelOutputTypes.GetItemsForChannel(channel), null);
            cobOutputType.DisplayMember = "Value";
            cobOutputType.ValueMember = "Key";
            cobOutputType.SelectedValueChanged += CobOutputType_SelectedValueChanged;
            cobOutputType.DataBindings.Add("SelectedValue", channelConfig, "outputMode");

            cobInput1.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobInput1.DisplayMember = "Value";
            cobInput1.ValueMember = "Key";
            cobInput1.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobInput1.DataBindings.Add("SelectedValue", channelConfig.channelMapping[0], "intDefinition");

            cobInput2.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobInput2.DisplayMember = "Value";
            cobInput2.ValueMember = "Key";
            cobInput2.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobInput2.DataBindings.Add("SelectedValue", channelConfig.channelMapping[1], "intDefinition");

            numDefaultChannelValue.DataBindings.Add("Value", channelConfig, "chDefaults");
            chbReversedChannel.DataBindings.Add("Checked", channelConfig, "reversed");
            chbCenteredStick.DataBindings.Add("Checked", channelConfig, "centeredStick");
            numSTEPMin.DataBindings.Add("Value", stepperConfig, "minFrequency");
            numSTEPMax.DataBindings.Add("Value", stepperConfig, "maxFrequency");
            numPWMFreq.DataBindings.Add("Value", pwmConfig, "frequency");
        }

        private void CobInput_SelectedValueChanged(object? sender, EventArgs e)
        {
            ComboBox chInput = (ComboBox)sender;
            int aIndex = (chInput == cobInput1 ? 0 : 1);

            channelConfig.channelMapping[aIndex].intDefinition = (int)chInput.SelectedValue;
        }

        private void CobOutputType_SelectedValueChanged(object? sender, EventArgs e)
        {
            Console.WriteLine("OutputChanged");
            channelConfig.outputMode = (byte)cobOutputType.SelectedValue;
            if (channelConfig.outputMode == (byte)ChannelOutputTypes.outputModes.OUTPUTMODE_PWM)
            {
                changeStepObjects(false);
                changePWMObjects(true);
            }
            else if (channelConfig.outputMode == (byte)ChannelOutputTypes.outputModes.OUTPUTMODE_STEP)
            {
                changeStepObjects(true);
                changePWMObjects(false);
            }
            else
            {
                changeStepObjects(false);
                changePWMObjects(false);
            }
        }
    }
}
