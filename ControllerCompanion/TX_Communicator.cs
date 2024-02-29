using ControllerCompanion.Structs;
using ControllerCompanion.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion
{
    internal class TX_Communicator
    {
        private enum CommunicationState
        {
            WAITING,
            REQUESTING_RAW,
            REQUESTING_RC,
            REQUESTING_AUX,
            REQUESTING_DETECTION,
            REQUESTING_RC_CHANNEL,
            REQUESTING_SETTINGS,
            TRANSMITTING_SETTINGS,
            TRANSMITTING_CHANNEL_CONFIG
        }

        public static void transmitChannelConfig(ChannelConfig channelConfig)
        {
            if (!checkState()) return;

            state = CommunicationState.TRANSMITTING_CHANNEL_CONFIG;

            using (var writer = new BinaryWriter(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                writer.Write('C');
                writer.Write(channelConfig.adcConfig.min);
                writer.Write(channelConfig.adcConfig.mid);
                writer.Write(channelConfig.adcConfig.max);

                writer.Write(channelConfig.trim);
                writer.Write(channelConfig.failsafe);
                writer.Write(channelConfig.startup);
                writer.Write(channelConfig.outputMode);
                writer.Write(channelConfig.centeredStick);

                writer.Write(channelConfig.endPoints.min);
                writer.Write(channelConfig.endPoints.mid);
                writer.Write(channelConfig.endPoints.max);

                writer.Write(channelConfig.pwmConfig.frequency);

                writer.Write(channelConfig.stepperConfig.minFrequency);
                writer.Write(channelConfig.stepperConfig.maxFrequency);

                foreach (var channelMapping in channelConfig.channelMapping)
                {
                    writer.Write(channelMapping.type);
                    writer.Write(channelMapping.index);
                }
                writer.Write(channelConfig.reversed);
                writer.Flush();
            }
            state = CommunicationState.WAITING;
        }

        public static void requestAndReadAUX(ushort[] aux_serial)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_AUX;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'S' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    aux_serial[i] = reader.ReadUInt16();
                }
            }
            state = CommunicationState.WAITING;
        }

        public static void requestAndReadRAW(ushort[] adc, ref UInt32 io)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_RAW;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'A' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    adc[i] = reader.ReadUInt16();
                }
                io = reader.ReadUInt32();
            }
            state = CommunicationState.WAITING;
        }

        public static void requestAndReadRC(ushort[] rc_data)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_RC;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'R' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    rc_data[i] = reader.ReadUInt16();
                }
            }
            state = CommunicationState.WAITING;
        }

        public static void requestAndReadDetectionVars(ushort[] adc, ushort[] aux_serial, ref UInt32 io)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_DETECTION;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'D' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    adc[i] = reader.ReadUInt16();
                }
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    aux_serial[i] = reader.ReadUInt16();
                }
                io = reader.ReadUInt32();
            }
            state = CommunicationState.WAITING;
        }

        public static void requestAndReadRCChannel(ref UInt16 rc_value)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_RC_CHANNEL;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'C' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                rc_value = reader.ReadUInt16();
            }
            state = CommunicationState.WAITING;
        }

        public static void requestSettings(ref Settings settings)
        {
            if (!checkState()) return;
            state = CommunicationState.REQUESTING_SETTINGS;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'R' }, 0, 1);
            Thread.Sleep(1000);
            Console.WriteLine($"Got {Config.SelectedSerialPort.BytesToRead} bytes to read");
            Settings.readBinary(Config.SelectedSerialPort.BaseStream, settings, true);
            if (Config.SelectedSerialPort.BytesToRead > 0)
            {
                Console.WriteLine($"Still got bytes left. {Config.SelectedSerialPort.BytesToRead}");
                Config.SelectedSerialPort.ReadExisting();
            }
            state = CommunicationState.WAITING;
        }

        public static void transmitSettings(Settings settings)
        {
            if (!checkState()) return;
            state = CommunicationState.TRANSMITTING_SETTINGS;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'T' }, 0, 1);
            try
            {
                Settings.writeBinary(Config.SelectedSerialPort.BaseStream, settings, true);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            state = CommunicationState.WAITING;
        }

        private static CommunicationState state = CommunicationState.WAITING;

        private static bool checkState(CommunicationState stateToCheck = CommunicationState.WAITING)
        {
            if (Config.SelectedSerialPort == null || !Config.SelectedSerialPort.IsOpen)
            {
                return false;
            }
            if (state != stateToCheck)
            {
                Console.WriteLine($"STATE NOT CORRECT, want {stateToCheck} is {state} ");
                while (state != stateToCheck)
                {
                    Thread.Sleep(10);
                }
            }
            return true;
        }
    }
}
