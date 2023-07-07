﻿using ControllerCompanion.Structs;
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
        public static byte RC_MAX_CHANNELS = 24;
        public static byte SETTINGS_VERSION = 21;
        public static SerialPort SelectedSerialPort;

        public static Settings settings = new Settings();
    }
}
