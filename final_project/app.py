import datetime
from email import message
import subprocess
import requests
import threading
from pickle import FALSE
import time
import Jetson.GPIO as GPIO
from flask import Flask, render_template, request
from telegram.ext import Updater, CommandHandler

SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

LED1 = 25
LED2 = 21

output_pin = 12

photo_ch = 0

value_detected = False

app = Flask(__name__)

url = "api"

bot_token = 'bot_token'

bot_chatID = 'bot_chatID'

isDetectValue = False

valueOut = []

mutex = threading.Lock()

lampStatus = False
airStatus = False
fridgeStatus = False

def readadc(adcnum, clockpin, mosipin, misopin, cspin):
    if((adcnum > 7) or (adcnum < 0)):
        return -1
    GPIO.output(cspin, True)

    GPIO.output(clockpin, False)
    GPIO.output(cspin, False)

    commandout = adcnum
    commandout |= 0x18
    commandout <<= 3
    for i in range(5):
        if(commandout & 0x80):
                GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)
        commandout <<=1
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)

    adcout = 0

    for i in range(12):
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
        adcout <<= 1
        if(GPIO.input(misopin)):
            adcout |= 0x1

    GPIO.output(cspin, True)

    adcout >>=1
    return adcout

def lightDetect(arg):
    t = threading.currentThread()
    while getattr(t, "do_detect", True):
        adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
        print(adc_value)
        valueOut.append(adc_value)	
        if(adc_value < 400): 
            GPIO.output(LED1, False)
            GPIO.output(LED2, False)
        elif(adc_value < 900):
            GPIO.output(LED1, True)
            GPIO.output(LED2, False)
        else:
            GPIO.output(LED1, True)
            GPIO.output(LED2, True)
        time.sleep(0.5)

valueThreads = [threading.Thread(target=lightDetect, args=("task",))]
    
@app.route("/")
def home():
    tonow = datetime.datetime.now()
    
    data = requests.get(url)   
    data_json = data.json()
    try:
        information_list = data_json["records"]["location"][0]["weatherElement"]

        for data in information_list:
            if data['elementName'] == "TEMP":
                temp = data['elementValue']
            if data['elementName'] == "HUMD":
                humd = data['elementValue']
    except:
        temp = "30"
        humd = "1"

    info = {
        "year" : tonow.year,
        "month" : tonow.month,
        "day" : tonow.day,
        "temp" : temp,
        "humd" : humd
    }

    return render_template('index.html', appInfo= info)


@app.route("/index2")
def Control():
    tonow = datetime.datetime.now()
    
    data = requests.get(url)   
    data_json = data.json()
    try:
        information_list = data_json["records"]["location"][0]["weatherElement"]

        for data in information_list:
            if data['elementName'] == "TEMP":
                temp = data['elementValue']
            if data['elementName'] == "HUMD":
                humd = data['elementValue']
    except:
        temp = "30"
        humd = "1"

    info = {
        "year" : tonow.year,
        "month" : tonow.month,
        "day" : tonow.day,
        "temp" : temp,
        "humd" : humd
    }

    return render_template('index2.html', appInfo= info)

@app.route("/submit", methods=['GET'])
def submit():
    switch = request.args.get('switch')
    try:
        subprocess.Popen(["sudo", "./L2Program", "LED1", switch])
    except:
        LED1 = "none"
    
    try:
        subprocess.Popen(["sudo", "./L2Program", "LED2", switch])
    except:
        LED2 = "none"   

    return "success"

@app.route("/mode", methods=['GET'])
def modeDetect():
    mode = request.args.get('detect')    
    if(mode == 'yes'):
        bot_message = "現在是偵測模式"
        send_text = 'https://api.telegram.org/bot' + bot_token + '/sendMessage?chat_id=' + bot_chatID + '&parse_mode=Markdown&text=' + bot_message
        response = requests.get(send_text)
        valueThreads[-1].start()
            
    elif(mode == 'no'):
        bot_message = '現在不是偵測模式'   
        GPIO.output(LED1, False)
        GPIO.output(LED2, False)
        valueOut = []
        valueThreads[-1].do_detect = False
        valueThreads.append(threading.Thread(target=lightDetect, args=("task",)))
        send_text = 'https://api.telegram.org/bot' + bot_token + '/sendMessage?chat_id=' + bot_chatID + '&parse_mode=Markdown&text=' + bot_message
        response = requests.get(send_text)

    return response.json()

@app.route("/mutex")
def mutexShine():
    times = request.args.get('times')
    frequent = request.args.get('frequent')
    subprocess.Popen(["sudo", "./mutex", "1001", times, frequent])
    return "success"

@app.route("/semphore")
def mutexSemphore():
    times = request.args.get('times')
    frequent = request.args.get('frequent')
    subprocess.Popen(["sudo", "./sempahore", "1001", times, frequent])
    return "success"

@app.route("/catchValue")
def catchValue():
    return str(valueOut[-1])

@app.route("/drive")
def drive():
    global lampStatus
    global airStatus
    global fridgeStatus

    led = request.args.get('led')
    switch = request.args.get('open')

    if switch == "on":
        status = True
    else:
        status = False

    if led == "LED1":
        mutex.acquire()      
        lampStatus = status
        mutex.release()
    if led == "LED2":
        mutex.acquire() 
        airStatus = status 
        mutex.release()   
    if led == "LED3":
        mutex.acquire() 
        fridgeStatus = status  
        mutex.release()
    
    subprocess.Popen(["sudo", "./drive", led, switch])

    return "success"

class FlaskThread(threading.Thread):
    def run(self) -> None:
        #app.run(host='0.0.0.0', port=8080)
        app.run(host="192.168.55.1", port=5000) 

class TelegramThread(threading.Thread):
    def run(self) -> None:
        updater = Updater(bot_token)

        updater.dispatcher.add_handler(CommandHandler('hello', self.hello))
        updater.dispatcher.add_handler(CommandHandler('check_lamp', self.lampStatus))
        updater.dispatcher.add_handler(CommandHandler('check_air', self.airStatus))
        updater.dispatcher.add_handler(CommandHandler('check_drying', self.fridgeStatus))

        updater.start_polling()
        updater.idle()

    def hello(self, update, context):
        update.message.reply_text("Hi")
    
    def lampStatus(self, update, context):
        global lampStatus
        message = "電燈狀態 :"
        if lampStatus == False:
            message += "關"
        else:
            message += "開"
        update.message.reply_text(message)
    
    def airStatus(self, update, context):
        global airStatus
        message = "冷氣狀態 :"
        if airStatus == False:
            message += "關"
        else:
            message += "開"
        update.message.reply_text(message)

    def fridgeStatus(self, update, context):
        global fridgeStatus
        message = "烘乾狀態 :"
        if fridgeStatus == False:
            message += "關"
        else:
            message += "開"
        update.message.reply_text(message)
     
if __name__ == '__main__':
    flask_thread = FlaskThread()
    flask_thread.start()

    telegram_thread = TelegramThread()
    telegram_thread.start()

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(output_pin, GPIO.OUT, initial = GPIO.HIGH)
    GPIO.setwarnings(False)	
            
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)

    GPIO.setup(SPIMOSI, GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    GPIO.setup(SPICLK, GPIO.OUT)
    GPIO.setup(SPICS, GPIO.OUT)
       
    GPIO.setup(LED1, GPIO.OUT)
    GPIO.setup(LED2, GPIO.OUT)
