

# ofxOpenVJ #


The goal of this project is to create an easy way
to create "Scenes" of audio reactive visuals with the Microsoft Kinect for live performances / installations.


originally a part of VJ Kinect HackWeek
@ Helios Interactive , San Francisco
www.heliosinteractive.com


This software is released under the MIT License
You can use it commercially or otherwise. For more details check out
http://opensource.org/licenses/MIT

## Update

 Update ! I no longer have an OSX computer so all further development / examples will focused on Windows 10+. But ! Since it's openFrameworks I'm sure most of it will work fine on OSX with just a little bit of love and project setup. The only split per platform should be using Spout or Syphon as your main output. 

 All examples from me will be in VS2015 moving forward

## end Update

Built using Open Frameworks latest on Github ( close to 0.9 release ) on Windows 10 in VS Community 2015

## Community addons 
	[ofxTweenzor] https://github.com/NickHardeman/ofxTweenzor
	
	[ofxSimpleTimer] https://github.com/HeliosInteractive/ofxSimpleTimer

	[ofxSimpleMask] https://github.com/HeliosInteractive/ofxSimpleMask
	
	[ofxBeat] https://github.com/darrenmothersele/ofxBeat
	
	[ofxPostProcessing] https://github.com/neilmendoza/ofxPostProcessing
	
	[ofxSyphon] https://github.com/astellato/ofxSyphon

## Contributors 
	Ben McChesney
		
	Nick Hardemann ( now inactive ) 
	
If you have questions, please contact ben.mcchesney@gmail.com 

If you find a bug / have a feature request please add an issue here on github.



Instructions
===========================================
navigate to /ofxOpenVJ/ inside a shell terminal and run [clone_addons.sh](clone_addons.sh), this will clone all the appropriate community addons to run the basic ofxOpenVJ examples.

This set of tools is meant to be extensible, more complicated or community generated scenes may require other dependencies.


The Gist
=============================================
There is a [ofxOpenVJSet](src/ofxOpenVJSet.h) object that contain a vector of scenes. Scenes all inherit from the [BaseScene](src/BaseScene.h) class which contains relevant pointers for shared resources such as : Kinect Point Cloud Data, Kinect openCV helpers, Beat Detection + FFT , and a shared ofCamera

You create scenes and add them to the set. The scene is your creative sketch playground you shouldn't have to edit the set class itself.

If you are not planning on using a kinect you can comment out

USE_KINECT 3 inside [ofxOpenVJConstants](src/ofxOpenVJConstants.h) and it will remove all mentions of the Kinect Manager , ofxOpenCV, and ofxKinect 

Creating your own scene
=============================================
It is recommended that you copy [EmptyScene](src/EmptyScene.h) into your own local project and rename it something unique. From there all the interaction can live inside this scene. To add it to set you'll first need to call : 

1) call ofxOpenVJSet::setup( ) 

2) call ofxOpenVJSet::addScene( ) with your every scene you want to include in the set

3) call ofxOpenVJ::initialize() 


and your scene will not be added and initialzied correctly for the set.


