SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\Common Files\Ulead Systems\MPEG;C:\Program Files\Git\cmd;C:\Program Files\PuTTY\;C:\Program Files (x86)\GnuWin32\bin\make.exe
SET CPU_TYPE=LPC2114
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\startup.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\time.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\retarget.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\irq.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\timer.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\global.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\fsm_master.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\led.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\botao.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\alarm.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\spo2.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\zigbee.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\vic.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\interrupt.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\output\9.lnp"
C:\Keil\ARM\ARMCC\bin\fromelf.exe ".\output\9.2" --i32combined --output ".\output\9.hex"
