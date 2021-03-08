// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/printk.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/fs.h>
#include <linux/slab.h>

struct kernel_kobj {
	char str[64];
	struct kobject *kobj;
	struct list_head list;
};

static LIST_HEAD(klist_head);
static struct kobject *kobj_hello;

static unsigned int print_list(struct list_head *lhead, char *buf)
{
	struct kernel_kobj *kkobj = NULL;
	unsigned int count = 0;

	list_for_each_entry(kkobj, lhead, list) {
		count += sprintf(buf+count, "%s ", kkobj->str);
	}
	count += sprintf(buf+count, "%s", "\n");
	return count;
}

static ssize_t list_show(struct kobject *kobj, struct kobj_attribute *attr,
			 char *buf)
{
	return print_list(&klist_head, buf);
}

static ssize_t list_store(struct kobject *kobj, struct kobj_attribute *attr,
			  const char *buf, size_t count)
{
	struct kernel_kobj *node;

	node = kmalloc(sizeof(struct kernel_kobj), GFP_KERNEL);
	node->kobj = kobj_hello;
	strncpy(node->str, buf, count);
	node->str[count-1] = '\0';
	list_add_tail(&node->list, &klist_head);
	return count;
}

static struct kobj_attribute kattr = __ATTR(list, 0660, list_show, list_store);

static int __init list_init(void)
{
	int error = 0;

	kobj_hello = kobject_create_and_add("hello", kernel_kobj);
	if (!kobj_hello)
		return -ENOMEM;

	error = sysfs_create_file(kobj_hello, &kattr.attr);
	if (error)
		pr_err("Failed to create the list file\n");

	return error;
}

static void __exit list_exit(void)
{
	if (!list_empty(&klist_head)) {
		struct kernel_kobj *node, *next;

		list_for_each_entry_safe(node, next, &klist_head, list) {
			list_del(&node->list);
			kfree(node);
		}
	}
	kobject_put(kobj_hello);
}

module_init(list_init);
module_exit(list_exit);

MODULE_AUTHOR("Roman Bublyk <rmn.bublyk@gmail.com>");
MODULE_DESCRIPTION("Linked list implementation in the sysfs");
MODULE_LICENSE("GPL");

