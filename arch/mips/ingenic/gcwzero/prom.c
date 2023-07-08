#include <uapi/linux/serial_reg.h>

#include <asm/bootinfo.h>

#include <asm/mach-ingenic/gcwzero/uart.h>

/* used by early printk */
void prom_putchar(char c)
{
	volatile u8 *uart_lsr = (volatile u8 *)(UART2_BASE + OFF_LSR);
	volatile u8 *uart_tdr = (volatile u8 *)(UART2_BASE + OFF_TDR);

	/* Wait for fifo to shift out some bytes */
	while ( !((*uart_lsr & (UART_LSR_THRE | UART_LSR_TEMT)) == 0x60) );

	*uart_tdr = (u8)c;
}
