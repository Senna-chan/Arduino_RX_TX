using ControllerCompanion.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControllerCompanion
{
    internal class DataGetter
    {
        private enum DataGetterState
        {
            WAITING,
            REQUESTING_RAW,
            REQUESTING_RC,
            REQUESTING_AUX,
            REQUESTING_DETECTION
        }

        private static DataGetterState state = DataGetterState.WAITING;

        private static void checkState()
        {
            if (state != DataGetterState.WAITING)
            {
                Console.WriteLine($"STATE NOT CORRECT, is {state}");
                while (state != DataGetterState.WAITING)
                {
                    Thread.Sleep(10);
                }
            }
        }

        public static void requestAndReadAUX(ushort[] aux_serial)
        {
            checkState();
            state = DataGetterState.REQUESTING_AUX;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'S' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    aux_serial[i] = reader.ReadUInt16();
                }
            }
            state = DataGetterState.WAITING;
        }

        public static void requestAndReadRAW(ushort[] adc, UInt32 io)
        {
            checkState();
            state = DataGetterState.REQUESTING_RAW;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'A' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    adc[i] = reader.ReadUInt16();
                }
                io = reader.ReadUInt32();
            }
            state = DataGetterState.WAITING;
        }

        public static void requestAndReadRC(ushort[] rc_data)
        {
            checkState();
            state = DataGetterState.REQUESTING_RC;
            Config.SelectedSerialPort.Write(new byte[] { (byte)'G', (byte)'R' }, 0, 2);
            using (var reader = new BinaryReader(Config.SelectedSerialPort.BaseStream, Encoding.UTF8, true))
            {
                for (int i = 0; i < Config.RC_MAX_CHANNELS; i++)
                {
                    rc_data[i] = reader.ReadUInt16();
                }
            }
            state = DataGetterState.WAITING;
        }

        public static void requestAndReadDetectionVars(ushort[] adc, ushort[] aux_serial, UInt32 io)
        {
            checkState();
            state = DataGetterState.REQUESTING_DETECTION;
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
            state = DataGetterState.WAITING;
        }
    }
}
