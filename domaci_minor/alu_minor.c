#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/semaphore.h>
#define BUFF_SIZE 20
MODULE_LICENSE("Dual BSD/GPL");

dev_t my_dev_id;
static struct class *my_class;
static struct device *my_device;
static struct cdev *my_cdev;
#define num_of_minors 6 //za rega, regb, regc, regd, op i result

char regA;
char regB;
char regC;
char regD;
int result; //potreban da bi rezultat mogao biti veci od 255 kako bi carry bio 1
char result2; //potreban u read funkciji kako bi u teminalu ispisivao samo osmobitne vrednosti
char carry;

int i=0;

int alu_open(struct inode *pinode, struct file *pfile);
int alu_close(struct inode *pinode, struct file *pfile);
ssize_t alu_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t alu_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);

struct file_operations my_fops =
{
	.owner = THIS_MODULE,
	.open = alu_open,
	.read = alu_read,
	.write = alu_write,
	.release = alu_close,
};


int alu_open(struct inode *pinode, struct file *pfile) 
{
		printk(KERN_INFO "Succesfully opened alu\n");
		return 0;
}

int alu_close(struct inode *pinode, struct file *pfile) 
{
		printk(KERN_INFO "Succesfully closed alu\n");
		return 0;
}

ssize_t alu_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset) 
{	int ret;
	char buff[BUFF_SIZE];
	long int len = 0;
	int minor=MINOR(pfile->f_inode->i_rdev);

	if(minor==0){
	len = scnprintf(buff, BUFF_SIZE, "%d\n", regA);	
		ret = copy_to_user(buffer, buff, len);
		if(ret)
			return -EFAULT;
		printk(KERN_INFO "%d",regA);
	}

	if(minor==1){
	len = scnprintf(buff, BUFF_SIZE, "%d\n", regB);	
		ret = copy_to_user(buffer, buff, len);
		if(ret)
			return -EFAULT;
		printk(KERN_INFO "%d",regB);
	}

	if(minor==2){
	len = scnprintf(buff, BUFF_SIZE, "%d\n", regC);	
		ret = copy_to_user(buffer, buff, len);
		if(ret)
			return -EFAULT;	
		printk(KERN_INFO "%d",regC);
	}

	if(minor==3){
	len = scnprintf(buff, BUFF_SIZE, "%d\n", regD);	
		ret = copy_to_user(buffer, buff, len);
		if(ret)
			return -EFAULT;
		printk(KERN_INFO "%d",regD);
	}

	if(minor==5){ //alu_result
		result2=result;
		len = scnprintf(buff, BUFF_SIZE, "%x %d\n", result2, carry);	//result2 je 8bitni
		ret = copy_to_user(buffer, buff, len);
		if(ret)
			return -EFAULT;
		printk(KERN_INFO "%x %d", result2, carry);
	}
return 0;
}

ssize_t alu_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) 
{
	char buff[BUFF_SIZE];
	int num;
	int ret;
 	char znak, sabirak1, sabirak2;
	int operand1, operand2;
	int minor=MINOR(pfile->f_inode->i_rdev);

	ret = copy_from_user(buff, buffer, length);
	if(ret)
		return -EFAULT;
	buff[length-1] = '\0';
	
	ret = sscanf(buff,"0x%x", &num); //npr. echo '0x0c' > dev/alu_regA
	if(ret==1){
		printk(KERN_INFO "Uspesno upisano u reg");
		if(minor==0){ 
			regA=num;
			printk(KERN_INFO "regA=%d", num);
		}
		else if(minor==1){
		       	regB=num;	
			printk(KERN_INFO "regB=%d", num);
	}
		else if(minor==2){
		       	regC=num;
			printk(KERN_INFO "regC=%d", num);
		}
		else if(minor==3){
		       	regD=num;
			printk(KERN_INFO "regD=%d", num);
		}
		else printk(KERN_WARNING "Greska");
	}

	if(minor==4){ //alu_op	
	ret = sscanf(buff, "reg%c %c reg%c", &sabirak1, &znak, &sabirak2);
		if(ret==3)
		{

			printk(KERN_INFO "Succesfully wrote reg%c %c reg%c", sabirak1, znak, sabirak2);
			switch(sabirak1){ 
				case 'A': operand1 = regA;
				break; 
				case 'B': operand1 = regB;
				break;
				case 'C': operand1 = regC;
				break; 
				case 'D': operand1 = regD;
				break;
				default:
				printk(KERN_WARNING "Greska pri dodavanju vrednosti operandu1");
			};
			switch(sabirak2){ 
				case 'A': operand2 = regA;
				break; 
				case 'B': operand2 = regB;
				break;
				case 'C': operand2 = regC;
				break; 
				case 'D': operand2 = regD;
				break;
				default:
				printk(KERN_WARNING "Greska pri dodavanju vrednosti operandu2");
			};
			switch(znak){
				case '+': result = operand1 + operand2;
				break;
				case '-': result = operand1 - operand2;
				break;
				case '*': result = operand1 * operand2;
				break;
				case '/': result = operand1/operand2;
				break;
				default:
				printk(KERN_WARNING "Greska u racunanju rezultata");
			};
				printk(KERN_INFO "Rezultat operacije je %d", result);
				if(result>255) carry=1;
				else carry=0;
		} // od ret==3			
	} //od if(minor==4)
	return length;
}

static int __init alu_init(void)
{
   int ret = 0;
regA=0;
regB=0;
regC=0;
regD=0;
   carry=0;
   result=0;
   result2=0;
   
   ret = alloc_chrdev_region(&my_dev_id, 0, num_of_minors, "alu_minor");
   if (ret){
      printk(KERN_ERR "failed to register char device\n");
      return ret;
   }
   printk(KERN_INFO "char device region allocated\n");

   my_class = class_create(THIS_MODULE, "alu_class");
   if (my_class == NULL){
      printk(KERN_ERR "failed to create class\n");
      goto fail_0;
   }
   printk(KERN_INFO "class created\n");
  
  for(i=0; i<num_of_minors; i++){
	if(i==0)	
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_regA");
	else if(i==1) 
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_regB");
	else if(i==2) 
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_regC");
	else if(i==3) 
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_regD");
	else if(i==4) 
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_op");
	else if(i==5) 
	my_device = device_create(my_class, NULL,  MKDEV(MAJOR(my_dev_id), i), NULL, "alu_result");

   if (my_device == NULL){
      printk(KERN_ERR "failed to create device\n");
      goto fail_1;
   }
  } // od for
   printk(KERN_INFO "device created\n");

	my_cdev = cdev_alloc();	
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	ret = cdev_add(my_cdev, my_dev_id, num_of_minors);
	if (ret)
	{
      printk(KERN_ERR "failed to add cdev\n");
		goto fail_2;
	}
   printk(KERN_INFO "cdev added\n");
   printk(KERN_INFO "Hello world\n");

   return 0;

   fail_2:
      device_destroy(my_class, my_dev_id);
   fail_1:
      class_destroy(my_class);
   fail_0:
      unregister_chrdev_region(my_dev_id, 1);//ovde 1????
   return -1;
}

static void __exit alu_exit(void)
{
   cdev_del(my_cdev);
   for(i=0; i<num_of_minors; i++)
   device_destroy(my_class, MKDEV(MAJOR(my_dev_id),i));
   class_destroy(my_class);
   unregister_chrdev_region(my_dev_id,num_of_minors);
   printk(KERN_INFO "Goodbye, cruel world\n");
}


module_init(alu_init);
module_exit(alu_exit);
