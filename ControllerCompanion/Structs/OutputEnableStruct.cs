using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Structs
{
    public class OutputEnableStruct : INotifyPropertyChanged
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

        public s_channelMapping inputIO;

        private UInt32 _ouputsToEnable;

        public UInt32 outputsToEnable
        {
            get { 
                return _ouputsToEnable; 
            }
            set { 
                _ouputsToEnable = value;
                NotifyPropertyChanged();
            }
        }

        void UpdateValues(OutputEnableStruct value)
        {
            inputIO.UpdateValues(value.inputIO);
            outputsToEnable = value.outputsToEnable;
        }

        public OutputEnableStruct()
        {
            inputIO = new s_channelMapping();
            outputsToEnable = 0;
        }
    }
}
