import subprocess
import os
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

def is_cmake_installed():
    try:
        output = subprocess.check_output(['cmake', '--version'])
        return True
    except FileNotFoundError:
        return False


def id_vcpkg_installed():
    try:
        output = subprocess.check_output(['vcpkg', '--version'])
        return True
    except FileNotFoundError:
        return False

print("this is the first script you should run")

if is_cmake_installed():
    print("found cmake")
else:
    print("need to install cmake")

buildFolderName = "build"
if not os.path.exists(buildFolderName):
    os.makedirs(buildFolderName)
    print(f"Creater folder '{buildFolderName}'.")
else:
    print(f"folder '{buildFolderName}' already exists.")

def cmake_build():
	try:
	    subprocess.check_call(['cmake', '-S', '.', '-B', buildFolderName])
	    print("CMake configuration completed.")
	except FileNotFoundError:
	    print ("CMake not found?")

try:
    output = subprocess.check_output(['where.exe', 'vcpkg'])
    vcpkg_path = output.decode('utf-8').strip().splitlines()[0]
    vcpkg_root = os.path.dirname(vcpkg_path)
    os.environ['VCPKG_ROOT'] = vcpkg_root
    print(f"vcpkg root is '{vcpkg_root}'")
except subprocess.CalledProcessError:
    print("vcpkg is not installed or not in PATH.")

cmake_build()

try:
    subprocess.check_call(['cmake', '--build', buildFolderName])
    print("CMake build completed.")
except FileNotFoundError:
    print("something failed buildign with cmake")


class FileChangeHandler(FileSystemEventHandler):
    def on_any_event(self, event):
        if event.is_directory:
            return
        file_extension = os.path.splitext(event.src_path)[-1]
        if(file_extension in ['.c', '.h']):
        	print(f"File with extension {file_extension} changed: {event.src_path}")
        	cmake_build()
        
def watch_folder(folder_to_watch):
    event_handler = FileChangeHandler()
    observer = Observer()
    observer.schedule(event_handler, folder_to_watch, recursive=True)
    observer.start()
    print(f"Watching folder: {folder_to_watch}")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()

    observer.join()


watch_folder('.')

# build exe
# build lib
# launch exe
# start watching the directory for changes
# if the exe file change compile and launch again
