
ofxOpenVJ

The goal of this project is to create an easy way
to create "Scenes" of audio reactive visuals with the Microsoft Kinect for live performances / installations.


originally a part of VJ Kinect HackWeek
@ Helios Interactive , San Francisco
www.heliosinteractive.com


This software is released under the MIT License
You can use it commercially or otherwise. For more details check out
http://opensource.org/licenses/MIT

Built using Open Frameworks version 0.74 on OS X ( for now ) 

Community addons :
	ofxFFT
	ofxTweenzor
	ofxKinect
	ofxUI
	ofxSimpleMask
	ofxMSABPMTapper
	ofxMSATimer
	ofxPostProcessing
	ofxSyphon

Contributors : 
	Ben McChesney	
	Nick Hardemann
	
If you have questions, please contact ben.mcchesney@gmail.com 

If you find a bug / have a feature request please add an issue here on github.



Instructions for beginners
===========================================
This project was built for OPEN FRAMEWORKS 0.8.1 
If you are using another version I suggest you use the project generator and include all the addons located in the "clone_addons.sh" git script



FFT Configuration
===========================================
You may have some initial errors with FFT depending on your platform


XCODE

Open "ofxFFT.h" with this addon you can only have one FFT library active at a time 
comment out the line that reads "#define FFTW"
remove "ofxFftw.h" and "ofxFftw.cpp" from the project

VISUAL STUDIO
(coming soon )

  

