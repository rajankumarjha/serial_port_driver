#include "headers.h"

MODULE_LICENSE("GPL");
#ifndef DEVNAME
#define DEVNAME "pc16550d_scdNX"
#endif

#ifndef MAJORNO
#define MAJORNO	0
#endif

#ifndef DEVNO
#define DEVNO	100
#endif

#ifndef BUFSIZE
#define BUFSIZE 100
#endif

#ifndef NUM_REGISTRES
#define NUM_REGISTRES 8
#endif

#ifndef SIZ_REGISTRES
#define SIZ_REGISTRES 1
#endif

/*
 * define the device size
 */
#ifndef DEV_SIZE
#define DEV_SIZE 128
#endif

/*
 * The bare device is a variable-length region of memory.
 * Use a linked list of indirect blocks.
 *
 * "scull_dev->data" points to an array of pointers, each
 * pointer refers to a memory area of SCULL_QUANTUM bytes.
 *
 * The array (quantum-set) is SCULL_QSET long.
 */
#ifndef NUM_QUANTUM
#define NUM_QUANTUM 40
#endif

#ifndef NUM_QSET
#define NUM_QSET    8
#endif
//--------------------------------------------------------------------
//			Serial Port regMap
//--------------------------------------------------------------------
#ifndef BASE_SERIAL_PORT_ADDRS
#define BASE_SERIAL_PORT_ADDRS 0x3F8
#endif
   
#define RBR     0x3f8   /* 0 DLAB = 0 */  /*DLAB::Divisor Latch Access Bits*/
#define THR     0x3f8   /* 0 DLAB = 0 */
#define DLS     0x3f8   /* 0 DLAB = 1 */

#define DMS     0x3f9   /* 1 DLAB = 1 */
#define IER     0x3f9   /* 1 DLAB = 0 */

#define IIR     0x3fa
#define FCR     0x3fa

#define LCR     0x3fb
#define MCR     0x3fc
#define LSR     0x3fd
#define MSR     0x3fe
#define SCR     0x3ff

//#define METHOD_REGSITER_CHARDEV
#define METHOD_ALLOC_CHARDEV

extern int majorno;     /* main.c */
extern int devno;
extern struct myDev *myDevices;        /* allocated in scull_init_module */

extern int no_of_registers;
extern int size_of_registers;
extern int no_of_qSet;
extern int no_of_quantum;
extern int devSize;

/*
 * Representation of scull quantum sets.
 */
struct myQset {
   struct myQset *next;
   void **data;
};

struct myDev {
   struct myQset *data;  /* Pointer to first quantum set */
   int quantum;              /* the current quantum size */
   int qset;                 /* the current array size */
   unsigned long size;       /* amount of data stored here */
   unsigned int access_key;  /* used by sculluid and scullpriv */
   struct semaphore sem;     /* mutual exclusion semaphore     */
   struct completion comp;
   struct cdev cdev;         /* Char device structure              */
};

//--------------------------------------------------------------------------------
/*	loff_t (*llseek) (struct file *, loff_t, int);
       	ssize_t (*read) (struct file *, char *, size_t, loff_t *);
       	ssize_t (*write) (struct file *, const char *, size_t, loff_t *);	*/
//--------------------------------------------------------------------------------
int openDev(struct inode *, struct file *);
int releaseDev(struct inode *, struct file *);
ssize_t readDev(struct file *, char *, size_t, loff_t *);
ssize_t writeDev(struct file *, const char *, size_t, loff_t *);
loff_t llseekDev (struct file *, loff_t, int);
//long ioctlDev(struct file *filp, unsigned int cmd, unsigned long arg);

int delMyDevices(void);
int trimDev(struct myDev *myDevices);
