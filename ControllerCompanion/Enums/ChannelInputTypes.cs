using System;
using System.Collections.Generic;
using System.DirectoryServices.ActiveDirectory;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Enums
{
    public class ChannelInputTypes
    {
        public const int INPUTVALUEBETWEEN = 50;
        public const byte NONE = 0;
        public const byte ADC = 1;
        public const byte IO = 2;
        public const byte AUX_IO = 3;
        public const byte AUX_SERIAL = 4;

        public static Dictionary<int, string> inputTypes = new();
        public static void PopulateInputTypes()
        {
            inputTypes.Add(0, "NONE");
            for(int i = 0; i < 32; i++) {
                if(i < 10) inputTypes.Add(i + (INPUTVALUEBETWEEN * ADC), "ADC" + i.ToString());
                inputTypes.Add(i + (INPUTVALUEBETWEEN * IO), "IO" + i.ToString());
                if (i < 5) inputTypes.Add(i + (INPUTVALUEBETWEEN * AUX_IO), "AUX_IO" + i.ToString());
                if (i < 16) inputTypes.Add(i + (INPUTVALUEBETWEEN * AUX_SERIAL  ), "AUX_SERIAL" + i.ToString());
            }
        }
    }
}
