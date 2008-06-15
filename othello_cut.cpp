// Game of Othello -- Cut from full code
// Universidad Simon Bolivar, 2005.
// Author: Blai Bonet
// Last Revision: 05/17/06
// Modified by: Ignacio

#include <iostream>
#include <iomanip>
#include <ext/hash_map>
#include "assert.h"

#define MAX(s,t)      ((s)>(t)?(s):(t))
#define MIN(s,t)      ((s)<(t)?(s):(t))
#define MAXVALUE      1000
#define DIM           36
#define N             6

const int rows[][7] = { { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
                        { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
                        {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
                        {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
                        {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
                        {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
                        {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
                        {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
                        {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
                        {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
                        {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 },
                        {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 } };
const int cols[][7] = { { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
                        { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
                        { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 } };
const int dia1[][7] = { { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
                        { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 }, { 9,-1,-1,-1,-1,-1,-1 },
                        {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
                        { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 },
                        {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 },
                        { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 },
                        {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
                        { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
                        {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
                        {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
                        {30,-1,-1,-1,-1,-1,-1 }, {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 },
                        {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 } };
const int dia2[][7] = { { 4,-1,-1,-1,-1,-1,-1 }, { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 },
                        { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 },
                        { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
                        { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
                        { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
                        {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
                        { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 },
                        {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 },
                        { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
                        {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 },
                        { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
                        {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 }, {35,-1,-1,-1,-1,-1,-1 } };

// moves on the principal variation
static int PV[] = { 12, 21, 26, 13, 22, 18,  7,  6,  5, 27, 33, 23, 17, 11, 19, 15,
                    14, 31, 20, 32, 30, 10, 25, 24, 34, 28, 16,  4, 29, 35, 36,  8, 9 };

class state_t
{
  unsigned char t_; 
  unsigned free_;
  unsigned pos_;
public:
  explicit state_t( unsigned char t = 6 ) : t_(t), free_(0), pos_(0) { }

  unsigned char t() const { return(t_); }
  unsigned free() const { return(free_); }
  unsigned pos() const { return(pos_); }

  bool is_color( bool color, int pos ) const { if( color ) return( pos<4?t_&(1<<pos):pos_&(1<<pos-4) ); else return( !(pos<4?t_&(1<<pos):pos_&(1<<pos-4)) ); }
  bool is_black( int pos ) const { return(is_color(true,pos)); }
  bool is_white( int pos ) const { return(is_color(false,pos)); }
  bool is_free( int pos ) const { return(pos<4?false:!(free_&(1<<pos-4))); }
  bool is_full() const { return(~free_==0); }

  unsigned value() const;
  bool terminal() const;
  bool outflank( bool color, int pos ) const;
  bool is_black_move( int pos ) const { return( (pos == DIM) || outflank(true,pos) ); }
  bool is_white_move( int pos ) const { return( (pos == DIM) || outflank(false,pos) ); }

  void set_color( bool color, int pos );
  state_t move( bool color, int pos ) const;
  state_t black_move( int pos ) { return(move(true,pos)); }
  state_t white_move( int pos ) { return(move(false,pos)); }

  bool operator<( const state_t &s ) const { return( (free_ < s.free_) || ((free_ == s.free_) && (pos_ < s.pos_)) ); }
  void print( std::ostream &os, int depth ) const;
  void print_bits( std::ostream &os ) const;
};

inline unsigned
state_t::value() const
{
  int v = 0;
  for( int pos = 0; pos < DIM; ++pos ) {
    if( !is_free(pos) ) v += (is_black(pos)?-1:1);
  }
  assert( (-36 <= v) && (v <= 36) );
  return(36+v);
}

inline bool
state_t::terminal( void ) const
{
  if( is_full() ) return(true);
  for( unsigned b = 0; b < DIM; ++b )
    if( is_black_move(b) || is_white_move(b) ) return(false);
  return(true);
}

bool
state_t::outflank( bool color, int pos ) const
{
  if( !is_free(pos) ) return(false);

  const int *p = 0;

  // check rows
  const int *r = rows[pos-4];
  while( *r != pos ) ++r;
  if( *(r+1) != -1 ) {
    for( p = r+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
    if( (p > r+1) && (*p != -1) && !is_free(*p) ) return(true);
  }
  if( r != rows[pos-4] ) {
    for( p = r-1; (p >= rows[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
    if( (p < r-1) && (p >= rows[pos-4]) && !is_free(*p) ) return(true);
  }

  // check cols
  const int *c = cols[pos-4];
  while( *c != pos ) ++c;
  if( *(c+1) != -1 ) {
    for( p = c+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
    if( (p > c+1) && (*p != -1) && !is_free(*p) ) return(true);
  }
  if( c != cols[pos-4] ) {
    for( p = c-1; (p >= cols[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
    if( (p < c-1) && (p >= cols[pos-4]) && !is_free(*p) ) return(true);
  }

  // CHECK OVER DIAGONALS REMOVED
  // ..
  // ..

  return(false);
}

inline void
state_t::set_color( bool color, int pos )
{
  if( color ) {
    if( pos < 4 )
      t_ |= (1<<pos);
    else {
      free_ |= (1<<pos-4);
      pos_ |= (1<<pos-4);
    }
  }
  else {
    if( pos < 4 )
      t_ &= ~(1<<pos);
    else {
      free_ |= (1<<pos-4);
      pos_ &= ~(1<<pos-4);
    }
  }
}

state_t
state_t::move( bool color, int pos ) const
{
  state_t s(*this);
  if( pos == DIM ) return(s);

  assert( outflank(color,pos) );
  s.set_color(color,pos);

  // process rows
  const int *p = 0;
  const int *r = rows[pos-4];
  while( *r != pos ) ++r;
  if( *(r+1) != -1 ) {
    for( p = r+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
    if( (p > r+1) && (*p != -1) && !is_free(*p) )
      for( const int *q = r+1; q < p; ++q ) s.set_color(color,*q);
  }
  if( r != rows[pos-4] ) {
    for( p = r-1; (p >= rows[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
    if( (p < r-1) && (p >= rows[pos-4]) && !is_free(*p) )
      for( const int *q = r-1; q > p; --q ) s.set_color(color,*q);
  }

  // process columns
  const int *c = cols[pos-4];
  while( *c != pos ) ++c;
  if( *(c+1) != -1 ) {
    for( p = c+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
    if( (p > c+1) && (*p != -1) && !is_free(*p) )
      for( const int *q = c+1; q < p; ++q ) s.set_color(color,*q);
  }
  if( c != cols[pos-4] ) {
    for( p = c-1; (p >= cols[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
    if( (p < c-1) && (p >= cols[pos-4]) && !is_free(*p) )
      for( const int *q = c-1; q > p; --q ) s.set_color(color,*q);
  }

  // PROCESS OF DIAGONALS REMOVED
  // ..
  // ..

  return(s);
}

void
state_t::print( std::ostream &os, int depth ) const
{
  os << "+";
  for( int j = 0; j < N; ++j ) os << "-";
  os << "+" << std::endl;

  int pos = 4;
  for( int i = 0; i < N; ++i ) {
    os << "|";
    for( int j = 0; j < N; ++j )
      if( ((i != 2) && (i != 3)) || ((j != 2) && (j != 3)) ) {
        os << (is_free(pos)?' ':(is_black(pos)?'&':'O'));
        ++pos;
      }
      else {
        assert( ((i == 2) || (i == 3)) && ((j == 2) || (j == 3)) );
        int p = ((i-2)<<1) + (j-2);
        os << (is_free(p)?' ':(is_black(p)?'&':'O'));
      }
    os << "|" << std::endl;
  }

  os << "+";
  for( int j = 0; j < N; ++j ) os << "-";
  os << "+" << std::endl;
}

void
state_t::print_bits( std::ostream &os ) const
{
  for( int i = 3; i >= 0; --i ) os << (t_&(1<<i)?'1':'0');
  os << ":";
  for( int i = 31; i >= 0; --i ) os << (pos_&(1<<i)?'1':'0');
  os << ":";
  for( int i = 31; i >= 0; --i ) os << (free_&(1<<i)?'1':'0');
}



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


////////////////////MAIN////////////////////
int main() { 

   return 1; 
    
}
