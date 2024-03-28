using ControllerCompanion.Enums;
using ControllerCompanion.Structs.HelperClasses;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ControllerCompanion.Structs
{
    public class s_calibrationConfig : StructBase
    {

        public s_calibrationConfig() {
            max = 0;
            min = 0;
            mid = 0;
        }

        private UInt16 _min; // ADC Minumum
        private UInt16 _mid; // ADC Midium
        private UInt16 _max; // ADC Max


        public void UpdateValues(s_calibrationConfig config)
        {
            max = config.max;
            min = config.min;
            mid = config.mid;
        }

        public UInt16 min
        {
            get { return _min; }
            set
            {
                if (value != this._min)
                {
                    _min = value;
                    if (_mid != 0)
                    {
                        if(value > _mid)
                        {
                            _min = _mid;
                        }
                    }
                    else if(_max != 0)
                    {
                        if(value > _max)
                        {
                            _min = _max;
                        }
                    }
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 mid
        {
            get { return _mid; }
            set
            {
                if (value != this._mid)
                {
                    _mid = value;
                    if (_max != 0)
                    {
                        if(value > _max)
                        {
                            _mid = _max;
                        }
                        else
                        {
                            _mid = value;
                        }
                    }
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 max
        {
            get { return _max; }
            set
            {
                if (value != this._max)
                {
                    _max = value;
                    if (_mid != 0)
                    {
                        if(value < _mid)
                        {
                            _max = _mid;
                        }
                        else
                        {
                            _max = value;
                        }
                    }
                    NotifyPropertyChanged();
                }
            }
        }

        public override string? ToString()
        {
            return $"Min {_min}, mid {_mid}, max {_max}";
        }

        public override void WriteValues(BinaryWriter writer)
        {
            writer.Write(min);
            writer.Write(mid);
            writer.Write(max);
        }

        public override void ReadValues(BinaryReader reader)
        {
            _max = 0;
            _mid = 0;
            _min = 0;
            _min = reader.ReadUInt16();
            _mid = reader.ReadUInt16();
            _max = reader.ReadUInt16();
        }
    }
}
