using ControllerCompanion.Structs;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion
{
    internal class SettingsHandler
    {


        public static Settings loadFromFile(string fileName)
        {
            Settings settings = new Settings();
            if (fileName.EndsWith("json"))
            {
                string fileContent = File.ReadAllText(fileName, Encoding.UTF8);
                try
                {
                    settings = JsonConvert.DeserializeObject<Settings>(fileContent);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
            else if (fileName.EndsWith("bin"))
            {
                using (var stream = File.Open(fileName, FileMode.Open))
                {
                    readBinary(stream, settings, false);
                }
                return settings;
            }

            return new Settings();
        }

        public static void saveToFile(string fileName, Settings settings)
        {
            if (fileName.EndsWith("json"))
            {
                string json = JsonConvert.SerializeObject(settings, Formatting.Indented);
                File.WriteAllText(fileName, json);
            }
            else if (fileName.EndsWith("bin"))
            {
                using var stream = File.Open(fileName, FileMode.Create);
                writeBinary(stream, settings, false);
                saveToFile($"{fileName}.json", settings);
            }
        }

        public static void writeBinary(Stream stream, Settings settings, bool keepOpen)
        {
            using var writer = new BinaryWriter(stream, Encoding.UTF8, keepOpen);
            writer.Flush();
            //writer.Write(settings.settingsSize);
            writer.Write(settings.version);
            writer.Write(settings.activeModel);
            foreach (Model model in settings.model)
            {
                model.WriteValues(writer);

                writer.Flush();
            }
        }

        public static void readBinary(Stream stream, Settings settings, bool keepOpen)
        {
            using (var reader = new BinaryReader(stream, Encoding.UTF8, keepOpen))
            {
                //Int32 settingsSizeArdu = reader.ReadInt32();
                //if(settings.settingsSize != settingsSizeArdu)
                //{
                //    Console.WriteLine($"ERROR: Incorrect datasize. We calculated {settings.settingsSize} Arduino calculated {settingsSizeArdu}");
                //    while(stream.ReadByte() != -1)
                //    {
                //        reader.ReadByte();
                //    }
                //    return;
                //}
                settings.version = reader.ReadUInt16();
                settings.activeModel = reader.ReadByte();
                foreach (Model model in settings.model)
                {
                    model.ReadValues(reader);
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
    }
}
