import os
import subprocess
import time
import threading
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

build_folder_name = "build"

def is_cmake_installed():
	try:
		subprocess.check_output(['cmake', '--version'])
		return True
	except FileNotFoundError:
		return False

def is_vcpkg_installed():
	try:
		subprocess.check_output(['vcpkg', '--version'])
		return True
	except FileNotFoundError:
		return False

def create_build_folder():
	if not os.path.exists(build_folder_name):
		os.makedirs(build_folder_name)
		print(f"Created folder '{build_folder_name}'.")
	else:
		print(f"Folder '{build_folder_name}' already exists.")

def cmake_build():
	try:
		subprocess.check_call(['cmake', '-S', '.', '-B', build_folder_name])
		print("CMake configuration completed.")
	except FileNotFoundError:
		print("CMake not found.")

	try:
		subprocess.check_call(['cmake', '--build', build_folder_name])
		print("CMake build completed.")
	except FileNotFoundError:
		print("Something failed building with CMake.")

def set_vcpkg_root():
	try:
		output = subprocess.check_output(['where.exe', 'vcpkg'])
		vcpkg_path = output.decode('utf-8').strip().splitlines()[0]
		vcpkg_root = os.path.dirname(vcpkg_path)
		os.environ['VCPKG_ROOT'] = vcpkg_root
		print(f"vcpkg root is '{vcpkg_root}'")
	except subprocess.CalledProcessError:
		print("vcpkg is not installed or not in PATH.")

def debounce(wait):
	def decorator(fn):
		def debounced(*args, **kwargs):
			def call_it():
				fn(*args, **kwargs)

			if debounced._timer is not None:
				debounced._timer.cancel()

			debounced._timer = threading.Timer(wait, call_it)
			debounced._timer.start()

		debounced._timer = None
		return debounced

	return decorator

class FileChangeHandler(FileSystemEventHandler):
	def __init__(self, observers=[]):
		self.observers = observers
		for observer in self.observers:
				observer.start()
		
	@debounce(wait=1.0)
	def on_any_event(self, event):
		if event.is_directory:
			return
		file_extension = os.path.splitext(event.src_path)[-1]
		if file_extension in ['.c', '.h']:
			print(f"File with extension {file_extension} changed: {event.src_path}")
			for observer in self.observers:
				observer.update()

def watch_folder(folder_to_watch, observers=[]):
	event_handler = FileChangeHandler(observers)
	observer = Observer()
	observer.schedule(event_handler, folder_to_watch, recursive=True)
	observer.start()
	print(f"Watching folder: {folder_to_watch}")

	try:
		while True:
			time.sleep(100)
	except KeyboardInterrupt:
		observer.stop()

	observer.join()

class Updatable:
	def start(self):
		pass
	def update(self):
		pass

class ProcessRestarter(Updatable):
	def __init__(self,process_name):
		self.process_name = process_name
		self.executable_path = os.path.join(build_folder_name, 'Debug', self.process_name);
		self.process = None

	def start(self):
		self.start_executable()

	def update(self):
		self.stop_executable()
		self.start_executable()

	def stop_executable(self):
		if self.process and self.process.poll() is None:
			self.process.terminate()
			self.process.wait()

	def start_executable(self):
		if(os.path.exists(self.executable_path)): # is this if necessary? every time? maybe 
			self.process = subprocess.Popen([self.executable_path])
			print("Started the build executable.")
		else:
			print("Executable not found.")

class CmakeBuild(Updatable):
	def start(self):
		pass

	def update(self):
		pass

def main():
	if is_cmake_installed():
		print("Found CMake")
	else:
		print("Need to install CMake")
		return

	if not is_vcpkg_installed():
		print("vcpkg not found or not in PATH.")
		return

	create_build_folder()
	set_vcpkg_root()
	cmake_build()

	watch_folder('launcher',observers=[CmakeBuild(), ProcessRestarter("GameEngine.exe")])
	watch_folder('engine',observers=[CmakeBuild()])

	# watch_folder('launcher',observers=[CmakeBuild(), ProcessRestarter("GameEngine.exe")])
	# watch_folder('engine',observers=[CmakeBuild(), ProcessRestarter("GameEngine.exe")])

if __name__ == "__main__":
	main()