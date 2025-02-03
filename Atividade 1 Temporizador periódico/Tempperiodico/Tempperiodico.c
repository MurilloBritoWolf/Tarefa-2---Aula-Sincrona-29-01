// bibbliotecas necessárias
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>

// Define os pinos dos LEDs (utilizando o LED RGB do BitDogLab: GPIO 11, 12 e 13)
#define LED_VERMELHO_PIN 11
#define LED_AMARELO_PIN  12
#define LED_VERDE_PIN    13

// Define os estados do semáforo
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} TrafficLightState;

volatile TrafficLightState estado_atual = VERMELHO;  // Estado inicial: Vermelho

// Função de call-back do timer (executada a cada 3000 ms)
bool repeating_timer_callback(struct repeating_timer *t) {
    // Atualiza o estado do semáforo e acende o LED correspondente
    switch (estado_atual) {
        case VERMELHO:
            // Apaga o LED vermelho e acende o LED amarelo
            gpio_put(LED_VERMELHO_PIN, 0);
            gpio_put(LED_AMARELO_PIN, 1);
            gpio_put(LED_VERDE_PIN, 0);
            estado_atual = AMARELO;
            break;
        case AMARELO:
            // Apaga o LED amarelo e acende o LED verde
            gpio_put(LED_VERMELHO_PIN, 0);
            gpio_put(LED_AMARELO_PIN, 0);
            gpio_put(LED_VERDE_PIN, 1);
            estado_atual = VERDE;
            break;
        case VERDE:
            // Apaga o LED verde e acende o LED vermelho
            gpio_put(LED_VERMELHO_PIN, 1);
            gpio_put(LED_AMARELO_PIN, 0);
            gpio_put(LED_VERDE_PIN, 0);
            estado_atual = VERMELHO;
            break;
        default:
            break;
    }
    return true; // Retorna true para manter o timer ativo
}

int main() {
    // Inicializa a comunicação serial e espera a conexão (opcional)
    stdio_init_all();
    sleep_ms(1000);  // Aguarda 1 segundo para garantir a inicialização da UART

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(LED_AMARELO_PIN);
    gpio_set_dir(LED_AMARELO_PIN, GPIO_OUT);
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);

    // Configura o estado inicial: LED vermelho aceso
    estado_atual = VERMELHO;
    gpio_put(LED_VERMELHO_PIN, 1);
    gpio_put(LED_AMARELO_PIN, 0);
    gpio_put(LED_VERDE_PIN, 0);

    // Cria e configura o timer para 3000 ms (3 segundos)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal: imprime uma mensagem a cada 1 segundo
    while (true) {
        // Imprime o estado atual do semáforo na porta serial
        switch (estado_atual) {
            case VERMELHO:
                printf("Semaforo: VERMELHO\n");
                break;
            case AMARELO:
                printf("Semaforo: AMARELO\n");
                break;
            case VERDE:
                printf("Semaforo: VERDE\n");
                break;
            default:
                break;
        }
        sleep_ms(1000);  // Atraso de 1 segundo
    }
    
    return 0;
}
