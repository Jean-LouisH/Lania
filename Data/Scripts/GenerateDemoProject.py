# Automatically forms a demo project directory for Lania
# without having to copy and rename existing folders.

import os.path

this_directory = os.path.dirname(__file__)
this_directory = this_directory.replace("\\", "/") #for use in non-Windows directories

print("\n\n\t\tLania Development Scripts\n")
print("\t\tGenerateDemoProjects.py\n\n")
print("Writes to Demos folder with init.cfg, icon.png and other placeholder data.\n\n")
demo_project_name = input("Demo project name? -> \n")
demo_directory = this_directory.replace("/Data/Scripts", "/Demos/" + demo_project_name + "/")

if not os.path.exists(demo_directory):
	os.makedirs(demo_directory)

inner_directory = demo_directory + demo_project_name + "/"
scene_directory = inner_directory + "Scenes/"
scripts_directory = inner_directory + "Scripts/"

init = open(demo_directory + "init.cfg", "w+")
init.write("--Application Window\n\ntitle=" + demo_project_name +"\n" + "resolution=853x480\nrenderer=SDL\nfullscreen=false\nresizable=false\nmaximized=false\nmain_scene=main.lscn")

icon = open(demo_directory + "icon.png", "w+")

if not os.path.exists(inner_directory):
	os.makedirs(inner_directory)
metadata = open(inner_directory + "metadata.txt", "w+")
metadata.write("name = " + demo_project_name + "\nversion = 1.0.0\napp_type = simulation\ndeveloper = "" ""\ndescription = ")

if not os.path.exists(scripts_directory):
	os.makedirs(scripts_directory)
if not os.path.exists(scene_directory):
	os.makedirs(scene_directory)

input = open(scripts_directory + "input.lasc", "w+")
main_scene = open(scene_directory + "main.lscn", "w+")