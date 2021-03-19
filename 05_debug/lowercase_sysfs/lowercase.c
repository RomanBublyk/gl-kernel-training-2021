// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/printk.h>
#include <linux/sysfs.h>

#define BUFSIZE 128

struct lowercase_sysfs {
	struct kobject *kobj;
	char str[BUFSIZE];
} lowercase_obj;

static unsigned int total_calls;
static unsigned int char_processed;
static unsigned int char_converted;

static struct kobject *kobj_lowercase;

static ssize_t show_lower(struct kobject *kobj, struct kobj_attribute *attr,
		    char *buf)
{
	return sprintf(buf, "%s", lowercase_obj.str);
}

static ssize_t show_total_calls(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", total_calls);
}

static ssize_t show_char_processed(struct kobject *kobj,
				   struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", char_processed);
}

static ssize_t show_char_converted(struct kobject *kobj,
				   struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", char_converted);
}

static ssize_t store_lower(struct kobject *kobj, struct kobj_attribute *attr,
		     const char *buf, size_t count)
{
	unsigned int i = 0;

	total_calls++;
	memset(lowercase_obj.str, '\0', BUFSIZE);
	for (i = 0; i < count; ++i) {
		char_processed++;
		if (buf[i] >= 'A' && buf[i] <= 'Z') {
			char_converted++;
			lowercase_obj.str[i] = 'a' + (buf[i] - 'A');
		} else
			lowercase_obj.str[i] = buf[i];
	}

	return count;
}

static struct kobj_attribute lower_kattr = __ATTR(converter, 0660, show_lower,
						  store_lower);
static struct kobj_attribute total_calls_kattr = __ATTR(total_calls, 0440,
							show_total_calls, NULL);
static struct kobj_attribute char_processed_kattr = __ATTR(char_processed, 0440,
							   show_char_processed,
							   NULL);
static struct kobj_attribute char_converted_kattr = __ATTR(char_converted, 0440,
							   show_char_converted,
							   NULL);

static int __init lower_init(void)
{
	int error = 0;

	kobj_lowercase = kobject_create_and_add("lowercase", kernel_kobj);
	if (!kobj_lowercase)
		return -ENOMEM;

	error = sysfs_create_file(kobj_lowercase, &lower_kattr.attr);
	if (error) {
		pr_err("Failed to create lowercase converter file\n");
		return error;
	}

	error = sysfs_create_file(kobj_lowercase, &total_calls_kattr.attr);
	if (error) {
		pr_err("Failed to create total calls file\n");
		return error;
	}

	error = sysfs_create_file(kobj_lowercase, &char_processed_kattr.attr);
	if (error) {
		pr_err("Failed to create char processed file\n");
		return error;
	}

	error = sysfs_create_file(kobj_lowercase, &char_converted_kattr.attr);
	if (error) {
		pr_err("Failed to create char converted file\n");
		return error;
	}

	return error;
}

static void __exit lower_exit(void)
{
	kobject_put(kobj_lowercase);
}

module_init(lower_init);
module_exit(lower_exit);

MODULE_AUTHOR("Roman Bublyk <rmn.bublyk@gmail.com>");
MODULE_DESCRIPTION("A simple string lowercase converter using sysfs");
MODULE_LICENSE("GPL");
