#ifndef MATHTOOLS_H
#define MATHTOOLS_H



class MathTools
{
public:
	MathTools();
	
	static float getRandFloat( float min, float max )
	{
		float range = max - min;

		float random  = ((float)rand()/(float)(RAND_MAX)) * range;
		random += min;

		return random;
	}


	static float getMax(const float first,const float second )
	{
		return first > second ? first : second;
	}
	static float getMin(const float first,const float second )
	{
		return first < second ? first : second;
	}
	
	static Vect getMaxValuedVector(const Vect& first,const Vect& second )
	{
		return Vect(
					getMax( first[x], second[x] ),
					getMax( first[y], second[y] ),
					getMax( first[z], second[z] )
					);
	}
	static Vect getMinValuedVector(const Vect& first,const Vect& second )
	{
		return Vect(
					getMin( first[x], second[x] ),
					getMin( first[y], second[y] ),
					getMin( first[z], second[z] )
					);
	}

	static bool doIntervalsOverlap( float aStart, float aEnd,
									float bStart, float bEnd )
	{
		return getMax( aStart, bStart ) <= getMin( aEnd, bEnd);
	}

	static bool isInInterval( float val, float min, float max )
	{
		return ( val > min && val < max );
	}

	static void clamp( float& toClamp, float min, float max )
	{
		if( toClamp < min ) 
			toClamp = min;
		else if( toClamp > max )
			toClamp = max;
	}

	static void clampVect( Vect& toClamp, Vect& min, Vect& max )
	{
		clamp( toClamp[x], min[x], max[x] );
		clamp( toClamp[y], min[y], max[y] );
		clamp( toClamp[z], min[z], max[z] );
	}
};

#endif //MATHTOOLS_H