//
//  Scenes.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once

#include "BaseScene.h"
#include "TriangleKinectShader.h"
#include "KinectShaderScene.h"
#include "SeizureCentralScene.h"
#include "CircleNoiseScene.h"
#include "RippleTunnelScene.h"
#include "ImageSpringParticles.h"
#include "AlienTunnelScene.h"
#include "KinectVertexShader.h"
#include "HexTunnelScene.h"
#include "KinectVertexShader_other.h"
#include "TriangleTunnelScene.h"
#include "SimpleMaskScene.h"
#include "CircleMaskScene.h"
#include "AlienTunnelMaskScene.h"



class Scenes {
public:
    static void registerScene( int a_index, string a_name );
    static string getSceneName( int a_index );
    static int getSceneIndex( string a_name ) ;
    
    static bool isValidIndex( int a_index );
    
    static void toString();
};