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

        private Int16 _trim;
        private UInt16 _failsafe;
        private byte _outputMode;
        private bool _centeredStick;

        public void UpdateValues(ChannelConfig config)
        {
            trim = config.trim;
            failsafe = config.failsafe;
            outputMode = config.outputMode;
            centeredStick = config.centeredStick;
            channelMapping[0].UpdateValues(config.channelMapping[0]);
            channelMapping[1].UpdateValues(config.channelMapping[1]);
            adcConfig.UpdateValues(config.adcConfig);
        }

        
        public Int16 trim
        {
            get { return _trim; }
            set
            {
                if(value != this._trim)
                {
                    this._trim = value;
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 failsafe
        {
            get { return _failsafe; }
            set
            {
                if (value != this._failsafe)
                {
                    this._failsafe = value;
                    NotifyPropertyChanged();
                }
            }
        }
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

        public s_adcConfig adcConfig { get; set; }
        public s_pwmConfig pwmConfig { get; set; }
        public s_stepperConfig stepperConfig { get; set; }
        public s_channelMapping[] channelMapping { get; set; }
        
        // CompanionOnlyStuff
        public bool reversed { get; set; }

        public ChannelConfig()
        {
            adcConfig = new s_adcConfig();
            pwmConfig = new s_pwmConfig();
            stepperConfig = new s_stepperConfig();
            channelMapping = new s_channelMapping[2];
            for(int i = 0; i < 2; i++)
                channelMapping[i] = new s_channelMapping();
        }
    }
}
