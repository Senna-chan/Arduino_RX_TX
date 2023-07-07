using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ControllerCompanion.Structs
{
    public class s_channelMapping : INotifyPropertyChanged
    {

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

        private sbyte _type;
        public sbyte type
        {
            get { return _type; }
            set
            {
                if (_type != value)
                {
                    _type = value;
                    intDefinition = _index * type;
                    NotifyPropertyChanged();
                }
            }
        }
        private byte _index;
        public byte index {
            get { return _index; }
            set
            {
                if (_index != value)
                {
                    _index = value;
                    intDefinition = _index * type;
                    NotifyPropertyChanged();
                }
            }
        }

        public string strDefinition
        {
            get
            {
                string str = string.Empty;
                if (type == 1) 
                    return "IO" + index.ToString();
                if (type == -1) 
                    return "ADC" + index.ToString();

                return "NONE";
            }
            set
            {
                strDefinition = value;
                if (value.StartsWith("IO"))
                {
                    type = 1;
                    index = Byte.Parse(value.Remove(0, 2));
                }
                if (value.StartsWith("ADC"))
                {
                    type = -1;
                    index = Byte.Parse(value.Remove(0, 3));
                }
                NotifyPropertyChanged();
            }
        }

        public int intDefinition
        {
            get { return _index * _type; }
            set
            {
                if (value == 0)
                {
                    _index = 0;
                    _type = 0;
                }
                if( value > 0)
                {
                    _type = 1;
                    _index = (byte)value;
                }
                if(value < 0)
                {
                    _type = -1;
                    _index = (byte)Math.Abs(value);
                }
                NotifyPropertyChanged();
            }
        }
    }
}