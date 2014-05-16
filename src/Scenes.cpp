//
//  Scenes.cpp
//  KinectPerformanceV01
//
//  Created by Nick Hardeman on 11/6/12.
//
//

#include "Scenes.h"

static map<string, int> sceneMap;

void Scenes::registerScene( int a_index, string a_name ) {
    sceneMap[a_name] = a_index;
}

string Scenes::getSceneName( int a_index ) {
    for( map<string, int>::iterator it = sceneMap.begin(); it != sceneMap.end(); ++it ) {
        if(it->second == a_index) {
            return it->first;
        }
    }
}

int Scenes::getSceneIndex( string a_name ) {
    if(sceneMap.find(a_name) != sceneMap.end()) {
        return sceneMap[a_name];
    }
    return -1;
}

void Scenes::toString() {
    cout << "Scenes -------------------------------------------- " << endl;
    for( map<string, int>::iterator it = sceneMap.begin(); it != sceneMap.end(); ++it ) {
        cout << "index: " << it->second << " | name: " << it->first << endl;
    }
    cout << "--------------------------------------------------- " << endl;
}

bool Scenes::isValidIndex( int a_index ) {
    return ((a_index >= 0) && (a_index < sceneMap.size()) );
}



