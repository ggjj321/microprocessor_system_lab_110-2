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