CC      = x86_64-w64-mingw32-gcc
CFLAGS  = -std=c99 -Wall -Wextra -Os -s -ffreestanding
LDFLAGS = -nostdlib -mwindows
LDLIBS  = -lkernel32 -luser32

vulkan_test.exe : vulkan_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean :
	$(RM) vulkan_test.exe
