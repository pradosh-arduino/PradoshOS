#include "imgBitmap.h"
/*
 * Simmple bitmap library used in kernel
 *
 * */
static unsigned char our_memory[1024 * 1024]; //reserve 1 MB for malloc
static size_t next_index = 0;

 void* _BTmalloc(size_t sz)
{
    void *mem;

    if(sizeof our_memory - next_index < sz)
        return NULL;

    mem = &our_memory[next_index];
    next_index += sz;
    return mem;
}

bitmap_t * bitmap_create(char * filename) {
    bitmap_t* ret = (bitmap_t*)_BTmalloc(sizeof(bitmap_t));
    //qemu_printf("Opening %s\n", filename);
    char* file = read_file(filename);
    if(!file) {
        createBitmap();
    }
    uint32_t size = get_file_size(filename);
    char * buf = (char*)_BTmalloc(size);
    //qemu_printf("Reading content of %s\n", filename);


    // Parse the bitmap
    bmp_fileheader_t * h = (bmp_fileheader_t*)buf;
    unsigned int offset = h->bfOffBits;
    //qemu_printf("bitmap size: %u\n", h->bfSize);
    //qemu_printf("bitmap offset: %u\n", offset);

    bmp_infoheader_t * info = (bmp_infoheader_t*)buf + sizeof(bmp_fileheader_t);

    ret->width = info->biWidth;
    ret->height = info->biHeight;
    ret->image_bytes= buf + offset;
    ret->buf =(char*) buf;
    ret->total_size= size;
    ret->bpp = info->biBitCount;
    GlobalRenderer->Print("bitmap is x:");
    GlobalRenderer->Print(to_string((long int)ret->width));
    GlobalRenderer->Print(" y:");
    GlobalRenderer->Print(to_string((long int)ret->height));
    GlobalRenderer->Next();
    GlobalRenderer->Print("image is here");
    GlobalRenderer->Print(to_string((long int)ret->image_bytes));
    return ret;
}



void bitmap_display(bitmap_t * bmp) {
    if(!bmp) return;
    uint8_t * image = (uint8_t*)bmp->image_bytes;
    uint32_t * screen = (uint32_t*)0xfd000000;
    int j = 0;
    // Do copy
    for(int i = 0; i < bmp->height; i++) {
        // Copy the ith row of image to height - 1 - i row of screen, each row is of length width * 3
        char * image_row = (char*)image + i * bmp->width * 3;
        uint32_t * screen_row = (uint32_t*)screen + (bmp->height - 1 - i) * bmp->width * 4;
        j = 0;
        for(int k = 0; k < bmp->width; k++) {
            uint32_t b = image_row[j++] & 0xff;
            uint32_t g = image_row[j++] & 0xff;
            uint32_t r = image_row[j++] & 0xff;
            uint32_t rgb = ((r << 16) | (g << 8) | (b)) & 0x00ffffff;
            rgb = rgb | 0xff000000;
            screen_row[k] = rgb;
        }
    }
}

/*
 * Copy bitmap content to frame buffer
 * */
void bitmap_to_framebuffer(bitmap_t * bmp, uint32_t * frame_buffer) {
    if(!bmp) return;
    uint8_t * image = (uint8_t*)bmp->image_bytes;
    int j = 0;
    // Do copy
    for(int i = 0; i < bmp->height; i++) {
        // Copy the ith row of image to height - 1 - i row of frame buffer, each row is of length width * 3
        char * image_row = (char*)image + i * bmp->width * 3;
        //uint32_t * framebuffer_row = (void*)frame_buffer + (bmp->height - 1 - i) * bmp->width * 4;
        uint32_t * framebuffer_row = (uint32_t*)frame_buffer + (bmp->height - 1 - i) * bmp->width * 4;
        j = 0;
        for(int k = 0; k < bmp->width; k++) {
            uint32_t b = image_row[j++] & 0xff;
            uint32_t g = image_row[j++] & 0xff;
            uint32_t r = image_row[j++] & 0xff;
            uint32_t rgb = ((r << 16) | (g << 8) | (b)) & 0x00ffffff;
            rgb = rgb | 0xff000000;
            framebuffer_row[k] = rgb;
        }
    }
}
void bitmap_to_framebuffer2(bitmap_t * bmp, uint32_t * frame_buffer) {
    if(!bmp) return;
    uint8_t * image = (uint8_t*)bmp->image_bytes;
    int j = 0;
    // Do copy
    for(int i = 0; i < bmp->height; i++) {
        // Copy the ith row of image to height - 1 - i row of frame buffer, each row is of length width * 3
        char * image_row = (char*)image + i * bmp->width * 4;
        //uint32_t * framebuffer_row = (void*)frame_buffer + (bmp->height - 1 - i) * bmp->width * 4;
        uint32_t * framebuffer_row = frame_buffer + (bmp->height - 1 - i) * bmp->width * 4;
        j = 0;
        for(int k = 0; k < bmp->width; k++) {
            uint32_t b = image_row[j++] & 0xff;
            uint32_t g = image_row[j++] & 0xff;
            uint32_t r = image_row[j++] & 0xff;
            uint32_t a = image_row[j++] & 0xff;
            uint32_t rgba = ((a << 24) | (r << 16) | (g << 8) | (b));
            framebuffer_row[k] = rgba;
        }
    }
}

void createBitmap(){
    
}