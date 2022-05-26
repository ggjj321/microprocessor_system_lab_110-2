def main():
    init()
    adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)	
    # if adc_value < 50: 
    #     GPIO.output(LED1, False)
    #     GPIO.output(LED2, False)
    # elif(adc_value < 300):
    #     GPIO.output(LED1, True)
    #     GPIO.output(LED2, False)
    # else:
    #     GPIO.output(LED1, True)
    #     GPIO.output(LED2, True)
    print(adc_value)
    sys.stdout.flush()
    GPIO.cleanup()