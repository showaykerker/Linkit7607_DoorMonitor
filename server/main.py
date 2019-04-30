from flask import Flask
import requests
import Keys

app = Flask(__name__)

@app.route('/<int:id>')
def index(id):
	if id == 0: text='HSP已啟動'
	elif id == 1: text='HSP警報<br>偵測到大門打開，有未授權進入'
	elif id == 2: text='HSP警報已解除'
	else: return 'Hi'
	data = {'value1': '<br>'+text} #, 'value2': 'http://youtube.com'}
	r = requests.get("https://maker.ifttt.com/trigger/%s/with/key/%s" % (Keys.EventName, Keys.Key), data = data)
	return r.text


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=5566)
