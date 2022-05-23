#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//要去define tx2上led對應io口的register位置

#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];

unsigned int *led_config;
unsigned int *led_data;

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos) {
    printk("device read\n");
    printk("Enter Read function\n");
    //##
    led_config = ioremap(/*define的東西*/, 4);  // 轉成虛擬位置
	writel(/*位置*/, led_config);
	led_data = ioremap(/*define的東西*/, 4);
	return 0;
    //##
    
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) {
    printk("Enter Write function\n");
    printk("device write\n");
    printk("%d\n", iCount);
    printk("W_buf_size: %d\n", (int)count);
    //##
    copy_from_user(userChar, buf, count);//接收buf
    //##
    userChar[count - 1] = 0;
    printk("userChar: %s\n", userChar);
    printk("userChar: %d\n", (int)sizeof(userChar));
    iCount++;
    return count;
}


long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    printk("Enter I/O Control function\n");
    printk("device ioctl\n");
    //##
    switch(cmd){
		case LED1_ON:
			writel(0x1c0, led_data);
			return 0;
		case LED2_ON:
			writel(0x1a0, led_data);
			return 0;
		case LED3_ON:
			writel(0x160, led_data);
			return 0;
		case LED4_ON:
			writel(0xe0, led_data);
			return 0;
		case LED_OFF:
			writel(0x1ff, led_data);
			return 0;
		default:
            return 0;
    }
    //##
}

static int drv_open(struct inode *inode, struct file *filp) {
    printk("Enter Open function\n");
    printk("device open\n");
    return 0;
}

static int drv_release(struct inode *inode, struct file *filp) {
    printk("Enter Release function\n");
    printk("device close\n");
    return 0;
}

struct file_operations drv_fops = {
    read: drv_read,
    write: drv_write,
    unlocked_ioctl: drv_ioctl,
    open: drv_open,
    release: drv_release,
    
};

static int demo_init(void) {
    if(register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0)
    {
        printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
        return (-EBUSY);
    }
    printk("<1>%s: started\n", MODULE_NAME);
    return 0;
}

static void demo_exit(void) {
    unregister_chrdev(MAJOR_NUM, "demo");
    printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);