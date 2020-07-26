/* $Id$Revision: */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      See the LICENSE file for copyright information.     *
**********************************************************/

#include "config.h"

#include "misc.h"
#include <stdio.h>

jmp_buf rb_jbuf;

/***********************************************************************/
/*  FUNCTION:  SafeMalloc */
/**/
/*    INPUTS:  size is the size to malloc */
/**/
/*    OUTPUT:  returns pointer to allocated memory if successful */
/**/
/*    EFFECT:  mallocs new memory.  If malloc fails, prints error message */
/*             and terminates program. */
/**/
/*    Modifies Input: none */
/**/
/***********************************************************************/

void * SafeMalloc(size_t size) {
  void * result;

  if ( (result = malloc(size)) ) { /* assignment intentional */
    return(result);
  } else {
    fprintf(stderr, "memory overflow: malloc failed in SafeMalloc.");
    /* printf("  Exiting Program.\n"); */
    longjmp(rb_jbuf, 2);
    return(0);
  }
}
/*  NullFunction does nothing it is included so that it can be passed */
/*  as a function to RBTreeCreate when no other suitable function has */
/*  been defined */

void NullFunction(void * junk) { ; }
