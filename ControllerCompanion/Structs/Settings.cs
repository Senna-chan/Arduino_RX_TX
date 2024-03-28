using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel.Design.Serialization;
using System.IO.Ports;
using System.Linq;
using System.Net.Http.Headers;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Structs
{
    public class Settings
    {
        public ushort version { get; set; }
        public byte activeModel { get; set; }
        public Model[] model { get; set; }

        public Int32 settingsSize { get; private set; }

        public Settings() {
            model = new Model[8];
            for(int i = 0; i < model.Length; i++)
                model[i] = new Model();

            InitDefaultSettings();
            using (var memstream = new MemoryStream())
            {
                SettingsHandler.writeBinary(memstream, this, true);
                settingsSize = (Int32)memstream.Length;
            }
        }

        public void UpdateValues(Settings settings)
        {
            version = settings.version;
            activeModel = settings.activeModel;
            for(int i = 0;i < model.Length;i++)
            {
                model[i].UpdateValues(settings.model[i]);
            }
        }

        public void InitDefaultSettings()
        {
            version = Config.SETTINGS_VERSION;
            activeModel = 0;
            for (int i = 0; i < model.Length; i++)
            {
                Model lmodel = model[i];
                lmodel.nameSize = 0;
                lmodel.name = "";
                //lmodel.nameSize = 6;
                //if (lmodel.nameSize > 0)
                //    lmodel.name = new String($"model{i}");

                foreach (ChannelConfig channelConfig in lmodel.channel_settings)
                {
                    channelConfig.adcConfig.min = 0;
                    channelConfig.adcConfig.mid = 0;
                    channelConfig.adcConfig.max = 1023;
                    channelConfig.endPoints.min = 1000;
                    channelConfig.endPoints.mid = 0;
                    channelConfig.endPoints.max = 2000;
                    channelConfig.trim = 0;
                    channelConfig.failsafe = 0;
                    channelConfig.outputMode = 0;
                    channelConfig.centeredStick = false;
                    channelConfig.reversed = false;

                    channelConfig.pwmConfig.frequency = 0;

                    channelConfig.stepperConfig.minFrequency = 0;
                    channelConfig.stepperConfig.maxFrequency = 0;

                    foreach (var channelMapping in channelConfig.channelMapping.inputs)
                    {
                        channelMapping.type = 0;
                        channelMapping.index = 0;
                    }
                }

                lmodel.deadzone = 20;
                lmodel.channelReversed = 0;

                foreach (var channelMixing in lmodel.channelMixing)
                {
                    channelMixing.source1 = 0;
                    channelMixing.source2 = 0;
                    channelMixing.dest1 = 0;
                    channelMixing.dest2 = 0;
                    channelMixing.type = 0;
                }

                lmodel.encoderSettings[0].minValue = 0;
                lmodel.encoderSettings[0].maxValue = 10;
                lmodel.encoderSettings[0].steps = 1;
                lmodel.encoderSettings[0].curValue = 1;
                lmodel.encoderSettings[0].devision = 1;

                lmodel.encoderSettings[1].minValue = -105;
                lmodel.encoderSettings[1].maxValue = 105;
                lmodel.encoderSettings[1].steps = 1;
                lmodel.encoderSettings[1].curValue = 5;
                lmodel.encoderSettings[1].devision = 10;

            }
        }
    }
}
