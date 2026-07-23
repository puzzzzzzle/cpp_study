#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define DEVICE_NAME "simple_char_device"
#define BUFFER_SIZE 1024

static int major;
static char device_buffer[BUFFER_SIZE];
static struct cdev simple_cdev;
static struct class *simple_class;
static struct device *simple_device;

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "simple_char_device: opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "simple_char_device: closed\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    ssize_t bytes_read;

    if (*ppos >= BUFFER_SIZE)
        return 0;

    if (*ppos + count > BUFFER_SIZE)
        count = BUFFER_SIZE - *ppos;

    bytes_read = count - copy_to_user(buf, device_buffer + *ppos, count);
    *ppos += bytes_read;

    printk(KERN_INFO "simple_char_device: read %zu bytes\n", bytes_read);
    return bytes_read;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    ssize_t bytes_written;

    if (*ppos >= BUFFER_SIZE)
        return -ENOSPC;

    if (*ppos + count > BUFFER_SIZE)
        count = BUFFER_SIZE - *ppos;

    bytes_written = count - copy_from_user(device_buffer + *ppos, buf, count);
    *ppos += bytes_written;

    printk(KERN_INFO "simple_char_device: wrote %zu bytes\n", bytes_written);
    return bytes_written;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};
static int __init simple_char_init(void)
{
    dev_t dev;
    int result;

    result = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (result < 0) {
        printk(KERN_WARNING "simple_char_device: can't get major number\n");
        return result;
    }

    major = MAJOR(dev);
    cdev_init(&simple_cdev, &fops);
    simple_cdev.owner = THIS_MODULE;
    result = cdev_add(&simple_cdev, dev, 1);
    if (result) {
        unregister_chrdev_region(dev, 1);
        printk(KERN_WARNING "simple_char_device: can't add cdev\n");
        return result;
    }

    simple_class = class_create(DEVICE_NAME);
    if (IS_ERR(simple_class)) {
        cdev_del(&simple_cdev);
        unregister_chrdev_region(dev, 1);
        printk(KERN_WARNING "simple_char_device: can't create class\n");
        return PTR_ERR(simple_class);
    }

    simple_device = device_create(simple_class, NULL, dev, NULL, DEVICE_NAME);
    if (IS_ERR(simple_device)) {
        class_destroy(simple_class);
        cdev_del(&simple_cdev);
        unregister_chrdev_region(dev, 1);
        printk(KERN_WARNING "simple_char_device: can't create device\n");
        return PTR_ERR(simple_device);
    }

    printk(KERN_INFO "simple_char_device: registered with major number %d\n", major);
    return 0;
}

static void __exit simple_char_exit(void)
{
    device_destroy(simple_class, MKDEV(major, 0));
    class_destroy(simple_class);
    cdev_del(&simple_cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
    printk(KERN_INFO "simple_char_device: unregistered\n");
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("puzzzzzzle");
MODULE_DESCRIPTION("A simple character device driver");
