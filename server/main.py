from camera_pi import Camera
import Keys
import UploadToGdrive as UTGD

import time, os
from flask import Flask, Response
import requests, socket, io
import numpy as np
from PIL import Image

app = Flask(__name__)
camera_pi = Camera()
n_pic = 20

dir_path = os.path.dirname(os.path.realpath(__file__)) + '/'

def gen():
	"""Video streaming generator function."""
	while True:
		frame = camera_pi.get_frame()
		yield (b'--frame\r\n'
				b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
	"""Video streaming route. Put this in the src attribute of an img tag."""
	return Response(gen(), mimetype='multipart/x-mixed-replace; boundary=frame')

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
		folder_name = time.strftime("%Y-%m-%d_%H:%M", time.localtime())
		folder_path = dir_path + folder_name + '/'
		if not os.path.exists(folder_path): os.makedirs(folder_path)
		img_list = []
		for i in range(n_pic*10):
			if i%10 == 0:
				img_list.append(camera_pi.get_frame())
		for i, frame_bytes in enumerate(img_list):
			pic_name = '%d.jpg' % (i+1)
			img = Image.open(io.BytesIO(frame_bytes))
			img.save(folder_path + pic_name)
		link = UTGD.Upload(fname=folder_name, fpath=folder_path, n_imgs=n_pic)
		
		# Send 1 more request for the link of share image.
		data = {
			'value1': '<br>以記錄門口照片，請從以下連結進入查看',
			'value2': str(link)
		}
		r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)
		
	

	return r.text


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8008)

