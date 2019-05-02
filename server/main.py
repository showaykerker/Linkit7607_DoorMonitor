from picamera import PiCamera
import time

from flask import Flask
import requests
import Keys

app = Flask(__name__)

camera = PiCamera(resolution=(512, 384))

@app.route('/')
def index():
	return "<h1>HSP</HSP>"

@app.route('/<int:id>')
def AlarmSystem(id):
	time_detected = time.strftime("%Y-%m-%d_%H:%M:%S", time.localtime())
	if id == 0:
		text='HSP已啟動'
	elif id == 1:
		text='HSP警報<br>偵測到大門打開，有未授權進入'
	elif id == 2:
		text='HSP警報已解除'
	else:
		return 'Hi'
	data = {'value1': '<br>'+text} #, 'value2': 'http://youtube.com'}
	r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)

	if id == 1:
		for i in range(20):
			pic_name = time.strftime("%Y-%m-%d_%H:%M:%S", time.localtime())
			pic_name += '_%d.jpg' % i
			camera.capture(pic_name)

	return r.text


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8008)
