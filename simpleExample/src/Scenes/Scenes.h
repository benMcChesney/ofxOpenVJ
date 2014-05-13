//
//  Scenes.h
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#pragma once

#include "BaseScene.h"
#include "TestScene.h"
#include "TriangleKinectShader.h"

class Scenes {
public:
    static void registerScene( int a_index, string a_name );
    static string getSceneName( int a_index );
    static int getSceneIndex( string a_name ) ;
    
    static bool isValidIndex( int a_index );
    
    static void toString();
};