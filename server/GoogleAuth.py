from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive
import pickle

gauth = GoogleAuth()
gauth.LocalWebserverAuth()

with open('myAuth.pkl', 'wb') as f:
	pickle.dump(gauth, f)
	