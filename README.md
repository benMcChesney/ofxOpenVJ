
# ofxOpenVJ #


The goal of this project is to create an easy way
to create "Scenes" of audio reactive visuals with the Microsoft Kinect for live performances / installations.


originally a part of VJ Kinect HackWeek
@ Helios Interactive , San Francisco
www.heliosinteractive.com


This software is released under the MIT License
You can use it commercially or otherwise. For more details check out
http://opensource.org/licenses/MIT

Built using Open Frameworks version 0.8.1 on OS X ( for now ) 

## Community addons 
	[ofxTweenzor] https://github.com/NickHardeman/ofxTweenzor
	
	[ofxUI] https://github.com/rezaali/ofxUI
	
	[ofxSimpleTimer] https://github.com/HeliosInteractive/ofxSimpleTimer
	
	[ofxBeatDetector] https://github.com/rezaali/ofxBeatDetector
	
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
There are [ofxOpenVJSet](src/ofxOpenVJSet.h) objets that contain a series of scenes. Scenes all inherit from the [BaseScene](src/BaseScene.h) which contains relevant pointers for shared resources such as : Kinect Point Cloud Data, Kinect openCV helpers, Beat Detection, and shared scene ofCamera


 You create scenes and add them to the set. The scene is your creative playground you shouldn't have to edit the set class itself.

If you are not planning on using a kinect and want to make compiling dependencies a little easier you can comment out

#define USE_KINECT 3 inside [ofxOpenVJConstants](src/ofxOpenVJConstants.h) and it will remove all mentions of the Kinect Manager , ofxOpenCV, and ofxKinect 

Creating your own scene
=============================================
It is recommended that you copy [EmptyScene](src/EmptyScene.h) into your own local project and rename it something unique. From there all the interaction can live inside this scene. To add it to set you'll first need to call : 

1) call ofxOpenVJSet::setup( ) 

2) call ofxOpenVJSet::addScene( ) with your custom scene class

3) call ofxOpenVJ::initialize() 


and your scene will not be added and initialzied correctly for the set.


