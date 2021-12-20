
limine-update:
	git -C Limine clone https://github.com/limine-bootloader/limine.git --branch=latest-binary --depth=1 limine
	rm -rf Limine/limine/.git
	rm Limine/limine/.gitignore
	mcopy Limine/limine/BOOTX64.EFI Limine/bootmgr/bootmgr.efi
