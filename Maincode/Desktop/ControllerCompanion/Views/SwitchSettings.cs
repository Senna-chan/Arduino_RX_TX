using ControllerCompanion.Enums;
using ControllerCompanion.Structs;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion.Views
{
    public partial class SwitchSettings : UserControl
    {
        OutputEnableStruct outputEnableConfig;
        RateLimitConfigStruct rateLimitConfig;

        bool blockCobUpdates = false;

        public SwitchSettings(OutputEnableStruct outputEnableConfig, RateLimitConfigStruct rateLimitConfig)
        {
            InitializeComponent();
            this.outputEnableConfig = outputEnableConfig;
            this.rateLimitConfig = rateLimitConfig;

            cobRateInput1.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobRateInput1.DisplayMember = "Value";
            cobRateInput1.ValueMember = "Key";
            cobRateInput1.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobRateInput1.DataBindings.Add("SelectedValue", rateLimitConfig.input.inputs[0], "intDefinition");

            cobRateInput2.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobRateInput2.DisplayMember = "Value";
            cobRateInput2.ValueMember = "Key";
            cobRateInput2.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobRateInput2.DataBindings.Add("SelectedValue", rateLimitConfig.input.inputs[1], "intDefinition");


            cobOutputIO.DataSource = new BindingSource(ChannelInputTypes.inputTypes, null);
            cobOutputIO.DisplayMember = "Value";
            cobOutputIO.ValueMember = "Key";
            cobOutputIO.SelectedValueChanged += CobInput_SelectedValueChanged;
            cobOutputIO.DataBindings.Add("SelectedValue", outputEnableConfig.inputIO, "intDefinition");

            numOutputMin.DataBindings.Add("Value", rateLimitConfig.outputValuesMax, "min");
            numOutputMid.DataBindings.Add("Value", rateLimitConfig.outputValuesMax, "mid");
            numOutputMax.DataBindings.Add("Value", rateLimitConfig.outputValuesMax, "max");


            cobLimitSide.DataSource = new BindingSource(new Dictionary<sbyte, string>() { { -1, "Only limit down" }, { 0, "Limit down and up" }, { 1, "Only limit up" } }, null);
            cobLimitSide.DisplayMember = "Value";
            cobLimitSide.ValueMember = "Key";
            cobLimitSide.SelectedIndex = 1;
            cobLimitSide.SelectedValueChanged += CobLimit_SelectedValueChanged;

            for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
            {
                lbOutputsToEnabled.Items.Add($"RC{i + 1}");
                cobChannelToRateLimit.Items.Add($"RC{i + 1}");
                if (((outputEnableConfig.outputsToEnable >> i) & 1) == 1)
                {
                    lbOutputsToEnabled.SelectedItems.Add($"RC{i + 1}");
                }
            }
            lbOutputsToEnabled.SelectedValueChanged += LbOutputsToEnabled_SelectedValueChanged;

            cobChannelToRateLimit.DataBindings.Add("SelectedIndex", rateLimitConfig, "outputToRateLimit");
        }

        private void LbOutputsToEnabled_SelectedValueChanged(object? sender, EventArgs e)
        {
            outputEnableConfig.outputsToEnable = 0;
            for (int i = 0; i < lbOutputsToEnabled.SelectedItems.Count; i++)
            {
                int bit = int.Parse(lbOutputsToEnabled.SelectedItems[i].ToString().Substring(2));
                bit--;
                outputEnableConfig.outputsToEnable |= (uint)(1 << bit);
            }
        }

        private void CobLimit_SelectedValueChanged(object? sender, EventArgs e)
        {
            rateLimitConfig.limitSide = (sbyte)cobLimitSide.SelectedValue;
        }

        private void CobInput_SelectedValueChanged(object? sender, EventArgs e)
        {
            if (blockCobUpdates) return;
            ComboBox chInput = (ComboBox)sender;
            int aIndex = (chInput == cobRateInput1 ? 0 : 1);
            if (chInput.SelectedValue == null)
            {
                Console.WriteLine($"chInput {aIndex} is null");
                return;
            }
            rateLimitConfig.input.inputs[aIndex].intDefinition = (int)chInput.SelectedValue;
        }


        public void setChannelMapping(byte inputType, byte inputIndex, byte channel)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(() =>
                {
                    blockCobUpdates = true;
                    if (channel == 3)
                    {
                        if (inputType == ChannelInputTypes.ADC)
                        {
                            btnDetectOutputEnableIO.Text = "Detecting enable";
                            InputDetector.detectSequence(setChannelMapping, 3);
                        }
                        else
                        {
                            outputEnableConfig.inputIO.type = inputType;
                            outputEnableConfig.inputIO.index = inputIndex;
                        }
                    }
                    else if(channel == 4)
                    {
                    }
                    else
                    {
                        channel--;
                        rateLimitConfig.input.inputs[channel].type = inputType;
                        rateLimitConfig.input.inputs[channel].index = inputIndex;
                    }
                    btnDetectRateInput1.Text = "Rate Input 1";
                    btnDetectRateInput2.Text = "Rate Input 2";
                    btnDetectOutputEnableIO.Text = "Enable Input";
                    blockCobUpdates = false;
                }));
            }
        }


        private void btnDetectRateInput1_Click(object sender, EventArgs e)
        {
            btnDetectRateInput1.Text = "Detecting rate 1";
            InputDetector.detectSequence(setChannelMapping, 1);
        }

        private void btnDetectRateInput2_Click(object sender, EventArgs e)
        {
            btnDetectRateInput2.Text = "Detecting rate 2";
            InputDetector.detectSequence(setChannelMapping, 2);
        }

        private void btnDetectOutputEnableIO_Click(object sender, EventArgs e)
        {
            btnDetectOutputEnableIO.Text = "Detecting enable";
            InputDetector.detectSequence(setChannelMapping, 3);
        }

        //private void btnDetectRateOutput_Click(object sender, EventArgs e)
        //{
        //    btnDetectRateOutput.Text = "Detecting Rate Output";
        //    InputDetector.detectSequence(setChannelMapping, 4);
        //}
    }
}
