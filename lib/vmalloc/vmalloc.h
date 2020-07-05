/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _VMALLOC_H
#define _VMALLOC_H	1

/*	Public header file for the virtual malloc package.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/

#define VMALLOC_VERSION	19990805L

#include "config.h"

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#endif // HAVE_SYS_TYPES_H

    typedef struct _vmalloc_s Vmalloc_t;
    typedef struct _vmstat_s Vmstat_t;
    typedef struct _vmdisc_s Vmdisc_t;
    typedef struct _vmethod_s Vmethod_t;
    typedef void *(*Vmemory_f)
	(Vmalloc_t *, void *, size_t, size_t, Vmdisc_t *);
    typedef int (*Vmexcept_f)
	(Vmalloc_t *, int, void *, Vmdisc_t *);

    struct _vmstat_s {
	int n_busy;		/* number of busy blocks        */
	int n_free;		/* number of free blocks        */
	size_t s_busy;		/* total amount of busy space   */
	size_t s_free;		/* total amount of free space   */
	size_t m_busy;		/* largest busy piece           */
	size_t m_free;		/* largest free piece           */
	int n_seg;		/* number of segments           */
	size_t extent;		/* total size of region         */
    };

    struct _vmdisc_s {
	Vmemory_f memoryf;	/* memory manipulator           */
	Vmexcept_f exceptf;	/* exception handler            */
	size_t round;		/* rounding requirement         */
    };

    struct _vmethod_s {
	void *(*allocf) (Vmalloc_t *, size_t);
	void *(*resizef) (Vmalloc_t *, void *, size_t, int);
	int (*freef) (Vmalloc_t *, void *);
	long (*addrf) (Vmalloc_t *, void *);
	unsigned short meth;
    };

    struct _vmalloc_s {
	Vmethod_t meth;		/* method for allocation        */
	char *file;		/* file name                    */
	int line;		/* line number                  */
#ifdef _VM_PRIVATE_
	 _VM_PRIVATE_
#endif
    };

#define VM_TRUST	0000001	/* forgo some security checks   */
#define VM_TRACE	0000002	/* generate trace               */
#define VM_DBCHECK	0000004	/* check for boundary overwrite */
#define VM_DBABORT	0000010	/* abort on any warning         */
#define VM_FLAGS	0000017	/* user-settable flags          */

#define VM_MTBEST	0000100	/* Vmbest method                */
#define VM_MTPOOL	0000200	/* Vmpool method                */
#define VM_MTLAST	0000400	/* Vmlast method                */
#define VM_MTDEBUG	0001000	/* Vmdebug method               */
#define VM_MTPROFILE	0002000	/* Vmdebug method               */
#define VM_METHODS	0003700	/* available allocation methods */

#define VM_RSCOPY	0000001	/* copy old contents            */
#define VM_RSMOVE	0000002	/* old contents is moveable     */
#define VM_RSZERO	0000004	/* clear new space              */

/* exception types */
#define VM_OPEN		0	/* region being opened          */
#define VM_CLOSE	1	/* region being closed          */
#define VM_NOMEM	2	/* can't obtain memory          */
#define VM_BADADDR	3	/* bad addr in vmfree/vmresize  */
#define VM_DISC		4	/* discipline being changed     */


    extern Vmethod_t *Vmbest;	/* best allocation              */

    extern Vmdisc_t *Vmdcheap;	/* heap discipline              */
    extern Vmdisc_t *Vmdcsbrk;	/* sbrk discipline              */

    extern Vmalloc_t *Vmheap;	/* heap region                  */
    extern Vmalloc_t *Vmregion;	/* malloc region                */

    extern Vmalloc_t *vmopen(Vmdisc_t *, Vmethod_t *, int);
    extern int vmclose(Vmalloc_t *);
    extern int vmclear(Vmalloc_t *);

    extern void *vmalloc(Vmalloc_t *, size_t);
    extern void *vmresize(Vmalloc_t *, void *, size_t, int);
    extern int vmfree(Vmalloc_t *, void *);

    extern long vmaddr(Vmalloc_t *, void *);

    extern int vmwalk(Vmalloc_t *,
			     int (*)(Vmalloc_t *, void *, size_t,
				     Vmdisc_t *));
    extern char *vmstrdup(Vmalloc_t *, const char *);


/* to coerce any value to a Vmalloc_t*, make ANSI happy */
#define _VM_(vm)	((Vmalloc_t*)(vm))
/* non-debugging/profiling allocation calls */
#ifndef vmalloc
#define vmalloc(vm,sz)		(*(_VM_(vm)->meth.allocf))((vm),(sz))
#endif
#ifndef vmresize
#define vmresize(vm,d,sz,type)	(*(_VM_(vm)->meth.resizef))\
					((vm),(void*)(d),(sz),(type))
#endif
#ifndef vmfree
#define vmfree(vm,d)		(*(_VM_(vm)->meth.freef))((vm),(void*)(d))
#endif
#define vmaddr(vm,addr)		(*(_VM_(vm)->meth.addrf))((vm),(void*)(addr))
#define vmoldof(v,p,t,n,x)	(t*)vmresize((v), (p), sizeof(t)*(n)+(x), \
					(VM_RSMOVE) )
#define vmnewof(v,p,t,n,x)	(t*)vmresize((v), (p), sizeof(t)*(n)+(x), \
					(VM_RSMOVE|VM_RSCOPY|VM_RSZERO) )
#endif				/* _VMALLOC_H */
#ifdef __cplusplus
}
#endif
