import csv
import time

import geocoder
import requests
import serial

myloc = geocoder.ip('me')
p=""
p+=str("Accident detected at:\n")
sas=f'{p}'
s=""
s+=str(myloc.lat+.1023636)
#
s+=','
s+=str(myloc.lng-.0704448)
#
url=f'https://www.google.com/maps/search/?api=1&query={s}'
s1=requests.post(url,json=s)

from twilio.rest import Client

account_sid = 'ACb7d86fd535c28891a8cd2788685350ba'
auth_token = 'd61f658059c0f65ab9dae009f36e0b2e'
client = Client(account_sid, auth_token)
ArduinoSerial=serial.Serial('com12',115200)
data=ArduinoSerial.readline()

if data==b'1\r\n':
    message = client.messages.create(
                            from_='+16072603826',
                            body=(sas+url),
                            to='+9163097xxxxx',
                        )

    print("\n*********** Accident Detected ***********")
    print("Hello, this is an automated message from AcciAlert. \nSorry to inform you that the Vehicle with Reg No: KA19 HQ 5970 has been involved in an accident.\nPlease take appropriate action as necessary.")
    print("\nLattitude, Longitude =",myloc.latlng)
    print("\nMessage sent:")
    print(message.sid)
    

with open('dataset.csv', 'r') as file:
    reader = csv.reader(file)
    dataset = list(reader)[1:]

while True:
    x = float(ArduinoSerial.readline().strip())
    y = float(ArduinoSerial.readline().strip())
    z = float(ArduinoSerial.readline().strip())

    accident_occurred = False
    accident_type = 'None'
    for data in dataset:
        if abs(x - float(data[0])) < 0.1 and abs(y - float(data[1])) < 0.1 and abs(z - float(data[2])) < 0.1:
            accident_occurred = True
            accident_type = data[3]
            break
        

