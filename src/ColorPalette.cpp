#include "ColorPalette.h"



void ColorPalette::addColor ( ofColor _color , string _name )
{
    sequenceIndex = 0 ;
    colorItem c ;
    c.color = _color ;
    c.name = _name ;
    palette.push_back( c ) ;
}

ofColor ColorPalette::getColorByLabel( string name , unsigned char alpha )
{
    for ( int i = 0 ; i < palette.size() ; i++ )
    {
        if ( name == palette[i].name )
        {
            ofColor col = palette[i].color ;
            col.a = alpha ;
            return col ;
        }
    }

    return ofColor ( 255 , 0 , 0 ) ;
}

ofColor ColorPalette::getRandomColor ( )
{
    int randomIndex = floor( ofRandom( 0 , palette.size() ) ) ;

	while ( lastRandomColor == palette[randomIndex].color )
	{
		randomIndex = floor(ofRandom(0 , palette.size() )); 
	}

	lastRandomColor = palette[randomIndex].color;
    return lastRandomColor ;
}

ofColor ColorPalette::getSequenceColor ( )
{
    sequenceIndex++ ;
    if ( sequenceIndex > ( palette.size() - 1 ) )
    {
        sequenceIndex = 0 ;
    }

    return palette[ sequenceIndex ].color ;
}

ofColor ColorPalette::getColor()
{
	if (bRandomColor == true)
		return getRandomColor(); 
	if (bSequentialColor == true)
		return getSequenceColor();
	else
		return getSequenceColor(); 

}
