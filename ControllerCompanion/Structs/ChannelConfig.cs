using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using ControllerCompanion.Structs.HelperClasses;

namespace ControllerCompanion.Structs
{
    public class ChannelConfig : StructBase
    {
        public s_calibrationConfig adcConfig { get; set; }
        private Int16 _trim;
        private UInt16 _failsafe;
        public UInt16 _startup;
        private byte _outputMode;
        private bool _centeredStick;
        public s_calibrationConfig endPoints { get; set; }
        public s_pwmConfig pwmConfig { get; set; }
        public s_stepperConfig stepperConfig { get; set; }
        public ChannelMappings channelMapping { get; set; }

        // CompanionOnlyStuff
        public bool reversed { get; set; }

        public ChannelConfig()
        {
            adcConfig = new s_calibrationConfig();
            pwmConfig = new s_pwmConfig();
            stepperConfig = new s_stepperConfig();
            channelMapping = new ChannelMappings();
            endPoints = new s_calibrationConfig();
        }

        public void UpdateValues(ChannelConfig config)
        {
            adcConfig.UpdateValues(config.adcConfig);
            trim = config.trim;
            failsafe = config.failsafe;
            startup = config.startup;
            outputMode = config.outputMode;
            centeredStick = config.centeredStick;
            endPoints.UpdateValues(config.endPoints);
            pwmConfig.UpdateValues(config.pwmConfig);
            stepperConfig.UpdateValues(config.stepperConfig);
            channelMapping.inputs[0].UpdateValues(config.channelMapping.inputs[0]);
            channelMapping.inputs[1].UpdateValues(config.channelMapping.inputs[1]);
        }

        public override void WriteValues(BinaryWriter writer)
        {
            adcConfig.WriteValues(writer);
            writer.Write(trim);
            writer.Write(failsafe);
            writer.Write(startup);
            writer.Write(outputMode);
            writer.Write(centeredStick);
            endPoints.WriteValues(writer);
            pwmConfig.WriteValues(writer);
            stepperConfig.WriteValues(writer);
            foreach (var channel in channelMapping.inputs)
            {
                channel.WriteValues(writer);
            }
        }

        public override void ReadValues(BinaryReader reader)
        {
            adcConfig.ReadValues(reader);
            trim = reader.ReadInt16();
            failsafe = reader.ReadUInt16();
            startup = reader.ReadUInt16();
            outputMode = reader.ReadByte();
            centeredStick = reader.ReadBoolean();
            endPoints.ReadValues(reader);
            pwmConfig.ReadValues(reader);
            stepperConfig.ReadValues(reader);
            foreach (var channel in channelMapping.inputs)
            {
                channel.ReadValues(reader);
            }
        }

        public Int16 trim
        {
            get { return _trim; }
            set
            {
                if(value != this._trim)
                {
                    this._trim = value;
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 failsafe
        {
            get { return _failsafe; }
            set
            {
                if (value != this._failsafe)
                {
                    this._failsafe = value;
                    NotifyPropertyChanged();
                }
            }
        }
        public UInt16 startup
        {
            get { return _startup; }
            set
            {
                if (value != this._startup)
                {
                    this._startup = value;
                    NotifyPropertyChanged();
                }
            }
        }
        public byte outputMode {
            get { return _outputMode; }
            set
            {
                if(value != this._outputMode)
                {
                    this._outputMode = value;
                    NotifyPropertyChanged();
                }
            }
        }

        public bool centeredStick
        {
            get { return _centeredStick; }
            set
            {
                if(value != this._centeredStick)
                {
                    this._centeredStick = value;
                    NotifyPropertyChanged();
                }
            }
        }

    }
}
