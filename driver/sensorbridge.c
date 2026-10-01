/*
 * SensorBridgeX - Linux character device driver
 *
 * Demonstration driver. It keeps the latest simulated sensor packet
 * in kernel memory and exposes it through /dev/sensorbridge.
 */

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#include "../include/sensorbridge_ioctl.h"

#define DEVICE_NAME "sensorbridge"
#define CLASS_NAME  "sensorbridge"

struct sensor_packet {
    float temperature;
    float humidity;
    int light;
};

static dev_t dev_number;
static struct cdev sensor_cdev;
static struct class *sensor_class;
static struct device *sensor_device;
static DEFINE_MUTEX(sensor_lock);

static struct sensor_packet packet = {
    .temperature = 25.0f,
    .humidity = 50.0f,
    .light = 500
};

static unsigned long read_count;
static int sample_rate_ms = 1000;

static int sensorbridge_open(struct inode *inode, struct file *file)
{
    pr_info("SensorBridgeX: device opened\n");
    return 0;
}

static int sensorbridge_release(struct inode *inode, struct file *file)
{
    pr_info("SensorBridgeX: device closed\n");
    return 0;
}

static ssize_t sensorbridge_read(struct file *file, char __user *buffer,
                                 size_t len, loff_t *offset)
{
    struct sensor_packet local;

    if (len < sizeof(local))
        return -EINVAL;

    if (*offset != 0)
        return 0;

    mutex_lock(&sensor_lock);
    local = packet;
    read_count++;
    mutex_unlock(&sensor_lock);

    if (copy_to_user(buffer, &local, sizeof(local)))
        return -EFAULT;

    *offset += sizeof(local);
    return sizeof(local);
}

static ssize_t sensorbridge_write(struct file *file,
                                  const char __user *buffer,
                                  size_t len, loff_t *offset)
{
    struct sensor_packet local;

    if (len != sizeof(local))
        return -EINVAL;

    if (copy_from_user(&local, buffer, sizeof(local)))
        return -EFAULT;

    mutex_lock(&sensor_lock);
    packet = local;
    mutex_unlock(&sensor_lock);

    pr_info("SensorBridgeX: sensor packet updated\n");
    return sizeof(local);
}

static long sensorbridge_ioctl(struct file *file, unsigned int cmd,
                               unsigned long arg)
{
    int value;

    switch (cmd) {
    case SENSORBRIDGE_GET_STATUS:
        value = 1;
        if (copy_to_user((int __user *)arg, &value, sizeof(value)))
            return -EFAULT;
        return 0;

    case SENSORBRIDGE_SET_SAMPLE_RATE:
        if (copy_from_user(&value, (int __user *)arg, sizeof(value)))
            return -EFAULT;
        if (value <= 0 || value > 60000)
            return -EINVAL;
        sample_rate_ms = value;
        pr_info("SensorBridgeX: sample rate set to %d ms\n", sample_rate_ms);
        return 0;

    case SENSORBRIDGE_RESET:
        mutex_lock(&sensor_lock);
        packet.temperature = 25.0f;
        packet.humidity = 50.0f;
        packet.light = 500;
        mutex_unlock(&sensor_lock);
        pr_info("SensorBridgeX: sensor reset\n");
        return 0;

    case SENSORBRIDGE_GET_READ_COUNT:
        if (copy_to_user((unsigned long __user *)arg,
                         &read_count, sizeof(read_count)))
            return -EFAULT;
        return 0;

    default:
        return -ENOTTY;
    }
}

static const struct file_operations sensorbridge_fops = {
    .owner = THIS_MODULE,
    .open = sensorbridge_open,
    .release = sensorbridge_release,
    .read = sensorbridge_read,
    .write = sensorbridge_write,
    .unlocked_ioctl = sensorbridge_ioctl,
};

static int __init sensorbridge_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret)
        return ret;

    cdev_init(&sensor_cdev, &sensorbridge_fops);
    ret = cdev_add(&sensor_cdev, dev_number, 1);
    if (ret)
        goto unregister_region;

    sensor_class = class_create(CLASS_NAME);
    if (IS_ERR(sensor_class)) {
        ret = PTR_ERR(sensor_class);
        goto del_cdev;
    }

    sensor_device = device_create(sensor_class, NULL, dev_number, NULL,
                                  DEVICE_NAME);
    if (IS_ERR(sensor_device)) {
        ret = PTR_ERR(sensor_device);
        goto destroy_class;
    }

    pr_info("SensorBridgeX: driver loaded\n");
    pr_info("SensorBridgeX: major=%d minor=%d\n",
            MAJOR(dev_number), MINOR(dev_number));
    return 0;

destroy_class:
    class_destroy(sensor_class);
del_cdev:
    cdev_del(&sensor_cdev);
unregister_region:
    unregister_chrdev_region(dev_number, 1);
    return ret;
}

static void __exit sensorbridge_exit(void)
{
    device_destroy(sensor_class, dev_number);
    class_destroy(sensor_class);
    cdev_del(&sensor_cdev);
    unregister_chrdev_region(dev_number, 1);
    pr_info("SensorBridgeX: driver unloaded\n");
}

module_init(sensorbridge_init);
module_exit(sensorbridge_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SensorBridgeX");
MODULE_DESCRIPTION("Embedded Linux Sensor Gateway Character Device Driver");
MODULE_VERSION("1.0");
