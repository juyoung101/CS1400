#include "jcl.h"
#include <cmath>
#include <iostream>


void jcl::Place(int minR,int maxR,int minC,int maxC, SitRep sitrep){
	bool done=false;
	int tr,tc;
	Dir td;
	while(!done){
		tr=minR+rand()%(maxR-minR);	
		tc=minC+rand()%(maxC-minC);	
		if(sitrep.thing[tr][tc].what==space)done=true;
	}
	int rdist=ROWS/2-tr;
	int cdist=COLS/2-tc;
	if(abs(rdist)<abs(cdist)){
		if(cdist>0)td=rt;
		else td=lt;
	}else{
		if(rdist>0)td=up;
		else td=dn;
	}
	r=tr;
	c=tc;
	dir=td;
}


// tell someone what you want to do
Action jcl::Recommendation(SitRep sitrep){

	// this code is provided as an example only
	// use at your own risk
	Action a;
	SitRep turns;

	// first, try to attack in front of you
	int tr = r, tc = c;
	switch (dir){
	case up: tr--; break;
	case dn: tr++; break;
	case rt: tc++; break;
	case lt: tc--; break;
	case none: break;
	}
	if (tr >= 0 && tr < ROWS && tc >= 0 && tc < COLS){
		if (sitrep.thing[tr][tc].what == unit){
			if (sitrep.thing[tr][tc].tla != tla){
				a.action = attack;
				a.ar = tr;
				a.ac = tc;
				return a;
			}
		}
	}
	// there is not an enemy in front of me
	// so head to the nearest enemy

	//commands for infantry
if (rank == infantry){
	if (dir == sitrep.nearestEnemyCrown.dirFor){
		a.action = fwd;
		a.maxDist = 1;
		return a;
	}else{
		a.action = turn;
		a.dir = sitrep.nearestEnemyCrown.dirFor;
		return a;
	}
		a.action = nothing;
		return a;
}

	//commands for archers
if (rank == archer){
	while (sitrep.turnNumber >= 10){ //once turns hits 10, the archers should start moving
		if (dir == sitrep.nearestEnemy.dirFor){
			a.action = fwd;
			a.maxDist = 1;
			return a;
		}else{
			a.action = turn;
			a.dir = sitrep.nearestEnemyCrown.dirFor;
			return a;
		}
	}
		a.action = nothing;
		return a;
}
	
	//commands for knights
if (rank == knight){
	while (sitrep.turnNumber >= 20){ //once turns hits 20, the knights should head for the nearest Crown
		if (dir == sitrep.nearestEnemyCrown.dirFor){
			a.action = fwd;
			a.maxDist = HORSESPEED - 3; //I couldn't figure out how to make the knights go shorter distances, so this is my answer.
			return a;
		}else{
			a.action = turn;
			a.dir = sitrep.nearestEnemyCrown.dirFor;
			return a;
		}
	}
a.action = nothing;
return a;
}

	//for the king
if (rank == crown && dir != sitrep.nearestEnemy.dirFor){
		a.action = fwd;
		a.maxDist = HORSESPEED;
		return a;
	}
		else if(sitrep.thing[tr][tc].what == unit){ //if there is a friendly unit in front of the Crown
			if (sitrep.thing[tr][tc].tla == tla){   //he should move around it and keep going.
				a.action = turn;
				a.dir = sitrep.anyOpenSpace;
				return a;
			}
		}
	a.action = nothing;
	return a;
}