#include <iomanip>
#include <ext/hash_map>
#include <limits.h>
#include <algorithm>
#include "othello_cut.h"



#define MINNODE 0
#define MAXNODE 1

//Variables Globales

bool myColor;
bool otColor;


////////////////////HASH////////////////////
//Estructura para manejar el hash
class alphaBeta {
    public:
    int f_minus, f_plus;
	explicit alphaBeta(): f_minus(INT_MIN), f_plus(INT_MAX) {}
};

namespace __gnu_cxx {
    template<> class hash<state_t> {
    public:
        size_t operator()( const state_t &s ) const { return(s.free() ^ s.pos()); }
    };
};

class hash_t : public __gnu_cxx::hash_map<state_t,alphaBeta> { };  // class
hash_t hash; // hash instance

////////////////////////////////////////////

state_t* firstchild (state_t node, int nodeType, int &p){

	bool color;
	state_t * rNode= (state_t *) malloc (sizeof(state_t));

	//Determinamos el color
	if (nodeType==MAXNODE){
		color = myColor;
	} else {
		color = otColor;
	}	


	//Busca posicion para colocar ficha de color
    for (int i= 0; i<=DIM; i++){
		
		if (node.outflank(color,i)){
			p= i;
			(*rNode)= node.move(color,p);
			return rNode;
		}
	}

	//Si no encuentra posicion
	return rNode;
}

state_t* nextchild (state_t node, int nodeType, int &p){

	bool color;
	state_t * rNode= (state_t *) malloc (sizeof(state_t));;

	//Determinamos el color
	if (nodeType==MAXNODE){
		color = myColor;
	} else {
		color = otColor;
	}	


	//Busca posicion para colocar ficha de color
    for (int i= p+1; i<DIM; i++){
		
		if (node.outflank(color,i)){
			p= i;
			(*rNode) = node.move(color,p);
			return rNode;
		}
	}

	//Si no encuentra posicion
	free(rNode);
	return NULL;
}


int alphabeta(state_t node, int alpha, int beta, int nodeType) {

	int g;
	int a;
	int b;
	state_t * c;
	int p = 0;
	alphaBeta ab;
	int arg;

    //Se busca el nodo en la tabla de hash
    hash_t::iterator it= hash.find(node);

    //Si el nodo esta en la tabla
    if(it!=hash.end()){

//std::cout<<"alpha: "<<alpha<<" beta: "<<beta;
//std::cout<<" f+: "<<((*it).second.f_plus)<<" f-: "<<((*it).second.f_minus)<<std::endl;
//node.print(std::cout,1);

		if(((*it).second.f_minus) >= beta)
			return ((*it).second.f_minus);
	    
		if(((*it).second.f_plus) <= alpha)
			return ((*it).second.f_plus);

    }

	if (node.terminal()) {
		g= (int) node.value();

	} else {

		if (nodeType==MAXNODE){

			g= INT_MIN;
			a= alpha;

			c= firstchild(node,nodeType,p);

			while ((g<beta) && (c!=NULL)) {
				arg= alphabeta((*c),a,beta,MINNODE);
				g= std::max(g,arg);
				a= std::max(a,g);

				free(c);
				c= nextchild(node,nodeType,p);
			}

		} else {

			g= INT_MAX;
			b= beta;

			c= firstchild(node,nodeType,p);
			
			while ((g>alpha) && (c!=NULL)) {
				arg= alphabeta((*c),alpha,b,MAXNODE);
				g= std::min(g,arg);
				b= std::min(b,g);
				free(c);
				c= nextchild(node,nodeType,p);
			}
		}
	}

	//UPDATEAR HASH AQUI?

	if (g<beta)
		ab.f_plus= g;
	if (g>alpha)
		ab.f_minus= g;

		hash.insert(std::make_pair(node,ab));


	return g;
}


int MT_SSS (state_t node){

	int g= INT_MAX;
	int y= 0;

	while (y!=g){
		y= g;
		g= alphabeta(node,(y-1),y,MAXNODE);
	}

	return g;
}




int main() {

	myColor= false;
	otColor= true;
	state_t prueba;

	prueba = prueba.move(true,12);
	prueba = prueba.move(false,21);
	prueba = prueba.move(true,26);
	prueba = prueba.move(false,13);
	prueba = prueba.move(true,22);
	prueba = prueba.move(false,18);
	prueba = prueba.move(true,7);
	prueba = prueba.move(false,6);
	prueba = prueba.move(true,5);
	prueba = prueba.move(false,27);
	prueba = prueba.move(true,33);
	prueba = prueba.move(false,23);
	prueba = prueba.move(true,17);
	prueba = prueba.move(false,11);
	prueba = prueba.move(true,19);
	prueba = prueba.move(false,15);
	prueba = prueba.move(true,14);
	prueba = prueba.move(false,31);
	prueba = prueba.move(true,20);
	prueba = prueba.move(false,32);
	prueba = prueba.move(true,30);
	prueba = prueba.move(false,10);
	prueba = prueba.move(true,25);
	prueba = prueba.move(false,24);
	prueba = prueba.move(true,34);
	prueba = prueba.move(false,28);
	prueba = prueba.move(true,16);
	prueba = prueba.move(false,4);
	prueba = prueba.move(true,29);
//	prueba = prueba.move(false,35);
//	prueba = prueba.move(true,36);


	std::cout<<MT_SSS(prueba)<<std::endl;






}























