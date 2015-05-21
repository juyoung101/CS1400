#ifndef drb_H
#define drb_H
#include "unit.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

class drb : public Unit {
public:
	drb():Unit(){}

	drb(int ir,int ic,int ihp,Dir idir,Rank irank,
	bool idead, string itla):
	Unit(ir,ic,ihp,idir,irank,idead,itla){} 

	void Place(int minR,int maxR,int minC,int maxC, SitRep sitrep);
	// put unit on board
	Action Recommendation(SitRep sitrep);
	// tell someone what you want to do

private:

};
#endif