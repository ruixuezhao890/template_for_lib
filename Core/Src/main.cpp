
#include <cstdio>
#include "main.h"
#include "Lib/BSP_lib/Rcc/Rcc.hpp"
#include "Lib/BSP_lib/SysTick/SysTick.hpp"
#include "Lib/BSP_lib/Gpio/Gpio.hpp"
#include "Lib/BSP_lib/Serial/Serial.hpp"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

int main()
{
    Rcc::clock_setup<RCC_OSCILLATORTYPE_HSE>(Rcc::default_clock_config);

    SysSetTick::sys_tick_setup(Rcc::clocks_.system_clock_frequency/1000);

    PF<>::clock(true);
    using LED1=PF<9>;
    using LED2=PF<10>;
    ConfigPPOut<LED1>();

    LED2 ::into_output().push_pull().verify();

    using KEY=PE<2>;
    KEY ::clock_enable();
    KEY ::into_input().pull_up().verify();
//    KEY ::enable_interrupt_from_exti_rising();
//    KEY ::exti_add_callback_function([](){
//        LED1 ::toggle();
//    });


//    using KEY1=PE<3>;
//    KEY1 ::clock_enable();
//    ConfigFloatInput<KEY1>();
//    KEY1 ::enable_interrupt_from_exti_rising();
//    KEY1 ::exti_add_callback_function([](){
//        LED2::toggle();
//    });
    using KEY2 =PA<0>;
    KEY2::clock_enable();
    KEY2 ::into_input().pull_down().verify();
    KEY2 ::enable_interrupt_from_exti_rising();
    KEY2 ::exti_add_callback_function([](){
        LED2 ::toggle();
    });

    serial1.clock(true);
//    serial1.pin_init<PIN_PORT_TX_1,PIN_TX_1,PIN_PORT_RX_1,PIN_RX_1>();
    serial1.pin_init_default();
    serial1.default_config(115200);
    serial1.enable();
    serial1.transmit("hello world\n",13);



    while (true)
    {
        if (KEY::is_high()){
            LED1 ::toggle();
        }else{
            LED2 ::toggle();
        }

//        LED1::toggle();
        SysSetTick::delay(1000);

    }

}
#pragma clang diagnostic pop

