#include<stdio.h>
#include<stdlib.h>
#include<SDL3/SDL.h>
int main(){
    if(!SDL_Init(SDL_INIT_VIDEO)){ // Inicia processos, nesse caso, inicia apenas o processo de video, porque o video é usado para a criação de janelas
        printf("fodeu geral galera\n");
    }
    SDL_Window* window = SDL_CreateWindow("sla mano", 440, 640, SDL_WINDOW_RESIZABLE); 
    SDL_Renderer* render = SDL_CreateRenderer(window, NULL);
    SDL_Event evento;
    SDL_SetRenderDrawColor(render, 0, 70, 70, 255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
        while(1){
            while(SDL_PollEvent(&evento)){
                if(evento.type == SDL_EVENT_QUIT){
                    SDL_DestroyRenderer(render);
                    SDL_DestroyWindow(window); 
                    SDL_Quit();// já que esse cu é tipo ponteiro
                        return 0;
                 }
           
        }
         const double now = ((double)SDL_GetTicks()) / 1000.0;
    const float red   = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue  = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
            
            SDL_SetRenderDrawColorFloat(render, red, green, blue, 255);
            SDL_RenderClear(render);
            SDL_RenderPresent(render);

    }
    return 0;
}
