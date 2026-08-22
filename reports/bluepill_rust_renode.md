root@343c02b5f414:/workspaces/demo_renode/sim/stm32f103_bluepill# renode blue_pill.resc 

(renode:2450): Gtk-WARNING **: 20:47:59.928: Locale not supported by C library.
        Using the fallback 'C' locale.

(renode:2450): Gdk-CRITICAL **: 20:47:59.935: gdk_keymap_get_for_display: assertion 'GDK_IS_DISPLAY (display)' failed
20:47:59.9403 [WARNING] Couldn't start UI - falling back to console mode
20:48:00.2448 [INFO] Loaded monitor commands from: /opt/renode/scripts/monitor.py
Renode, version 1.16.1 (d66b0c2a-202602160933)

(monitor) i $CWD/blue_pill.resc
20:48:00.3493 [INFO] Including script(s): /workspaces/demo_renode/sim/stm32f103_bluepill/blue_pill.resc
20:48:00.3621 [INFO] System bus created.
20:48:00.6850 [WARNING] Translation cache size 536870912 is larger than maximum allowed 134217728. It will be clampedto maximum
20:48:00.9483 [INFO] sysbus: Loaded SVD: /tmp/renode-2450/bd85bccd-596b-439a-8785-72abd5eabb78.tmp. Name: STM32F103. Description: STM32F103.
20:48:00.9767 [INFO] sysbus: Loading block of 304 bytes length at 0x8000000.
20:48:00.9886 [INFO] sysbus: Loading block of 5396 bytes length at 0x8000130.
20:48:00.9887 [INFO] sysbus: Loading block of 1044 bytes length at 0x8001644.
20:48:00.9887 [INFO] sysbus: Loading block of 4 bytes length at 0x20000000.
20:48:01.2487 [INFO] stm32f103_bluepill: CPUs: ["stm32f103_bluepill.cpu"] were added to a new GDB server created on port :3333
20:48:01.2489 [INFO] stm32f103_bluepill: GDB server with all CPUs started on port :3333
Starting emulation...
20:48:01.2555 [INFO] stm32f103_bluepill: Machine started.
20:48:01.2781 [WARNING] gpioPortC: Trying to set the state of the input pin #13
20:48:01.2862 [INFO] usart1: [host: 55.84ms (+55.84ms)|virt: 0s (+0s)] Hello from STM32F103 Rust Firmware!
20:48:01.2877 [INFO] usart1: [host:   57.4ms (+1.56ms)|virt: 0s (+0s)] sum(10, 32) = 42
20:48:01.2882 [INFO] usart1: [host:  57.89ms (+0.49ms)|virt: 0s (+0s)] Blink STM32 loop executed. Pin PC13 state: 1
(stm32f103_bluepill) 20:48:19.6790 [INFO] usart1: [host:   18.45s (+18.39s)|virt: 0.11s (+0.11s)] Blink STM32 loop executed. Pin PC13 state: 0
20:48:22.2032 [INFO] usart1: [host:    20.97s (+2.52s)|virt: 0.22s (+0.11s)] Blink STM32 loop executed. Pin PC13 state: 1
20:48:24.4738 [INFO] usart1: [host:    23.24s (+2.27s)|virt: 0.33s (+0.11s)] Blink STM32 loop executed. Pin PC13 state: 0
20:48:26.5245 [INFO] usart1: [host:    25.29s (+2.05s)|virt: 0.44s (+0.11s)] Blink STM32 loop executed. Pin PC13 state: 1
pause
Pausing emulation...
20:48:28.3990 [INFO] stm32f103_bluepill: Machine paused.
(stm32f103_bluepill) q
Renode is quitting
20:48:52.4943 [INFO] stm32f103_bluepill: Disposed.
root@343c02b5f414:/workspaces/demo_renode/sim/stm32f103_bluepill# 