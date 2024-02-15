using System;
using System.Collections.Generic;
using System.DirectoryServices.ActiveDirectory;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Enums
{
    public class ChannelInputTypes
    {
        private const int ADC = -1;
        private const int IO = 1;
        private const int NONE = 0;

        public static Dictionary<int, string> inputTypes = new();
        public static void PopulateInputTypes()
        {
            inputTypes.Add(0, "NONE");
            for(int i = 1; i <= 32; i++) {
                inputTypes.Add(i, "IO" + i.ToString());
            }
            for(int i = 1; i <= 10; i++) {
                inputTypes.Add(i * ADC, "ADC" + i.ToString());
            }
        }
    }
}
