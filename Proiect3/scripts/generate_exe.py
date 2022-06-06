from os import environ as environ
from subprocess import run
from sys import executable

from os import rmdir, listdir, remove, rename, mkdir, getcwd

# import pyinstaller

OUT_FOLDER = 'out'
packages = ['image_import', 'image_export']

for package in packages:

    py_file = f'{package}/__init__.py'
    paths__ = f'{package}/venv/Lib/site-packages'
    package_executable = f'{getcwd()}/{package}/venv/Scripts/python.exe'

    # remove build/ and dist/ folders, and also any file that ends with .spec ATTENTION if you need these files

    try:
        rmdir('build')
    except:
        pass
    try:
        rmdir('dist')
    except:
        pass

    for fname in listdir('.'):
        if fname.endswith('.spec'):
            remove(fname)

#     my_env = environ.copy()
#     my_env['PYTHONOPTIMIZE'] = '2'

    # pyinstaller = './venv/Scripts/pyinstaller.exe'
    proc = run([
        package_executable,
        '-m',
        'PyInstaller',
        '--onefile',
        '--paths',
        paths__,
        # '--noconsole',
        py_file,
    ], text=True, capture_output=True)  #, env=my_env)

    # Make output dir
    try:
        mkdir(OUT_FOLDER)
    except BaseException as e:
        # print(e)  # The folder already exists
        pass

    # move exe to output dir
    exe_path = f'dist/__init__.exe'
    exe_out_path = f'{OUT_FOLDER}/{package}.exe'
    try:
        remove(exe_out_path)
    except:
        pass  # the file does not exist yet
    rename(exe_path, exe_out_path)
