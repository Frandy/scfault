#ifndef OPTION_H
#define OPTION_H

// enable DEBUG
#define DEBUG

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#endif

//#define DEBUG_PARALLEL
//#define DEBUG_SPAN
//#define DEBUG_GraphReduction
//#define DEBUG_OPAMP
//#define DEBUG_ORDER
//#define DEBUG_SIGN


// enable check netlist
#define CHECK_NETLIST

// thread count
//#define THREAD

// Print
#define PRINT_EXP
#define PRINT_COEF

/* - - - - - - - - - - - - - - - - - - - - - - - - - */
/** SYMBOL_ORDER */
// Order as node domain, 
// select as the default order
//#define SYMBOL_ORDER_NODE_DOMAIN
//#define NODE_SYMBOL_OUT_IN

// Order as it appear in the netlist
#define SYMBOL_ORDER_NATURE_DOMAIN

// Order as its type X < C,L < R
//#define SYMBOL_ORDER_TYPE_DOMAIN


/* - - - - - - - - - - - - - - - - - - - - - - - - - */
/** GraphReduction */
// GraphReduction DFS in stack
//#define GraphReduction_DFS

// GraphReduction BFS in queue
#define GraphReduction_BFS


/* - - - - - - - - - - - - - - - - - - - - - - - - - */
/**	Zero Suppress	*/
// Zero Suppress Method
//#define ZERO_SUPPRESS_DIRECT

//#define DELETE_ON_FLY
/*
#ifdef DELETE_ON_FLY
#define REFERENCE
#else
#undef REFERENCE
#endif
*/

#define REFERENCE

// ZS Recursive 
#define ZERO_SUPPRESS_RECURSIVE


/* - - - - - - - - - - - - - - - - - - - - - - - - - */
/** Reduce */
// reduce bottom up


/* - - - - - - - - - - - - - - - - - - - - - - - - - */
/** Others */
// enable graph connectivity chech
#define GRAPH_CONNECTIVITY_CHECK

// enable graph isomorphic check
//#define GRAPH_ISOMORPHIC_ON

#endif
