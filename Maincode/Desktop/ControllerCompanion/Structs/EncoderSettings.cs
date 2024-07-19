
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class EncoderSettings : StructBase
    {
        public int minValue { get; set; }
        public int maxValue {get; set;}
        public int steps {get; set;}
        public int curValue {get; set;}
        public int devision { get; set; }

        public override void ReadValues(BinaryReader reader)
        {
            minValue = reader.ReadInt32();
            maxValue = reader.ReadInt32();
            steps = reader.ReadInt32();
            curValue = reader.ReadInt32();
            devision = reader.ReadInt32();
        }

        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(minValue);
            writer.Write(maxValue);
            writer.Write(steps);
            writer.Write(curValue);
            writer.Write(devision);
        }

        internal void UpdateValues(EncoderSettings encoderSettings)
        {
            minValue = encoderSettings.minValue;
            maxValue = encoderSettings.maxValue;
            steps = encoderSettings.steps;
            curValue = encoderSettings.curValue;
            devision = encoderSettings.devision;

        }
    }
}