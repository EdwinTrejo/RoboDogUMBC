from flask import Flask
from io import StringIO
import json
import codecs
import serial

ser = serial.Serial('/dev/serial0', 9600, timeout=1)
if (ser.isOpen() == True):
    ser.close()
    ser.open()

app = Flask(__name__)

actionID = 0

@app.route('/')
def index():
    ser.write("system start")
    return 'welcome'

@app.route('/reset')
def resetAction():
    ser.close()
    ser.open()
    ser.write("testing")
    return 'System Reset'

@app.route('/start')
def startAction():
    ser.open()
    ser.write("testing")
    return 'System Start'

@app.route('/close')
def closeAction():
    ser.write("Closing Connection")
    ser.close()
    return 'System Close'

@app.route('/change/<int:newID>')
def newIdAction(newID):
    actionID = newID
    print(actionID)
    serializeAction(actionID)
    return 'Success'

def serializeAction(actionID):
    #send the serialized data
    data3 = str(actionID).encode()
    #data2 = chr(actionID)
    #data = bytes(data2)  # encoded to UTF-8
    print(data3)
    ser.write(data3)
    #sendData = json.dumps(actionID, default=convert)
    #print(sendData)
    
def convert(o):
    if isinstance(o, numpy.int64): return int(o)
    raise TypeError

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

