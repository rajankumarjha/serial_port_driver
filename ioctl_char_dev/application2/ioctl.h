/*struct parameters 
{ 
   int regsize;
   int regno;
   int devsize;
   int datasize;
   int baudrate;
;*/

#ifndef MAGIC
#define MAGIC 'K'  
#endif

#ifndef DEVRESET
#define DEVRESET     _IO(MAGIC,0)      //no read write requires in reset  
#endif

#ifndef GETREGSIZE   
#define GETREGSIZE   _IOR(MAGIC,1,int)        //size is found by macro expansion which is using sizeof(type)  
#endif

#ifndef GETREGNO
#define GETREGNO     _IOR(MAGIC,2,int)       //max arg size is 2^14=16KB;
#endif

#ifndef GETDEVSIZE
#define GETDEVSIZE   _IOR(MAGIC,3,int) 
#endif

#ifndef GETDATASIZE
#define GETDATASIZE  _IOR(MAGIC,4,int) 
#endif

#ifndef GETBAUDRATE
#define GETBAUDRATE  _IOR(MAGIC,5,int) 
#endif

#ifndef SETREGSIZE
#define SETREGSIZE   _IOW(MAGIC,6,int) 
#endif

#ifndef SETREGNO
#define SETREGNO     _IOW(MAGIC,7,int) 
#endif

/*#ifndef SETREGSIZE
#define SETREGSIZE   _IOWR(MAGIC,6,int) 
#endif

#ifndef SETREGNO
#define SETREGNO     _IOWR(MAGIC,7,int) 
#endif*/

#ifndef SETBAUDRATE
#define SETBAUDRATE  _IOW(MAGIC,8,int) 
#endif
