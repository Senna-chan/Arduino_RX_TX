using Meadow.Devices;
using Meadow.Hardware;

namespace Meadow_TX
{
    public class NRF24
    {
        private IDigitalOutputPort cs;
        private IDigitalOutputPort ce;
        private IDigitalInterruptPort irq;
        private ISpiPeripheral spiPeriph;
        public NRF24(F7Micro device, ISpiBus spi, IPin csPin, IPin cePin, IPin irqPin)
        {
            cs = device.CreateDigitalOutputPort(device.Pins.D03);
            spiPeriph = new SpiPeripheral(spi, cs);
        }
    }
}