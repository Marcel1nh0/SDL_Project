#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
bool done = false;
void SDLCALL on_file_selected(void* userdata, const char* const* filelist, int filter) {
    char* path = (char*)userdata;
    if (filelist && filelist[0]) {
        strncpy(path, filelist[0], 1023);
    }
    done = true;
}
int main(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        printf("Error in initializing\nClosing program");
        SDL_Quit();
        return 0;
    
    }
    SDL_DialogFileFilter filters[]={
        {"images", "png;jpeg;jpg"},
        {"all archives","*"}
        
    };
    char path[1024] = "";
    SDL_Window* window = SDL_CreateWindow("image", 960, 1080, SDL_WINDOW_RESIZABLE);
    if(!window){
        printf("failed to initialize window");
        return 0;
    }
    SDL_Renderer* render = SDL_CreateRenderer(window, NULL);
    if(!render){
        printf("failed to initialize renderer");
        return 0;
    }
    SDL_Event event;
    SDL_ShowOpenFileDialog(on_file_selected, path, window, filters, 2, NULL, false);
    while(!done){
        SDL_PollEvent(&event);
    }
    if (path[0] == '\0') {
        puts("No path found");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_DestroySurface(surface);
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_Delay(16);
        SDL_RenderClear(render);
        SDL_RenderTexture(render, texture, NULL, NULL);
        SDL_RenderPresent(render);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;

}
