from pickle import FALSE
import Jetson.GPIO as GPIO
import time
import sys

LED1 = 4
LED2 = 27

def init():
    GPIO.setmode(GPIO.BCM)

    GPIO.setup(LED1, GPIO.OUT)
    GPIO.setup(LED2, GPIO.OUT)

def main():
    init()
    adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)	
    if adc_value < 50: 
        GPIO.output(LED1, False)
        GPIO.output(LED2, False)
    elif(adc_value < 300):
        GPIO.output(LED1, True)
        GPIO.output(LED2, False)
    else:
        GPIO.output(LED1, True)
        GPIO.output(LED2, True)