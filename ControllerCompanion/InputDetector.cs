using ControllerCompanion.Enums;
using ControllerCompanion.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
namespace ControllerCompanion
{
    internal class InputDetector
    {
        public static bool detectionRunning = false;
        static private UInt32 IOBits = 0;
        static private ushort[] ADCChannels = new ushort[Config.RC_MAX_CHANNELS];
        static private ushort[] AUX_Serial_Channels = new ushort[Config.RC_MAX_CHANNELS];
        static private UInt32 InitialIOBits = 0;
        static private ushort[] InitialADCChannels = new ushort[Config.RC_MAX_CHANNELS];
        static private ushort[] InitialAUX_Serial_Channels = new ushort[Config.RC_MAX_CHANNELS];

        public static bool detectSequence(Action<byte, byte, byte> setChannelMapping, byte input)
        {
            if (detectionRunning)
            {
                return false;
            }
            detectionRunning = true;
            new Thread(() =>
            {
                Thread.CurrentThread.Name = "InputDetector";
                Console.WriteLine("Starting input detection");
                TX_Communicator.requestAndReadDetectionVars(InitialADCChannels, InitialAUX_Serial_Channels, ref InitialIOBits);

                while (detectionRunning)
                {
                    TX_Communicator.requestAndReadDetectionVars(ADCChannels, AUX_Serial_Channels, ref IOBits);
                    for (byte i = 0; i < Config.RC_MAX_CHANNELS; i++)
                    {
                        short initADC = (short)InitialADCChannels[i];
                        short curADC = (short)ADCChannels[i];
                        short initAS = (short)InitialAUX_Serial_Channels[i];
                        short curAS = (short)AUX_Serial_Channels[i];
                        if (i < 12)
                        {
                            if(Math.Abs(initADC - curADC) > 200)
                            {
                                Console.WriteLine($"ADCChannel {i} detected", i);
                                setChannelMapping(ChannelInputTypes.ADC, i, input);
                                detectionRunning = false;
                                return;
                            }
                        }
                        if (Math.Abs(initAS - curAS) > 200)
                        {
                            Console.WriteLine($"AUX_SerialChannel {i} detected", i);
                            setChannelMapping(ChannelInputTypes.AUX_SERIAL, i, input);
                            detectionRunning = false;
                            return;
                        }
                        var newbit = (IOBits >> i) & 1;
                        var prevbit = (InitialIOBits >> i) & 1;
                        if(newbit != prevbit)
                        {
                            Console.WriteLine($"IOBit {i} detected", i);
                            setChannelMapping(ChannelInputTypes.IO, i, input);
                            detectionRunning = false;
                            return;
                        }
                    }
                    Thread.Sleep(100);
                }
            }).Start();

            return true;
        }
    }
}
