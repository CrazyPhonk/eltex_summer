#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>

static int major = 0;
static struct proc_dir_entry *test = NULL;
static struct kobject *test_kobj = NULL;
static char test_string[15] = "Hello!\n\0";

ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off);
ssize_t test_write(struct file *fd, const char __user *buff, size_t size, loff_t *off);
ssize_t test_proc_read(struct file *fd, char __user *buff, size_t size, loff_t *off);
ssize_t test_proc_write(struct file *fd, const char __user *buff, size_t size, loff_t *off);

ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    rc = simple_read_from_buffer(buff, size, off, test_string, 15);

    return rc;
}

ssize_t test_write(struct file *fd, const char __user *buff, size_t size, loff_t *off) {
    size_t rc = 0;
    if (size > 15)
        return -EINVAL;

    rc = simple_write_to_buffer(test_string, 15, off, buff, size);

    return rc;
}

ssize_t test_proc_read(struct file *fd, char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    rc = simple_read_from_buffer(buff, size, off, test_string, 15);

    return rc;
}

ssize_t test_proc_write(struct file *fd, const char __user *buff, size_t size, loff_t *off) {
    size_t rc = 0;

    rc = simple_write_to_buffer(test_string, 15, off, buff, size);

    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};

static const struct proc_ops pops = {
    .proc_read = test_proc_read,
    .proc_write = test_proc_write,
};


int init_module(void) {

    pr_info("Test module is loaded.\n");
    major = register_chrdev(major, "task1", &fops);

    if (major < 0)
        return major;
    pr_info("Major number is %d.\n", major);

    test = proc_create("task1", 0666, NULL, &pops);

    test_kobj = kobject_create_and_add("kobject_test", kernel_kobj);

    if (!test_kobj)
        return -ENOMEM;

    return 0;
}

void cleanup_module(void) {
    unregister_chrdev(major, "task1");
    proc_remove(test);
    kobject_put(test_kobj);
    pr_info("My test module unloaded!");
}

MODULE_LICENSE("GPL");
