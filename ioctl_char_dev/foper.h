struct file_operations fops=
 {
          open         	: devOpen,
          release  	: devRelease,
          write    	: devWrite,
          read     	: devRead,
          llseek   	: devLlseek,
          unlocked_ioctl: devIoctl
         
 };
