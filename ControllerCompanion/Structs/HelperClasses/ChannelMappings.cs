using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion.Structs.HelperClasses
{
    public class ChannelMappings
    {
        public s_channelMapping[] inputs { get; set; }
        public ChannelMappings() 
        {
            inputs = new s_channelMapping[2];
            inputs[0] = new s_channelMapping();
            inputs[1] = new s_channelMapping();
        }

        public override string? ToString()
        {
            return $"Input 1: {inputs[0]}, Input 2: {inputs[1]}";
        }
    }
}
