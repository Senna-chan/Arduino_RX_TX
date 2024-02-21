using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ControllerCompanion;

namespace ControllerCompanion.Structs
{
    public class Model
    {
        public byte nameSize { get; set; }
        public string name { get; set; }
        public ChannelConfig[] channel_settings { get; set; }
        public short deadzone { get; set; }
        public uint channelReversed { get; set; }
        public ChannelMixSettings[] channelMixing { get; set; }
        public EncoderSettings[] encoderSettings { get; set; }

        public Model()
        {
            nameSize = 5;
            name = "MODEL";
            channel_settings = new ChannelConfig[Config.RC_MAX_CHANNELS];
            for(int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                channel_settings[i] = new ChannelConfig();

            channelMixing = new ChannelMixSettings[8];
            for(int i = 0; i < 8; i++)
                channelMixing[i] = new ChannelMixSettings();

            encoderSettings = new EncoderSettings[2];
            for(int i = 0; i < 2; i++)
                encoderSettings[i] = new EncoderSettings();
        }
    }
}
