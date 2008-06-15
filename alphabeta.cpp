#include "othello_cut.h"
#include <iomanip>
#include <ext/hash_map>
#include <limits.h>

#define MAX(s,t)      ((s)>(t)?(s):(t))
#define MIN(s,t)      ((s)<(t)?(s):(t))

#define MINNODE 0
#define MAXNODE 1

//Variables Globales

bool myColor;
bool otColor;


////////////////////HASH////////////////////
//Estructura para manejar el hash
class alphaBeta {
    public:
    unsigned f_minus, f_plus;
};

namespace __gnu_cxx {
    template<> class hash<state_t> {
    public:
        size_t operator()( const state_t &s ) const { return(s.free()); }
    };
};

class hash_t : public __gnu_cxx::hash_map<state_t,alphaBeta> { };  // class
hash_t hash; // hash instance

////////////////////////////////////////////

state_t* firstchild (state_t node, int nodeType, int &p){

	bool color;
	state_t * rNode= NULL;

	//Determinamos el color
	if (nodeType==MAXNODE){
		color = myColor;
	} else {
		color = otColor;
	}	


	//Busca posicion para colocar ficha de color
    for (int i= 0; i<DIM; i++){
		
		if (node.outflank(color,i)){
			p= i;
			(*rNode)= node.move(color,p);
			return rNode;
		}
	}

	//Si no encuentra posicion
	return NULL;
}

state_t* nextchild (state_t node, int nodeType, int &p){

	bool color;
	state_t * rNode= NULL;

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
	return NULL;
}


unsigned alphabeta(state_t node, unsigned alpha, unsigned beta, int nodeType) {

	unsigned g;
	unsigned a;
	unsigned b;
	state_t * c;
	int p = 0;
	alphaBeta ab;

    //Se busca el nodo en la tabla de hash
    hash_t::iterator it= hash.find(node);

    //Si el nodo esta en la tabla
    if(it!=hash.end()){

		if(((*it).second.f_minus) >= beta)
			return ((*it).second.f_minus);
	    
		if(((*it).second.f_plus) <= alpha)
			return ((*it).second.f_plus);

    }

    //Si el nodo no esta en la tabla
	if (node.terminal()) {
		g= node.value();
	} else {

		
		if (nodeType==MAXNODE){

			g= INT_MIN;
			a= alpha;

			c= firstchild(node,nodeType,p);
			
			while (g<beta && c!=NULL) {

				g= MAX(g, alphabeta((*c),alpha,beta,MINNODE));
				a= MAX(a,g);
				free(c);
				c= nextchild(node,nodeType,p);
			}

		} else {

			g= INT_MAX;
			b= beta;

			c= firstchild(node,nodeType,p);
			
			while (g>alpha && c!=NULL) {

				g= MIN(g, alphabeta((*c),alpha,beta,MAXNODE));
				b= MIN(b,g);
				free(c);
				c= nextchild(node,nodeType,p);
			}
		}
	}

	if (g<beta)
		ab.f_plus= g;
	if (g>alpha)
		ab.f_minus= g;

	hash.insert(std::make_pair(node,ab));

	return g;
}






























