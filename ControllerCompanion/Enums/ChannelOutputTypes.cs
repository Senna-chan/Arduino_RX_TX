using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Enums
{
    public class ChannelOutputTypes
    {
        public enum outputModes
        {
            OUTPUTMODE_NONE =0,
            OUTPUTMODE_RC   =1,
            OUTPUTMODE_IO 	=2,
            OUTPUTMODE_PWM 	=3,
            OUTPUTMODE_STEP	=4,
            OUTPUTMODE_DAC 	=5,

        }
        public enum outputTypes
        {
            RC_NONE = outputModes.OUTPUTMODE_NONE,
            RCIO = ((1 << outputModes.OUTPUTMODE_RC) | (1 << outputModes.OUTPUTMODE_IO))                                                              ,
            RCIODAC =           ((1 << outputModes.OUTPUTMODE_RC) | (1 << outputModes.OUTPUTMODE_IO) | (1 << outputModes.OUTPUTMODE_DAC))                         ,
            RCIOPWM =           ((1 << outputModes.OUTPUTMODE_RC) | (1 << outputModes.OUTPUTMODE_IO) | (1 << outputModes.OUTPUTMODE_PWM))                         ,
            RCIOPWMSTEP =       ((1 << outputModes.OUTPUTMODE_RC) | (1 << outputModes.OUTPUTMODE_IO) | (1 << outputModes.OUTPUTMODE_PWM) | (1 << outputModes.OUTPUTMODE_STEP)),
        }
        private static outputTypes[] channelOutputs =
        {
            outputTypes.RCIOPWM, // CH1
	        outputTypes.RCIOPWM, // CH2
	        outputTypes.RCIO,
            outputTypes.RCIO,
            outputTypes.RCIODAC,
            outputTypes.RCIODAC,
            outputTypes.RCIO,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RCIO,
            outputTypes.RCIO,
            outputTypes.RCIO,
            outputTypes.RCIO,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RCIOPWMSTEP,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE,
            outputTypes.RC_NONE
        };
        public static outputTypes GetOutputTypesForChannel(int channel)
        {
            return channelOutputs[channel];
        }

        public static Dictionary<byte, string> GetItemsForChannel(int channel) {
            Dictionary<byte, string> result = new();
            outputTypes outputType = GetOutputTypesForChannel(channel);

            result.Add((byte)outputModes.OUTPUTMODE_NONE, "NONE");
            if (outputType != outputTypes.RC_NONE)
            {
                result.Add((byte)outputModes.OUTPUTMODE_RC,"RC");
                if (outputType == outputTypes.RCIO)
                {
                    result.Add((byte)outputModes.OUTPUTMODE_IO, "IO");
                }

                if (outputType == outputTypes.RCIODAC)
                {
                    result.Add((byte)outputModes.OUTPUTMODE_IO, "IO");
                    result.Add((byte)outputModes.OUTPUTMODE_DAC, "DAC");
                }

                if (outputType == outputTypes.RCIOPWM)
                {
                    result.Add((byte)outputModes.OUTPUTMODE_IO, "IO");
                    result.Add((byte)outputModes.OUTPUTMODE_PWM, "PWM");
                }

                if (outputType == outputTypes.RCIOPWMSTEP)
                {
                    result.Add((byte)outputModes.OUTPUTMODE_IO, "IO");
                    result.Add((byte)outputModes.OUTPUTMODE_PWM, "PWM");
                    result.Add((byte)outputModes.OUTPUTMODE_STEP, "STEPPER");
                }
            }
            
            return result;
        }
    }
}
