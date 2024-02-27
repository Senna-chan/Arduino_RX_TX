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

        public Settings() {
            model = new Model[8];
            for(int i = 0; i < model.Length; i++)
                model[i] = new Model();

            InitDefaultSettings();
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

                    foreach (var channelMapping in channelConfig.channelMapping)
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

        public static Settings loadFromFile(string fileName)
        {
            Settings settings = new Settings();
            if (fileName.EndsWith("json"))
            {
                string fileContent = File.ReadAllText(fileName, Encoding.UTF8);
                settings = JsonConvert.DeserializeObject<Settings>(fileContent);
            }
            else if (fileName.EndsWith("bin"))
            {
                
                using (var stream = File.Open(fileName, FileMode.Open))
                {
                    readBinary(stream, settings, false);
                }
                return settings;
            }
            else if (fileName.EndsWith("hex"))
            {
                using (var stream = File.Open(fileName, FileMode.Open))
                {
                    readHex(stream, settings, false);
                }
            }

            return settings;
        }

        public static void saveToFile(string fileName, Settings settings)
        {
            if (fileName.EndsWith("json"))
            {
                string json = JsonConvert.SerializeObject(settings);
                File.WriteAllText(fileName, json);
            }
            else if (fileName.EndsWith("bin"))
            {
                using (var stream = File.Open(fileName, FileMode.Create))
                {
                    writeBinary(stream, settings, false);
                }
            }
            else if (fileName.EndsWith("hex"))
            {
                using (var stream = File.Open(fileName, FileMode.Create))
                {
                    writeHex(stream, settings, false);
                }
            }
        }

        internal static void readFromRemote(SerialPort selectedSerialPort, ref Settings settings)
        {
            selectedSerialPort.Write(new byte[] { (byte)'R' }, 0, 1);
            Thread.Sleep(1000);
            Console.WriteLine($"Got {selectedSerialPort.BytesToRead} bytes to read");
            readBinary(selectedSerialPort.BaseStream, settings, true);
            if (selectedSerialPort.BytesToRead > 0)
            {
                Console.WriteLine($"Still got bytes left. {selectedSerialPort.BytesToRead}");
                selectedSerialPort.ReadExisting();
            }
        }

        internal static void writeToRemote(SerialPort selectedSerialPort, Settings settings)
        {
            selectedSerialPort.Write(new byte[] { (byte)'T' }, 0, 1);
            try
            {
                writeBinary(selectedSerialPort.BaseStream, settings, true);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        
        private static void writeBinary(Stream stream, Settings settings, bool keepOpen)
        {
            using (var writer = new BinaryWriter(stream, Encoding.UTF8, keepOpen))
            {
                writer.Flush();
                writer.Write(settings.version);
                writer.Write(settings.activeModel);
                foreach (Model model in settings.model)
                {
                    writer.Write(model.nameSize);
                    char[] charBuf = new char[20];
                    for(int i = 0; i < model.nameSize; i++)
                    {
                        charBuf[i] = model.name[i];
                    }
                    for (int i = 0; i < 20; i++)
                    {
                        writer.Write((byte)charBuf[i]);
                    }

                    int bitIndex = 0;
                    foreach (ChannelConfig channelConfig in model.channel_settings)
                    {
                        uint bitShiftedValue = ((uint)(bitIndex << (channelConfig.reversed ? 1 : 0)));
                        model.channelReversed = model.channelReversed |= bitShiftedValue;

                        writer.Write(channelConfig.adcConfig.min);
                        writer.Write(channelConfig.adcConfig.mid);
                        writer.Write(channelConfig.adcConfig.max);

                        writer.Write(channelConfig.trim);
                        writer.Write(channelConfig.failsafe);
                        writer.Write(channelConfig.startup);
                        writer.Write(channelConfig.outputMode);
                        writer.Write(channelConfig.centeredStick);

                        writer.Write(channelConfig.endPoints.min);
                        writer.Write(channelConfig.endPoints.mid);
                        writer.Write(channelConfig.endPoints.max);

                        writer.Write(channelConfig.pwmConfig.frequency);

                        writer.Write(channelConfig.stepperConfig.minFrequency);
                        writer.Write(channelConfig.stepperConfig.maxFrequency);

                        foreach (var channelMapping in channelConfig.channelMapping)
                        {
                            writer.Write(channelMapping.type);
                            writer.Write(channelMapping.index);
                        }
                        writer.Flush();
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

        private static void readBinary(Stream stream, Settings settings, bool keepOpen)
        {
            using (var reader = new BinaryReader(stream, Encoding.UTF8, keepOpen))
            {
                settings.version = reader.ReadUInt16();
                settings.activeModel = reader.ReadByte();
                foreach (Model model in settings.model)
                {
                    model.nameSize = reader.ReadByte();
                    model.name = new String(reader.ReadChars(20));

                    foreach (ChannelConfig channelConfig in model.channel_settings)
                    {
                        channelConfig.adcConfig.min = 0;
                        channelConfig.adcConfig.mid = 0;
                        channelConfig.adcConfig.min = 1023;

                        channelConfig.adcConfig.min = reader.ReadUInt16();
                        channelConfig.adcConfig.mid = reader.ReadUInt16();
                        channelConfig.adcConfig.max = reader.ReadUInt16();

                        channelConfig.trim = reader.ReadInt16();
                        channelConfig.failsafe = reader.ReadUInt16();
                        channelConfig.startup = reader.ReadUInt16();
                        channelConfig.outputMode = reader.ReadByte();
                        channelConfig.centeredStick = reader.ReadBoolean();

                        channelConfig.endPoints.min = reader.ReadUInt16();
                        channelConfig.endPoints.mid = reader.ReadUInt16();
                        channelConfig.endPoints.max = reader.ReadUInt16();

                        channelConfig.pwmConfig.frequency = reader.ReadUInt32();

                        channelConfig.stepperConfig.minFrequency = reader.ReadUInt32();
                        channelConfig.stepperConfig.maxFrequency = reader.ReadUInt32();

                        foreach (var channelMapping in channelConfig.channelMapping)
                        {
                            channelMapping.type = reader.ReadByte();
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
                        encoderSettings.minValue = reader.ReadInt32();
                        encoderSettings.maxValue = reader.ReadInt32();
                        encoderSettings.steps = reader.ReadInt32();
                        encoderSettings.curValue = reader.ReadInt32();
                        encoderSettings.devision = reader.ReadInt32();
                    }
                }
            }

            foreach (Model model in settings.model)
            {
                int bitIndex = 0;
                foreach (ChannelConfig channelConfig in model.channel_settings)
                {
                    if ((model.channelReversed & (1 << bitIndex)) != 0)
                    {
                        channelConfig.reversed = true;
                    }
                    else
                    {
                        channelConfig.reversed = false;
                    }
                }
            }
        }


        private static void writeHex(Stream stream, Settings settings, bool keepOpen)
        {

        }

        private static void readHex(Stream stream, Settings settings, bool keepOpen)
        {

        }
    }
}
