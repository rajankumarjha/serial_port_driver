int myModule(void);

MODULE_LICENSE("GPL");

int devOpen(struct inode *, struct file*);
int devRelease(struct inode *, struct file*);
ssize_t devWrite(struct file *, const char __user *,size_t , loff_t *);
Qset* createScull(int,int);
ssize_t devRead(struct file *, char __user *,size_t , loff_t *);
loff_t devLlseek(struct file *,loff_t,int);
long devIoctl(struct file *, unsigned int, unsigned long);

//int (*tmrfp)(unsigned long);
void timerFunc(unsigned long);
 
int devTrim(Dev*);
