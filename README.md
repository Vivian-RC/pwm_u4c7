# **Controle de Servo Motor e LED RGB - Raspberry Pi Pico**

## 📌 **Descrição do Projeto**
Este projeto implementa o controle de um **servo motor** e a **intensidade de um LED RGB** utilizando **PWM (Modulação por Largura de Pulso)** no **Raspberry Pi Pico**. 

✔️ O **servo motor** se movimenta suavemente entre **0° e 180°**.
✔️ A **intensidade do LED** é ajustada proporcionalmente à posição do servo.
✔️ O LED **desliga quando o servo está em 0°**.
✔️ Os valores de PWM são exibidos no **Serial Monitor** para depuração.

---
## 📂 **Repositório no GitHub**
O código-fonte deste projeto está disponível no GitHub:
🔗 [PWM_U4C7 - Repositório GitHub](https://github.com/Vivian-RC/pwm_u4c7.git)

---
## 🔧 **Hardware Necessário**
- Raspberry Pi Pico
- Servo Motor (ex: SG90)
- LED RGB
- Resistor de 330Ω
- Fonte de alimentação 5V
- Cabos jumper

**📌 Ligações:**
| Componente  | Pino no Pico |
|------------|--------------|
| Servo (Sinal)  | **GPIO 22** |
| LED RGB (Anodo) | **GPIO 12** |
| GND        | **GND** |
| VCC (5V)   | **VSYS** |

---
## 🚀 **Compilação e Execução**
### **1️⃣ Configurar o Ambiente**
Certifique-se de que você tem o **SDK do Raspberry Pi Pico** configurado. Se ainda não configurou:
```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
```

### **2️⃣ Compilar o Código**
Abra o terminal e execute:
```sh
mkdir build && cd build
cmake ..
make
```

### **3️⃣ Enviar para o Raspberry Pi Pico**
1. Conecte o Raspberry Pi Pico segurando o botão **BOOTSEL**.
2. Monte o dispositivo USB no seu PC e copie o arquivo `.uf2` gerado.
3. O código será executado automaticamente.

---
## 📟 **Monitoramento via Serial**
Para visualizar os dados no **Serial Monitor**, conecte-se à UART com:
```sh
minicom -b 115200 -o -D /dev/ttyUSB0
```
Ou no Windows, use **Putty** e configure a porta COM correta.

Você verá mensagens como:
```
Movendo para 180 graus
PWM Servo: 2400 µs, LED Intensity: 100%
Movendo para 90 graus
PWM Servo: 1470 µs, LED Intensity: 50%
Movendo para 0 graus
PWM Servo: 500 µs, LED Intensity: 0%
```

---
## 🎥 **Demonstração em Vídeo**
Para uma melhor compreensão do funcionamento do projeto, assista ao vídeo demonstrativo:
🔗 [Link para o vídeo](#) *(Substituir pelo link do vídeo após o upload)*

---
## 📌 **Funcionamento do Código**
1. O código configura **PWM** para controlar o servo motor e o LED.
2. O **servo se movimenta** entre 0° e 180°.
3. O **LED aumenta de brilho conforme o servo se move**.
4. **O LED desliga quando o servo está em 0°**.
5. Os valores são exibidos no **Serial Monitor**.

📌 **Loop contínuo:** O processo se repete indefinidamente.

