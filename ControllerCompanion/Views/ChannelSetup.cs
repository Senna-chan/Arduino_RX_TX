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
using System.Reflection;
using System.IO;

namespace ControllerCompanion.Views
{
    public partial class ChannelSetup : UserControl
    {
        int channel;
        ChannelConfig channelConfig;
        s_pwmConfig pwmConfig;
        s_stepperConfig stepperConfig;

        bool blockCobUpdates = false;

        private static Thread dataThread = new Thread(dataGetter);
        private static bool getData = false;
        private static ChannelSetup? currentChannelSetup;
        private static void dataGetter()
        {
            Thread.CurrentThread.Name = "RCChannelGetter";
            UInt16 rcValue = 0;
            int count = 0;
            while (true)
            {
                if (getData && currentChannelSetup != null)
                {
                    count++;
                    if (count % 8 == 0)
                    {
                        count = 0;
                        TX_Communicator.transmitChannelConfig(currentChannelSetup.channelConfig);
                    }

                    TX_Communicator.requestAndReadRCChannel(ref rcValue);
                    if (currentChannelSetup.InvokeRequired)
                    {
                        currentChannelSetup.BeginInvoke(new Action(() =>
                        {
                            for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                            {
                                currentChannelSetup.lblRCValue.Text = rcValue.ToString();
                            }
                        }));
                    }
                }
                Thread.Sleep(250);
            }
        }

        public static void startDataGetter()
        {
            getData = true;
            if (dataThread.ThreadState == ThreadState.Unstarted)
            {
                dataThread.Start();
            }
        }

        public static void stopDataGetter()
        {
            getData = false;
        }

        public static void tempStopDataGetter()
        {
            currentChannelSetup = null;
        }

        public void getThisRCValue()
        {
            currentChannelSetup = this;
            TX_Communicator.transmitChannelConfig(channelConfig);
        }

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
            lblChannelId.Text = $"Channel {channel}";
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

            numFailsafeValue.DataBindings.Add("Value", channelConfig, "failsafe");
            numStartupValue.DataBindings.Add("Value", channelConfig, "startup");
            chbReversedChannel.DataBindings.Add("Checked", channelConfig, "reversed");
            chbCenteredStick.DataBindings.Add("Checked", channelConfig, "centeredStick");
            numSTEPMin.DataBindings.Add("Value", stepperConfig, "minFrequency");
            numSTEPMax.DataBindings.Add("Value", stepperConfig, "maxFrequency");
            numPWMFreq.DataBindings.Add("Value", pwmConfig, "frequency");
            numEndPointMin.DataBindings.Add("Value", channelConfig.endPoints, "min");
            numEndPointMax.DataBindings.Add("Value", channelConfig.endPoints, "max");
        }

        private void CobInput_SelectedValueChanged(object? sender, EventArgs e)
        {
            if (blockCobUpdates) return;
            ComboBox chInput = (ComboBox)sender;
            int aIndex = (chInput == cobInput1 ? 0 : 1);
            if (chInput.SelectedValue == null)
            {
                Console.WriteLine($"chInput {aIndex} is null");
                return;
            }
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

        public void setChannelMapping(byte inputType, byte inputIndex, byte channel)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(() =>
                {
                    channel--;
                    blockCobUpdates = true;
                    channelConfig.channelMapping[channel].type = inputType;
                    channelConfig.channelMapping[channel].index = inputIndex;
                    btnDetectInput1.Text = "Input 1";
                    btnDetectInput2.Text = "Input 2";
                    blockCobUpdates = false;
                }));
            }
        }

        public ChannelConfig getChannelConfig()
        {
            return channelConfig;
        }

        private void btnDetectInput1_Click(object sender, EventArgs e)
        {
            btnDetectInput1.Text = "Detecting 1";
            InputDetector.detectSequence(this, 1);
        }

        private void btnDetectInput2_Click(object sender, EventArgs e)
        {
            btnDetectInput2.Text = "Detecting 2";
            InputDetector.detectSequence(this, 2);
        }

        private void numFailsafeValue_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.failsafe = (ushort)numFailsafeValue.Value;
        }
        private void numStartupValue_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.startup = (ushort)numStartupValue.Value;
        }

        private void numEndPointMin_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.endPoints.min = (ushort)numEndPointMin.Value;
        }
        private void numEndPointMax_ValueChanged(object sender, EventArgs e)
        {
            channelConfig.endPoints.max = (ushort)numEndPointMax.Value;
        }
    }
}
