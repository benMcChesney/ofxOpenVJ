#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include "ofMain.h"
#include "ofxGui.h"

class ColorPalette
{

    public:
        ColorPalette( ) 
		{
			
		}

        struct colorItem
        {
            ofColor color ;
            string name ;
        };

		static ColorPalette* Instance()
		{
			static ColorPalette inst ;
			return &inst ;
		}

		void addColor ( ofColor _color , string _name ) ;
        ofColor getColorByLabel( string name , unsigned char alpha = 255 ) ;
        ofColor getRandomColor ( ) ;
        ofColor getSequenceColor ( ) ;
		ofColor getColor(); 

		ofxToggle bRandomColor;
		ofxToggle bSequentialColor;

	private :
        vector<colorItem> palette ;
        int sequenceIndex ;

		ofColor lastRandomColor; 

		


};

#endif // COLORPALETTE_H