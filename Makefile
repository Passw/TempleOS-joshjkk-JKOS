ASM = nasm
ASM_FLAGS = -f bin
BUILD_DIR = build
SRC_DIR = src

boot:
	mkdir -p $(BUILD_DIR)
	$(ASM) $(ASM_FLAGS) $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.bin
