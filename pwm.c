#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22   // GPIO do servo motor
#define LED_RGB_PIN 12 // GPIO do LED azul
#define PWM_FREQ 50    // Frequência do PWM para o servo (50Hz)
#define STEP_DELAY 10  // Tempo de atraso para movimento suave (10ms)

// Função para converter tempo de pulso (em microssegundos) para duty cycle do PWM
uint16_t micros_to_pwm(uint16_t micros, uint16_t wrap) {
    return (wrap * micros) / 20000; // 20000µs = 20ms (período do PWM)
}

// Função que move o servo e ajusta a intensidade do LED azul
void move_servo_and_led(uint16_t pulse_width, uint16_t wrap) {
    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    uint slice_led = pwm_gpio_to_slice_num(LED_RGB_PIN);

    uint16_t pwm_value = micros_to_pwm(pulse_width, wrap);
    pwm_set_chan_level(slice_servo, pwm_gpio_to_channel(SERVO_PIN), pwm_value);
    
    // Se o servo estiver em 0°, desligar o LED azul completamente
    if (pulse_width <= 500) {
        pwm_set_chan_level(slice_led, pwm_gpio_to_channel(LED_RGB_PIN), 0);
    } else {
        pwm_set_chan_level(slice_led, pwm_gpio_to_channel(LED_RGB_PIN), pwm_value);
    }
    
    // Exibe no Serial Monitor os valores do PWM do servo e LED
    printf("PWM Servo: %d, PWM LED: %d\n", pwm_value, pulse_width <= 500 ? 0 : pwm_value);
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Pequeno atraso para estabilização do sistema

    // Configuração dos GPIOs como PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_RGB_PIN, GPIO_FUNC_PWM);

    // Obtendo os slices de PWM correspondentes
    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    uint slice_led = pwm_gpio_to_slice_num(LED_RGB_PIN);
    
    float clkdiv = 64.0f; // Divisor de clock para configurar a frequência
    uint16_t wrap = 25000; // Definição do período do PWM

    // Configuração do PWM para o servo
    pwm_set_clkdiv(slice_servo, clkdiv);
    pwm_set_wrap(slice_servo, wrap);
    pwm_set_enabled(slice_servo, true);

    // Configuração do PWM para o LED
    pwm_set_clkdiv(slice_led, clkdiv);
    pwm_set_wrap(slice_led, wrap);
    pwm_set_enabled(slice_led, true);

    // Definição dos tempos de pulso para os ângulos do servo
    uint16_t pulse_180 = 2400; // 2.400µs (180°)
    uint16_t pulse_90  = 1470; // 1.470µs (90°)
    uint16_t pulse_0   = 500;  // 500µs (0°)

    // Movimentação do servo para ângulos fixos
    move_servo_and_led(pulse_180, wrap);
    sleep_ms(5000);
    move_servo_and_led(pulse_90, wrap);
    sleep_ms(5000);
    move_servo_and_led(pulse_0, wrap);

    while (true) {
        sleep_ms(1000);
        // Movimento suave do servo de 0° a 180°
        for (uint16_t pulse = pulse_0; pulse <= pulse_180; pulse += 5) {
            move_servo_and_led(pulse, wrap);
            sleep_ms(STEP_DELAY);
        }
        sleep_ms(1000);
        // Movimento suave do servo de 180° a 0°
        for (uint16_t pulse = pulse_180; pulse >= pulse_0; pulse -= 5) {
            move_servo_and_led(pulse, wrap);
            sleep_ms(STEP_DELAY);
        }
    }
}

