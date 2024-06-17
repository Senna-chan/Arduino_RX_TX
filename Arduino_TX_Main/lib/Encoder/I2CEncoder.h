#ifndef _I2C_ENCODER_H_
#define _I2C_ENCODER_H_

class I2CEncoder : public EncoderBase
{
    public:
    private:
        i2cEncoderLibV2 *encoder;
};

#endif
