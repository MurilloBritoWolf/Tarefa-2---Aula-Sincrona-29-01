# Projeto de Temporizadores com Raspberry Pi Pico W

Este repositório contém dois projetos simulados na plataforma Wokwi utilizando o Raspberry Pi Pico W e o Pico SDK. São duas atividades que demonstram o uso de temporizadores:

- **Atividade 1:** Semáforo com temporização repetitiva, usando a função `add_repeating_timer_ms()`.
- **Atividade 2:** Temporizador One-Shot acionado por botão, usando a função `add_alarm_in_ms()`.

---

## Eletrônicos Utilizados

### Componentes Comuns (Atividades 1 e 2)
- **Raspberry Pi Pico W:** Microcontrolador utilizado para executar o código em C.
- **Resistores de 330 Ω:** Utilizados para limitar a corrente dos LEDs.
- **Fios de conexão:**
  - **Fio Verde:** Representa os fios negativos.
  - **Fio Preto:** Representa os fios positivos.

### Atividade 1: Semáforo
- **LEDs:** 03 LEDs (vermelho, amarelo e verde) conectados aos GPIOs 11, 12 e 13.  
  *Utiliza o LED RGB do BitDogLab.*

### Atividade 2: Temporizador One-Shot
- **LEDs:** 03 LEDs (azul, vermelho e verde) conectados aos GPIOs 11, 12 e 13.  
  *Utiliza o LED RGB do BitDogLab.*
- **Botão (Pushbutton):** Conectado ao GPIO 5 (Botão A), utilizado para iniciar a sequência.

---

## Descrição das Atividades

### Atividade 1: Semáforo com Temporização Repetitiva

**Objetivo:**  
Implementar um semáforo que inicia com o LED vermelho aceso e, a cada 3 segundos, alterna os sinais na seguinte ordem: vermelho → amarelo → verde → vermelho.

**Funcionamento:**  
- A função `add_repeating_timer_ms()` é utilizada para agendar uma rotina de callback a cada 3000 ms.
- Na rotina de callback, o estado do semáforo é atualizado e o LED correspondente é ligado, enquanto os outros são desligados.
- No loop principal, uma mensagem é impressa na porta serial a cada 1 segundo informando o estado atual do semáforo.

**Link Virtual Wokwi:**  
[Link Atividade 1](https://wokwi.com/projects/421898605193840641)

---

### Atividade 2: Temporizador One-Shot com Botão

**Objetivo:**  
Criar um sistema de temporização que aciona uma sequência de desligamento dos LEDs a partir do clique em um botão.

**Funcionamento:**  
- Ao pressionar o botão (com debounce implementado), os três LEDs são ligados.
- Utiliza a função `add_alarm_in_ms()` para agendar callbacks que, a cada 3000 ms, desligam sequencialmente:
  - Primeiro, o LED azul é desligado (mantendo os LEDs vermelho e verde ligados).
  - Em seguida, o LED vermelho é desligado (mantendo apenas o LED verde ligado).
  - Por fim, o LED verde é desligado, finalizando a sequência.
- Durante a execução da sequência, novas pressões do botão são ignoradas até que a sequência esteja completa.

**Link Virtual Wokwi:**  
[Link Atividade 2](https://wokwi.com/projects/421900373561846785)

---

## Instruções de Uso

1. **Pré-requisitos:**
   - Instale e configure o [Pico SDK](https://github.com/raspberrypi/pico-sdk).
   - Acesse a plataforma [Wokwi](https://wokwi.com/) para simulação.

2. **Carregamento do Código:**
   - Selecione a atividade desejada e copie o código correspondente para o projeto na plataforma Wokwi.
   - Conecte os componentes de acordo com as especificações:
     - **LEDs:** Conectados aos GPIOs 11, 12 e 13, utilizando resistores de 330 Ω.
     - **Botão (para Atividade 2):** Conectado ao GPIO 5.
     - **Fiação:** Utilize fio verde para os negativos e fio preto para os positivos.

3. **Execução:**
   - Compile e inicie a simulação.
   - **Para a Atividade 1:** Observe a sequência do semáforo e as mensagens exibidas na porta serial.
   - **Para a Atividade 2:** Pressione o botão para iniciar a sequência de acionamento dos LEDs e acompanhe a execução pela porta serial.

---

## Considerações Finais

Estes projetos demonstram como utilizar temporizadores e alarmes no Pico SDK para controlar dispositivos externos. As atividades abordam desde a implementação de um semáforo com temporização repetitiva até o acionamento sequencial de LEDs por meio de um temporizador one-shot, reforçando conceitos importantes de temporização e debounce de botões.

---

*Desenvolvido por João murillo brito taveira -  grupo 4 - subgrupo 6.*
