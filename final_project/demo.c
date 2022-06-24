#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>


#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];

static int led1Pin = 396;
static int led2Pin = 397;
static int led3Pin = 398;
static int led4Pin = 254;

int gpio_set_led_value(unsigned int gpio, int value)
{
    struct file *fp;
    loff_t pos = 0;
    mm_segment_t old_fs;

    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);

    old_fs = get_fs();
    set_fs(get_ds());

    fp = filp_open(buf, O_WRONLY, 0);

    if(value == 0)
        vfs_write(fp, "0", 2, &pos);
    else   
        vfs_write(fp, "1", 2, &pos);
    
    filp_close(fp, NULL);
    return 0;
}

int gpio_get_value(unsigned int gpio)
{
    struct file *fp;
    loff_t pos = 0;
    mm_segment_t old_fs;
    char buf[64];
    char value[10];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);

    fp = filp_open(buf, O_WRONLY, 0);

    vfs_read(fp, value, 2, &pos);

    printk("input: %d\n", gpio);

    if(gpio == led1Pin){
        printk("LED1(GPIO=%d) Status : %s", gpio, value);
    }

    if(gpio == led2Pin){
        printk("LED2(GPIO=%d) Status : %s", gpio, value);
    }

    if(gpio == led3Pin){
        printk("LED3(GPIO=%d) Status : %s", gpio, value);
    }

    if(gpio == led4Pin){
        printk("LED1(GPIO=%d) Status : %s", gpio, value);
    }
}


static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos) {
    printk("Read: %s\n", "Enter Read function");
    printk("device read\n");

    copy_from_user(userChar, buf, count);
    userChar[count - 1] = 0;

    int led = (int) userChar[0] - 48;

    if(led == 1) {
        printk("userChar: %d\n", led1Pin);
        printk("Read-Value: %d\n", led1Pin);
    }
    

    if(led == 2) {
        printk("userChar: %d\n", led2Pin);
        printk("Read-Value: %d\n", led2Pin);
    }

    if(led == 3) {
        printk("userChar: %d\n", led3Pin);
        printk("Read-Value: %d\n", led3Pin);
    }

    if(led == 4) {
        printk("userChar: %d\n", led4Pin);
        printk("Read-Value: %d\n", led4Pin);
    }
	return 0;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) {
    printk("Write: %s\n", "Enter Write function");
    printk("device write\n");
    printk("%d\n", iCount);

    int len = (int)count;
    printk("W_buf_size: %d\n", len);

    copy_from_user(userChar, buf, count);

    userChar[count - 1] = 0;

    int led = (int) userChar[0] - 48;

    if(len == 2){
        if(led == 1) {
            printk("userChar: %d\n", led1Pin);
            gpio_get_value(led1Pin);
        }

        if(led == 2) {
            printk("userChar: %d\n", led2Pin);
            gpio_get_value(led2Pin);
        }

        if(led == 3) {
            printk("userChar: %d\n", led4Pin);
            gpio_get_value(led3Pin);
        }

        if(led == 4) {
            printk("userChar: %d\n", led4Pin);
            gpio_get_value(led4Pin);
        }
    }

    if(len == 3){
        int state = (int) userChar[1] - 48;

        if(led == 1) {
            printk("userChar: %d\n", led1Pin);
            gpio_set_led_value(led1Pin, state);
        }
        
        if(led == 2) {
            printk("userChar: %d\n", led2Pin);
            gpio_set_led_value(led2Pin, state);
        }

        if(led == 3) {
            printk("userChar: %d\n", led3Pin);
            gpio_set_led_value(led3Pin, state);
        }

        if(led == 4) {
            printk("userChar: %d\n", led4Pin);
            gpio_set_led_value(led4Pin, state);
        }
    }

    iCount++;
    return count;
}


long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    printk("I/O Control: %s\n", "Enter I/O Control function");
    printk("device ioctl\n");
}

static int drv_open(struct inode *inode, struct file *filp) {
    printk("Open: %s\n", "Enter Open function");
    printk("device open\n");
    return 0;
}

static int drv_release(struct inode *inode, struct file *filp) {
    printk("Release: %s\n", "Enter Release function");
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