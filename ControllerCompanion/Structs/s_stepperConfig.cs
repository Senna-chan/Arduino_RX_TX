
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class s_stepperConfig : StructBase 
    {
        private UInt32 _minFrequency;

        public UInt32 minFrequency
        {
            get { return _minFrequency; }
            set { _minFrequency = value; NotifyPropertyChanged(); }
        }

        private UInt32 _maxFrequency;

        public UInt32 maxFrequency
        {
            get { return _maxFrequency; }
            set { _maxFrequency = value; NotifyPropertyChanged(); }
        }



        public override void ReadValues(BinaryReader reader)
        {
            _minFrequency = reader.ReadUInt32();
            _maxFrequency = reader.ReadUInt32();
        }

        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(_minFrequency);
            writer.Write(_maxFrequency);
        }

        internal void UpdateValues(s_stepperConfig stepperConfig)
        {
            minFrequency = stepperConfig.minFrequency;
            maxFrequency = stepperConfig.maxFrequency;
        }
    }
}