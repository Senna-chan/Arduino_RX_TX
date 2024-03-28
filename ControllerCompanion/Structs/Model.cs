using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using ControllerCompanion;
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class Model : StructBase
    {
        public byte nameSize { get; set; }
        public string name { get; set; }
        public ChannelConfig[] channel_settings { get; set; }
        public short deadzone { get; set; }
        public uint channelReversed { get; set; }
        public ChannelMixSettings[] channelMixing { get; set; }
        public EncoderSettings[] encoderSettings { get; set; }
        public OutputEnableStruct outputEnable { get; set; }
        public RateLimitConfigStruct rateLimitConfig { get; set; }
        internal void UpdateValues(Model model)
        {
            nameSize = model.nameSize;
            name = model.name;
            deadzone = model.deadzone;
            channelReversed = model.channelReversed;

            for(int i = 0; i < channel_settings.Length; i++)
            {
                channel_settings[i].UpdateValues(model.channel_settings[i]);
            }
            for(int i = 0;  i < channelMixing.Length; i++)
            {
                channelMixing[i].UpdateValues(model.channelMixing[i]);
            }
            for(int i = 0; i < encoderSettings.Length; i++)
            {
                encoderSettings[i].UpdateValues(model.encoderSettings[i]);
            }
            outputEnable.UpdateValues(model.outputEnable);
            rateLimitConfig.UpdateValues(model.rateLimitConfig);
        }

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

            outputEnable = new OutputEnableStruct();
            rateLimitConfig = new RateLimitConfigStruct();
        }


        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(nameSize);
            char[] charBuf = new char[20];
            for (int i = 0; i < nameSize; i++)
            {
                charBuf[i] = name[i];
            }
            for (int i = 0; i < 20; i++)
            {
                writer.Write((byte)charBuf[i]);
            }
            int bitIndex = 0;
            channelReversed = 0;
            foreach (var channelSetting in channel_settings)
            {
                uint bitShiftedValue = ((uint)((channelSetting.reversed ? 1 : 0) << bitIndex));
                channelReversed |= bitShiftedValue;
                channelSetting.WriteValues(writer);
                writer.Flush();
                bitIndex++;
            }
            writer.Write(deadzone);
            writer.Write(channelReversed);
            foreach(var channelMix in channelMixing)
            {
                channelMix.WriteValues(writer);
            }
            foreach(var encoder in encoderSettings)
            {
                encoder.WriteValues(writer);
            }
            outputEnable.WriteValues(writer);
            rateLimitConfig.WriteValues(writer);
            
        }

        public override void ReadValues(BinaryReader reader)
        {
            nameSize = reader.ReadByte();
            name = new String(reader.ReadChars(20));
            foreach (ChannelConfig channelConfig in channel_settings)
            {
                channelConfig.ReadValues(reader);
            }

            deadzone = reader.ReadInt16();
            channelReversed = reader.ReadUInt32();

            foreach (var channelMixing in channelMixing)
            {
                channelMixing.ReadValues(reader);
            }

            foreach (var encoderSettings in encoderSettings)
            {
                encoderSettings.ReadValues(reader);
            }

            outputEnable.ReadValues(reader); 
            rateLimitConfig.ReadValues(reader);
        }

    }
}
