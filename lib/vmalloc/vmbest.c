/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

#include "vmhdr.h"
#include "vmalloc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/** make room to store a new pointer we are about to allocate
 *
 * @param vd Vmdata to operate on
 * @returns true on success
 */
static bool make_space(Vmdata_t *vd) {

  if (vd->size == vd->capacity) {
    void **p;

    /* expand our allocation storage */
    size_t c = vd->capacity == 0 ? 1 : vd->capacity * 2;
    p = realloc(vd->allocated, sizeof(vd->allocated[0]) * c);
    if (p == NULL) {
      return false;
    }

    /* save the new array */
    vd->allocated = p;
    vd->capacity = c;
  }

  return true;
}

/**
 * @param vm region allocating from
 * @param size desired block size
 */
void *bestalloc(Vmalloc_t *vm, size_t size) {
  Vmdata_t *vd = vm->data;
  void *p;

  if (!make_space(vd)) {
    return NULL;
  }

  p = malloc(size);
  if (p == NULL) {
    return NULL;
  }

  vd->allocated[vd->size] = p;
  ++vd->size;

  return p;
}

int bestfree(Vmalloc_t *vm, void *data) {
  Vmdata_t *vd = vm->data;
  size_t i;

  if (!data) { /* ANSI-ism */
    return 0;
  }

  /* find the pointer we previously allocated */
  for (i = 0; i < vd->size; ++i) {
    if (vd->allocated[i] == data) {

      /* clear this slot */
      size_t extent = sizeof(vd->allocated[0]) * (vd->size - i - 1);
      memmove(vd->allocated + i, vd->allocated + i + 1, extent);
      --vd->size;

      /* give this back to the underlying allocator */
      free(data);

      return 0;
    }
  }

  /* we did not find this pointer; free() of something we did not allocate */
  return -1;
}

/**
 * @param vm region allocation from
 * @param data old block of data
 * @param size new size
 * @param type ignored
 */
void *bestresize(Vmalloc_t *vm, void *data, size_t size, int type) {
  Vmdata_t *vd = vm->data;
  size_t i;

  /* ignore type */
  (void)type;

  if (!data) {
    return bestalloc(vm, size);
  }

  /* find the pointer we previously allocated */
  for (i = 0; i < vd->size; ++i) {
    if (vd->allocated[i] == data) {

      /* resize the allocation */
      void *p = realloc(data, size);
      if (p == NULL) {
        return p;
      }

      /* save the updated pointer */
      vd->allocated[i] = p;

      return p;
    }
  }

  /* the pointer the caller gave us was not allocated by us */
  return NULL;
}

static Vmethod_t _Vmbest = {
    bestalloc,
    bestresize,
    bestfree,
    0,
    VM_MTBEST
};

/* The heap region */
static Vmdata_t _Vmdata = {
    VM_MTBEST | VM_TRUST,	/* mode         */
    0,				/* incr         */
    0,				/* pool         */
    NIL(Seg_t *),		/* seg          */
    NIL(Block_t *),		/* free         */
    NIL(Block_t *),		/* wild         */
    NIL(Block_t *),		/* root         */
    { NULL },			/* tiny         */
    { NULL },			/* cache        */
    NULL,			/* allocated    */
    0,				/* size         */
    0,				/* capacity     */
};
static Vmalloc_t _Vmheap = {
    {bestalloc,
     bestresize,
     bestfree,
     0,
     VM_MTBEST},
    NIL(char *),		/* file         */
    0,				/* line         */
    NULL,			/* disc         */
    &_Vmdata,			/* data         */
    NIL(Vmalloc_t *)		/* next             */
};

Vmalloc_t* Vmheap = &_Vmheap;
Vmalloc_t* Vmregion = &_Vmheap;
Vmethod_t* Vmbest = &_Vmbest;
