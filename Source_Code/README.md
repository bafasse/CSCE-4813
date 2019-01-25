This is a folder contains source code from my professor

Install instructions:

0) Install VirtualBox and Ubuntu Linux
- go to the CSCE technical support page
http://pausch.ddns.uark.edu/?page_id=249
- follow instructions to install VirtualBox
- follow instructions to install Ubuntu Linux

1) Install OpenGL on your Linux machine
- open a terminal window
- type "sudo apt-get -y install mesa-common-dev freeglut3-dev"
- enter the administrator password
- wait a few minutes for everything to download and install

2) Install 4813 sample code
- download src.tar to your Linux machine
- run "tar xvf src.tar" to create src directory
- cd into src directory
- type "cd jpeg; make clean; make; cd .." 
- type "cd libim; make clean; make; cd .." 
- run "make" to compile all graphics code

