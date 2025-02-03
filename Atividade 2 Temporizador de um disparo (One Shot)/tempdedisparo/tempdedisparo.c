#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>

// Define os pinos: LED RGB (azul, vermelho e verde) e botão
#define LED_AZUL_PIN   11
#define LED_VERMELHO_PIN 12
#define LED_VERDE_PIN  13
#define BOTAO_PIN      5

// Variáveis globais para controlar a sequência
volatile bool sequencia_ativa = false;
volatile int etapa = 0;  // 0: inativa; 1: após início; 2: depois do 1º alarme; 3: depois do 2º alarme

/**
 * Função de callback do alarme one-shot.
 * A cada chamada, desliga um LED conforme a etapa da sequência e agenda o próximo alarme, se necessário.
 */
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    if (etapa == 1) {
        // Desliga o LED azul: ficam ligados vermelho e verde
        gpio_put(LED_AZUL_PIN, 0);
        etapa = 2;
        // Agenda o próximo alarme para 3000ms
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (etapa == 2) {
        // Desliga o LED vermelho: fica apenas o LED verde ligado
        gpio_put(LED_VERMELHO_PIN, 0);
        etapa = 3;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (etapa == 3) {
        // Desliga o LED verde: sequência finalizada
        gpio_put(LED_VERDE_PIN, 0);
        sequencia_ativa = false;
        etapa = 0;
        printf("Sequencia finalizada\n");
    }
    return 0;  // Retorna 0 para indicar que este alarme one-shot não se repete automaticamente
}

int main() {
    stdio_init_all();
    sleep_ms(1000);  // Aguarda a inicialização do sistema

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);

    // Inicializa o pino do botão como entrada com resistor pull-up (assumindo botão ativo em nível baixo)
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    // Garante que os LEDs iniciem apagados
    gpio_put(LED_AZUL_PIN, 0);
    gpio_put(LED_VERMELHO_PIN, 0);
    gpio_put(LED_VERDE_PIN, 0);

    printf("Aguardando pressionar o botao...\n");

    while (true) {
        // Se não houver sequência ativa e o botão for pressionado (nível 0)
        if (!sequencia_ativa && gpio_get(BOTAO_PIN) == 0) {
            // Debounce simples: espera 50ms e verifica novamente
            sleep_ms(50);
            if (gpio_get(BOTAO_PIN) == 0) {
                // Inicia a sequência
                sequencia_ativa = true;
                etapa = 1;

                // Liga os três LEDs (nível alto)
                gpio_put(LED_AZUL_PIN, 1);
                gpio_put(LED_VERMELHO_PIN, 1);
                gpio_put(LED_VERDE_PIN, 1);
                printf("Sequencia iniciada\n");

                // Agenda o primeiro alarme one-shot para 3000ms
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);

                // Aguarda até que o botão seja solto para evitar reentrada imediata
                while (gpio_get(BOTAO_PIN) == 0) {
                    sleep_ms(10);
                }
            }
        }
        sleep_ms(10);
    }
    
    return 0;
}
