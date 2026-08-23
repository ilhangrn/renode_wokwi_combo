root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# renode blue_pill.resc 

(renode:59064): Gtk-WARNING **: 08:58:16.262: Locale not supported by C library.
        Using the fallback 'C' locale.

(renode:59064): Gdk-CRITICAL **: 08:58:16.269: gdk_keymap_get_for_display: assertion 'GDK_IS_DISPLAY (display)' failed
08:58:16.2740 [WARNING] Couldn't start UI - falling back to console mode
08:58:16.5660 [INFO] Loaded monitor commands from: /opt/renode/scripts/monitor.py
Renode, version 1.16.1 (d66b0c2a-202602160933)

(monitor) i $CWD/blue_pill.resc
08:58:16.6548 [INFO] Including script(s): /workspaces/demo_renode/sim/renode/stm32f103_bluepill/blue_pill.resc
08:58:16.6677 [INFO] System bus created.
08:58:16.9822 [WARNING] Translation cache size 536870912 is larger than maximum allowed 134217728. It will be clamped to maximum
08:58:17.2348 [INFO] sysbus: Loaded SVD: /tmp/renode-59064/821649f2-470d-4088-93c5-d21a3d102629.tmp. Name: STM32F103. Description: STM32F103.
08:58:17.2891 [INFO] sysbus: Loading block of 4900 bytes length at 0x8000000.
08:58:17.3020 [INFO] sysbus: Loading block of 528 bytes length at 0x8001324.
08:58:17.3021 [INFO] sysbus: Loading block of 1536 bytes length at 0x8001380.
Starting emulation...
08:58:17.5420 [INFO] cpu: Setting initial values: PC = 0x80011E1, SP = 0x20005000.
08:58:17.5439 [INFO] stm32f103_bluepill: Machine started.
08:58:17.5677 [WARNING] sysbus: [cpu: 0x80001AC] ReadDoubleWord from an unimplemented register FLASH:ACR (0x40022000), returning a value from SVD: 0x30
08:58:17.5689 [WARNING] sysbus: [cpu: 0x80001B4] WriteDoubleWord of value 0x30 to an unimplemented register FLASH:ACR (0x40022000) generated from SVD
08:58:17.5775 [WARNING] sysbus: [cpu: 0x8000728] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5775 [WARNING] sysbus: [cpu: 0x8000730] WriteDoubleWord of value 0x4 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
08:58:17.5775 [WARNING] sysbus: [cpu: 0x8000732] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5775 [WARNING] sysbus: [cpu: 0x800073E] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5776 [WARNING] sysbus: [cpu: 0x8000744] WriteDoubleWord of value 0x10 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
08:58:17.5776 [WARNING] sysbus: [cpu: 0x8000746] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5797 [WARNING] sysbus: [cpu: 0x800078A] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5797 [WARNING] sysbus: [cpu: 0x8000792] WriteDoubleWord of value 0x4000 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
08:58:17.5797 [WARNING] sysbus: [cpu: 0x8000794] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:58:17.5805 [WARNING] sysbus: [cpu: 0x80004A0] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
08:58:17.5818 [INFO] usart1: [host: 44.8ms (+44.8ms)|virt: 6.77µs (+6.77µs)] Hello from STM32F103 C Firmware!
08:58:17.5826 [INFO] usart1: [host: 45.88ms (+1.09ms)|virt:     6.77µs (+0s)] sum(10, 32) = 42
08:58:17.5828 [INFO] usart1: [host: 46.16ms (+0.27ms)|virt:     6.77µs (+0s)] Blink STM32 loop executed. Pin PC13 state: 1
(stm32f103_bluepill) 08:58:18.9223 [INFO] usart1: [host:    1.39s (+1.34s)|virt:         1s (+1s)] Blink STM32 loop executed. Pin PC13 state: 0
08:58:20.2076 [INFO] usart1: [host:    2.67s (+1.29s)|virt:         2s (+1s)] Blink STM32 loop executed. Pin PC13 state: 1
08:58:21.4993 [INFO] usart1: [host:    3.96s (+1.29s)|virt:         3s (+1s)] Blink STM32 loop executed. Pin PC13 state: 0
08:58:22.7828 [INFO] usart1: [host:    5.25s (+1.28s)|virt:         4s (+1s)] Blink STM32 loop executed. Pin PC13 state: 1
q
Renode is quitting
08:58:23.5935 [INFO] stm32f103_bluepill: Machine paused.
08:58:23.6160 [INFO] stm32f103_bluepill: Disposed.
root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# q
bash: q: command not found
root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# renode blue_pill.resc 

(renode:59319): Gtk-WARNING **: 08:59:00.853: Locale not supported by C library.
        Using the fallback 'C' locale.

(renode:59319): Gdk-CRITICAL **: 08:59:00.860: gdk_keymap_get_for_display: assertion 'GDK_IS_DISPLAY (display)' failed
08:59:00.8650 [WARNING] Couldn't start UI - falling back to console mode
08:59:01.1630 [INFO] Loaded monitor commands from: /opt/renode/scripts/monitor.py
Renode, version 1.16.1 (d66b0c2a-202602160933)

(monitor) i $CWD/blue_pill.resc
08:59:01.2562 [INFO] Including script(s): /workspaces/demo_renode/sim/renode/stm32f103_bluepill/blue_pill.resc
08:59:01.2687 [INFO] System bus created.
08:59:01.5764 [WARNING] Translation cache size 536870912 is larger than maximum allowed 134217728. It will be clamped to maximum
08:59:01.8312 [INFO] sysbus: Loaded SVD: /tmp/renode-59319/5d3adba3-2fa9-4eb0-bfc9-cbbff46e4819.tmp. Name: STM32F103. Description: STM32F103.
08:59:01.8808 [INFO] sysbus: Loading block of 8836 bytes length at 0x8000000.
08:59:01.8925 [INFO] sysbus: Loading block of 528 bytes length at 0x8002284.
08:59:01.8926 [INFO] sysbus: Loading block of 1536 bytes length at 0x80022E0.
Starting emulation...
08:59:02.1177 [INFO] cpu: Setting initial values: PC = 0x8000515, SP = 0x20005000.
08:59:02.1195 [INFO] stm32f103_bluepill: Machine started.
08:59:02.1437 [WARNING] sysbus: [cpu: 0x8000566] ReadDoubleWord from an unimplemented register FLASH:ACR (0x40022000), returning a value from SVD: 0x30
08:59:02.1450 [WARNING] sysbus: [cpu: 0x800056E] WriteDoubleWord of value 0x30 to an unimplemented register FLASH:ACR (0x40022000) generated from SVD
08:59:02.1540 [WARNING] sysbus: [cpu: 0x8000350] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:59:02.1540 [WARNING] sysbus: [cpu: 0x8000358] WriteDoubleWord of value 0x1 to an unimplementedregister RCC:APB2ENR (0x40021018) generated from SVD
08:59:02.1540 [WARNING] sysbus: [cpu: 0x800035C] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
08:59:02.1540 [WARNING] sysbus: [cpu: 0x8000368] ReadDoubleWord from an unimplemented register RCC:APB1ENR (0x4002101C), returning a value from SVD: 0x0
08:59:02.1540 [WARNING] sysbus: [cpu: 0x8000370] WriteDoubleWord of value 0x10000000 to an unimplemented register RCC:APB1ENR (0x4002101C) generated from SVD
08:59:02.1541 [WARNING] sysbus: [cpu: 0x8000374] ReadDoubleWord from an unimplemented register RCC:APB1ENR (0x4002101C), returning a value from SVD: 0x0
08:59:02.1571 [WARNING] afio: Unhandled write to offset 0x4. Unhandled bits: [26] when writing value 0x4000000. Tags: SWJ_CFG (0x4).
08:59:02.1572 [WARNING] sysbus: [cpu: 0x8000BEE] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
08:59:02.1573 [WARNING] sysbus: [cpu: 0x8000BFA] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
08:59:02.1574 [WARNING] sysbus: [cpu: 0x8000C36] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
08:59:02.1575 [WARNING] sysbus: [cpu: 0x8000C3E] WriteDoubleWord of value 0xA030083 to an unimplemented register RCC:CR (0x40021000) generated from SVD
08:59:02.1575 [WARNING] sysbus: [cpu: 0x8000CC4] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
08:59:02.1575 [WARNING] sysbus: [cpu: 0x8000FB6] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
08:59:02.1577 [WARNING] sysbus: [cpu: 0x8000FCC] WriteDoubleWord to non existing peripheral at 0x42420060, value 0x0.
08:59:02.1578 [WARNING] sysbus: [cpu: 0x8000FEA] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
08:59:02.2055 [WARNING] sysbus: [cpu: 0x8000FEA] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083. (10000)
(stm32f103_bluepill) 08:59:02.7073 [WARNING] sysbus: [cpu: 0x8000FEA] (tag: 'RCC_CR') ReadDoubleWord from non existing peripheral at 0x40021000, returning 0x0A020083. (5722)
q
Renode is quitting
08:59:12.1169 [INFO] stm32f103_bluepill: Machine paused.
08:59:12.1416 [INFO] stm32f103_bluepill: Disposed.
root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# 


---
after fix
root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# renode blue_pill.resc 

(renode:63129): Gtk-WARNING **: 09:15:35.809: Locale not supported by C library.
        Using the fallback 'C' locale.

(renode:63129): Gdk-CRITICAL **: 09:15:35.816: gdk_keymap_get_for_display: assertion 'GDK_IS_DISPLAY (display)' failed
09:15:35.8212 [WARNING] Couldn't start UI - falling back to console mode
09:15:36.1295 [INFO] Loaded monitor commands from: /opt/renode/scripts/monitor.py
Renode, version 1.16.1 (d66b0c2a-202602160933)

(monitor) i $CWD/blue_pill.resc
09:15:36.2273 [INFO] Including script(s): /workspaces/demo_renode/sim/renode/stm32f103_bluepill/blue_pill.resc
09:15:36.2395 [INFO] System bus created.
09:15:36.5569 [WARNING] Translation cache size 536870912 is larger than maximum allowed 134217728. It will be clamped to maximum
09:15:36.8330 [INFO] sysbus: Loaded SVD: /tmp/renode-63129/762a7e7b-3e10-49ac-a9b2-00c316e6e267.tmp. Name: STM32F103. Description: STM32F103.
09:15:36.8830 [INFO] sysbus: Loading block of 8816 bytes length at 0x8000000.
09:15:36.8966 [INFO] sysbus: Loading block of 528 bytes length at 0x8002270.
09:15:36.8967 [INFO] sysbus: Loading block of 1536 bytes length at 0x80022CC.
Starting emulation...
09:15:37.1415 [INFO] cpu: Setting initial values: PC = 0x8000501, SP = 0x20005000.
09:15:37.1433 [INFO] stm32f103_bluepill: Machine started.
09:15:37.1677 [WARNING] sysbus: [cpu: 0x8000552] ReadDoubleWord from an unimplemented register FLASH:ACR (0x40022000), returning a value from SVD: 0x30
09:15:37.1689 [WARNING] sysbus: [cpu: 0x800055A] WriteDoubleWord of value 0x30 to an unimplemented register FLASH:ACR (0x40022000) generated from SVD
09:15:37.1778 [WARNING] sysbus: [cpu: 0x800033C] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1779 [WARNING] sysbus: [cpu: 0x8000344] WriteDoubleWord of value 0x1 to an unimplementedregister RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1779 [WARNING] sysbus: [cpu: 0x8000348] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1779 [WARNING] sysbus: [cpu: 0x8000354] ReadDoubleWord from an unimplemented register RCC:APB1ENR (0x4002101C), returning a value from SVD: 0x0
09:15:37.1779 [WARNING] sysbus: [cpu: 0x800035C] WriteDoubleWord of value 0x10000000 to an unimplemented register RCC:APB1ENR (0x4002101C) generated from SVD
09:15:37.1780 [WARNING] sysbus: [cpu: 0x8000360] ReadDoubleWord from an unimplemented register RCC:APB1ENR (0x4002101C), returning a value from SVD: 0x0
09:15:37.1810 [WARNING] afio: Unhandled write to offset 0x4. Unhandled bits: [26] when writing value 0x4000000. Tags: SWJ_CFG (0x4).
09:15:37.1811 [WARNING] sysbus: [cpu: 0x8000CF4] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1813 [WARNING] sysbus: [cpu: 0x8000D18] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
09:15:37.1813 [WARNING] sysbus: [cpu: 0x8000D30] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
09:15:37.1814 [WARNING] sysbus: [cpu: 0x8000D40] WriteDoubleWord of value 0xA020083 to an unimplemented register RCC:CR (0x40021000) generated from SVD
09:15:37.1814 [WARNING] sysbus: [cpu: 0x80010D2] ReadDoubleWord from an unimplemented register FLASH:ACR (0x40022000), returning a value from SVD: 0x30
09:15:37.1815 [WARNING] sysbus: [cpu: 0x800111A] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1815 [WARNING] sysbus: [cpu: 0x8001122] WriteDoubleWord of value 0x700 to an unimplemented register RCC:CFGR (0x40021004) generated from SVD
09:15:37.1815 [WARNING] sysbus: [cpu: 0x8001132] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1815 [WARNING] sysbus: [cpu: 0x800113A] WriteDoubleWord of value 0x3800 to an unimplemented register RCC:CFGR (0x40021004) generated from SVD
09:15:37.1815 [WARNING] sysbus: [cpu: 0x800113E] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1815 [WARNING] sysbus: [cpu: 0x800114C] WriteDoubleWord of value 0x0 to an unimplementedregister RCC:CFGR (0x40021004) generated from SVD
09:15:37.1816 [WARNING] sysbus: [cpu: 0x800118C] (tag: 'RCC_CR') ReadDoubleWord from non existingperipheral at 0x40021000, returning 0x0A020083.
09:15:37.1816 [WARNING] sysbus: [cpu: 0x800119C] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1816 [WARNING] sysbus: [cpu: 0x80011AA] WriteDoubleWord of value 0x0 to an unimplementedregister RCC:CFGR (0x40021004) generated from SVD
09:15:37.1816 [WARNING] sysbus: [cpu: 0x80011CC] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1816 [WARNING] sysbus: [cpu: 0x80011DE] ReadDoubleWord from an unimplemented register FLASH:ACR (0x40022000), returning a value from SVD: 0x30
09:15:37.1816 [WARNING] sysbus: [cpu: 0x800121A] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1817 [WARNING] sysbus: [cpu: 0x8001228] WriteDoubleWord of value 0x400 to an unimplemented register RCC:CFGR (0x40021004) generated from SVD
09:15:37.1817 [WARNING] sysbus: [cpu: 0x8001238] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1817 [WARNING] sysbus: [cpu: 0x8001248] WriteDoubleWord of value 0x0 to an unimplementedregister RCC:CFGR (0x40021004) generated from SVD
09:15:37.1817 [WARNING] sysbus: [cpu: 0x80012AC] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1817 [WARNING] sysbus: [cpu: 0x8001252] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1819 [WARNING] sysbus: [cpu: 0x80002A6] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002AE] WriteDoubleWord of value 0x10 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002B2] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002BE] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002C6] WriteDoubleWord of value 0x20 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002CA] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002D6] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002DE] WriteDoubleWord of value 0x4 to an unimplementedregister RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1820 [WARNING] sysbus: [cpu: 0x80002E2] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1823 [WARNING] gpioPortC: Trying to set the state of the input pin #13
09:15:37.1843 [WARNING] sysbus: [cpu: 0x80003BA] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1843 [WARNING] sysbus: [cpu: 0x80003C2] WriteDoubleWord of value 0x4000 to an unimplemented register RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1843 [WARNING] sysbus: [cpu: 0x80003C6] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1843 [WARNING] sysbus: [cpu: 0x80003D2] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1844 [WARNING] sysbus: [cpu: 0x80003DA] WriteDoubleWord of value 0x4 to an unimplementedregister RCC:APB2ENR (0x40021018) generated from SVD
09:15:37.1844 [WARNING] sysbus: [cpu: 0x80003DE] ReadDoubleWord from an unimplemented register RCC:APB2ENR (0x40021018), returning a value from SVD: 0x0
09:15:37.1852 [WARNING] sysbus: [cpu: 0x8001380] ReadDoubleWord from an unimplemented register RCC:CFGR (0x40021004), returning a value from SVD: 0x0
09:15:37.1882 [INFO] usart1: [host: 52.01ms (+52.01ms)|virt: 14.34µs (+14.34µs)] Cubemx C loop executed. Pin PC13 state: 1
(stm32f103_bluepill) 09:15:38.1459 [INFO] usart1: [host:     1.01s (+0.96s)|virt:           1s (+1s)] Cubemx C loop executed. Pin PC13 state: 0
09:15:39.1461 [INFO] usart1: [host:        2.01s (+1s)|virt:           2s (+1s)] Cubemx C loop executed. Pin PC13 state: 1
09:15:40.1467 [INFO] usart1: [host:        3.01s (+1s)|virt:           3s (+1s)] Cubemx C loop executed. Pin PC13 state: 0
09:15:41.1475 [INFO] usart1: [host:        4.01s (+1s)|virt:           4s (+1s)] Cubemx C loop executed. Pin PC13 state: 1
09:15:42.1484 [INFO] usart1: [host:        5.01s (+1s)|virt:           5s (+1s)] Cubemx C loop executed. Pin PC13 state: 0
q
Renode is quitting
09:15:42.7764 [INFO] stm32f103_bluepill: Machine paused.
09:15:42.7980 [INFO] stm32f103_bluepill: Disposed.
root@343c02b5f414:/workspaces/demo_renode/sim/renode/stm32f103_bluepill# 