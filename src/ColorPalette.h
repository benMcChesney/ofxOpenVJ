#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include "ofMain.h"


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

	//private :
        vector<colorItem> palette ;
        int sequenceIndex ;
       

};

#endif // COLORPALETTE_H