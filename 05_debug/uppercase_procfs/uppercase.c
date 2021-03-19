// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <asm/param.h>
#include <linux/string.h>

#define BUFSIZE 128
#define TMP_BUFSIZE 16

static char str[BUFSIZE];
static char tmp[TMP_BUFSIZE];
static unsigned int total_calls;
static unsigned int char_processed;
static unsigned int char_converted;

static struct proc_dir_entry *upper_ent, *total_calls_ent, *char_processed_ent,
			     *char_converted_ent;

static ssize_t upper_write(struct file *file, const char __user *ubuf,
			   size_t count, loff_t *ppos)
{
	int ret, i;

	memset(str, '\0', BUFSIZE);

	ret = simple_write_to_buffer(str, sizeof(str), ppos, ubuf, count);

	for (i = 0; str[i]; ++i) {
		char_processed++;
		if (str[i] >= 'a' && str[i] <= 'z') {
			char_converted++;
			str[i] = 'A' + (str[i] - 'a');
		}
	}

	total_calls++;

	return ret;
}

static ssize_t upper_read(struct file *file, char __user *ubuf, size_t count,
			  loff_t *ppos)
{
	return simple_read_from_buffer(ubuf, count, ppos, str, strlen(str));
}

static ssize_t total_calls_read(struct file *file, char __user *ubuf,
				size_t count, loff_t *ppos)
{
	int ret;

	memset(tmp, '\0', TMP_BUFSIZE);
	ret = sprintf(tmp, "%u\n", total_calls);
	return simple_read_from_buffer(ubuf, count, ppos, tmp, ret);
}

static ssize_t char_processed_read(struct file *file, char __user *ubuf,
				size_t count, loff_t *ppos)
{
	int ret;

	memset(tmp, '\0', TMP_BUFSIZE);
	ret = sprintf(tmp, "%u\n", char_processed);
	return simple_read_from_buffer(ubuf, count, ppos, tmp, ret);
}

static ssize_t char_converted_read(struct file *file, char __user *ubuf,
				size_t count, loff_t *ppos)
{
	int ret;

	memset(tmp, '\0', TMP_BUFSIZE);
	ret = sprintf(tmp, "%u\n", char_converted);
	return simple_read_from_buffer(ubuf, count, ppos, tmp, ret);
}

static struct proc_ops upper_ops = {
	.proc_read = upper_read,
	.proc_write = upper_write,
};

static struct proc_ops total_calls_ops = {
	.proc_read = total_calls_read,
};

static struct proc_ops char_processed_ops = {
	.proc_read = char_processed_read,
};

static struct proc_ops char_converted_ops = {
	.proc_read = char_converted_read,
};

static int __init upper_init(void)
{
	upper_ent = proc_create("uppercase", 0660, NULL, &upper_ops);
	total_calls_ent = proc_create("total_calls", 0440, NULL,
				      &total_calls_ops);
	char_processed_ent = proc_create("char_processed", 0440, NULL,
					 &char_processed_ops);
	char_converted_ent = proc_create("char_converted", 0440, NULL,
					 &char_converted_ops);
	return 0;
}

static void __exit upper_exit(void)
{
	proc_remove(upper_ent);
	proc_remove(total_calls_ent);
	proc_remove(char_processed_ent);
	proc_remove(char_converted_ent);
}

module_init(upper_init);
module_exit(upper_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roman Bublyk <roman.bublyk@globallogic.com>");
MODULE_DESCRIPTION("Uppercase converter using procfs");
MODULE_VERSION("0.1");
