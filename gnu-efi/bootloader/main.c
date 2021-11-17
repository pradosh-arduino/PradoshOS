#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
} Framebuffer;

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

typedef struct {
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
} PSF1_HEADER;

typedef struct {
	PSF1_HEADER* psf1_Header;
	void* glyphBuffer;
} PSF1_FONT;
/*
typedef struct{
	bool FS0;
	bool FS1;
	bool FS2;
	bool FS3;
	bool FS4;
	bool FS5;
	bool FS6;
	bool FS7;

	bool BLK0;
} FILE_READING;*/

Framebuffer framebuffer;
EFI_STATUS status;
//FILE_READING fs;
Framebuffer* InitializeGOP(){
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop);
	if(EFI_ERROR(status)){
		Print(L"Unable to locate GOP\n\r");
		return NULL;
	}
	else
	{
		Print(L"GOP located\n\r");
	}

	framebuffer.BaseAddress = (void*)gop->Mode->FrameBufferBase;
	framebuffer.BufferSize = gop->Mode->FrameBufferSize;
	framebuffer.Width = gop->Mode->Info->HorizontalResolution;
	framebuffer.Height = gop->Mode->Info->VerticalResolution;
	framebuffer.PixelsPerScanLine = gop->Mode->Info->PixelsPerScanLine;

	return &framebuffer;
	
}

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){
	EFI_FILE* LoadedFile;

	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Directory == NULL){
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (s != EFI_SUCCESS){
		return NULL;
	}
	return LoadedFile;

}

PSF1_FONT* LoadPSF1Font(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
	EFI_FILE* font = LoadFile(Directory, Path, ImageHandle, SystemTable);
	if (font == NULL) return NULL;

	PSF1_HEADER* fontHeader;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_HEADER), (void**)&fontHeader);
	UINTN size = sizeof(PSF1_HEADER);
	font->Read(font, &size, fontHeader);

	if (fontHeader->magic[0] != PSF1_MAGIC0 || fontHeader->magic[1] != PSF1_MAGIC1){
		return NULL;
	}

	UINTN glyphBufferSize = fontHeader->charsize * 256;
	if (fontHeader->mode == 1) { //512 glyph mode
		glyphBufferSize = fontHeader->charsize * 512;
	}

	void* glyphBuffer;
	{
		font->SetPosition(font, sizeof(PSF1_HEADER));
		SystemTable->BootServices->AllocatePool(EfiLoaderData, glyphBufferSize, (void**)&glyphBuffer);
		font->Read(font, &glyphBufferSize, glyphBuffer);
	}

	PSF1_FONT* finishedFont;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_FONT), (void**)&finishedFont);
	finishedFont->psf1_Header = fontHeader;
	finishedFont->glyphBuffer = glyphBuffer;
	return finishedFont;

}

int memcmp(const void* aptr, const void* bptr, size_t n){
	const unsigned char* a = aptr, *b = bptr;
	for (size_t i = 0; i < n; i++){
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}

typedef struct {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	UINTN mMapSize;
	UINTN mMapDescSize;
	void* rsdp;
} BootInfo;

UINTN strcmp(CHAR8* a, CHAR8* b, UINTN length){
	for(UINTN i = 0; i < length; i++){
		if(*a != *b) return 0;
	}
	return 1;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"Booting to PradoshOS... \n\r");
	EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable);
	if (Kernel == NULL){
		Print(L"Could not load kernel \n\r");
	}
	else{
		Print(L"Kernel loaded: \n\r");
		Print(L"Kernel Loaded Successfully \n\r");
	}
	//verify drives
	/*
	EFI_FILE* fs->fileSys1 = LoadFile(NULL, L"FS1:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fs->fileSys2 = LoadFile(NULL, L"FS2:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fs->fileSys3 = LoadFile(NULL, L"FS3:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fileSys4 = LoadFile(NULL, L"FS4:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fileSys5 = LoadFile(NULL, L"FS5:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fileSys6 = LoadFile(NULL, L"FS6:\\drive.config", ImageHandle, SystemTable);
	EFI_FILE* fileSys7 = LoadFile(NULL, L"FS7:\\drive.config", ImageHandle, SystemTable);
	
	if(fileSys1 == NULL){
		FS1 = false;
	}else{
		FS1 = true;
	}

	if(fileSys2 == NULL){
		FS2 = false;
	}else{
		FS2 = true;
	}

	if(fileSys3 == NULL){
		FS3 = false;
	}else{
		FS3 = true;
	}

	if(fileSys4 == NULL){
		FS4 = false;
	}else{
		FS4 = true;
	}

	if(fileSys5 == NULL){
		FS5 = false;
	}else{
		FS5 = true;
	}

	if(fileSys6 == NULL){
		FS6 = false;
	}else{
		FS6 = true;
	}

	if(fileSys7 == NULL){
		FS7 = false;
	}else{
		FS7 = true;
	}*/
	
	Print(L"handleprotocol: \n\r");
	uefi_call_wrapper(SystemTable->ConOut->SetAttribute, 1, SystemTable->ConOut, EFI_GREEN);
	Print(L"%r", status);
	uefi_call_wrapper(SystemTable->ConOut->SetAttribute, 1, SystemTable->ConOut, EFI_LIGHTGRAY);
	Print(L"\n");
	Elf64_Ehdr header;
	{
		UINTN FileInfoSize;
		EFI_FILE_INFO* FileInfo;
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header);
		Kernel->Read(Kernel, &size, &header);
	}

	if (
		memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
		header.e_ident[EI_CLASS] != ELFCLASS64 ||
		header.e_ident[EI_DATA] != ELFDATA2LSB ||
		header.e_type != ET_EXEC ||
		header.e_machine != EM_X86_64 ||
		header.e_version != EV_CURRENT
	)
	{
		Print(L"kernel format is unreadable\r\n");
	}
	else
	{
		Print(L"kernel header successfully verified\r\n");
	}

	Elf64_Phdr* phdrs;
	{
		Kernel->SetPosition(Kernel, header.e_phoff);
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
		Kernel->Read(Kernel, &size, phdrs);
	}

	for (
		Elf64_Phdr* phdr = phdrs;
		(char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize;
		phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)
	)
	{
		switch (phdr->p_type){
			case PT_LOAD:
			{
				int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
				Elf64_Addr segment = phdr->p_paddr;
				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				Kernel->SetPosition(Kernel, phdr->p_offset);
				UINTN size = phdr->p_filesz;
				Kernel->Read(Kernel, &size, (void*)segment);
				break;
			}
		}
	}

	Print(L"Kernel Loaded\n\r");
	

	PSF1_FONT* newFont = LoadPSF1Font(NULL, L"zap-light16.psf", ImageHandle, SystemTable);
	if (newFont == NULL){
		Print(L"Font is not valid or is not found\n\r");
	}
	else
	{
		Print(L"Font found. char size = %d\n\r", newFont->psf1_Header->charsize);
	}
	

	Framebuffer* newBuffer = InitializeGOP();

	Print(L"Base: 0x%x\n\rSize: 0x%x\n\rWidth: %d\n\rHeight: %d\n\rPixelsPerScanline: %d\n\r", 
	newBuffer->BaseAddress, 
	newBuffer->BufferSize, 
	newBuffer->Width, 
	newBuffer->Height, 
	newBuffer->PixelsPerScanLine);

	EFI_MEMORY_DESCRIPTOR* Map = NULL;
	UINTN MapSize, MapKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;
	{
		
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, MapSize, (void**)&Map);
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);

	}

	EFI_CONFIGURATION_TABLE* configTable = SystemTable->ConfigurationTable;
	void* rsdp = NULL;
    EFI_GUID Acpi2TableGuid = ACPI_20_TABLE_GUID;

	for(UINTN index = 0; index < SystemTable->NumberOfTableEntries; index++){
		if(CompareGuid(&configTable[index].VendorGuid, &Acpi2TableGuid)){
             if(strcmp((CHAR8*)"RSD PTR ", (CHAR8*)configTable->VendorTable, 8)){
				 rsdp = (void*)configTable->VendorTable;
				// break; it causes general protction fault
			 }
		}
		configTable++;
	}
	void (*KernelStart)(BootInfo*) = ((__attribute__((sysv_abi)) void (*)(BootInfo*) ) header.e_entry);

	BootInfo bootInfo;
	bootInfo.framebuffer = newBuffer;
	bootInfo.psf1_Font = newFont;
	bootInfo.mMap = Map;
	bootInfo.mMapSize = MapSize;
	bootInfo.mMapDescSize = DescriptorSize;
    bootInfo.rsdp = rsdp;
	SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);

	KernelStart(&bootInfo);
	
	return EFI_SUCCESS; // Exit the UEFI application
}
EFI_SYSTEM_TABLE *SystemTable;
void COLD_REBOOT()
{
    // Hardware Reboot
    SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, 0);
}

void WARM_REBOOT()
{
    // Software reboot
    SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, 0);
}

void SHUTDOWN()
{
    // Shuts off the computer
    // NOTE : This does not work in VirtualBox.
    // WORKS in QEMU !!!
    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
}
