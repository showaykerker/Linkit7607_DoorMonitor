from camera_pi import Camera
import Keys
import UploadToGdrive as UTGD

import time, os
from flask import Flask, Response
import requests, socket, io
import numpy as np
from PIL import Image

app = Flask(__name__)

# For Capturing image
n_pic = 20
sleep_time = 0.5

dir_path = os.path.dirname(os.path.realpath(__file__)) + '/'

silent = False

"""
def gen():
	# Video streaming generator function.
	while True:
		frame = camera_pi.get_frame()
		yield (b'--frame\r\n'
				b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
	# Video streaming route. Put this in the src attribute of an img tag.
	return Response(gen(), mimetype='multipart/x-mixed-replace; boundary=frame')

"""

@app.route('/')
def index():
	return "<h1>HSP</HSP>"

@app.route('/<int:id>')
def AlarmSystem(id):
	time_detected = time.strftime("%Y-%m-%d_%H:%M:%S", time.localtime())
	if id == 0:
		text='HSP已開機'
	elif id == 1:
		text='HSP警報<br>感測到大門打開'
	elif id == 2:
		text='HSP警報已解除'
	else:
		return 'Request #%d' % id

	data = {'value1': '<br>'+text} #, 'value2': 'http://youtube.com'}
	if not silent: r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)

	if id == 1:
		camera_pi = Camera()
		folder_name = time.strftime("%Y-%m-%d_%H:%M", time.localtime())
		folder_path = dir_path + 'imgs/' + folder_name + '/'
		if not os.path.exists(folder_path): os.makedirs(folder_path)

		img_list = []
		time.sleep(0.5)
		for i in range(n_pic):
			print(i, time.time())
			img_list.append(camera_pi.get_frame())
			time.sleep(sleep_time)


		link, fid, drive = UTGD.GetLink(fname=folder_name)

		# Send 1 more request for the link of share image.
		data = {
			'value1': '<br>已拍下門口照片,正在上傳到GoogleDrive<br>',
			'value2': str(link),
			'value3': '延平派出所電話：(02)25564340'
		}
		if not silent: r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)


		for i, frame_bytes in enumerate(img_list):
			pic_name = '%d.jpg' % (i+1)
			img = Image.open(io.BytesIO(frame_bytes))
			img.save(folder_path + pic_name)


		# Start Upload
		UTGD.Upload(drive, fpath=folder_path, fid=fid, n_imgs=n_pic)
		del camera_pi


	if not silent: return r.text
	else: return 'Server at silent mode.'


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8008)


