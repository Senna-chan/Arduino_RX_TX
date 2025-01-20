using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class RateLimitConfigStruct : StructBase
    {

        public RateLimitConfigStruct()
        {
            outputValuesMax = new s_calibrationConfig();
            outputValuesMax.min = 30;
            outputValuesMax.mid = 60;
            outputValuesMax.max = 100;
            input = new ChannelMappings();
        }


        public ChannelMappings input { get; set; }
        public s_calibrationConfig outputValuesMax { get; set; }

        private Byte _outputToRateLimit;
        public Byte outputToRateLimit
        {
            get { return _outputToRateLimit; }
            set { _outputToRateLimit = value; NotifyPropertyChanged(); }
        }

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

        private bool _analogInput;

        public bool analogInput
        {
            get { return _analogInput; }
            set { _analogInput = value; }
        }


        public void UpdateValues(RateLimitConfigStruct values)
        {
            input.inputs[0].UpdateValues(values.input.inputs[0]);
            input.inputs[1].UpdateValues(values.input.inputs[1]);
            outputValuesMax.UpdateValues(values.outputValuesMax);
            outputToRateLimit = values.outputToRateLimit;
            limitSide = values.limitSide;
            analogInput = values.analogInput;
        }

        public override void WriteValues(BinaryWriter writer)
        {
            foreach (var ratelimitinput in input.inputs)
            {
                ratelimitinput.WriteValues(writer);
            }
            outputValuesMax.WriteValues(writer);
            writer.Write(outputToRateLimit);
            writer.Write(limitSide);
            writer.Write(analogInput);
        }

        public override void ReadValues(BinaryReader reader)
        {
            foreach (var ratelimitinput in input.inputs)
            {
                ratelimitinput.ReadValues(reader);
            }
            outputValuesMax.ReadValues(reader);
            outputToRateLimit = reader.ReadByte();
            limitSide = reader.ReadSByte();
            analogInput = reader.ReadBoolean();
        }
    }
}
