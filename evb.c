#include <linux/slab.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/jiffies.h>

#define GENERATOR_LENGTH 8
#define MSG_MAX 1024

MODULE_AUTHOR("TEAM 7");
MODULE_LICENSE("GPL");

static int j_temp = 0;
static char keyboard_pool[MSG_MAX];
static char mouse_pool[MSG_MAX];
static char tmp_buf[MSG_MAX];

unsigned mask =  (1 >> GENERATOR_LENGTH) - 1;
int pow(int base, int exp)
    {
      if(exp < 0)
        return -1;

        int result = 1;
        while (exp)
        {
            if (exp & 1)
                result *= base;
            exp >>= 1;
            base *= base;
        }

        return result;
    }

static void evbug_event(struct input_handle *handle, unsigned int type, unsigned int code, int value)
{

if(!strcmp(dev_name(&handle->dev->dev), "input1") && type == 1 && value == 1){

j_temp = jiffies % pow(2, GENERATOR_LENGTH) & mask;
printk(KERN_DEBUG "KEYBOARD %lu\n", j_temp);
sprintf(tmp_buf, "%lu\n", j_temp);
strcat(keyboard_pool, tmp_buf);
strcpy(tmp_buf, "");
}

else if(!strcmp(dev_name(&handle->dev->dev), "input4") && type != 0 && code == 1 && value != 0 && (value % pow(2, GENERATOR_LENGTH) & mask - j_temp > 4)){

j_temp = value % pow(2, GENERATOR_LENGTH) & mask;
printk(KERN_DEBUG "MOUSE %lu\n", j_temp);
sprintf(tmp_buf, "%lu\n", j_temp);
strcat(mouse_pool, tmp_buf);
strcpy(tmp_buf, "");
}
/*
else

printk(KERN_DEBUG "Event. Dev: %s, Type: %d, Code: %d, Value: %d\n", dev_name(&handle->dev->dev), type, code, value);
*/
}

static int evbug_connect(struct input_handler *handler, struct input_dev *dev,
			 const struct input_device_id *id)
{
	struct input_handle *handle;
	int error;

	handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "evbug";

	error = input_register_handle(handle);
	if (error)
		goto err_free_handle;

	error = input_open_device(handle);
	if (error)
		goto err_unregister_handle;

	printk(KERN_DEBUG pr_fmt("Connected device: %s (%s at %s)\n"),
	       dev_name(&dev->dev),
	       dev->name ?: "unknown",
	       dev->phys ?: "unknown");

	return 0;

 err_unregister_handle:
	input_unregister_handle(handle);
 err_free_handle:
	kfree(handle);
	return error;
}

static void evbug_disconnect(struct input_handle *handle)
{
	printk(KERN_DEBUG pr_fmt("Disconnected device: %s\n"),
	       dev_name(&handle->dev->dev));

	input_close_device(handle);
	input_unregister_handle(handle);
	kfree(handle);
}

static const struct input_device_id evbug_ids[] = {
	{ .driver_info = 1 },	/* Matches all devices */
	{ },			/* Terminating zero entry */
};

MODULE_DEVICE_TABLE(input, evbug_ids);

static struct input_handler evbug_handler = {
	.event =	evbug_event,
	.connect =	evbug_connect,
	.disconnect =	evbug_disconnect,
	.name =		"evbug",
	.id_table =	evbug_ids,
};

static int __init evbug_init(void)
{
	return input_register_handler(&evbug_handler);
}

static void __exit evbug_exit(void)
{

printk(KERN_DEBUG "----KEYBOARD POOL----\n %s \n", keyboard_pool);

printk(KERN_DEBUG "----MOUSE POOL----\n %s \n", mouse_pool);

	input_unregister_handler(&evbug_handler);
}

module_init(evbug_init);
module_exit(evbug_exit);
