root@343c02b5f414:/workspaces/demo_renode/sim/stm32f103_bluepill# renode blue_pill.resc 

(renode:3328): Gtk-WARNING **: 20:51:03.742: Locale not supported by C library.
        Using the fallback 'C' locale.

(renode:3328): Gdk-CRITICAL **: 20:51:03.749: gdk_keymap_get_for_display: assertion 'GDK_IS_DISPLAY (display)' failed
20:51:03.7544 [WARNING] Couldn't start UI - falling back to console mode
20:51:04.0548 [INFO] Loaded monitor commands from: /opt/renode/scripts/monitor.py
Renode, version 1.16.1 (d66b0c2a-202602160933)

(monitor) i $CWD/blue_pill.resc
20:51:04.1457 [INFO] Including script(s): /workspaces/demo_renode/sim/stm32f103_bluepill/blue_pill.resc
20:51:04.1581 [INFO] System bus created.
20:51:04.4961 [WARNING] Translation cache size 536870912 is larger than maximum allowed 134217728. It will be clamped to maximum
20:51:04.7639 [INFO] sysbus: Loaded SVD: /tmp/renode-3328/48df15b3-71e8-4810-bae0-002dd25b6f46.tmp. Name: STM32F103. Description: STM32F103.
20:51:04.7932 [INFO] sysbus: Loading block of 13108 bytes length at 0x8000000.
20:51:04.8020 [INFO] sysbus: Loading block of 1132 bytes length at 0x8003334.
20:51:04.8021 [INFO] sysbus: Loading block of 1540 bytes length at 0x2000046C.
20:51:05.0993 [INFO] stm32f103_bluepill: CPUs: ["stm32f103_bluepill.cpu"] were added to a new GDB server created on port :3333
20:51:05.0994 [INFO] stm32f103_bluepill: GDB server with all CPUs started on port :3333
Starting emulation...
20:51:05.1058 [INFO] stm32f103_bluepill: Machine started.
(stm32f103_bluepill) 