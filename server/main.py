import picamera
import Keys
import UploadToGdrive as UTGD

import time, os, cv2
from flask import Flask, Response
import requests, socket, io
import numpy as np

app = Flask(__name__)

# For Capturing image
n_pic = 40
sleep_time = 0.25

dir_path = os.path.dirname(os.path.realpath(__file__)) + '/'

silent = True


@app.route('/')
def index():
	return "<h1>HSP</HSP>"

@app.route('/<int:id>')
def AlarmSystem(id):
	time_detected = time.strftime("%Y-%m-%d_%H:%M:%S", time.localtime())
	if id == 0:
		text='HSP已開啟'
	elif id == 1:
		text='HSP警報<br>偵測到大門打開'
	elif id == 2:
		text='HSP警報已解除'
	else:
		return 'Request #%d' % id

	data = {'value1': '<br>'+text} #, 'value2': 'http://youtube.com'}
	if not silent: r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)

	if id == 1:
		folder_name = time.strftime("%Y-%m-%d_%H:%M", time.localtime())
		folder_path = dir_path + 'imgs/' + folder_name + '/'
		if not os.path.exists(folder_path): os.makedirs(folder_path)
		img_list = []
		with picamera.PiCamera() as camera:
			# camera setup
			camera.resolution = (512, 384)
			camera.iso = 800
			camera.brightness = 55
			camera.exposure_mode = "night"
			camera.framerate = 24
			time.sleep(0.5)

			for i in range(n_pic):
				output = np.empty((384 * 512 * 3), dtype=np.uint8)
				camera.capture(output, 'bgr')
				output = output.reshape((384, 512, 3))
				img_list.append(output.copy())

				pic_name = folder_path + '%d.jpg' % (i+1)
				cv2.imwrite(pic_name, output)				
				time.sleep(sleep_time)

		link, fid, drive = UTGD.GetLink(fname=folder_name)

		# Send 1 more request for the link of share image.
		data = {
			'value1': '<br>已拍下照片上傳至GoogleDrive中：<br>',
			'value2': str(link),
			'value3': '延平派出所電話(02)2556-4340'
		}
		if not silent: r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)


		# Start Upload
		UTGD.Upload(drive, fpath=folder_path, fid=fid, n_imgs=n_pic)
		


	if not silent: return r.text
	else: return 'Server at silent mode.'


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8008)


