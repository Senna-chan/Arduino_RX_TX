using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Structs
{
    public class RateLimitConfigStruct : INotifyPropertyChanged
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

        public RateLimitConfigStruct()
        {
            outputValuesMax = new s_calibrationConfig
            {
                max = 2000,
                min = 1200,
                mid = 1600,
            };
            input = new s_channelMapping[2];
            input[0] = new s_channelMapping();
            input[1] = new s_channelMapping();
        }

        public s_channelMapping[] input { get; set; }
        public s_calibrationConfig outputValuesMax { get; set; }

        private sbyte _limitSide;

        public sbyte limitSide
        {
            get { return _limitSide; }
            set
            {
                _limitSide = value;
                NotifyPropertyChanged();
            }
        }

        private Byte _outputToRateLimit;

        public Byte outputToRateLimit
        {
            get { return _outputToRateLimit; }
            set { _outputToRateLimit = value; NotifyPropertyChanged(); }
        }

        public void UpdateValues(RateLimitConfigStruct values)
        {
            limitSide = values.limitSide;
            outputToRateLimit = values.outputToRateLimit;
            input[0].UpdateValues(values.input[0]);
            input[1].UpdateValues(values.input[1]);
            outputValuesMax.UpdateValues(values.outputValuesMax);
        }

        //typedef struct
        //{
        //    s_channelMapping input[2]; // Two needed since we can have two IO ports for low, mid and high
        //    uint16_t outputValuesMax[3]; // 3, for low speed, mid speed and high speed
        //    uint32_t outputsToRateLimit;
        //    int8_t limitSide;   // If 0 then both, if -1 then only min to mid, if 1 then only mid to max.
        //} rateLimitConfigStruct;

    }
}
