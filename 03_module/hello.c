// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("Roman Bublyk <rmn.bublyk@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

enum ret_code {
	OK = 0,
	ERROR = 1,
};

static unsigned int param;
module_param(param, uint, 0644);
MODULE_PARM_DESC(param, "Some test parameter");

static int __init hello_init(void)
{
	enum ret_code ret = OK;

	if (param <= 10) {
		pr_notice("The parameter is %u\n", param);
		ret = OK;
	} else {
		pr_err("ERROR: The parameter greater then 10\n");
		ret = ERROR;
	}

	return ret;
}

static void __exit hello_exit(void)
{
	pr_warn("Exit from kernel module\n");
}

module_init(hello_init);
module_exit(hello_exit);

