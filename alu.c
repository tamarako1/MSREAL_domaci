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

DECLARE_WAIT_QUEUE_HEAD(readQ);
DECLARE_WAIT_QUEUE_HEAD(writeQ);
struct semaphore sem;
char regA;
char regB;
char regC;
char regD;
int result; //potreban da bi rezultatm mogao biti veci od 255 kako bi carry bio 1
char result2; //potreban u read funkciji kako bi u teminalu ispisivao samo osmobitne vrednosti
char carry;
char format[4];

int pos = 0;  //mozda ce trebati u read f-ji
int endRead = 0; //takodje

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
	
	if(down_interruptible(&sem))
		return -ERESTARTSYS; 
	while(pos==0){
		up(&sem);
		if(wait_event_interruptible(readQ,(pos>0))) //da bi imao sta da procita ceka da je nesto upisano
			return -ERESTARTSYS;
		if(down_interruptible(&sem))//semafor zauzima podatak koji treba da se ispise
			return -ERESTARTSYS; 
	}
	if(pos==1){
		pos=0; //da bih osigurala da se samo jednom upise
		len = scnprintf(buff, BUFF_SIZE, "%d ", result);
		ret = copy_to_user(buffer, buff, len);
		result2=result;
		if(ret)
			return -EFAULT;
			
			if(result<255){
				carry=0;			
				printk(KERN_INFO "Succesfully read\n");
			if(format[1]=='h' && format[2]=='e' && format[3]=='x') printk(KERN_INFO "0x%x %d\n", result2, carry);
			if(format[1]=='d' && format[2]=='e' && format[3]=='c') printk(KERN_INFO "%d %d\n", result2, carry);
			

			} else {
				carry=1;
				if(format[1]=='h' && format[2]=='e' && format[3]=='x') printk(KERN_INFO "0x%x %d\n", result2, carry);
				if(format[1]=='d' && format[2]=='e' && format[3]=='c'){ printk(KERN_INFO "%d %d\n", result2, carry);
				printk(KERN_INFO "Overfflow is happened\n");
			}
			}
	} else {
		printk(KERN_WARNING "Nema sta da se procita");
	}
	up(&sem);
	wake_up_interruptible(&writeQ); //kada se nesto upise, moci ce da se procita
		return 0;	
}

ssize_t alu_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) 
{
	char buff[BUFF_SIZE];
	char reg;
	int num;
	int ret;
 	char znak, sabirak1, sabirak2;
	int operand1, operand2;

	ret = copy_from_user(buff, buffer, length);
	if(ret)
		return -EFAULT;
	buff[length-1] = '\0';
	
	if(down_interruptible(&sem))
		return -ERESTARTSYS;
	while(pos==1)
	{	
		up(&sem);
		if(wait_event_interruptible(writeQ,(pos==0))) //ceka da nema nista izracunato
			return -ERESTARTSYS;
		if(down_interruptible(&sem))
			return -ERESTARTSYS;
	}	
	if(pos==0){
	ret = sscanf(buff,"reg%c=%x", &reg, &num);	
		if(ret==2)//two parameter parsed in sscanf
		{
			printk(KERN_INFO "Succesfully wrote at reg%c, number %d\n", reg, num);
		
		switch(reg){
			case 'A': regA = num;
				printk(KERN_INFO "regA=%d", num);
			break;
			case 'B': regB = num;
				printk(KERN_INFO "regB=%d", num);
			break;
			case 'C': regC = num;
				printk(KERN_INFO "regC=%d", num);
			break; 	
			case 'D': regD = num;
				printk(KERN_INFO "regD=%d", num);
			break;
			default:
			printk(KERN_WARNING "greska prilikom upisa u registre");
		};	
		}

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
				pos++; //poveca se svaki put kad se upise neki rezultat
				printk(KERN_INFO "Rezultat operacije je %d", result);
		} // od ret==3			

		ret = sscanf(buff, "format%c%c%c%c", &format[0], &format[1], &format[2], &format[3]);
			if(ret==4){
			printk(KERN_INFO "Format je %c%c%c", format[1], format[2], format[3]);
			}
	} else {
		printk(KERN_WARNING "Ne moze da se upise, jer jos nije procitano");
	}
	up(&sem);
	wake_up_interruptible(&readQ);
	return length; //probaj return 0;
}

static int __init alu_init(void)
{
   int ret = 0;
   format[0]='=';
   format[1]='h';
   format[2]='e';
   format[3]='x';
   regA=0;
   regB=0;
   regC=0;
   regD=0;
   carry=0;
   result=0;
   result2=0;
   sema_init(&sem,1);
   ret = alloc_chrdev_region(&my_dev_id, 0, 1, "alu");
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
   
   my_device = device_create(my_class, NULL, my_dev_id, NULL, "alu");
   if (my_device == NULL){
      printk(KERN_ERR "failed to create device\n");
      goto fail_1;
   }
   printk(KERN_INFO "device created\n");

	my_cdev = cdev_alloc();	
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	ret = cdev_add(my_cdev, my_dev_id, 1);
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
      unregister_chrdev_region(my_dev_id, 1);
   return -1;
}

static void __exit alu_exit(void)
{
   cdev_del(my_cdev);
   device_destroy(my_class, my_dev_id);
   class_destroy(my_class);
   unregister_chrdev_region(my_dev_id,1);
   printk(KERN_INFO "Goodbye, cruel world\n");
}


module_init(alu_init);
module_exit(alu_exit);
