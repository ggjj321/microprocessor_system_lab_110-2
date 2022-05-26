#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>


#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];

static int led1State = 0;
static int led2State = 0;
static int led3State = 0;
static int led4State = 0;

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

    printk("set_led_buf: %s\n", buf);

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

int gpio_led_unexport(unsigned int gpio)
{
    struct file *fp;
    loff_t pos = 0;
    mm_segment_t old_fs;

    char buf[64];

    fp = filp_open("/sys/class/gpio/unexport", O_WRONLY, 0);

    int len = snprintf(buf, sizeof(buf), "%d", gpio);
    vfs_write(fp, buf, len, &pos);
    filp_close(fp, NULL);
    return 0;
}

int gpio_export(unsigned int gpio)
{
    struct file *fp;
    loff_t pos = 0;
    mm_segment_t old_fs;
    char buf[64];

    fp = filp_open("/sys/class/gpio/export", O_WRONLY, 0);

    int len = snprintf(buf, sizeof(buf), "%d", gpio);
    vfs_write(fp, buf, len, &pos);
    filp_close(fp, NULL);
    return 0;
}

int gpio_set_dir(unsigned int gpio)
{
    struct file *fp;
    loff_t pos = 0;
    mm_segment_t old_fs;
    char buf[64];

    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/direction", gpio);

    fp = filp_open(buf, O_WRONLY, 0);

    vfs_write(fp, "out", 4, &pos);

    filp_close(fp, NULL);
    return 0;
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos) {
    printk("device read\n");
    printk("Enter Read function\n");

    copy_from_user(userChar, buf, count);
    userChar[count - 1] = 0;

    int led = (int) userChar[0];
	return 0;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) {
    printk("Enter Write function\n");
    printk("device write\n");
    printk("%d\n", iCount);
    printk("W_buf_size: %d\n", (int)count);

    copy_from_user(userChar, buf, count);

    userChar[count - 1] = 0;

    printk("userChar: %s\n", userChar);

    int led = (int) userChar[0] - 48;
    int state = (int) userChar[1] - 48;

    printk("led1: %d %d", led, state);

    if(led == 1) {
        printk("led1: %d %d", led, state);
        gpio_set_led_value(led1Pin, state);
    }
    

    if(led == 2) gpio_set_led_value(led2Pin, state);

    if(led == 3) gpio_set_led_value(led3Pin, state);

    if(led == 4) gpio_set_led_value(led4Pin, state);

    iCount++;
    return count;
}


long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    printk("Enter I/O Control function\n");
    printk("device ioctl\n");
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

    // gpio_export(led1Pin);
    // gpio_export(led2Pin);
    // gpio_export(led3Pin);
    // gpio_export(led4Pin);

    // gpio_set_dir(led1Pin);
    // gpio_set_dir(led2Pin);
    // gpio_set_dir(led3Pin);
    // gpio_set_dir(led4Pin);

    return 0;
}

static void demo_exit(void) {
    unregister_chrdev(MAJOR_NUM, "demo");
    printk("<1>%s: removed\n", MODULE_NAME);

    // gpio_led_unexport(led1Pin);
    // gpio_led_unexport(led2Pin);
    // gpio_led_unexport(led3Pin);
    // gpio_led_unexport(led4Pin);
}

module_init(demo_init);
module_exit(demo_exit);