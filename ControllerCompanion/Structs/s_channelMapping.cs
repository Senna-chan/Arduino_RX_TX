using ControllerCompanion.Enums;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ControllerCompanion.Structs
{
    public class s_channelMapping : INotifyPropertyChanged
    {
        ChannelConfig parent;
        public s_channelMapping(ChannelConfig parent)
        {
            this.parent = parent;
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        private byte _type; // Type of the channel
        private byte _index; // Index of the channel

        public void UpdateValues(s_channelMapping config)
        {
            type = config.type; 
            index = config.index;
        }

        public byte type
        {
            get { return _type; }
            set
            {
                if (_type != value)
                {
                    _type = value;
                    if (type == ChannelInputTypes.NONE)
                    {
                        intDefinition = 0;
                    }
                    else
                    {
                        intDefinition = _index + (type * ChannelInputTypes.INPUTVALUEBETWEEN);
                    }
                    NotifyPropertyChanged();
                }
            }
        }

        public byte index {
            get { return _index; }
            set
            {
                if (_index != value)
                {
                    _index = value;
                    if (type == ChannelInputTypes.NONE)
                    {
                        intDefinition = 0;
                    }
                    else
                    {
                        intDefinition = _index + (type * ChannelInputTypes.INPUTVALUEBETWEEN);
                    }
                    NotifyPropertyChanged();
                }
            }
        }

        public string strDefinition
        {
            get
            {
                string str = string.Empty;
                switch (type)
                {
                    case ChannelInputTypes.IO:
                        str = "IO";
                    break;
                    
                    case ChannelInputTypes.ADC:
                        str = "ADC";
                    break;

                    case ChannelInputTypes.AUX_IO:
                        str = "AUX_IO";
                    break;

                    case ChannelInputTypes.AUX_SERIAL:
                        str = "AUX_SERIAL";
                    break;

                    default:
                        return "NONE";
                }
                str += index.ToString();
                return str;
            }
            set
            {
                strDefinition = value;
                if (value.StartsWith("IO"))
                {
                    type = ChannelInputTypes.IO;
                    index = Byte.Parse(value.Remove(0, 2));
                }
                if (value.StartsWith("ADC"))
                {
                    type = ChannelInputTypes.ADC;
                    index = Byte.Parse(value.Remove(0, 3));
                }
                if (value.StartsWith("AUX_IO"))
                {
                    type = ChannelInputTypes.AUX_IO;
                    index = Byte.Parse(value.Replace("AUX_IO", ""));
                }
                if (value.StartsWith("AUX_SERIAL"))
                {
                    type = ChannelInputTypes.AUX_SERIAL;
                    index = Byte.Parse(value.Replace("AUX_SERIAL", ""));
                }
                NotifyPropertyChanged();
            }
        }

        public int intDefinition
        {
            get 
            {
                if (type == ChannelInputTypes.NONE)
                {
                    return 0;
                }
                return _index + (ChannelInputTypes.INPUTVALUEBETWEEN * type); 
            }
            set
            {
                if (value == 0)
                {
                    _index = 0;
                    _type = 0;
                }

                _type = (byte)(value / ChannelInputTypes.INPUTVALUEBETWEEN);
                _index = (byte)(value % ChannelInputTypes.INPUTVALUEBETWEEN);
                //if( value >= 50 && value < 100)
                //{
                //    _type = ChannelInputTypes.ADC;
                //    _index = (byte)(value - 50);
                //}
                //if (value >= 100 && value < 150)
                //{
                //    _type = ChannelInputTypes.IO;
                //    _index = (byte)(value - 100);
                //}
                //if (value >= 150 && value < 200)
                //{
                //    _type = ChannelInputTypes.AUX_IO;
                //    _index = (byte)(value - 150);
                //}
                //if (value > 200 && value < 250)
                //{
                //    _type = ChannelInputTypes.AUX_SERIAL;
                //    _index = (byte)(value - 200);
                //}
                NotifyPropertyChanged();
            }
        }
    }
}