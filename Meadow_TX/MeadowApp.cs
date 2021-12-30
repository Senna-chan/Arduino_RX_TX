using System;
using System.Threading;
using Meadow;
using Meadow.Devices;
using Meadow.Hardware;
namespace Meadow_TX
{
    public class MeadowApp : App<F7Micro, MeadowApp>
    {
        IDigitalOutputPort redLed;
        IDigitalOutputPort blueLed;
        IDigitalOutputPort greenLed;
        IAnalogInputPort RCAY = Device.CreateAnalogInputPort(Device.Pins.A00);
        IAnalogInputPort RCAX = Device.CreateAnalogInputPort(Device.Pins.A01);
        IAnalogInputPort RCBY = Device.CreateAnalogInputPort(Device.Pins.A02);
        IAnalogInputPort RCBX = Device.CreateAnalogInputPort(Device.Pins.A03);
        IAnalogInputPort RCM1 = Device.CreateAnalogInputPort(Device.Pins.A04);
        IAnalogInputPort RCM2 = Device.CreateAnalogInputPort(Device.Pins.A05);
        ISpiBus spiBus = Device.CreateSpiBus();
        NRF24 nrf24;

        
        public MeadowApp()
        {
            ConfigurePorts();

            nrf24 = new NRF24(Device, spiBus, Device.Pins.D00, Device.Pins.D01, Device.Pins.D02);
        }

        public void ConfigurePorts()
        {
            Console.WriteLine("Creating Outputs...");

        }
    }
}
