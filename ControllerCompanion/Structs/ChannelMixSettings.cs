
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class ChannelMixSettings : StructBase
    {
        public byte source1 {get;set;}
        public byte source2 {get;set;}
        public byte dest1 {get;set;}
        public byte dest2 {get;set;}
        public byte type { get; set; }

        public override void ReadValues(BinaryReader reader)
        {
            source1 = reader.ReadByte();
            source2 = reader.ReadByte();
            dest1 = reader.ReadByte();
            dest2 = reader.ReadByte();
            type = reader.ReadByte();
        }

        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(source1);
            writer.Write(source2);
            writer.Write(dest1);
            writer.Write(dest2);
            writer.Write(type);
        }

        internal void UpdateValues(ChannelMixSettings channelMixSettings)
        {
            source1 = channelMixSettings.source1;
            source2 = channelMixSettings.source2;
            dest1 = channelMixSettings.dest1;
            dest2 = channelMixSettings.dest2;
            type = channelMixSettings.type;
        }
    }
}