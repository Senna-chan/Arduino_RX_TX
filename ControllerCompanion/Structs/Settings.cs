using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel.Design.Serialization;
using System.IO.Ports;
using System.Linq;
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

        public Settings() {
            model = new Model[8];
            for(int i = 0; i < model.Length; i++)
                model[i] = new Model();
        }

        public static Settings loadFromFile(string fileName)
        {
            if (fileName.EndsWith("json"))
            {
                string fileContent = File.ReadAllText(fileName, Encoding.UTF8);
                return JsonConvert.DeserializeObject<Settings>(fileContent);
            }
            else
            {
                Settings settings = new Settings();
                using (var stream = File.Open(fileName, FileMode.Open))
                {
                    using (var reader = new BinaryReader(stream, Encoding.UTF8, false))
                    {
                        settings.version = reader.ReadUInt16();
                        settings.activeModel =reader.ReadByte();
                        foreach (Model model in settings.model)
                        {
                            model.nameSize = reader.ReadByte();
                            model.name = new String(reader.ReadChars(model.nameSize));

                            foreach (ChannelConfig channelConfig in model.channel_settings)
                            {
                                channelConfig.chMin = reader.ReadUInt16();
                                channelConfig.chMid = reader.ReadUInt16();
                                channelConfig.chMax = reader.ReadUInt16();
                                channelConfig.chOffset = reader.ReadInt16();
                                channelConfig.chDefaults = reader.ReadUInt16();
                                channelConfig.outputMode = reader.ReadByte();

                                channelConfig.pwmConfig.frequency = reader.ReadUInt32();

                                channelConfig.stepperConfig.minFrequency = reader.ReadUInt32();
                                channelConfig.stepperConfig.maxFrequency = reader.ReadUInt32();

                                foreach (var channelMapping in channelConfig.channelMapping)
                                {
                                    channelMapping.type = reader.ReadSByte();
                                    channelMapping.index = reader.ReadByte();
                                }
                            }

                            model.deadzone = reader.ReadInt16();
                            model.channelReversed = reader.ReadUInt32();

                            foreach (var channelMixing in model.channelMixing)
                            {
                                channelMixing.source1 = reader.ReadByte();
                                channelMixing.source2 = reader.ReadByte();
                                channelMixing.dest1 = reader.ReadByte();
                                channelMixing.dest2 = reader.ReadByte();
                                channelMixing.type = reader.ReadByte();
                            }

                            foreach (var encoderSettings in model.encoderSettings)
                            {
                                encoderSettings.minValue = reader.Read();
                                encoderSettings.maxValue = reader.Read();
                                encoderSettings.steps = reader.Read();
                                encoderSettings.curValue = reader.Read();
                                encoderSettings.devision = reader.Read();
                            }
                        }
                    }
                }
                return settings;
            }
        }

        public static void saveToFile(string fileName, Settings settings)
        {
            if (fileName.EndsWith("json"))
            {
                string json = JsonConvert.SerializeObject(settings);
                File.WriteAllText(fileName, json);
            }
            else
            {
                using (var stream = File.Open(fileName, FileMode.Create))
                {
                    writeBinary(stream, settings);
                }
            }
        }

        internal static Settings readFromRemote(SerialPort selectedSerialPort)
        {
            Settings settings = new Settings();
            using (var stream = selectedSerialPort.BaseStream)
            {
                readBinary(stream, settings);
            }
            return settings;
        }

        internal static void writeToRemote(SerialPort selectedSerialPort, Settings settings)
        {
            writeBinary(selectedSerialPort.BaseStream, settings);
        }
        
        private static void writeBinary(Stream stream, Settings settings)
        {
            using (var writer = new BinaryWriter(stream, Encoding.UTF8, false))
            {
                writer.Write(settings.version);
                writer.Write(settings.activeModel);
                foreach (Model model in settings.model)
                {
                    writer.Write(model.name);
                    writer.Write(model.nameSize);

                    foreach (ChannelConfig channelConfig in model.channel_settings)
                    {
                        writer.Write(channelConfig.chMin);
                        writer.Write(channelConfig.chMid);
                        writer.Write(channelConfig.chMax);
                        writer.Write(channelConfig.chOffset);
                        writer.Write(channelConfig.chDefaults);
                        writer.Write(channelConfig.outputMode);
                        writer.Write(channelConfig.centeredStick);

                        writer.Write(channelConfig.pwmConfig.frequency);

                        writer.Write(channelConfig.stepperConfig.minFrequency);
                        writer.Write(channelConfig.stepperConfig.maxFrequency);

                        foreach (var channelMapping in channelConfig.channelMapping)
                        {
                            writer.Write(channelMapping.type);
                            writer.Write(channelMapping.index);
                        }
                    }

                    writer.Write(model.deadzone);
                    writer.Write(model.channelReversed);

                    foreach (var channelMixing in model.channelMixing)
                    {
                        writer.Write(channelMixing.source1);
                        writer.Write(channelMixing.source2);
                        writer.Write(channelMixing.dest1);
                        writer.Write(channelMixing.dest2);
                        writer.Write(channelMixing.type);
                    }

                    foreach (var encoderSettings in model.encoderSettings)
                    {
                        writer.Write(encoderSettings.minValue);
                        writer.Write(encoderSettings.maxValue);
                        writer.Write(encoderSettings.steps);
                        writer.Write(encoderSettings.curValue);
                        writer.Write(encoderSettings.devision);
                    }
                    writer.Flush();
                }
            }
        }

        private static void readBinary(Stream stream, Settings settings)
        {
            using (var reader = new BinaryReader(stream, Encoding.UTF8, false))
            {
                settings.version = reader.ReadUInt16();
                settings.activeModel = reader.ReadByte();
                foreach (Model model in settings.model)
                {
                    model.nameSize = reader.ReadByte();
                    model.name = new String(reader.ReadChars(model.nameSize));

                    foreach (ChannelConfig channelConfig in model.channel_settings)
                    {
                        channelConfig.chMin = reader.ReadUInt16();
                        channelConfig.chMid = reader.ReadUInt16();
                        channelConfig.chMax = reader.ReadUInt16();
                        channelConfig.chOffset = reader.ReadInt16();
                        channelConfig.chDefaults = reader.ReadUInt16();
                        channelConfig.outputMode = reader.ReadByte();
                        channelConfig.centeredStick = reader.ReadByte();

                        channelConfig.pwmConfig.frequency = reader.ReadUInt32();

                        channelConfig.stepperConfig.minFrequency = reader.ReadUInt32();
                        channelConfig.stepperConfig.maxFrequency = reader.ReadUInt32();

                        foreach (var channelMapping in channelConfig.channelMapping)
                        {
                            channelMapping.type = reader.ReadSByte();
                            channelMapping.index = reader.ReadByte();
                        }
                    }

                    model.deadzone = reader.ReadInt16();
                    model.channelReversed = reader.ReadUInt32();

                    foreach (var channelMixing in model.channelMixing)
                    {
                        channelMixing.source1 = reader.ReadByte();
                        channelMixing.source2 = reader.ReadByte();
                        channelMixing.dest1 = reader.ReadByte();
                        channelMixing.dest2 = reader.ReadByte();
                        channelMixing.type = reader.ReadByte();
                    }

                    foreach (var encoderSettings in model.encoderSettings)
                    {
                        encoderSettings.minValue = reader.Read();
                        encoderSettings.maxValue = reader.Read();
                        encoderSettings.steps = reader.Read();
                        encoderSettings.curValue = reader.Read();
                        encoderSettings.devision = reader.Read();
                    }
                }
            }
        }

    }
}
