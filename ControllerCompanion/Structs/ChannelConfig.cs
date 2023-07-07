using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Structs
{
    public class ChannelConfig : INotifyPropertyChanged
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

        private UInt16 minValue;
        private UInt16 midValue;
        private UInt16 maxValue;


        public UInt16 chMin
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
        public UInt16 chMid
        {
            get { return midValue; }
            set
            {
                if (value != this.midValue)
                {
                    if(!(value < this.minValue || value > this.maxValue) || value == 0)
                    {
                        this.midValue = value;
                    }
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 chMax
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
        private Int16 _chOffset;
        public Int16 chOffset
        {
            get { return _chOffset; }
            set
            {
                if(value != this._chOffset)
                {
                    this._chOffset = value;
                    NotifyPropertyChanged();
                }
            }
        }
        private UInt16 _chDefaults;
        public UInt16 chDefaults
        {
            get { return _chDefaults; }
            set
            {
                if (value != this._chDefaults)
                {
                    this._chDefaults = value;
                    NotifyPropertyChanged();
                }
            }
        }
        private byte _outputMode;
        public byte outputMode {
            get { return _outputMode; }
            set
            {
                if(value != this._outputMode)
                {
                    this._outputMode = value;
                    NotifyPropertyChanged();
                }
            }
        }

        private bool _centeredStick;
        public bool centeredStick
        {
            get { return _centeredStick; }
            set
            {
                if(value != this._centeredStick)
                {
                    this._centeredStick = value;
                    NotifyPropertyChanged();
                }
            }
        }

        public s_pwmConfig pwmConfig { get; set; }
        public s_stepperConfig stepperConfig { get; set; }
        public s_channelMapping[] channelMapping { get; set; }
        
        // CompanionOnlyStuff
        public bool reversed { get; set; }

        public ChannelConfig()
        {
            chMax = 1023;
            chMin = 0;
            chMid = 512;
            pwmConfig = new s_pwmConfig();
            stepperConfig = new s_stepperConfig();
            channelMapping = new s_channelMapping[2];
            for(int i = 0; i < 2; i++)
                channelMapping[i] = new s_channelMapping();
        }
    }
}
