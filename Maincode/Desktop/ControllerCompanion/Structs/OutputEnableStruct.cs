using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class OutputEnableStruct : StructBase
    {
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

        public void UpdateValues(OutputEnableStruct value)
        {
            inputIO.UpdateValues(value.inputIO);
            outputsToEnable = value.outputsToEnable;
        }

        public override void WriteValues(BinaryWriter writer)
        {
            inputIO.WriteValues(writer);
            writer.Write(outputsToEnable);
        }

        public override void ReadValues(BinaryReader reader)
        {
            inputIO.ReadValues(reader);
            outputsToEnable = reader.ReadUInt32();
        }

        public OutputEnableStruct()
        {
            inputIO = new s_channelMapping();
            outputsToEnable = 0;
        }
    }
}
