using ControllerCompanion.Enums;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ControllerCompanion.Structs
{
    public class s_adcConfig : INotifyPropertyChanged
    {

        public s_adcConfig() {
            max = 1023;
            min = 0;
            mid = 512;
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

        private UInt16 minValue; // ADC Minumum
        private UInt16 midValue; // ADC Midium
        private UInt16 maxValue; // ADC Max
        

        public void UpdateValues(s_adcConfig config)
        {
            max = config.max;
            min = config.min;
            mid = config.mid;
        }

        public UInt16 min
        {
            get { return minValue; }
            set
            {
                if (value != this.minValue)
                {
                    if (value > this.midValue && this.midValue != 0)
                    {
                        this.minValue = this.midValue;
                    }
                    else
                    {
                        this.minValue = value;
                    }
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 mid
        {
            get { return midValue; }
            set
            {
                if (value != this.midValue)
                {
                    if (!(value < this.minValue || value > this.maxValue) || value == 0)
                    {
                        this.midValue = value;
                    }
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 max
        {
            get { return maxValue; }
            set
            {
                if (value != this.maxValue)
                {

                    if (value < this.midValue && this.midValue != 0)
                    {
                        this.maxValue = this.midValue;
                    }
                    else
                    {
                        this.maxValue = value;
                    }
                    NotifyPropertyChanged();
                }
            }
        }
    }
}