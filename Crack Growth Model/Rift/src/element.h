/*
 * site.h
 *
 *  Created on: Sep 26, 2012
 *      Author: jqnorris
 */

#ifndef SITE_H_
#define SITE_H_

class site
{
public:
	double gap;
	int N;
    site& operator[](int i)
    {
    	return ((i%N+N)%N);
    }

};



#endif /* SITE_H_ */
