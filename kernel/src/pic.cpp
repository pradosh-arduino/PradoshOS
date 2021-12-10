#include "pic.h"
#include "IO.h"
#include "BasicRenderer.h"

#include <stdint.h>

void pic_init()
{
	/* We have to remap the IRQs to be able to process
	 * hardware-related interrupt requests and to service
	 * exceptions as well.
	 */
	

	/* First step is to save current masks, set by BIOS */
	GlobalRenderer->Println("Beginning initialization of PIC");
	/* set up cascading mode */
	outb(PIC_MASTER_CMD, 0x10 + 0x01);
	outb(PIC_SLAVE_CMD,  0x10 + 0x01);
	/* Setup master's vector offset */
	outb(PIC_MASTER_DATA, 0x20);
	/* Tell the slave its vector offset */
	outb(PIC_SLAVE_DATA, 0x28);
	/* Tell the master that he has a slave */
	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2);
	/* Enabled 8086 mode */
	outb(PIC_MASTER_DATA, 0x01);
	outb(PIC_SLAVE_DATA, 0x01);

	GlobalRenderer->Println("Resetting masks...");
	outb(PIC_MASTER_DATA, 0);
	outb(PIC_SLAVE_DATA, 0);
	GlobalRenderer->Println("Init done.");
}

void pic_send_eoi(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC_SLAVE_CMD, PIC_CMD_EOI);
	outb(PIC_MASTER_CMD, PIC_CMD_EOI);
}