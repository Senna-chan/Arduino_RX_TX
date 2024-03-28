
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class s_pwmConfig : StructBase
    {
        private UInt32 _frequency;

        public UInt32 frequency
        {
            get { return _frequency; }
            set { _frequency = value; NotifyPropertyChanged(); }
        }


        public override void ReadValues(BinaryReader reader)
        {
            frequency = reader.ReadUInt32();
        }

        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(frequency);
        }

        internal void UpdateValues(s_pwmConfig pwmConfig)
        {
            frequency = pwmConfig.frequency;
        }
    }
}