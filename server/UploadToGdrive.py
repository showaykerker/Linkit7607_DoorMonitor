from pydrive.drive import GoogleDrive
import pickle
import time, os
import unittest
if __name__ == '__main__': 
	import cv2
	import numpy as np

Project_Root_Name = 'HSProject'
dir_path = os.path.dirname(os.path.realpath(__file__)) + '/'
myAuth_path = dir_path + 'myAuth.pkl'

def Upload(fname, fpath, n_imgs=20):
	# Get Google Auth
	with open(myAuth_path, 'rb') as f:
		gauth = pickle.load(f)
	drive = GoogleDrive(gauth)
	
	# Find project root directory id `project_root_id`
	file_list = drive.ListFile({'q': "'root' in parents and trashed=false"}).GetList()
	for file in file_list:       
		if file['title'] == 'HSProject': 
			project_root_id = file['id']
			break
	else: assert False, 'Can\'t find project root named `HSProject` on google drive.'
	
	# Get all folder under project root
	sub_list = drive.ListFile( {'q': "'{}' in parents and trashed=false".format(project_root_id)}).GetList()
	print('Project_root: \"HSProject\", id: %s' % (project_root_id))
	
	# Check if filename exists, if not, create one. Then get the fid.
	for f in sub_list:
		if f['title'] == fname: 
			fid = f['id']
			print('Folder \"%s\" already in project_root, id %s' % (f['title'], str(fid)) )
			break
	else:
		folder_meta_data = {
			'title': fname, 
			"parents":  [{"id": project_root_id}], 
			"mimeType": "application/vnd.google-apps.folder"
		}
		folder = drive.CreateFile(folder_meta_data)
		folder.Upload()
		fid = folder['id']
		print('Create folder \"%s\", id %s' % (fname, str(fid)))
	
	for i in range(n_imgs):
		upload_name = '%d.jpg' % (i+1)
		local_fname = fpath + upload_name
		metadata = {
			'title': upload_name + '.jpg',
			'parent': [{"kind": "drive#fileLink", "id": fid}]
		}
		file2upload = drive.CreateFile(metadata)
		file2upload.SetContentFile(local_fname)
		file2upload.Upload()
		print('Created file %s with mimeType %s' % (file2upload['title'],
		file2upload['mimeType']))
	
	print('Done.')

class GoogleDriveAPITestCase(unittest.TestCase):
	fname = 'test01'
	fpath = 'test/' + fname + '/'
	def test_all(self):
		if not os.path.exists(self.fpath): os.makedirs(self.fpath)
		for i in range(20):
			fake_img = np.random.normal(120, 40, (480, 640, 3)).astype(np.uint8)
			img_name = self.fpath + "%d.jpg" % (i+1)
			cv2.imwrite(img_name, fake_img)
		Upload(self.fname, self.fpath, 20)	
		
		
if __name__ == '__main__':
	unittest.main(verbosity=2)

	
	