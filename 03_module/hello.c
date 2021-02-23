// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("Roman Bublyk <rmn.bublyk@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
	pr_info("Hello, world!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_warn("Exit from kernel module");
}

module_init(hello_init);
module_exit(hello_exit);

