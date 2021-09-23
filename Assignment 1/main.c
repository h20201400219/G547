#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/uaccess.h>        
#include <linux/time.h>
#include <linux/ioctl.h>
#include <linux/slab.h>


#include "ASSIGN.h"     //header consisting of REQUEST CODES for ioctl function calls
#define SUCCESS 14
#define DEVICE_NAME "imu_char"


uint16_t i1;

static dev_t first;          //variable for device number
static struct cdev c_dev;    //variable for the character device structure
static struct class *cls;    //varible for the device class

static int my_open(struct inode *i, struct file *f)            //open function of file
{
   printk(KERN_INFO "Device : open()\n");
   return 0;
}

static int my_close(struct inode *i, struct file *f)            //close function of file
{
   printk(KERN_INFO "Device : close()\n");                     //printing in kernel
   return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)      //read function of file
{
   printk(KERN_INFO "Device : read()\n");                                    //printing in kernel
       /*
     * Number of bytes actually written to the buffer
     */

#ifdef DEBUG
    printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buf, length);
#endif

    /*     Actually put the data into the buffer   */
    get_random_bytes(&i1, sizeof(i1));
    i1 = i1%1023;                                          //generating 10-bit random number
    printk(KERN_INFO "random number : %d\n", i1);          //printing generated random number in kernel
   
    return i1;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)              //write function of file
{
   printk(KERN_INFO "Device : write()\n");                 //printing in kernel
   return len;
}


////////////////  file operations  ////////////////
static struct file_operations fops =
{
   .owner     = THIS_MODULE,
   .open      = my_open,
   .release   = my_close,
   .read      = my_read,
   .write     = my_write
};




static long ioctl(struct file *file,             
                  unsigned int ioctl_num,        /* number and param for ioctl */
                  unsigned long ioctl_param)
{
    char *temp;

    /* Switch according to the ioctl called    */
    switch (ioctl_num) {
   
    case IOCTL_X_PITCH_GYRO:                           
          temp = (char *) ioctl_param;                 // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));         //passing random number to user space

         break;
         
    case IOCTL_Y_YAW_GYRO:  
          
         temp = (char *)ioctl_param;                  // type casting ioctl param to char *
         copy_to_user(temp, &i1, sizeof(i1));         //passing random number to user space


         break;
                           
    case IOCTL_Z_ROLL_GYRO:  
          
         temp = (char *)ioctl_param;                // type casting ioctl param to char *
         copy_to_user(temp, &i1, sizeof(i1));       //passing generated random number to user space
         
         break;
         
    case IOCTL_X_FB_ACCELERO:    
          temp = (char *)ioctl_param;              // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));     //passing generated random number to user space

         break;
         
    case IOCTL_Y_LR_ACCELERO:    
          temp = (char *)ioctl_param;             // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));    //passing generated random number to user space

         break;
                           
    case IOCTL_Z_UD_ACCELERO:    
          temp = (char *)ioctl_param;            // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));   //passing generated random number to user space

         break; 
         
    case IOCTL_X_DIR_COMPASS:    
          temp = (char *)ioctl_param;            // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));    //passing generated random number to user space

         break;
         
    case IOCTL_Y_DIR_COMPASS:    
          temp = (char *)ioctl_param;            // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));   //passing generated random number to user space

         break;
                           
    case IOCTL_Z_DIR_COMPASS:    
          temp = (char *)ioctl_param;             // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));    //passing generated random number to user space

         break;  
         
    case IOCTL_PRESSURE_BAROMETER:
         
          temp = (char *)ioctl_param;            // type casting ioctl param to char *
          copy_to_user(temp, &i1, sizeof(i1));   //passing generated random number to user space

         break;
    default :  
             break;

    }

    return SUCCESS;
}




static int __init mychar_init(void)
{
  printk(KERN_INFO  "IMU CHAR driver registered ");
  
  //////////////////////reserve <major,minor>/////////////////////////
  if(alloc_chrdev_region(&first,0,1,"BITS-PILANI")<0)
  {
        return -1;
  }
  
  ////////////////dynamically create device node in /dev directory     ////////////////////////
  if((cls=class_create(THIS_MODULE,"chardev"))==NULL)    //creating class
  {
      unregister_chrdev_region(first,1);                 //unregistering the character device with major and minor number
	  return -1;
  }
  
 //////////// creating device node ////////////////////////
  if((device_create(cls,NULL,first,NULL,"imu_char"))==NULL)
  {
      class_destroy(cls);                                     //destroying the device class 
      unregister_chrdev_region(first,1);                      //unregistering the character device with major and minor number 
	  return -1;
  }
  
  
/////////// Link file_operations and Cdev to device node///////////////////
  cdev_init(&c_dev,&fops);
  if(cdev_add(&c_dev,first,1)== -1)
  {
      device_destroy(cls,first);                            //destroy device node
      class_destroy(cls);                                   //destroying the device class 
      unregister_chrdev_region(first,1);                   //unregistering the character device with major and minor number 
	  return -1;
  }
  return 0;  
}


//Deregistering or removing the device file
static void __exit mychar_exit(void)
{
   cdev_del(&c_dev);                            //deleting the link between cdev and file operations
   device_destroy(cls,first);                   //destroy device node
   class_destroy(cls);                          //destroying the device class 
   unregister_chrdev_region(first,1);           //unregistering the character device with major and minor number
   printk(KERN_INFO "Bye:imu char driver unregistered\n\n");
   
}

module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");   
MODULE_AUTHOR("SAINADH");
MODULE_DESCRIPTION("Assignment-1");
