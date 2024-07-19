using ControllerCompanion.Structs;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllerCompanion
{
    public class Config
    {
        public static byte RC_MAX_CHANNELS = 20;
        public static byte SETTINGS_VERSION = 25;
        public static SerialPort SelectedSerialPort;

        public static Settings settings = new Settings();
    }
}
